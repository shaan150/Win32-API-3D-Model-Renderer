#pragma once
#include <cmath>
using namespace std;
class Vector3D
{
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	~Vector3D();
	//Accessors to get and set the variables _x, _y, _z
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float w);
	//Calculates the dot product and cross product, returning a float data type for dot product and 
	float DotProduct(Vector3D a, Vector3D b);
	Vector3D CrossProduct(Vector3D a, Vector3D b);

	//Calculates the normalisation
	float CalculateLength();
	Vector3D Normalise();

	Vector3D& operator=(const Vector3D& rhs);

private:
	float _x;
	float _y;
	float _z;
};



