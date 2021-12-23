#include "Rasteriser.h"
#include "Polygon3D.h"
#include <cmath>
#include <windowsx.h>
#define PI 3.14159265f


Rasteriser app;


bool Rasteriser::Initialise()
{
	// This method override can be used to initialise any
	/*_x = 0;
	_y = 0;
	_xScale = 1.3f;
	_yScale = 1.2f;
	_translation = 5;*/
	_x = 0;
	_y = 0;
	_z = 0;
	_xRot = 1.0f;
	_yRot = 1.0f;
	_zRot = 1.0f;
	_xScale = 1.0f;
	_yScale = 1.0f;
	_camX = 0.0f;
	_camY = 0.0f;
	_camZ = 0.0f;
	_cam = Camera(0, 0, 0, Vertex(0.0f, 0.0f, -50.0f));
	dirLighting.push_back(DirectionalLighting(Vector3D(1.0f, 0.0f, 1.0f), 0, 10, 5));
	if (!MD2Loader::LoadModel("chef.md2", _model,
		&Model::AddPolygon,
		&Model::AddVertex))
	{
		return false;
	}
	return true;

	
	

	// Make sure you return true unless there were any errors
	// in this method
	return true;
}

void Rasteriser::Update(const Bitmap& bitmap)
{
	float width = (float)bitmap.GetWidth();
	float height = (float)bitmap.GetHeight();
	float aspectRatio = width / height;
	_modelTransfromation = Matrix({
		1,0,0,_x,
		0,1,0,_y,
		0,0,1,_z,
		0,0,0,1
		});

	_modelTransfromation = Matrix(
		{
			_xScale, 0, 0,0,
			0, _yScale,0,0,
			0,0,1,0,
			0,0,0,1
		}) * _modelTransfromation;

	/*_modelTransfromation = Matrix(
		{
			1 , 0, 0, 0,
			0, cos(_xRot * (PI / 180)), -sin(_xRot * (PI / 180)), 0,
			0, sin(_xRot * (PI / 180)), cos(_xRot * (PI / 180)), 0,
			0, 0, 0, 1
		}) * _modelTransfromation;*/

	_modelTransfromation = Matrix({
		cos(_yRot * (PI / 180)), 0, sin(_yRot * (PI / 180)), 0,
		0, 1, 0, 0,
		-sin(_yRot * (PI / 180)), 0, cos(_yRot * (PI / 180)), 0,
		0, 0, 0, 1
		}) * _modelTransfromation;

	/*_modelTransfromation = Matrix({
		cos(_zRot * (PI / 180)), -sin(_zRot * (PI / 180)), 0, 0,
		sin(_zRot * (PI / 180)), cos(_zRot * (PI / 180)), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		}) * _modelTransfromation;*/


	/*if (_x > 100)
	{
		_x -= 0.5;
	}
	else
	{
		_x += 0.5;
	}

	if (_y > bitmap.GetHeight())
	{
		_y -= 0.5;
	}
	else
	{
		_y += 0.5;
	}*/
	if (_xScale > 2)
	{
		_xScale -= 0.5;
	}
	else if (_xScale == 0)
	{
		_xScale += 0.5;
	}
	if (_yScale > 2)
	{
		_yScale -= 0.5;
	}
	else if (_yScale == 0)
	{
		_yScale += 0.5;
	}
	_xRot += 0.5;
	_yRot += 1;
	_zRot += 1.5;


	GeneratePerspectiveMatrix(1, aspectRatio);
	GenerateScreenMatrix(1, width, height);

	

/*
	for (int i = 0;  i < 4; i++)
	{
		Vertex translLine = Matrix({
			1,0,0,_translation,
			0,1,0,_translation,
			0,0,1,1,
			0,0,0,1
		}) * square[i];
		translLine = Matrix({
			_xScale, 0, 0,0,
			0, _yScale,0,0,
			0,0,1,0,
			0,0,0,1
			}) * translLine;
		translLine = Matrix({
			cos(_rotation * (PI / 180)), -sin(_rotation * (PI / 180)), 0,0,
			sin(_rotation * (PI / 180)), cos(_rotation * (PI / 180)), 0,0,
			0, 0, 1,0,
			0,0,0,1
			})* translLine;
		newSquare[i] = translLine;
	}
	_translation += 5;
	_xScale += 1.3f;
	_yScale += 1.2f;
	_rotation -= 5;
	
	_x = newSquare[0].GetX();
	_y = newSquare[0].GetY();

	if (_x > bitmap.GetWidth() && _y > bitmap.GetHeight())
	{
		_x = 0;
		_y = 0;
		_xScale = 1.3f;
		_yScale = 1.2f;
		_translation = 5;
		_rotation = 5;

		for (int i = 0; i < 4; i++)
		{
			newSquare[i] = square[i];
		}
	}
	*/


}


