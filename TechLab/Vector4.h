#pragma once
#include <cmath>

constexpr float KINDA_SMALL_NUMBER_V4 = 1.e-4f;

struct FVector;
struct FVector4
{
	float X, Y, Z, W;

	FVector4() : X(0.0f), Y(0.0f), Z(0.0f), W(0.0f) {}
	FVector4(float InX, float InY, float InZ, float InW) : X(InX), Y(InY), Z(InZ), W(InW) {}
	FVector4(const FVector& V3, float InW);

	float Dot(const FVector4& Other) const noexcept;

	FVector4 operator+(const FVector4& Other) const noexcept;
	FVector4 operator-(const FVector4& Other) const noexcept;
	FVector4 operator*(float Scale) const noexcept;
	FVector4 operator/(float Scale) const noexcept;
	FVector4 operator-() const noexcept;
	FVector4& operator+=(const FVector4& Other) noexcept;
	FVector4& operator-=(const FVector4& Other) noexcept;
	FVector4& operator*=(float Scale) noexcept;
	FVector4& operator/=(float Scale) noexcept;
	bool operator==(const FVector4& Other) const noexcept;
	bool operator!=(const FVector4& Other) const noexcept;

	float Length() const noexcept;
	float LengthSquared() const noexcept;
	void Normalize() noexcept;
	FVector4 GetNormalized() const noexcept;
	bool IsNearlyZero(float Tolerance = KINDA_SMALL_NUMBER_V4) const noexcept;
};