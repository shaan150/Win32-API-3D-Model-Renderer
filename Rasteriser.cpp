#include "Rasteriser.h"
#include <windowsx.h>
#include <cmath>

#define PI 3.14159265f

Rasteriser app;


bool Rasteriser::Initialise()
{
	_cam = Camera(0, 0, 0, Vertex(0.0f, 0.0f, -50.0f)); //Added camera class instance with values set to example ones provided in tutorial
	_ambient.SetColour(0, 100, 50);
	_dirLightingSources.push_back(DirectionalLighting(Vector3D(1.0f, 0.0f, 1.0f), 0, 200, 50));
	_pointLightingSources.push_back(PointLighting(Vector3D(1.0f, 0.0f, 10.0f), Vertex(0.0f, 0.0f, -50.0f), 0, 10, 10, 0, 1, 0));
	_xScale = 1.0f;
	_yScale = 1.0f;
	_zScale = 1.0f;
	_yRot = 1.0f;
	// This method override can be used to initialise any
	if (!MD2Loader::LoadModel("marvin.md2", _model, // I am utilising just the name of the 3D model as it's in the project files
		&Model::AddPolygon,
		&Model::AddVertex))
	{
		return false;
	}
	return true;
	
	// Make sure you return true unless there were any errors
	// in this method
}

