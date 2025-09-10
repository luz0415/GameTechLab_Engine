#pragma once
#include <cmath>

constexpr float KINDA_SMALL_NUMBER = 1.e-4f;

struct FVector
{
	union {
		struct { float X, Y, Z; };
		float V[3];
	};

	FVector() : X(0.0f), Y(0.0f), Z(0.0f) {}
	FVector(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) {}

	float Dot(const FVector& Other) const noexcept;
	FVector Cross(const FVector& Other) const noexcept;
	float Length() const noexcept;
	void Normalize() noexcept;

	FVector operator+(const FVector& Other) const noexcept;
	FVector operator-(const FVector& Other) const noexcept;
	FVector operator*(float Scale) const noexcept;
	FVector operator/(float Scale) const noexcept;
	FVector operator-() const noexcept;
	FVector& operator+=(const FVector& Other) noexcept;
	FVector& operator-=(const FVector& Other) noexcept;
	FVector& operator*=(float Scale) noexcept;
	FVector& operator/=(float Scale) noexcept;
	bool operator==(const FVector& Other) const noexcept;
	bool operator!=(const FVector& Other) const noexcept;
	float& operator[](int i) { return V[i]; }
	float operator[](int i) const { return V[i]; }

	float Sign(float Num) noexcept;
	float LengthSquared() const noexcept;
	FVector GetNormalized() const noexcept;
	FVector GetAbs() const noexcept;
	bool IsNearlyZero(float Tolerance = KINDA_SMALL_NUMBER) const noexcept;
	static float Dist(const FVector& V1, const FVector& V2) noexcept;
	static float DistSquared(const FVector& V1, const FVector& V2) noexcept;
	static bool Invalid() { return true; }
};

inline FVector operator*(float Scale, const FVector& V) noexcept { return V * Scale; }

inline float Sign(float Num) noexcept
{
	return static_cast<float>((Num > 0.0f) - (Num < 0.0f));
}