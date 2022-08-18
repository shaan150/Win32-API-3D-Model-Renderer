#include "AmbientLighting.h"

AmbientLighting::AmbientLighting()
{
}

AmbientLighting::AmbientLighting( int ka_red, int ka_green, int ka_blue)
{
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


