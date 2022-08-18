#pragma once

#include "Vector3D.h"
using namespace std;
class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(const Vertex& other);

	// Accessors To Retrieve Or Set The X, Y, W Or Z Private Variables
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float w);
	float GetW() const;
	void SetW(const float w);

	Vertex DehomogeniseVertex();
	


	// Assignment operator
	Vertex& operator= (const Vertex& rhs);

	bool operator== (const Vertex& rhs) const;

	const Vertex operator+ (const Vertex& rhs) const;

	const Vector3D operator- (const Vertex& rhs) const;
private:
	float _x;
	float _y;
	float _z;
	float _w;
};

