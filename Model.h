#pragma once
#include "Polygon3D.h"
#include "Vertex.h"
#include "Matrix.h"
#include <algorithm>
#include <vector>
#include "DirectionalLighting.h"
#include "AmbientLighting.h"
#include "PointLighting.h"

using namespace std;
class Model
{
public:
	Model();
	~Model();
	// Accessors To Get The Polygons & Vertices Lists (and size of lists) & Add Vertices And Polygons To The Them
	const vector<Polygon3D>& GetPolygons();
	const vector<Vertex>& GetVertices();
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);
	//Both of the methods below allow the vertices to be multiplied by a transformation matrix
	void ApplyTransformToLocalVertices(const Matrix& transform);
	void ApplyTransformToTransformedVertices(const Matrix& transform);

	void DehomogeniseVertices();
	void CalculateBackfaces(const Vertex& pos);
	void Sort();

	int RGBValidator(int value) const;
	void CalculateAmbientLighting(AmbientLighting ambient);
	void CalculateLightingDirectional(const vector<DirectionalLighting> dirLightingSources);
	void CalculateLightingPoint(vector<PointLighting> pointLightingSources);
	
private:
	vector<Polygon3D> _polygons;
	vector<Vertex> _vertices;
	vector<Vertex> _transformedVertices; // List to store transformed vertices
	float ka_red = 1.0f;
	float ka_green = 1.0f; 
	float ka_blue = 1.0f;
	float kd_red = 1.0f;
	float kd_green = 1.0f;
	float kd_blue = 1.0f;
	float ks_red = 1.0f;
	float ks_green = 1.0f;
	float ks_blue = 1.0f;
};

