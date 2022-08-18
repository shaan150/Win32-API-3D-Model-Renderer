#pragma once
#include "Vector3D.h"
class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	~Polygon3D(); 
	Polygon3D(const Polygon3D& p);
	// Accessors to retrieve and set the private variables
	int GetIndex(int) const;
	bool GetCulling() const;
	void SetCulling(const bool culled);
	Vector3D GetNormal() const;
	void SetNormal(const Vector3D normal);
	float GetAvg() const;
	void SetAvg(const float zAvg);
	int GetColour(const int index) const;
	void SetColour(const int r, const int g, const int b);
	// Method to copy polygon variable information
	void Copy(const Polygon3D& other);

	Polygon3D& operator= (const Polygon3D& rhs);
	
private:
	int _indices[3] = { 0,0,0 }; //Initializes the array for the index of each Vertex to be 0
	bool _culled = false;
	Vector3D _normal;
	float _zAvg = 0;
	int _colour[3] = { 0, 0, 0 };
};

