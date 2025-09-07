#include "Transform.h"
#include "Math.h"

FTransform::FTransform(const FVector& InLocation, const FVector& InRotation, const FVector& InScale)
	: CachedMatrix(FMatrix::Identity()), Location(InLocation), Rotation(InRotation), Scale(InScale), bIsMatrixDirty(false)
{
}

FTransform::~FTransform()
{
}

FTransform FTransform::operator*(FTransform& Other)
{
	FTransform Result;
	const FMatrix& ThisMatrix = ToMatrixWithScale();
	const FMatrix& OtherMatrix = Other.ToMatrixWithScale();

	FMatrix ResultMatrix = ThisMatrix * OtherMatrix;

	// 예를 들어, FMatrix에 이러한 정보를 추출하는 메서드가 있다고 가정합니다.
	Result.SetScale(ResultMatrix.GetScale());
	Result.SetRotation(ResultMatrix.GetRotation());
	Result.SetLocation(ResultMatrix.GetTranslation());

	return Result;
}

FTransform& FTransform::operator=(const FTransform& Other)
{    
	if (this != &Other)
	{
		Scale = Other.Scale;
		Rotation = Other.Rotation;
		Location = Other.Location;

		bIsMatrixDirty = false;
	}

	return *this;
}

void FTransform::SetScale(float X, float Y, float Z)
{
	Scale = FVector(X, Y, Z);
	MarkAsDirty();
}

void FTransform::SetScale(const FVector& InScale)
{
	Scale = InScale;
	MarkAsDirty();
}

void FTransform::SetRotation(float X, float Y, float Z)
{
	Rotation = FVector(X, Y, Z);
	MarkAsDirty();
}

void FTransform::SetRotation(const FVector& InDegree)
{
	Rotation = InDegree;
	MarkAsDirty();
}

void FTransform::AddRotationX(float Degree)
{
	Rotation.X += Degree;
	MarkAsDirty();
}

void FTransform::AddRotationY(float Degree)
{
	Rotation.Y += Degree;
	MarkAsDirty();
}

void FTransform::AddRotationZ(float Degree)
{
	Rotation.Z += Degree;
	MarkAsDirty();
}

void FTransform::SetLocation(float X, float Y, float Z)
{
	Location = FVector(X, Y, Z);
	MarkAsDirty();
}

void FTransform::SetLocation(const FVector& InLocation)
{
	Location = InLocation;
	MarkAsDirty();
}

void FTransform::Translate(float Dx, float Dy, float Dz)
{
	Location += FVector(Dx, Dy, Dz);
	MarkAsDirty();
}

void FTransform::Translate(const FVector& InTranslation)
{
	Location += InTranslation;
	MarkAsDirty();
}

FVector FTransform::GetRotationRadians() const
{
	FVector Radian(DegreeToRadians(Rotation.X), DegreeToRadians(Rotation.Y), DegreeToRadians(Rotation.Z));
	return Radian;
}

const FMatrix& FTransform::ToMatrixWithScale()
{
	if (bIsMatrixDirty)
	{
		UpdateMatrix();
		bIsMatrixDirty = false;
	}
	return CachedMatrix;
}

void FTransform::UpdateMatrix()
{
	FMatrix S = FMatrix::ScaleMatrix(Scale);
	FVector Radian = GetRotationRadians();
	// Z > X > Y (Roll > Pitch > Yaw)
	FMatrix R = FMatrix::RotateMatrixZ(Radian.Z) * FMatrix::RotateMatrixX(Radian.X) * FMatrix::RotateMatrixY(Radian.Y);
	FMatrix T = FMatrix::TranslateMatrix(Location);

	CachedMatrix = S * R * T;
}