void Rasteriser::Update(const Bitmap& bitmap)
{
	float width = (float)bitmap.GetWidth();
	float height = (float)bitmap.GetHeight();
	float aspectRatio = width / height;

		switch ((int)_timer)
		{
			case 0:
				_displayRenderType = "Wireframe without culling";
				_displayTransformation = "Translating On X & Y & Z";
				_displayLighting = "";
				_wireframe = true;
				_backculling = false;
				_flat = false;
				_ambientLighting = false;
				_directionalLighting = false;
				_pointLighting = false;
				_translDisplay = true;
				_rotDisplay = false;
				_scaleDisplay = false;
				break;

			case 4:
				_displayTransformation = "Rotating On X & Y & Z Axis";
				_translDisplay = false;
				_rotDisplay = true;
				break;

			case 8:
				_displayTransformation = "Scaling On X & Y & Z Axis";
				_rotDisplay = false;
				_scaleDisplay = true;
				break;

			case 12:
				_displayTransformation = "Performing All Transformations";
				_translDisplay = true;
				_rotDisplay = true;
				break;

			case 16:
				_backculling = true;
				_displayRenderType = "Wireframe with culling";
				_displayTransformation = "Translating On X & Y & Z";
				_rotDisplay = false;
				_scaleDisplay = false;
				break;
			
			case 20:
				_displayTransformation = "Rotating On X & Y & Z Axis";
				_translDisplay = false;
				_rotDisplay = true;
				break;

			case 24:
				_displayTransformation = "Scaling On X & Y & Z Axis";
				_rotDisplay = false;
				_scaleDisplay = true;
				break;

			case 28:
				_displayTransformation = "Performing All Transformations";
				_translDisplay = true;
				_rotDisplay = true;
				break;

			case 32:
				_wireframe = false;
				_flat = true;
				_displayRenderType = "Flat";
				_displayLighting = "Ambient Lighting";
				_displayTransformation = "Rotating On X & Y & Z Axis";
				_ambientLighting = true;
				_translDisplay = false;
				_scaleDisplay = false;
				_xRot = 0.0f, _yRot = 0.0f, _zRot = 0.0f;
				break;

			case 40:
				_displayLighting = "Directional Lighting";
				_ambientLighting = false;
				_directionalLighting = true;
				_xRot = 0.0f, _yRot = 0.0f, _zRot = 0.0f;
				break;

			case 48:
				_displayLighting = "Point Lighting";
				_directionalLighting = false;
				_pointLighting = true;
				_xRot = 0.0f, _yRot = 0.0f, _zRot = 0.0f;
				break;

			case 56:
				_displayLighting = "All Lighting";
				_directionalLighting = true;
				_ambientLighting = true;
				_xRot = 0.0f, _yRot = 0.0f, _zRot = 0.0f;
				break;

		}

		

	_modelTransformation = Matrix({
	1,0,0,_x,
	0,1,0,_y,
	0,0,1,_z,
	0,0,0,1
		});

	_modelTransformation = Matrix(
		{
			_xScale, 0, 0,0,
			0, _yScale,0,0,
			0,0,1,_zScale,
			0,0,0,1
		}) * _modelTransformation;

	_modelTransformation = Matrix(
		{
			1 , 0, 0, 0,
			0, cos(_xRot * (PI / 180)), -sin(_xRot * (PI / 180)), 0,
			0, sin(_xRot * (PI / 180)), cos(_xRot * (PI / 180)), 0,
			0, 0, 0, 1
		}) * _modelTransformation;

	_modelTransformation = Matrix({
		cos(_yRot * (PI / 180)), 0, sin(_yRot * (PI / 180)), 0,
		0, 1, 0, 0,
		-sin(_yRot * (PI / 180)), 0, cos(_yRot * (PI / 180)), 0,
		0, 0, 0, 1
		}) * _modelTransformation;

	_modelTransformation = Matrix({
		cos(_zRot * (PI / 180)), -sin(_zRot * (PI / 180)), 0, 0,
		sin(_zRot * (PI / 180)), cos(_zRot * (PI / 180)), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		}) * _modelTransformation;

	if (_translDisplay)
	{
		if (_left)
		{
			_x += 0.5;
			if (_x == 10)
			{
				_left = false;
			}
		}

		else if (!_left)
		{
			_x -= 0.5;
			if (_x == -10)
			{
				_left = true;
			}
		}

		if (_up)
		{
			_y += 0.5;
			if (_y == 10)
			{
				_up = false;
			}
		}

		else if (!_up)
		{
			_y -= 0.5;
			if (_y == -10)
			{
				_up = true;
			}
		}

		if (_forwards)
		{
			_z += 0.5;
			if (_z == 10)
			{
				_forwards = false;
			}
		}

		if (!_forwards)
		{
			_z -= 0.5;
			if (_z == -10)
			{
				_forwards = true;
			}
		}
	}
	else
	{
		_x = 0.0f;
		_y = 0.0f;
		_z = 0.0f;
	}
	if (_scaleDisplay)
	{
		if (_wider)
		{
			_xScale += 0.01f;
			if (_xScale >= 1.2)
			{
				_wider = false;
			}
		}
		else
		{
			_xScale -= 0.01f;
			if (_xScale <= 0.8)
			{
				_wider = true;
			}
		}
		if (_taller)
		{
			_yScale += 0.01f;
			if (_yScale >= 1.2)
			{
				_taller = false;
			}
		}
		else
		{
			_yScale -= 0.01f;
			if (_yScale <= 0.8f)
			{
				_taller = true;
			}
		}
		if (_longer)
		{
			_zScale += 0.01f;
			if (_zScale >= 1.2)
			{
				_longer = false;
			}
		}
		else
		{
			_zScale -= 0.01f;
			if (_zScale <= 0.8f)
			{
				_longer = true;
			}
		}
	}
	else
	{
		_xScale = 1.0f;
		_yScale = 1.0f;
		_zScale = 1.0f;
	}

	if (_rotDisplay)
	{
		if (_clockwise)
		{
			_xRot += 0.5;
			_yRot += 0.5;
			_zRot += 0.5;
			if (_xRot >= 75 || _yRot >= 75 || _zRot >= 75)
			{
				_clockwise = false;
			}
		}
		else
		{
			_xRot -= 0.5;
			_yRot -= 0.5;
			_zRot -= 0.5;
			if (_xRot <= -75 || _yRot <= -75 || _zRot <= -75)
			{
				_clockwise = true;
			}
		}
		
	}
	else
	{
		_xRot = 0;
		_yRot = 0;
		_zRot = 0;
	}
	_timer+= 0.05f;

	GeneratePerspectiveMatrix(1, aspectRatio);
	GenerateScreenMatrix(1, width, height);
}


void Rasteriser::Render(const Bitmap& bitmap)
{
	bitmap.Clear(RGB(0, 0, 0)); //Sets background colour
	_model.ApplyTransformToLocalVertices(_modelTransformation); //Applies the transformations generated in the update class such as rotation
	if (_backculling)
	{
		_model.CalculateBackfaces(_cam.GetPos()); // Marks which polygons are to visible
	}
	
	if (_ambientLighting)
	{
		_model.CalculateAmbientLighting(_ambient);
	}
	if (_directionalLighting)
	{
		_model.CalculateLightingDirectional(_dirLightingSources);
	}
	
	if (_pointLighting)
	{
		_model.CalculateLightingPoint(_pointLightingSources);
	}
	
	_model.ApplyTransformToTransformedVertices(_cam.getTransformation()); //Applies the camera / viewing transformations
	if (_backculling)
	{
		_model.Sort();
	}
	_model.ApplyTransformToTransformedVertices(_persMatrix); //Applies the perspective transformations
	_model.DehomogeniseVertices(); // Dehomogenises the model vertices
	_model.ApplyTransformToTransformedVertices(_screenMatrix); // Applies screen transformations
	if (_wireframe)
	{
		DrawWireFrame(bitmap.GetDC()); // Generates the wireframe of the model
	}
	if (_flat)
	{
		DrawSolidFlat(bitmap.GetDC());
	}
	wstring displayRenderType_wstr(_displayRenderType.begin(), _displayRenderType.end());
	wstring displayTransformation_wstr(_displayTransformation.begin(), _displayTransformation.end());
	wstring displayLighting_wstr(_displayLighting.begin(), _displayLighting.end());
	//then this should work:
	
	DrawString(bitmap, displayRenderType_wstr.c_str(),10,10);
	DrawString(bitmap, displayTransformation_wstr.c_str(),10,60);
	DrawString(bitmap, displayLighting_wstr.c_str(), 10, 110);
}

