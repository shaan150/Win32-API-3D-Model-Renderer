#include "Polygon3D.h"

Polygon3D::Polygon3D()
{
}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;

}

Polygon3D::~Polygon3D()
{
}

Polygon3D::Polygon3D(const Polygon3D& p)
{
	Copy(p);
}

int Polygon3D::GetIndex(int index) const
{
	return _indices[index];
}

bool Polygon3D::GetCulling() const
{
	return _culled;
}

void Polygon3D::SetCulling(const bool culled)
{
	_culled = culled;
}

Vector3D Polygon3D::GetNormal() const
{
	return _normal;
}

void Polygon3D::SetNormal(const Vector3D normal)
{
	_normal = normal;
}

float Polygon3D::GetAvg() const
{
	return _zAvg;
}

void Polygon3D::SetAvg(const float zAvg)
{
	_zAvg = zAvg;
}

int Polygon3D::GetColour(const int index) const
{
	return _colour[index];
}

void Polygon3D::SetColour(const int r, const int g, const int b)
{
	_colour[0] = r;
	_colour[1] = g;
	_colour[2] = b;
}

void Polygon3D::Copy(const Polygon3D& other)
{
	for (int i = 0; i < 3; i++)
	{
		_indices[i] = other.GetIndex(i);
	}

	SetCulling(other.GetCulling());
	SetNormal(other.GetNormal());
	SetAvg(other.GetAvg());
	SetColour(other.GetColour(0), other.GetColour(1), other.GetColour(2));
}

Polygon3D& Polygon3D::operator=(const Polygon3D& rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}

	return *this;
}


