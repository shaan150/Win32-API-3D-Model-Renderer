#pragma once
#include "Vertex.h"
#include "Matrix.h"
#define PI 3.14159265f
class Camera
{
public:
	Camera();
	Camera(float xRot, float yRot, float zRot, const Vertex& pos);
	~Camera() noexcept;

	Matrix getTransformation();
	Vertex GetPos();
	void SetPos(Vertex pos);
private:
	float _xRot;
	float _yRot;
	float _zRot;
	Vertex _pos;
	Matrix _viewMatrix;

};

