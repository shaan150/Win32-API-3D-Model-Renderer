#pragma once
class AmbientLighting
{
public:
	AmbientLighting();
	AmbientLighting(int ka_red, int ka_green, int ka_blue);

	void SetColour(int ka_red, int ka_green, int ka_blue);
	int GetColour(int index);

private:
	int _reflection[3] = { 0, 0, 0 };
};
