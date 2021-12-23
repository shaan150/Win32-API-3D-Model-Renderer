#include "Model.h"
#include <algorithm>

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
	_vertices.push_back(Vertex(x, y, z));
	_transformedVertices.push_back(Vertex(x, y, z));
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.push_back(Polygon3D(i0, i1, i2));
}

void Model::ApplyTransformToLocalVertices(const Matrix& transform)
{
	for (int i = 0; i < _transformedVertices.size(); i++)
	{
		_transformedVertices[i] = transform * _vertices[i];
	}
}

void Model::ApplyTransformToTransformedVertices(const Matrix& transform)
{
	for (int i = 0; i < _transformedVertices.size(); i++)
	{
		_transformedVertices[i] = transform * _transformedVertices[i];
	}
}

void Model::DehomogeniseVertices()
{
	for (int i = 0; i < _transformedVertices.size(); i++)
	{
		_transformedVertices[i] = _transformedVertices[i].DehomogeniseVertex();
	}
}

void Model::CalculateBackfaces(const Vertex& pos)
{
	Vector3D a, b, normal, eyeVect;
	float result = 0.0f;
	for (int i =0; i < _polygons.size(); i++)
	{
		a = _transformedVertices[_polygons[i].GetIndex(0)] - _transformedVertices[_polygons[i].GetIndex(1)];
		b = _transformedVertices[_polygons[i].GetIndex(0)] - _transformedVertices[_polygons[i].GetIndex(2)];
		normal = Vector3D().CrossProduct(b,a);
		eyeVect = _transformedVertices[_polygons[i].GetIndex(0)] - pos;
		result = Vector3D().DotProduct(normal,eyeVect);
		if (result < 0)
		{
			_polygons[i].SetCulling(true);
		}
		else
		{
			_polygons[i].SetCulling(false);
			
		}
		_polygons[i].SetResult(result);
		_polygons[i].SetNormal(normal);
	}
}

void Model::Sort()
{
	for (int i = 0; i < _polygons.size(); i++)
	{
		float zAverage = (_transformedVertices[_polygons[i].GetIndex(0)].GetZ() + _transformedVertices[_polygons[i].GetIndex(1)].GetZ() + _transformedVertices[_polygons[i].GetIndex(2)].GetZ()) / 3;
		_polygons[i].SetAvg(zAverage);
	}

	sort(_polygons.begin(),
		_polygons.end(),
		[](const Polygon3D& lhs, const Polygon3D& rhs)
		{
			return lhs.GetAvg() < rhs.GetAvg();
		});
}

void Model::CalculateAmbientLighting(AmbientLighting ambient)
{
	int index = 0;
	for (Polygon3D poly : _polygons)
	{

		index++;
	}
}

void Model::CalculateLightingDirectional(vector<DirectionalLighting> dirLightingSources)
{
	float tempR, tempG, tempB;
	int totalR, totalG, totalB, index = 0;
	for (Polygon3D poly : _polygons)
	{
		totalR = 0, totalG = 0, totalB = 0;
		for (DirectionalLighting source : dirLightingSources)
		{
			tempR = (float)source.GetL(0), tempG = (float)source.GetL(1), tempB = (float)source.GetL(2);
			tempR = (tempR * kd_red);// +(tempR * ka_red) + (tempR * ks_red);
			tempG = (tempG * kd_green); //+ (tempG * ka_green) + (tempG * ks_green);
			tempB = (tempB * kd_blue); //+ (tempR * ka_blue) + (tempR * ks_blue);
			float dotProduct = Vector3D().DotProduct(source.GetDirection().Normalise(), _polygons[index].GetNormal());
			tempR = tempR * dotProduct, tempG = tempG * dotProduct, tempB = tempB * dotProduct;
			totalR = RGBValidator(totalR + (int)tempR), totalG = RGBValidator(totalG + (int)tempG), totalB = RGBValidator(totalB + (int)tempB);
		}
		_polygons[index].SetColour(totalR, totalG, totalB);
		index++;
	}
}
int Model::RGBValidator(int value)
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
void Model::SetColour(int red, int green, int blue)
{
	_colour[0] = red;
	_colour[1] = green;
	_colour[2] = blue;
}

int Model::GetColour(int index)
{
	return _colour[index];
}