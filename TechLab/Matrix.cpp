#include "Matrix.h"
#include "Vector.h"
#include <cmath>

FMatrix FMatrix::Identity() noexcept
{
	FMatrix Output{};
	Output[0][0] = 1;	Output[1][1] = 1;
	Output[2][2] = 1;	Output[3][3] = 1;
	return Output;
}

FMatrix FMatrix::Transpose() const noexcept
{
	FMatrix Output{};
	for (int R = 0; R < 4; R++) {
		for (int C = 0; C < 4; C++) {
			Output[R][C] = M[C][R];
		}
	}
	return Output;
}

FMatrix FMatrix::InverseAffine() const noexcept
{
	FMatrix Output{};

	// R_inv = R^T
	Output[0][0] = M[0][0]; Output[0][1] = M[1][0]; Output[0][2] = M[2][0];
	Output[1][0] = M[0][1]; Output[1][1] = M[1][1]; Output[1][2] = M[2][1];
	Output[2][0] = M[0][2]; Output[2][1] = M[1][2]; Output[2][2] = M[2][2];

	const float Tx = M[3][0];
	const float Ty = M[3][1];
	const float Tz = M[3][2];

	// T_inv
	Output[3][0] = -(Tx * Output[0][0] + Ty * Output[1][0] + Tz * Output[2][0]);
	Output[3][1] = -(Tx * Output[0][1] + Ty * Output[1][1] + Tz * Output[2][1]);
	Output[3][2] = -(Tx * Output[0][2] + Ty * Output[1][2] + Tz * Output[2][2]);

	Output[3][3] = 1.0f;

	return Output;
}

FMatrix FMatrix::TransformMatrix(FVector Trans) noexcept
{
	FMatrix T = FMatrix::Identity();
	T[3][0] = Trans.X;
	T[3][1] = Trans.Y;
	T[3][2] = Trans.Z;
	return T;
}

FMatrix FMatrix::ScaleMatrix(FVector Scale) noexcept
{
	FMatrix S = FMatrix::Identity();
	S[0][0] = Scale.X;
	S[1][1] = Scale.Y;
	S[2][2] = Scale.Z;
	return S;
}

FMatrix FMatrix::RotateMatrixX(float AngleRad) noexcept
{
	FMatrix R = FMatrix::Identity();
	float c = std::cos(AngleRad);
	float s = std::sin(AngleRad);
	R[1][1] = c; R[1][2] = s;
	R[2][1] = -s; R[2][2] = c;
	return R;
}

FMatrix FMatrix::RotateMatrixY(float AngleRad) noexcept
{
	FMatrix R = FMatrix::Identity();
	float c = std::cos(AngleRad);
	float s = std::sin(AngleRad);
	R[0][0] = c; R[0][2] = s;
	R[2][0] = -s; R[2][2] = c;
	return R;
}

FMatrix FMatrix::RotateMatrixZ(float AngleRad) noexcept
{
	FMatrix R = FMatrix::Identity();
	float c = std::cos(AngleRad);
	float s = std::sin(AngleRad);
	R[0][0] = c; R[0][1] = s;
	R[1][0] = -s; R[1][1] = c;
	return R;
}

FMatrix FMatrix::ViewMatrix(const FVector& Eye, const FVector& At, const FVector& Up) noexcept
{
	FMatrix Output = FMatrix::Identity();
	FVector N = At - Eye;
	N.Normalize();
	FVector U = Up.Cross(N);
	U.Normalize();
	FVector V = N.Cross(U);
	V.Normalize();

	Output[0][0] = U.X; Output[1][0] = U.Y; Output[2][0] = U.Z;
	Output[0][1] = V.X; Output[1][1] = V.Y; Output[2][1] = V.Z;
	Output[0][2] = N.X; Output[1][2] = N.Y; Output[2][2] = N.Z;

	Output[3][0] = -U.Dot(Eye);
	Output[3][1] = -V.Dot(Eye);
	Output[3][2] = -N.Dot(Eye);

	return Output;
}

FMatrix FMatrix::ProjectionMatrix(float FovYRad, float AspectRatio, float NearZ, float FarZ) noexcept
{
	FMatrix P{};

	const float YScale = 1.0f / tanf(FovYRad / 2.0f);
	const float XScale = YScale / AspectRatio;

	P[0][0] = XScale;
	P[1][1] = YScale;
	P[2][2] = FarZ / (FarZ - NearZ);
	P[3][2] = -FarZ * NearZ / (FarZ - NearZ);
	P[2][3] = 1.0f;

	return P;
}

FMatrix FMatrix::operator*(const FMatrix& Other) const noexcept
{
	FMatrix Output{};

	for (int R = 0; R < 4; R++)
	{
		for (int C = 0; C < 4; C++)
		{
			for (int K = 0; K < 4; K++)
			{
				Output[R][C] += (*this)[R][K] * Other[K][C];
			}
		}
	}
	return Output;
}