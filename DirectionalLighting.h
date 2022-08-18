#pragma once
#include "Vector3D.h"
#include <vector>
class DirectionalLighting
{
public:

	DirectionalLighting();
	DirectionalLighting(const Vector3D direction, const int redL, const int greenL, const int blueL);
	~DirectionalLighting();

	//Accessors to retrieve and set the properties
	Vector3D GetDirection() const;
	int GetL(const int index) const; // Gets the values from the _l array based on specific index
	void SetDirection(const Vector3D direction);
	void SetL(const int redL, const int greenL, const int blueL);


private:
	Vector3D _direction;
	int _l[3] = { 0,0,0 };// Array to hold the rgb values of the light intensity

};



