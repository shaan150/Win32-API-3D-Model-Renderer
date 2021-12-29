#pragma once
#include "ocidl.h"
#include "Vector3D.h"
using namespace std;
class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(const Vertex& other);

	// Accessors
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float w);
	float GetW() const;
	void SetW(const float w);
	Vector3D GetNormal();
	void SetNormal(Vector3D normal);
	int GetCount();
	void SetCount(int contCount);
	int GetColour(int index);
	void SetColours(int red, int green, int blue);

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
	Vector3D _normal;
	int _contCount;
	int _colours[3] = { 0,0,0 };
};

