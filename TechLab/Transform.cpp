#include "Transform.h"
#include "Math.h"
#include "Quaternion.h"
FTransform::FTransform(const FVector& InLocation, const FVector& InRotation, const FVector& InScale)
	: CachedMatrix(FMatrix::Identity()), Location(InLocation), Scale(InScale), bIsMatrixDirty(false)
{
	SetRotationFromEuler(InRotation);
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
	Result.SetRotationFromEuler(ResultMatrix.GetRotation());
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

void FTransform::SetRotationFromEuler(const FVector& InEulerRotation)
{
	EulerRotation = InEulerRotation;
	Rotation = FQuaternion::FromYawPitchRollLH(InEulerRotation.Y, InEulerRotation.X, InEulerRotation.Z);
	Rotation.Normalize();
	MarkAsDirty();
}

void FTransform::SetRotation(const FQuaternion& InQuat)
{
	Rotation = InQuat;
	Rotation.Normalize();
	EulerRotation = Rotation.ToYawPitchRoll();
	MarkAsDirty();
}
void FTransform::AddRotationX(float Degree)
{
	//Rotation.X += Degree;
	MarkAsDirty();
}

void FTransform::AddRotationY(float Degree)
{
	//Rotation.Y += Degree;
	MarkAsDirty();
}

void FTransform::AddRotationZ(float Degree)
{
	//Rotation.Z += Degree;
	MarkAsDirty();
}

void FTransform::AddLocationX(float X)
{
	Location.X += X;
	MarkAsDirty();
}

void FTransform::AddLocationY(float Y)
{
	Location.Y += Y;
	MarkAsDirty();
}

void FTransform::AddLocationZ(float Z)
{
	Location.Z += Z;
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
	FVector Radian(DegreeToRadians(Rotation.x), DegreeToRadians(Rotation.y), DegreeToRadians(Rotation.z));
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
	//FMatrix R = FMatrix::RotateMatrixZ(Radian.Z) * FMatrix::RotateMatrixX(Radian.X) * FMatrix::RotateMatrixY(Radian.Y);
	FMatrix R = Rotation.ToMatrix4x4_RowMajor_LH();
	FMatrix T = FMatrix::TranslateMatrix(Location);

	CachedMatrix = S * R * T;
}
