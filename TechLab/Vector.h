#pragma once
#include <math.h>
struct FVector
{
	float x, y, z;
	FVector() : FVector(0, 0, 0) {}
	FVector(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}

	FVector& operator+=(const FVector& other)
	{
		x = x + other.x;
		y = y + other.y;
		z = z + other.z;
		return *this;
	}

	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	void Normalize()
	{
		float len = Length();
		x = x / len;
		y = y / len;
		z = z / len;
	}

	float Dot(const FVector& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}
	FVector Cross(const FVector& other) const
	{
		return FVector(
			(y * other.z) - (z * other.y),
			(z * other.x) - (x * other.z),
			(x * other.y) - (y * other.x)
		);
	}
};

FVector operator+(const FVector& one, const FVector& other);
FVector operator-(const FVector& one, const FVector& other);
FVector operator*(const FVector& one, const FVector& other);
