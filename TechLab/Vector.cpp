#include "Vector.h"

FVector operator+(const FVector& one, const FVector& other)
{
	return FVector(one.x + other.x, one.y + other.y, one.z + other.z);
}

FVector operator-(const FVector& one, const FVector& other)
{
	return FVector(one.x - other.x, one.y - other.y, one.z - other.z);
}

FVector operator*(const FVector& one, const FVector& other)
{
	return FVector(one.x * other.x, one.y * other.y, one.z * other.z);
}
