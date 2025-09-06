#include "Vector.h"
#include <cassert>

float FVector::Dot(const FVector& Other) const noexcept
{
	return X * Other.X + Y * Other.Y + Z * Other.Z;
}

FVector FVector::Cross(const FVector& Other) const noexcept
{
	return FVector(
		Y * Other.Z - Z * Other.Y,
		Z * Other.X - X * Other.Z,
		X * Other.Y - Y * Other.X
	);
}

float FVector::Length() const noexcept
{
	return std::sqrt(X * X + Y * Y + Z * Z);
}

void FVector::Normalize() noexcept
{
	const float Mag = Length();
	if (Mag > KINDA_SMALL_NUMBER)
	{
		const float InvMag = 1.0f / Mag;
		X *= InvMag;
		Y *= InvMag;
		Z *= InvMag;
	}
}

FVector FVector::operator+(const FVector& Other) const noexcept
{
	return FVector(X + Other.X, Y + Other.Y, Z + Other.Z);
}

FVector FVector::operator-(const FVector& Other) const noexcept
{
	return FVector(X - Other.X, Y - Other.Y, Z - Other.Z);
}

FVector FVector::operator*(float Scale) const noexcept
{
	return FVector(X * Scale, Y * Scale, Z * Scale);
}

FVector FVector::operator/(float Scale) const noexcept
{
	assert(std::fabs(Scale) > KINDA_SMALL_NUMBER);
	const float InvScale = 1.0f / Scale;
	return FVector(X * InvScale, Y * InvScale, Z * InvScale);
}

FVector FVector::operator-() const noexcept
{
	return FVector(-X, -Y, -Z);
}

FVector& FVector::operator+=(const FVector& Other) noexcept
{
	X += Other.X;
	Y += Other.Y;
	Z += Other.Z;
	return *this;
}

FVector& FVector::operator-=(const FVector& Other) noexcept
{
	X -= Other.X;
	Y -= Other.Y;
	Z -= Other.Z;
	return *this;
}

FVector& FVector::operator*=(float Scale) noexcept
{
	X *= Scale;
	Y *= Scale;
	Z *= Scale;
	return *this;
}

FVector& FVector::operator/=(float Scale) noexcept
{
	assert(std::fabs(Scale) > KINDA_SMALL_NUMBER);
	const float InvScale = 1.0f / Scale;
	X *= InvScale;
	Y *= InvScale;
	Z *= InvScale;
	return *this;
}

bool FVector::operator==(const FVector& Other) const noexcept
{
	return (*this - Other).IsNearlyZero();
}

bool FVector::operator!=(const FVector& Other) const noexcept
{
	return !(*this == Other);
}

float FVector::LengthSquared() const noexcept
{
	return X * X + Y * Y + Z * Z;
}

FVector FVector::GetNormalized() const noexcept
{
	FVector Copy = *this;
	Copy.Normalize();
	return Copy;
}

bool FVector::IsNearlyZero(float Tolerance) const noexcept
{
	return LengthSquared() < (Tolerance * Tolerance);
}

float FVector::Dist(const FVector& V1, const FVector& V2) noexcept
{
	return (V2 - V1).Length();
}

float FVector::DistSquared(const FVector& V1, const FVector& V2) noexcept
{
	return (V2 - V1).LengthSquared();
}
