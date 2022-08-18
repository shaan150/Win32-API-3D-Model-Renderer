#pragma once
#include "Framework.h"
#include "Vertex.h"
#include "Matrix.h"
#include "MD2Loader.h"
#include "Polygon3D.h"
#include "Camera.h"
#include "Vector3D.h"
#include <vector>
#include <string>

class Rasteriser : public Framework
{
public:
	bool Initialise();
	void Update(const Bitmap& bitmap);
	void Render(const Bitmap& bitmap);
	//Methods to generate the matrix transformations and stores them in the variables
	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateScreenMatrix(float d, float width, float height);
	void DrawWireFrame(HDC dc);
	void DrawSolidFlat(HDC dc);

	void DrawString(const Bitmap& bitmap, const LPCTSTR text, const int x, const int y);

private:
	Model _model; 
	Camera _cam;

	Matrix _persMatrix;
	Matrix _screenMatrix;

	Matrix _modelTransformation;
	float _x{ 0 };
	float _y{ 0 };
	float _z{ 0 };
	float _yRot = 0.0f;
	float _xScale{ 0 };
	float _yScale{ 0 };
	float _zScale{ 0 };
	float _xRot{ 0 };
	float _zRot{ 0 };
	bool _up = true;
	bool _left = true;
	bool _forwards = true;
	bool _taller = true;
	bool _wider = true;
	bool _longer = true;
	bool _clockwise = true;
	AmbientLighting _ambient;
	vector<DirectionalLighting> _dirLightingSources;
	vector<PointLighting> _pointLightingSources;

	string _displayRenderType = "Wireframe without culling";
	string _displayTransformation = "Translating On X";
	string _displayLighting = "";
	bool _wireframe = true;
	bool _backculling = false;
	bool _flat = false;
	bool _ambientLighting = false;
	bool _directionalLighting = false;
	bool _pointLighting = false;
	bool _translDisplay = true;
	bool _rotDisplay = false;
	bool _scaleDisplay = false;
	float _timer = 0;

};

