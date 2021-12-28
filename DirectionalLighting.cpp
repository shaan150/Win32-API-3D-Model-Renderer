#include "DirectionalLighting.h"

DirectionalLighting::DirectionalLighting()
{
}

DirectionalLighting::DirectionalLighting(Vector3D direction, int redL, int greenL, int blueL)
{
	SetDirection(direction);
	SetL(redL, greenL, blueL);
}

Vector3D DirectionalLighting::GetDirection()
{
	return _direction;
}

int DirectionalLighting::GetL(int index)
{
	return _l[index];
}

void DirectionalLighting::SetDirection(Vector3D direction)
{
	_direction = direction;
}

void DirectionalLighting::SetL(int redL, int greenL, int blueL)
{
	_l[0] = redL;
	_l[1] = greenL;
	_l[2] = blueL;
}
