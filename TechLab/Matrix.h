#pragma once

struct FVector;
struct FVector4;
struct FMatrix
{
	float M[4][4]{};

	static FMatrix Identity() noexcept;
	FMatrix Transpose() const noexcept;
	FMatrix Inverse() const noexcept;
	FMatrix InverseAffine() const noexcept;
	FVector TransformVector(const FVector& InVector) const noexcept;

	static FMatrix TranslateMatrix(FVector Trans) noexcept;
	static FMatrix ScaleMatrix(FVector Scale) noexcept;
	static FMatrix RotateMatrixX(float AngleRad) noexcept;
	static FMatrix RotateMatrixY(float AngleRad) noexcept;
	static FMatrix RotateMatrixZ(float AngleRad) noexcept;

	FVector GetTranslation() const noexcept;
	FVector GetScale() const noexcept;
	FVector GetRotation() const noexcept;

	static FMatrix ViewMatrix(const FVector& Eye, const FVector& At, const FVector& Up) noexcept;
	static FMatrix PrespectiveProjectionMatrix(float FovYRad, float AspectRatio, float NearZ, float FarZ) noexcept;

	static FMatrix OrthographicProjectionMatrix(float Height, float AspectRatio, float NearZ, float FarZ) noexcept;

	FMatrix operator*(const FMatrix& Other) const noexcept;
	FVector4 operator*(const FVector4& Other) const noexcept;

	//bool Decompose(FVector& OutScale, FQuaternion& OutRotation, FVector& OutTranslation) const;

	float(&operator[](int Row) noexcept)[4] { return M[Row]; }
	const float(&operator[](int Row) const noexcept)[4] { return M[Row]; }
};
FVector4 operator*(const FVector4& v, const FMatrix& M) noexcept;