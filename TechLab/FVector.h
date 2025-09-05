#pragma once
#include <math.h>
struct FVector
{
	float x, y, z;
	FVector(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}

	FVector& operator+=(const FVector& other)
	{
		x = x + other.x;
		y = y + other.y;
		z = z + other.z;
		return *this;
	}

	float Length()
	{
		return sqrt(x * x + y * y + z * z);
	}

	FVector Norm()
	{
		float len = Length();
		return FVector(x / len, y / len, z / len);
	}
};

FVector operator+(const FVector& one, const FVector& other);
FVector operator-(const FVector& one, const FVector& other);
FVector operator*(const FVector& one, const FVector& other);
