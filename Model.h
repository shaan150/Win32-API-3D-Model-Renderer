#pragma once
#include "Polygon3D.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Vector3D.h"
#include "AmbientLighting.h"
#include "DirectionalLighting.h"
#include "PointLighting.h"
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
	int GetColour(int index);
	void SetColour(int red, int green, int blue);
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);
	void ApplyTransformToLocalVertices(const Matrix& transform);
	void ApplyTransformToTransformedVertices(const Matrix& transform);
	void DehomogeniseVertices();
	void CalculateBackfaces(const Vertex& pos);
	void Sort();
	void CalculateAmbientLighting(AmbientLighting ambient);
	void CalculateLightingDirectional(vector<DirectionalLighting> dirLightingSources);
	void CalculateLightingPoint(vector<PointLighting> pointLightingSources);
	int RGBValidator(int value);
	
private:
	vector<Polygon3D> _polygons;
	vector<Vertex> _vertices;
	vector<Vertex> _transformedVertices;
	int _colour[3] = { 0,0,0 };
	float ka_red = 0.2f;
	float ka_green = 0.2f;
	float ka_blue = 0.2f;
	float kd_red = 0.5f;
	float kd_green = 0.5f;
	float kd_blue = 0.5f;
	float ks_red = 0.5f;
	float ks_green = 0.5f;
	float ks_blue = 0.5f;
};

