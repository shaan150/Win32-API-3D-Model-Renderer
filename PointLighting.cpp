#include "PointLighting.h"

PointLighting::PointLighting()
{
}

PointLighting::PointLighting(Vector3D direction, const Vertex& pos, int redL, int greenL, int blueL, float a, float b, float c)
{
	SetDirection(direction);
	SetPos(pos);
	SetL(redL, greenL, blueL);
	SetCoeffs(a, b, c);
}

PointLighting::~PointLighting()
{
}

Vector3D PointLighting::GetDirection()
{
	return _direction;
}

void PointLighting::SetDirection(Vector3D direction)
{
	_direction = direction;
}

Vertex PointLighting::GetPos()
{
	return _pos;
}

void PointLighting::SetPos(const Vertex& pos)
{
	_pos = pos;
}

int PointLighting::GetL(int index)
{
	return _l[index];
}

void PointLighting::SetL(int redL, int greenL, int blueL)
{
	_l[0] = redL;
	_l[1] = greenL;
	_l[2] = blueL;
}

float PointLighting::GetCoeffs(int index)
{
	return _attenuationCoefficients[index];
}

void PointLighting::SetCoeffs(float a, float b, float c)
{
	_attenuationCoefficients[0] = a;
	_attenuationCoefficients[1] = b;
	_attenuationCoefficients[2] = c;
}
