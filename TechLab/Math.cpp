#include "Math.h"

float RadiansToDegree(float Radians)
{
	float Degree = Radians * (180.0f / PI);
	while (Degree <= -360)
	{
		Degree += 360;
	}
	while (Degree >= 360)
	{
		Degree -= 360;
	}
	return Degree;
}