void Rasteriser::Render(const Bitmap& bitmap)
{
	_model.ApplyTransformToLocalVertices(_modelTransfromation);
	_model.CalculateBackfaces(_cam.GetPos());
	_model.CalculateLightingDirectional(dirLighting);
	_model.Sort();
	_model.ApplyTransformToTransformedVertices(_cam.getTransformation());
	_model.ApplyTransformToTransformedVertices(_persMatrix);
	_model.DehomogeniseVertices();
	_model.ApplyTransformToTransformedVertices(_screenMatrix);
	
	
	// Clear the bitmap to white
	bitmap.Clear(RGB(0, 0, 0));
	DrawWireFrame(bitmap.GetDC());
	DrawSolidFlat(bitmap.GetDC());
	// Now draw a 50 pixel square at the cursor position
	//DrawSquare(newSquare,bitmap.GetDC());
	// We do not need to call InvalidateRect since this is taken care of 
	// in the framework every time Render() is called
}
void Rasteriser::DrawSquare(Vertex square[4], HDC hdc)
{
		HPEN hPenOld;
		HPEN hLinePen;
		COLORREF qLineColor;
		qLineColor = RGB(255, 0, 0);
		hLinePen = CreatePen(PS_SOLID, 1, qLineColor);
		hPenOld = (HPEN)SelectObject(hdc, hLinePen);
		MoveToEx(hdc, (int)square[0].GetX(), (int)square[0].GetY(), NULL);
		LineTo(hdc, (int)square[1].GetX(), (int)square[1].GetY());
		LineTo(hdc, (int)square[2].GetX(), (int)square[2].GetY());
		LineTo(hdc, (int)square[3].GetX(), (int)square[3].GetY());
		LineTo(hdc, (int)square[0].GetX(), (int)square[0].GetY());
		DeleteObject(hLinePen);
	
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
	vector<Vertex> _transformedVertices = _model.GetVertices();
	//HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	//HPEN hOldPen = SelectPen(dc, hPen);

	for (Polygon3D poly : polygons)
	{
		bool culling = polygons[index].GetCulling();
		if (culling == false)
		{
			MoveToEx(dc, (int)_transformedVertices[poly.GetIndex(0)].GetX(), (int)_transformedVertices[poly.GetIndex(0)].GetY(), NULL);
			for (int i = 0; i < 3; i++)
			{
				LineTo(dc, (int)_transformedVertices[poly.GetIndex(i)].GetX(), (int)_transformedVertices[(int)poly.GetIndex(i)].GetY());
				if (i >= 2)
				{
					LineTo(dc, (int)_transformedVertices[poly.GetIndex(i)].GetX(), (int)_transformedVertices[(int)poly.GetIndex(i)].GetY());
					LineTo(dc, (int)_transformedVertices[poly.GetIndex(0)].GetX(), (int)_transformedVertices[(int)poly.GetIndex(0)].GetY());
				}
			}
		}

		index++;
		
	}

	//SelectPen(dc, hOldPen);
	//DeleteObject(hPen);

}
void Rasteriser::DrawSolidFlat(HDC dc)
{
	/**/

	
	vector<Polygon3D> polygons = _model.GetPolygons();
	vector<Vertex> _transformedVertices = _model.GetVertices();
	int index = 0;
	for (Polygon3D poly : polygons)
	{
		bool culling = polygons[index].GetCulling();
		if (culling == false)
		{
			HPEN hPen = CreatePen(PS_SOLID, 2, RGB(poly.GetColour(0), poly.GetColour(1), poly.GetColour(2)));
			HPEN hOldPen = SelectPen(dc, hPen);
			HBRUSH hBrush = CreateSolidBrush(RGB(poly.GetColour(0), poly.GetColour(1), poly.GetColour(2)));
			HBRUSH hOldBrush = SelectBrush(dc, hBrush);
			POINT points[3];
			for (int i = 0; i < 3; i++)
			{
				points[i] = POINT({
					(int)_transformedVertices[poly.GetIndex(i)].GetX(),(int)_transformedVertices[poly.GetIndex(i)].GetY(),
					});
			}

			Polygon(dc, points, 3);
			SelectBrush(dc, hOldBrush);
			DeleteObject(hBrush);
			SelectPen(dc, hOldPen);
			DeleteObject(hPen);
			
		}
		
		index++;
	}
	

	/**/
}
void Rasteriser::TransformationControls()
{
	if (GetKeyState(0x41) & 0x8000)
	{
		_x -= 0.5f;
	}
	else if (GetKeyState(0x44) & 0x8000)
	{
		_x += 0.5f;
	}
	else if (GetKeyState(0x57) & 0x8000)
	{
		_y += 0.5f;
	}
	else if (GetKeyState(0x53) & 0x8000)
	{
		_y -= 0.5f;
	}
	else if (GetKeyState(0x46) & 0x8000)
	{
		_z += 0.5f;
	}
	else if (GetKeyState(0x47) & 0x8000)
	{
		_z -= 0.5f;
	}

	else if (GetKeyState(0x5A) & 0x8000)
	{
		_xScale += 0.5f;
		_yScale += 0.5f;
	}
	else if (GetKeyState(0x58) & 0x8000)
	{
		
	}
	else if (GetKeyState(0x51) & 0x8000)
	{
		_xRot++;
	}
	else if (GetKeyState(0x45) & 0x8000)
	{
		_xRot--;
	}
	else if (GetKeyState(0x52) & 0x8000)
	{
		_yRot++;

	}
	else if (GetKeyState(0x54) & 0x8000)
	{
		_yRot--;

	}
	else if (GetKeyState(0x59) & 0x8000)
	{
		_zRot++;

	}
	else if (GetKeyState(0x55) & 0x8000)
	{
		_zRot--;

	}

	
}
void Rasteriser::CameraControls()
{
	_camX = 0, _camY = 0, _camZ = 0;
	if (GetKeyState(VK_LEFT) & 0x8000)
	{

		_camX += 0.5f;
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		_camX -= 0.5f;
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		_camY -= 0.5f;
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		_camY += 0.5f;

	}
	else if (GetKeyState(VK_OEM_PLUS) & 0x8000)
	{
		_camZ += 0.5f;
	}
	else if (GetKeyState(VK_OEM_MINUS) & 0x8000)
	{
		_camZ -= 0.5f;
	};
	_cam = Camera(0, 0, 0,
		Matrix({
		   1,0,0,_camX,
		   0,1,0,_camY,
		   0,0,1,_camZ,
		   0,0,0,1
			}) * _cam.GetPos()
	);
}



