#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

const vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

const vector<Vertex>& Model::GetVertices()
{
	return _transformedVertices;
}

size_t Model::GetPolygonCount() const
{
	return size_t(_polygons.size());
}

size_t Model::GetVertexCount() const
{
	return size_t(_vertices.size());
}

void Model::AddVertex(float x, float y, float z)
{
	_vertices.push_back(Vertex(x, y, z)); // Adds a vertex to the back of the _vertices list
	_transformedVertices.push_back(Vertex(x, y, z)); // Adds the same vertex to maintain the same sizing between each of the lists and same default values
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.push_back(Polygon3D(i0, i1, i2)); // Adds a Polygon3D to the back of the _polygons list
}


void Model::ApplyTransformToLocalVertices(const Matrix& transform)
{
	for (int i = 0; i < _transformedVertices.size(); i++)
	{
		_transformedVertices[i] = transform * _vertices[i]; //loops through each vertex in the _transformedVertices list and multiplies the original vertices list by the transformation matrix
	}
}

void Model::ApplyTransformToTransformedVertices(const Matrix& transform)
{
	for (int i = 0; i < _transformedVertices.size(); i++)
	{
		_transformedVertices[i] = transform * _transformedVertices[i]; //loops through each vertex in the _transformedVertices list and multiplies each value by the transformation provided
	}

}

//Loops through each vertex and uses the Vertex method DehomogeniseVertex() to dehomogenise each vertex in the list
void Model::DehomogeniseVertices()
{
	for (int i = 0; i < _transformedVertices.size(); i++)
	{
		_transformedVertices[i] = _transformedVertices[i].DehomogeniseVertex();
	}
}

void Model::CalculateBackfaces(const Vertex& pos)
{
	//Initalises the variables to be used
	Vector3D a, b, normal, eyeVect;
	float result = 0.0f;
	//Loops through each polygon in _polygons
	for (int i = 0; i < _polygons.size(); i++)
	{
		//retrieves the vertices from the specifed index stored in the polygon
		a = _transformedVertices[_polygons[i].GetIndex(0)] - _transformedVertices[_polygons[i].GetIndex(1)];  
		b = _transformedVertices[_polygons[i].GetIndex(0)] - _transformedVertices[_polygons[i].GetIndex(2)];
		//calculates the cross product from the Vectors b and a
		normal = Vector3D().CrossProduct(b, a);
		//Subtracts the position of the camera from the first vertex in the polygon
		eyeVect = _transformedVertices[_polygons[i].GetIndex(0)] - pos;
		// Calcates the dot product based on the normal and eye vector
		result = Vector3D().DotProduct(normal, eyeVect);
		// if the result is less than zero then it needs to be culled
		if (result < 0)
		{
			_polygons[i].SetCulling(true);
		}
		else
		{
			_polygons[i].SetCulling(false);
		}
		//Stores the normal for later use
		_polygons[i].SetNormal(normal);
	}
}

void Model::Sort()
{
	for (int i = 0; i < _polygons.size(); i++) //loops through all the polygons
	{
		// Calculates the mean of the z value in each vertex in each polygon
		float zAverage = (_transformedVertices[_polygons[i].GetIndex(0)].GetZ() + _transformedVertices[_polygons[i].GetIndex(1)].GetZ() + _transformedVertices[_polygons[i].GetIndex(2)].GetZ()) / 3;
		// Stores the z average in each polygon
		_polygons[i].SetAvg(zAverage); 
	}

	sort(_polygons.begin(),
		_polygons.end(),
		[](const Polygon3D& lhs, const Polygon3D& rhs) 
		{
			return lhs.GetAvg() > rhs.GetAvg();
		}); // sorts through each polygon and puts them in order largest going in front
}

int Model::RGBValidator(int value) const
{
	if (value < 0)
	{
		value = 0;
	}
	else if (value > 255)
	{
		value = 255;
	}

	return value;
}

