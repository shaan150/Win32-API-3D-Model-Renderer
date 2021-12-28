#pragma once
#include "Framework.h"
#include "Vertex.h"
#include "Matrix.h"
#include "MD2Loader.h"
#include "Camera.h"
#include "AmbientLighting.h"
#include "DirectionalLighting.h"
#include "PointLighting.h"
#include "Triangle.h"
#include <vector>

class Rasteriser : public Framework
{
public:
	bool Initialise();
	void Update(const Bitmap& bitmap);
	void Render(const Bitmap& bitmap);
	void DrawSquare(Vertex square[4], HDC dc);
	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateScreenMatrix(float d, float width, float height);
	void DrawWireFrame(HDC dc);
	void DrawSolidFlat(HDC dc);
	void MyDrawSolidFlat(HDC dc);
	void FillPolygonFlat(Vertex v1, Vertex v2, Vertex v3, int colours[3]);
	void TransformationControls();
	void CameraControls();

private:
	/*float _x{ 0 };
	float _y{ 0 };
	float _translation{ 0 };
	float _xScale{ 0 };
	float _yScale{ 0 };
	Vertex square[4] = { Vertex(0,0,0),Vertex(50,0,0),Vertex(50,50,0),Vertex(0,50,0) };
	Vertex newSquare[4] = { Vertex(0,0,0),Vertex(50,0,0),Vertex(50,50,0),Vertex(0,50,0) };*/
	Model _model;
	Matrix _modelTransfromation;
	Matrix _persMatrix;
	Matrix _screenMatrix;
	// Initalise camera variables
	Camera _cam;
	float _camX{ 0 };
	float _camY{ 0 };
	float _camZ{ 0 };
	float _camRotX{ 0 };
	float _camRotY{ 0 };
	float _camRotZ{ 0 };
	// Initalise transformation variables
	float _x{ 0 };
	float _y{ 0 };
	float _z{ 0 };
	float _xScale{ 0 };
	float _yScale{ 0 };
	float _zScale{ 0 };
	float _xRot{ 0 };
	float _yRot{ 0 };
	float _zRot{ 0 };
	AmbientLighting ambient;
	vector<DirectionalLighting> dirLighting;
	vector<PointLighting> pointLightingSources;
};

