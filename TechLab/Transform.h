#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"
class FTransform
{
public:
	FTransform(const FVector& InLocation = FVector(), const FVector& InRotation = FVector(), const FVector& InScale = FVector(1.0f, 1.0f, 1.0f));
	~FTransform();

	FTransform operator*(FTransform& Other);
	FTransform& operator=(const FTransform& Other);

	void SetScale(float X, float Y, float Z);
	void SetScale(const FVector& InScale);

	void SetRotationFromEuler(const FVector& InEulerRotation);
	void SetRotation(const FQuaternion& InQuat);

	void AddRotationX(float Degree);
	void AddRotationY(float Degree);
	void AddRotationZ(float Degree);

	void SetLocation(float X, float Y, float Z);
	void SetLocation(const FVector& InLocation);

	void Translate(float Dx, float Dy, float Dz);
	void Translate(const FVector&);

	const FVector& GetScale() const { return Scale; }
	const FVector& GetRotationAsEuler() const { return EulerRotation; }
	const FQuaternion& GetRotation() const { return Rotation; }
	FVector GetRotationRadians() const;
	const FVector& GetLocation() const { return Location; }

	const FMatrix& ToMatrixWithScale();
	
private:
	void UpdateMatrix();
	void MarkAsDirty() { bIsMatrixDirty = true; }

	FMatrix CachedMatrix;

	FVector Location{ 0,0,0 };
	FVector EulerRotation;
	FQuaternion Rotation;
	FVector Scale{ 1,1,1 };

	bool bIsMatrixDirty;
};