void Model::CalculateAmbientLighting(AmbientLighting ambient)
{
	int index = 0;
	float tempR = 0, tempG = 0, tempB = 0;
	//loops through each polygon
	for (Polygon3D poly : _polygons)
	{
		//Ensure that the default colour is black
		_polygons[index].SetColour(0, 0, 0); 

		//Multiplies each colour in the light by the reflection coefficients
		tempR = ambient.GetColour(0) * ka_red;
		tempG = ambient.GetColour(1) * ka_green;
		tempB = ambient.GetColour(2) * ka_blue;
		//Adds colour value to the polygon
		_polygons[index].SetColour((int)tempR, (int)tempG, (int)tempB);
		index++;
	}
}

void Model::CalculateLightingDirectional(const vector<DirectionalLighting> dirLightingSources)
{
	float tempR, tempG, tempB;
	int totalR, totalG, totalB, index = 0;
	for (Polygon3D poly : _polygons)
	{

		totalR = _polygons[index].GetColour(0), totalG = _polygons[index].GetColour(1), totalB = _polygons[index].GetColour(2);
		for (DirectionalLighting source : dirLightingSources)
		{
			// Gets the colour from the light
			tempR = (float)source.GetL(0), tempG = (float)source.GetL(1), tempB = (float)source.GetL(2);

			// Multiplies the temp colour by their reflection coefficients
			tempR = (tempR * kd_red);
			tempG = (tempG * kd_green);
			tempB = (tempB * kd_blue);
			// Calculates the dot product of the normalised vector to the light source and the polygons’ normal vector
			float dotProduct = Vector3D().DotProduct(source.GetDirection().Normalise(), _polygons[index].GetNormal());
			// Multiplies temp r,g,b by dot-product
			tempR = tempR * dotProduct, tempG = tempG * dotProduct, tempB = tempB * dotProduct;
			// Adds the temp colour values to the total and then check they are within the restraints of the rgb limits
			totalR = RGBValidator(totalR + (int)tempR), totalG = RGBValidator(totalG + (int)tempG), totalB = RGBValidator(totalB + (int)tempB);
		}
		_polygons[index].SetColour(totalR, totalG, totalB);
		index++;
	}
}

void Model::CalculateLightingPoint(vector<PointLighting> pointLightingSources)
{
	float tempR, tempG, tempB, dotProduct, distance, atten;
	int totalR, totalG, totalB, index = 0;
	Vector3D lightSource;
	for (Polygon3D poly : _polygons)
	{
		totalR = _polygons[index].GetColour(0), totalG = _polygons[index].GetColour(1), totalB = _polygons[index].GetColour(2);
		for (PointLighting source : pointLightingSources)
		{
			tempR = (float)source.GetL(0), tempG = (float)source.GetL(1), tempB = (float)source.GetL(2);
			tempR = (tempR * ks_red);
			tempG = (tempG * ks_green);
			tempB = (tempB * ks_blue);
			dotProduct = Vector3D().DotProduct(source.GetDirection().Normalise(), _polygons[index].GetNormal());
			tempR = tempR * dotProduct, tempG = tempG * dotProduct, tempB = tempB * dotProduct;
			// Calculates the vector of the first vertex minus the position of the light
			lightSource = _transformedVertices[_polygons[index].GetIndex(0)] - source.GetPos();
			distance = lightSource.CalculateLength();
			lightSource.Normalise();

			// calculate the attenuation
			atten = (1 / (source.GetCoeffs(0) + source.GetCoeffs(1) * distance + source.GetCoeffs(2) * sqrtf(distance))) * 100;
			tempR = tempR * atten, tempG = tempG * atten, tempB = tempB * atten;
			totalR = RGBValidator(totalR + (int)tempR), totalG = RGBValidator(totalG + (int)tempG), totalB = RGBValidator(totalB + (int)tempB);
		}
		_polygons[index].SetColour(totalR, totalG, totalB);
		index++;
	}
}