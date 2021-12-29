#include "Vertex.h"
#include "Matrix.h"

Vertex::Vertex()
{
	SetX(0.0f);
	SetY(0.0f);
	SetW(0.0f);
	SetZ(0.0f);
	SetCount(0);
}

Vertex::Vertex(float x, float y, float z)
{
	SetX(x);
	SetY(y);
	SetW(1.0f);
	SetZ(z);
	SetCount(0);
}

Vertex::Vertex(const Vertex & other)
{
	SetX(other.GetX());
	SetY(other.GetY());
	SetW(other.GetW());
	SetZ(other.GetZ());

}

float Vertex::GetX() const
{
	return _x;
}

void Vertex::SetX(const float x)
{
	_x = x;
}

float Vertex::GetY() const
{
	return _y;
}

void Vertex::SetY(const float y)
{
	_y = y;
}

float Vertex::GetZ() const
{
	return _z;
}

void Vertex::SetZ(const float z)
{
	_z = z;
}
float Vertex::GetW() const
{
	return _w;
}

void Vertex::SetW(const float w)
{
	_w = w;
}

Vector3D Vertex::GetNormal()
{
	return _normal;
}

void Vertex::SetNormal(Vector3D normal)
{
	_normal = normal;
}

int Vertex::GetCount()
{
	return _contCount;
}

void Vertex::SetCount(int contCount)
{
	_contCount = contCount;
}

int Vertex::GetColour(int index)
{
	return _colours[index];
}

void Vertex::SetColours(int red, int green, int blue)
{
	_colours[0] = red;
	_colours[1] = green;
	_colours[2] = blue;
}

Vertex Vertex::DehomogeniseVertex()
{
	SetX(_x / _w);
	SetY(_y / _w);
	SetW(_w / _w);
	SetZ(_z / _w);
	return  Vertex(GetX(),GetY(), GetZ());
}

Vertex& Vertex::operator=(const Vertex& rhs)
{
	// Only do the assignment if we are not assigning
	// to ourselves
	if (this != &rhs)
	{
		SetX(rhs.GetX());
		SetY(rhs.GetY());
		SetW(rhs.GetW());
		SetZ(rhs.GetZ());
	}
	return *this;
}

// The const at the end of the declaraion for '==" indicates that this operation does not change
// any of the member variables in this class.

bool Vertex::operator==(const Vertex& rhs) const
{
	return (_x == rhs.GetX() && _y == rhs.GetY() && _z == rhs.GetZ() &&_w == rhs.GetW());
}

// You can see three different uses of 'const' here:
//
// The first const indicates that the method changes the return value, but it is not moved in memory
// The second const indicates that the parameter is passed by reference, but it is not modified
// The third const indicates that the operator does not change any of the memory variables in the class.

const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ());
}

const Vector3D Vertex::operator-(const Vertex& rhs) const
{
	return Vector3D(
		_x - rhs.GetX(), 
		_y - rhs.GetY(),
		_z - rhs.GetZ());
}