void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	_persMatrix = Matrix({
		d / aspectRatio, 0, 0, 0,
		0, d, 0, 0,
		0, 0, d, 0,
		0, 0, 1, 0
		});
}

void Rasteriser::GenerateScreenMatrix(float d, float width, float height)
{
	_screenMatrix = Matrix({
		width / 2, 0, 0, width / 2,
		0, -height / 2, 0, height / 2,
		0, 0, d / 2, d / 2,
		0, 0, 0, 1
		});
}

void Rasteriser::DrawWireFrame(HDC dc)
{
	int index = 0;
	vector<Polygon3D> polygons = _model.GetPolygons();
	vector<Vertex> transformedVertices = _model.GetVertices();

	for (Polygon3D poly : polygons) //Loops through each of the polygons
	{
		if (poly.GetCulling() == false)
		{
			HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); //Sets the colour of the lines
			HPEN hOldPen = SelectPen(dc, hPen);
			MoveToEx(dc, (int)transformedVertices[poly.GetIndex(0)].GetX(), (int)transformedVertices[poly.GetIndex(0)].GetY(), NULL); // updates the current position to the first vertex in this polygon
			for (int i = 0; i < 3; i++)
			{
				LineTo(dc, (int)transformedVertices[poly.GetIndex(1)].GetX(), (int)transformedVertices[(int)poly.GetIndex(1)].GetY());// Create a line from the current position to the second vertex in this polygon
				LineTo(dc, (int)transformedVertices[poly.GetIndex(2)].GetX(), (int)transformedVertices[(int)poly.GetIndex(2)].GetY());// Create a line from the current position to the last vertex in this polygon
				LineTo(dc, (int)transformedVertices[poly.GetIndex(0)].GetX(), (int)transformedVertices[(int)poly.GetIndex(0)].GetY());// Create a line from the current position to the first vertex in this polygon

			}
			SelectPen(dc, hOldPen);
			DeleteObject(hPen); //Gets rid of the pen, to allow a different colour to be used per each polygon, if required

			index++;
		}

	}
}

void Rasteriser::DrawSolidFlat(HDC dc)
{
	vector<Polygon3D> polygons = _model.GetPolygons();
	vector<Vertex> _transformedVertices = _model.GetVertices();
	int index = 0;
	for (Polygon3D poly : polygons)
	{
		if (poly.GetCulling() == false)
		{
			HPEN hPen = CreatePen(PS_SOLID, 2, RGB(poly.GetColour(0), poly.GetColour(1), poly.GetColour(2)));
			HPEN hOldPen = SelectPen(dc, hPen);
			//Fills The Polygons With The Colour Specified
			HBRUSH hBrush = CreateSolidBrush(RGB(poly.GetColour(0), poly.GetColour(1), poly.GetColour(2)));
			HBRUSH hOldBrush = SelectBrush(dc, hBrush);
			POINT points[3];
			for (int i = 0; i < 3; i++)
			{
				// Converts the 
				points[i] = POINT({
					(int)_transformedVertices[poly.GetIndex(i)].GetX(),(int)_transformedVertices[poly.GetIndex(i)].GetY()
					});
			}

			Polygon(dc, points, 3); //Generates The Polygon
			SelectBrush(dc, hOldBrush);
			DeleteObject(hBrush);
			SelectPen(dc, hOldPen);
			DeleteObject(hPen);

		}

		index++;
	}
}

void Rasteriser::DrawString(const Bitmap& bitmap, const LPCTSTR text, const int x, const int y)
{
	HDC hdc = bitmap.GetDC();
	HFONT hFont, hOldFont;

	// Retrieve a handle to the variable stock font.  
	hFont = hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Myfont"));

	// Select the variable stock font into the specified device context. 
	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));

		// Display the text string.  
		TextOut(hdc, x, y, text, lstrlen(text));

		// Restore the original font.        
		SelectObject(hdc, hOldFont);
	}
	DeleteObject(hFont);
}
