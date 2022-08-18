#include "Triangle.h"
#include <windowsx.h>

Triangle::Triangle()
{
}

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3, int red, int green, int blue)
{
	SetVertex(0, v1);
	SetVertex(1, v2);
	SetVertex(2, v3);
	SetColours(red, green, blue);

}

Triangle::~Triangle()
{
}

void Triangle::SetVertex(int index, Vertex pos)
{
	_vertices[index] = pos;
}

Vertex Triangle::GetVertex(int index)
{
	return _vertices[index];
}

void Triangle::SetColours(int red, int green, int blue)
{
	_colours[0] = red;
	_colours[1] = green;
	_colours[2] = blue;
}

int Triangle::GetColor(int index)
{
	return _colours[index];
}

float Triangle::CrossProduct(Vertex v1, Vertex v2)
{
	return ((v1.GetY() * v2.GetZ()) - (v1.GetZ() * v2.GetY()),
		(v1.GetZ() * v2.GetX()) - (v1.GetX() * v2.GetZ()),
		(v1.GetX() * v2.GetY()) - (v1.GetY() * v2.GetX()));
}

void Triangle::SortByY()
{
    Vertex vTmp;

    if (_vertices[0].GetY() > _vertices[1].GetY())
    {
        vTmp = _vertices[0];
        _vertices[0] = _vertices[1];
        _vertices[1] = vTmp;
    }
    /* here v1.y <= v2.y */
    if (_vertices[0].GetY() > _vertices[2].GetY())
    {
        vTmp = _vertices[0];
        _vertices[0] = _vertices[2];
        _vertices[2] = vTmp;
    }
    /* here v1.y <= v2.y and v1.y <= v3.y so test v2 vs. v3 */
    if (_vertices[1].GetY() > _vertices[2].GetY())
    {
        vTmp = _vertices[1];
        _vertices[1] = _vertices[2];
        _vertices[2] = vTmp;
    }
}

void Triangle::DrawBarycentric(HDC dc)
{
    SortByY();
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(_colours[0], _colours[1], _colours[2]));
    HPEN hOldPen = SelectPen(dc, hPen);
    MoveToEx(dc, (int)_vertices[0].GetX(), (int)_vertices[0].GetY(), (LPPOINT)NULL);
    LineTo(dc, (int)_vertices[1].GetX(), (int)_vertices[1].GetY());
    LineTo(dc, (int)_vertices[2].GetX(), (int)_vertices[2].GetY());
    LineTo(dc, (int)_vertices[0].GetX(), (int)_vertices[0].GetY());
    SelectPen(dc, hOldPen);
    DeleteObject(hPen);

    float maxX = max(_vertices[0].GetX(), max(_vertices[1].GetX(), _vertices[2].GetX()));
    float minX = min(_vertices[0].GetX(), min(_vertices[1].GetX(), _vertices[2].GetX()));
    float maxY = max(_vertices[0].GetY(), max(_vertices[1].GetY(), _vertices[2].GetY()));
    float minY = min(_vertices[0].GetY(), min(_vertices[1].GetY(), _vertices[2].GetY()));
    float maxZ = max(_vertices[0].GetZ(), max(_vertices[1].GetZ(), _vertices[2].GetZ()));
    float minZ = min(_vertices[0].GetZ(), min(_vertices[1].GetZ(), _vertices[2].GetZ()));

    Vertex v1 = Vertex(_vertices[1].GetX() - _vertices[0].GetX(), _vertices[1].GetY() - _vertices[0].GetY(), _vertices[1].GetZ() - _vertices[0].GetZ());
    Vertex v2 = Vertex(_vertices[2].GetX() - _vertices[0].GetX(), _vertices[2].GetY() - _vertices[0].GetY(), _vertices[2].GetZ() - _vertices[0].GetZ());

    for (float x = minX; x <= maxX; x++)
    {
        for (float y = minY; y <= maxY; y++)
        {
            for (float z = minZ; z <= maxZ; z++)
            {
                Vertex q = Vertex(x - _vertices[0].GetX(), y - _vertices[0].GetY(), z - _vertices[0].GetZ());

                float s = (float)CrossProduct(q, v2) / CrossProduct(v1, v2);
                float t = (float)CrossProduct(v1, q) / CrossProduct(v1, v2);

                if ((s >= 0) && (t >= 0) && (s + t <= 1))
                {
                    SetPixel(dc, (int)x, (int)y, COLORREF(RGB(_colours[0], _colours[1], _colours[2])));
                }
            }
        }
    }
}
