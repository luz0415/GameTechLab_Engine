#include "Matrix.h"
#include "Vector.h"
#include "Vector4.h"
#include <cmath>
#include "Math.h"
#include "Quaternion.h"


//-1 : 1 = left :right
//

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

static inline float Cofactor(const float M[4][4], int R0, int R1, int R2, int C0, int C1, int C2)
{
	const float A = M[R0][C0], B = M[R0][C1], C = M[R0][C2];
	const float D = M[R1][C0], E = M[R1][C1], F = M[R1][C2];
	const float G = M[R2][C0], H = M[R2][C1], I = M[R2][C2];
	return A * (E * I - F * H) - B * (D * I - F * G) + C * (D * H - E * G);
}

FMatrix FMatrix::Inverse() const noexcept
{
	FMatrix Output{};

	// Use the adjugate matrix formula.
	float C00 = Cofactor(M, 1, 2, 3, 1, 2, 3);
	float C01 = -Cofactor(M, 1, 2, 3, 0, 2, 3);
	float C02 = Cofactor(M, 1, 2, 3, 0, 1, 3);
	float C03 = -Cofactor(M, 1, 2, 3, 0, 1, 2);

	float Determinant = M[0][0] * C00 + M[0][1] * C01 + M[0][2] * C02 + M[0][3] * C03;
	if (std::fabs(Determinant) < 1e-8f) {
		return FMatrix{};
	}
	float InvDet = 1.0f / Determinant;

	Output.M[0][0] = C00 * InvDet;
	Output.M[1][0] = C01 * InvDet;
	Output.M[2][0] = C02 * InvDet;
	Output.M[3][0] = C03 * InvDet;

	Output.M[0][1] = -Cofactor(M, 0, 2, 3, 1, 2, 3) * InvDet;
	Output.M[1][1] = Cofactor(M, 0, 2, 3, 0, 2, 3) * InvDet;
	Output.M[2][1] = -Cofactor(M, 0, 2, 3, 0, 1, 3) * InvDet;
	Output.M[3][1] = Cofactor(M, 0, 2, 3, 0, 1, 2) * InvDet;

	Output.M[0][2] = Cofactor(M, 0, 1, 3, 1, 2, 3) * InvDet;
	Output.M[1][2] = -Cofactor(M, 0, 1, 3, 0, 2, 3) * InvDet;
	Output.M[2][2] = Cofactor(M, 0, 1, 3, 0, 1, 3) * InvDet;
	Output.M[3][2] = -Cofactor(M, 0, 1, 3, 0, 1, 2) * InvDet;

	Output.M[0][3] = -Cofactor(M, 0, 1, 2, 1, 2, 3) * InvDet;
	Output.M[1][3] = Cofactor(M, 0, 1, 2, 0, 2, 3) * InvDet;
	Output.M[2][3] = -Cofactor(M, 0, 1, 2, 0, 1, 3) * InvDet;
	Output.M[3][3] = Cofactor(M, 0, 1, 2, 0, 1, 2) * InvDet;

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

FVector FMatrix::TransformVector(const FVector& InVector) const noexcept
{
    FVector Out;
    Out.X = InVector.X * M[0][0] + InVector.Y * M[1][0] + InVector.Z * M[2][0];
    Out.Y = InVector.X * M[0][1] + InVector.Y * M[1][1] + InVector.Z * M[2][1];
    Out.Z = InVector.X * M[0][2] + InVector.Y * M[1][2] + InVector.Z * M[2][2];
    return Out;
}

FMatrix FMatrix::TranslateMatrix(FVector Trans) noexcept
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
	R[0][0] = c; R[0][2] = -s;
	R[2][0] = s; R[2][2] = c;
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

FVector FMatrix::GetTranslation() const noexcept
{
	return FVector(M[3][0], M[3][1], M[3][2]);
}

FVector FMatrix::GetScale() const noexcept
{
	FVector XAxis(M[0][0], M[1][0], M[2][0]);
	FVector YAxis(M[0][1], M[1][1], M[2][1]);
	FVector ZAxis(M[0][2], M[1][2], M[2][2]);

	return FVector(XAxis.Length(), YAxis.Length(), ZAxis.Length());
}

FVector FMatrix::GetRotation() const noexcept
{
	FVector Scale = GetScale();
	FMatrix RotationMatrix;
	RotationMatrix.M[0][0] = M[0][0] / Scale.X; RotationMatrix.M[1][0] = M[1][0] / Scale.X; RotationMatrix.M[2][0] = M[2][0] / Scale.X;
	RotationMatrix.M[0][1] = M[0][1] / Scale.Y; RotationMatrix.M[1][1] = M[1][1] / Scale.Y; RotationMatrix.M[2][1] = M[2][1] / Scale.Y;
	RotationMatrix.M[0][2] = M[0][2] / Scale.Z; RotationMatrix.M[1][2] = M[1][2] / Scale.Z; RotationMatrix.M[2][2] = M[2][2] / Scale.Z;

	float Pitch, Yaw, Roll;

	if (RotationMatrix.M[2][1] < 1.0f)
	{
		if (RotationMatrix.M[2][1] > -1.0f)
		{
			Pitch = asinf(RotationMatrix.M[2][1]);  // M[2][1] = sin(x)

			// M[2][0] = cos(x)sin(y), M[2][2] = cos(x)cos(y)
			Yaw = atan2f(RotationMatrix.M[2][0], RotationMatrix.M[2][2]);  // atan2(sin(y), cos(y))

			// M[0][1] = sin(z)cos(x), M[1][1] = cos(z)cos(x)
			Roll = atan2f(RotationMatrix.M[0][1], RotationMatrix.M[1][1]);  // atan2(sin(z), cos(z))
		}
		else // Pitch = -90 (Gimbal Lock)
		{
			Pitch = -PI / 2;

			// M[0][0] = cos(z)cos(y) + sin(z)sin(x)sin(y) = cos(z-y) (when sin(x) = -1)
			// M[1][0] = -sin(z)cos(y) + cos(z)sin(x)sin(y) = sin(z-y) (when sin(x) = -1)
			Yaw = atan2f(-RotationMatrix.M[1][0], RotationMatrix.M[0][0]);  // atan2(-sin(z-y), cos(z-y))
			Roll = 0.0f;  // 임의로 0 설정 (Gimbal Lock)
		}
	}
	else // Pitch = 90 (Gimbal Lock)
	{
		Pitch = PI / 2;

		// M[0][0] = cos(z)cos(y) + sin(z)sin(x)sin(y) = cos(z+y) (when sin(x) = 1)
		// M[1][0] = -sin(z)cos(y) + cos(z)sin(x)sin(y) = sin(z+y) (when sin(x) = 1)
		Yaw = atan2f(RotationMatrix.M[1][0], RotationMatrix.M[0][0]);  // atan2(sin(z+y), cos(z+y))
		Roll = 0.0f;  // 임의로 0 설정 (Gimbal Lock)
	}

	return FVector(Pitch, Yaw, Roll);
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

FMatrix FMatrix::PrespectiveProjectionMatrix(float FovYRad, float AspectRatio, float NearZ, float FarZ) noexcept
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

FMatrix FMatrix::OrthographicProjectionMatrix(float Left, float Right, float Bottom, float Top, float NearZ, float FarZ) noexcept
{
	FMatrix P{};

	P[0][0] = 2.0f / (Right - Left);
	P[1][1] = 2.0f / (Top - Bottom);
	P[2][2] = 1.0f / (FarZ - NearZ);

	P[3][0] = -(Right + Left) / (Right - Left);
	P[3][1] = -(Top + Bottom) / (Top - Bottom);
	P[3][2] = -NearZ / (FarZ - NearZ);
	P[3][3] = 1.0f;

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

FVector4 FMatrix::operator*(const FVector4& Other) const noexcept
{
	FVector4 Output;
	Output.X = M[0][0] * Other.X + M[1][0] * Other.Y + M[2][0] * Other.Z + M[3][0] * Other.W;
	Output.Y = M[0][1] * Other.X + M[1][1] * Other.Y + M[2][1] * Other.Z + M[3][1] * Other.W;
	Output.Z = M[0][2] * Other.X + M[1][2] * Other.Y + M[2][2] * Other.Z + M[3][2] * Other.W;
	Output.W = M[0][3] * Other.X + M[1][3] * Other.Y + M[2][3] * Other.Z + M[3][3] * Other.W;
	return Output;
}

FVector4 operator*(const FVector4& v, const FMatrix& M) noexcept {
	return FVector4(
		v.X * M[0][0] + v.Y * M[1][0] + v.Z * M[2][0] + v.W * M[3][0],
		v.X * M[0][1] + v.Y * M[1][1] + v.Z * M[2][1] + v.W * M[3][1],
		v.X * M[0][2] + v.Y * M[1][2] + v.Z * M[2][2] + v.W * M[3][2],
		v.X * M[0][3] + v.Y * M[1][3] + v.Z * M[2][3] + v.W * M[3][3]
	);
}

