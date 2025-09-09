#include "Math.h"

FVector DegreeToRadians(const FVector& Degree)
{
	return Degree * (PI / 180.0f);
}

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

FVector RadiansToDegree(const FVector& Radians)
{
	FVector result;
	result.X = RadiansToDegree(Radians.X);
	result.Y = RadiansToDegree(Radians.Y);
	result.Z = RadiansToDegree(Radians.Z);
	return result;
}
