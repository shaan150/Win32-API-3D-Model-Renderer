#pragma once
#include "Vector3D.h"
#include <vector>
class DirectionalLighting
{
public:
	
	DirectionalLighting();
	DirectionalLighting(Vector3D direction, int redL, int greenL, int blueL);


	Vector3D GetDirection();
	int GetL(int index);
	void SetDirection(Vector3D direction);
	void SetL(int redL, int greenL, int blueL);


private:
	Vector3D _direction;
	int _l[3] = { 0,0,0 };

};

