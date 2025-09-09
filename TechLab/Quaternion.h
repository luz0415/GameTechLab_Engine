#pragma once
#include <cmath>
#include "Vector.h"
#include "Matrix.h"
struct FQuaternion
{
	float w, x, y, z;

	FQuaternion() : x(0), y(0), z(0), w(1) {}
	FQuaternion(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) {}

	static FQuaternion Identity() { return FQuaternion(0.f, 0.f, 0.f, 1.f); }

	float LengthSquare() const { return x * x + y * y + z * z + w * w; }
	float Length() const { return std::sqrt(LengthSquare()); }

	void Normalize()
	{
		float L = Length();
		if (L > 0.0f) { x /= L;y /= L;z /= L;w /= L; }
		else { *this = Identity(); }
	}
	//ÄÓ·¹ º¹ÇÕ¼ö
	FQuaternion Conjugate() const { return FQuaternion(-x, -y, -z, w); }
	FQuaternion Inverse() const { return Conjugate(); }

	FQuaternion operator*(const FQuaternion& r) const {
		return FQuaternion(
			w * r.x + x * r.w + y * r.z - z * r.y,
			w * r.y - x * r.z + y * r.w + z * r.x,
			w * r.z + x * r.y - y * r.x + z * r.w,
			w * r.w - x * r.x - y * r.y - z * r.z
		);
	}

	static FQuaternion FromAxisAngleLH(const FVector& axis, float angleRad);
	static FQuaternion FromYawPitchRollLH(float yawY, float pitchX, float rollZ);
	FVector RotateVector(const FVector& v) const;
	FMatrix ToMatrix4x4_RowMajor_LH() const;
};