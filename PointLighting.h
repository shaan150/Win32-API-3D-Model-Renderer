#pragma once
#include "Vector3D.h"
#include "Vertex.h"
class PointLighting
{
public:
	PointLighting();
	PointLighting(Vector3D direction, const Vertex& pos, int redL, int greenL, int blueL, float a, float b, float c);
	~PointLighting();

	Vector3D GetDirection();
	void SetDirection(Vector3D direction);
	Vertex GetPos();
	void SetPos(const Vertex& pos);
	int GetL(int index);
	void SetL(int redL, int greenL, int blueL);
	float GetCoeffs(int index);
	void SetCoeffs(float a, float b, float c);

private:
	Vector3D _direction;
	Vertex _pos;
	int _l[3] = { 0,0,0 };
	float _attenuationCoefficients[3] = { 0, 0, 0 };
};

