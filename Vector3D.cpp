#include "Vector3D.h"
#include "Vertex.h"

Vector3D::Vector3D()
{
	_x = 0;
	_y = 0;
	_z = 0;
}

Vector3D::Vector3D(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

Vector3D::~Vector3D()
{
}

float Vector3D::GetX() const
{
	return _x;
}

void Vector3D::SetX(const float x)
{
	_x = x;
}

float Vector3D::GetY() const
{
	return _y;
}

void Vector3D::SetY(const float y)
{
	_y = y;
}

float Vector3D::GetZ() const
{
	return _z;
}

void Vector3D::SetZ(const float z)
{
	_z = z;
}

float Vector3D::DotProduct(Vector3D a, Vector3D b)
{
	return (
		(a.GetX() * b.GetX()) +
		(a.GetY() * b.GetY()) +
		(a.GetZ() * b.GetZ())
		);
}

Vector3D Vector3D::CrossProduct(Vector3D a, Vector3D b)
{
	return Vector3D(
		(a.GetY() * b.GetZ()) - (a.GetZ() * b.GetY()),
		(a.GetZ() * b.GetX()) - (a.GetX() * b.GetZ()),
		(a.GetX() * b.GetY()) - (a.GetY() * b.GetX())
	);
}

float Vector3D::CalculateLength()
{
	return sqrtf((float)pow(_x, 2) + (float)pow(_y, 2) + (float)pow(_z, 2)); 
}

Vector3D Vector3D::Normalise()
{
	float length = CalculateLength();
	return Vector3D(
		_x / length,
		_y / length,
		_z / length
	);
}

Vector3D& Vector3D::operator=(const Vector3D& rhs)
{

	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
	}
	return *this;
}

