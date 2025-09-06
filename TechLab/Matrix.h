#pragma once

struct FVector;

struct FMatrix
{
	float M[4][4]{};

	//FMatrix();

	static const FMatrix Identity();
	static const FMatrix TransformMatrix(FVector trans);
	static const FMatrix ScaleMatrix(FVector trans);
	static const FMatrix RotateMatrixX(float angle);
	static const FMatrix RotateMatrixY(float angle);
	static const FMatrix RotateMatrixZ(float angle);
	static const FMatrix ViewMatrix(const FVector& eye, const FVector& at, const FVector& up);
	static const FMatrix ProjectionMatrix(float floatAngleY, float aspectRatio, float nearZ, float farZ);
	FMatrix operator*(const FMatrix& Other) const;
	float(&operator[](unsigned row))[4];
};
