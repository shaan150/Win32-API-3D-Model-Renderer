#pragma once
#include "Vertex.h"
#include "Matrix.h"
#include <cmath>
#define PI 3.14159265f //Defined PI as a global variable to use in viewing calculations
class Camera
{
public:
	Camera();
	Camera(float xRot, float yRot, float zRot, const Vertex& pos);
	~Camera() noexcept;

	Matrix getTransformation();
	Vertex GetPos();
	void SetPos(const Vertex& pos);
private:
	Vertex _pos;
	Matrix _viewMatrix;

};



