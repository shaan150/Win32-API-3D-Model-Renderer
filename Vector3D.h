#pragma once
using namespace std;
class Vector3D
{
public:
	Vector3D();
	Vector3D(float x, float y, float z);

	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float w);

	Vector3D Normalise();
	float DotProduct(Vector3D a, Vector3D b);
	Vector3D CrossProduct(Vector3D a, Vector3D b);

	Vector3D& operator=(const Vector3D& rhs);

private:
	float _x;
	float _y;
	float _z;
};

