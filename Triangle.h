#pragma once
#include "Vertex.h"
#include <math.h>
class Triangle
{
public:
	Triangle();
	Triangle(Vertex v1, Vertex v2, Vertex v3, int red, int green, int blue);
	~Triangle();

	void SetVertex(int index, Vertex pos);
	Vertex GetVertex(int index);
	void SetColours(int red, int green, int blue);
	int GetColor(int index);

	float CrossProduct(Vertex v1, Vertex v2);
	void SortByY();
	void Draw(HDC dc);
private:
	Vertex _vertices[3] = { Vertex(), Vertex(), Vertex() };
	int _colours[3] = { 0, 0, 0 };
};

