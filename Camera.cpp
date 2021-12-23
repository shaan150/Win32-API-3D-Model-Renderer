#include "Camera.h"
#include <cmath>

Camera::Camera()
{
	_xRot = 0.0f;
	_yRot = 0.0f;
	_zRot = 0.0f;
}

Camera::Camera(float xRot, float yRot, float zRot, const Vertex& pos)
{
	Matrix viewingTransf = Matrix(
		{
		1, 0, 0, 0,
		0, cos(xRot * (PI / 180)), sin(xRot * (PI / 180)), 0,
		0,-sin(xRot * (PI / 180)), cos(xRot * (PI / 180)), 0,
		0, 0, 0, 1
		});
	viewingTransf = viewingTransf * Matrix(
		{
			cos(yRot * (PI / 180)), 0, -sin(yRot * (PI / 180)), 0,
			0, 1, 0, 0,
			sin(yRot * (PI / 180)), 0, cos(yRot * (PI / 180)), 0,
			0, 0, 0, 1
		});
	viewingTransf = viewingTransf * Matrix(
		{
			cos(zRot * (PI / 180)), sin(zRot * (PI / 180)), 0, 0,
			-sin(zRot * (PI / 180)), cos(zRot * (PI / 180)), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		});
	viewingTransf = viewingTransf * Matrix(
		{
			1, 0, 0, -pos.GetX(),
			0, 1, 0, -pos.GetY(),
			0, 0, 1, -pos.GetZ(),
			0, 0, 0, 1
		});

	_viewMatrix = viewingTransf;
	_xRot = xRot;
	_yRot = yRot;
	_zRot = zRot;
	_pos = pos;
}

Camera::~Camera()
{
}

Matrix Camera::getTransformation()
{
	return _viewMatrix;
}

Vertex Camera::GetPos()
{
	return _pos;
}

void Camera::SetPos(Vertex pos)
{
	_pos = pos;
}
