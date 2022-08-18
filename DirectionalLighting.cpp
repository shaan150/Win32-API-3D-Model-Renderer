#include "DirectionalLighting.h"

DirectionalLighting::DirectionalLighting()
{
}

DirectionalLighting::DirectionalLighting(const Vector3D direction, const int redL, const int greenL, const int blueL)
{
	SetDirection(direction);
	SetL(redL, greenL, blueL);
}

DirectionalLighting::~DirectionalLighting()
{
}

Vector3D DirectionalLighting::GetDirection() const
{
	return _direction;
}

int DirectionalLighting::GetL(const int index) const
{
	return _l[index];
}

void DirectionalLighting::SetDirection(const Vector3D direction)
{
	_direction = direction;
}

void DirectionalLighting::SetL(const int redL, const int greenL, const int blueL)
{
	_l[0] = redL;
	_l[1] = greenL;
	_l[2] = blueL;
}
