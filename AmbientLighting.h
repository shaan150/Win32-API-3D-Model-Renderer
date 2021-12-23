#pragma once
class AmbientLighting
{
public:
	AmbientLighting();
	AmbientLighting(float intensity, int ka_red, int ka_green, int ka_blue);

	void SetColour(int ka_red, int ka_green, int ka_blue);
	int GetColour(int index);
	void SetIntensity(float intensity);
	float GetIntensity();

private:
	float _intensity;
	int _reflection[3] = { 0, 0, 0 };
};

