#pragma once
#include "Vertex.h"
#include "Vector3D.h"
#include <array>
class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	~Polygon3D();
	void Copy(const Polygon3D& other);
	Polygon3D(const Polygon3D& p);
	// Accessor to return index of specified vertex
	int GetIndex(int) const;
	bool GetCulling() const;
	void SetCulling(const bool culled);
	Vector3D GetNormal() const;
	void SetNormal(const Vector3D normal);
	float GetAvg() const;
	void SetAvg(const float zAvg);
	int GetColour(const int index) const;
	void SetColour(int r, int g, int b);
	void SetResult(const float result);

	Polygon3D& operator= (const Polygon3D& rhs);
	
private:
	int _indices[3];
	bool _culled;
	Vector3D _normal;
	float _zAvg;
	float _result;
	int _colour[3] = { 0, 0, 0 };
};

