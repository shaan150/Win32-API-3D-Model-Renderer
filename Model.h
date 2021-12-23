#pragma once
#include "Polygon3D.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Vector3D.h"
#include "AmbientLighting.h"
#include "DirectionalLighting.h"
#include <vector>
using namespace std;
class Model
{
public:
	Model();
	~Model();
	// Accessors
	const vector<Polygon3D>& GetPolygons();
	const vector<Vertex>& GetVertices();
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;

	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);
	void ApplyTransformToLocalVertices(const Matrix& transform);
	void ApplyTransformToTransformedVertices(const Matrix& transform);
	void DehomogeniseVertices();
	void CalculateBackfaces(const Vertex& pos);
	void Sort();
	void CalculateAmbientLighting(AmbientLighting ambient);
	void CalculateLightingDirectional(vector<DirectionalLighting> dirLightingSources);
	int RGBValidator(int value);
	void SetColour(int red, int green, int blue);
	int GetColour(int index);
private:
	vector<Polygon3D> _polygons;
	vector<Vertex> _vertices;
	vector<Vertex> _transformedVertices;
	float ka_red = 1.0f;
	float ka_green = 1.0f;
	float ka_blue = 1.0f;
	float kd_red = 1.0f;
	float kd_green = 1.0f;
	float kd_blue = 1.0f;
	float ks_red = 1.0f;
	float ks_green = 1.0f;
	float ks_blue = 1.0f;

	int _colour[3] = { 0,0,0 };

};

