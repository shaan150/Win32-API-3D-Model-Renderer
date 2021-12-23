#include "AmbientLighting.h"

AmbientLighting::AmbientLighting()
{
	_intensity = 0.0f;
}

AmbientLighting::AmbientLighting(float intensity, int ka_red, int ka_green, int ka_blue)
{
	SetIntensity(intensity);
	SetColour(ka_red, ka_green, ka_blue);
}

void AmbientLighting::SetColour(int ka_red, int ka_green, int ka_blue)
{
	_reflection[0] = ka_red;
	_reflection[1] = ka_green;
	_reflection[2] = ka_blue;
}

int AmbientLighting::GetColour(int index)
{
	return _reflection[index];
}

void AmbientLighting::SetIntensity(float intensity)
{
	_intensity = intensity;
}

float AmbientLighting::GetIntensity()
{
	return _intensity;
}

