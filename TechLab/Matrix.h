#pragma once

struct FVector;
struct FMatrix
{
	float M[4][4]{};

	static FMatrix Identity() noexcept;
	FMatrix Transpose() const noexcept;
	FMatrix InverseAffine() const noexcept;

	static FMatrix TransformMatrix(FVector Trans) noexcept;
	static FMatrix ScaleMatrix(FVector Scale) noexcept;
	static FMatrix RotateMatrixX(float AngleRad) noexcept;
	static FMatrix RotateMatrixY(float AngleRad) noexcept;
	static FMatrix RotateMatrixZ(float AngleRad) noexcept;

	static FMatrix ViewMatrix(const FVector& Eye, const FVector& At, const FVector& Up) noexcept;
	static FMatrix ProjectionMatrix(float FovYRad, float AspectRatio, float NearZ, float FarZ) noexcept;

	FMatrix operator*(const FMatrix& Other) const noexcept;
	float(&operator[](int Row) noexcept)[4] { return M[Row]; }
	const float(&operator[](int Row) const noexcept)[4] { return M[Row]; }
};
