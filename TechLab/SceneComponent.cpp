#include "SceneComponent.h"
#include "Quaternion.h"
USceneComponent::USceneComponent() : UObject()
{
}

USceneComponent::~USceneComponent()
{
}

void USceneComponent::SetRelativeLocation(const FVector& InLocation)
{
	SetDirty(); 
	CachedRelativeTransform.SetLocation(InLocation);
}

void USceneComponent::SetRelativeRotation(const FVector& InRotation)
{
	SetDirty();
	CachedRelativeTransform.SetRotationFromEuler(InRotation);
}

void USceneComponent::SetRelativeRotation(const FQuaternion& InRotation)
{
	SetDirty();
	CachedRelativeTransform.SetRotation(InRotation);
}

void USceneComponent::SetRelativeScale(const FVector& InScale)
{
	SetDirty(); 
	CachedRelativeTransform.SetScale(InScale);
}

void USceneComponent::AddLocalRotation(const FVector& InRotationDelta)
{
	FQuaternion DeltaQuat = FQuaternion::FromYawPitchRollLH(
		InRotationDelta.Y, // Yaw
		InRotationDelta.X, // Pitch
		InRotationDelta.Z  // Roll
	);

	// 2. 현재 '상대 회전 쿼터니언'에 '변화량 쿼터니언'을 곱하여 회전을 누적시킵니다.
	//    이것이 바로 짐벌락 없는 회전 누적의 핵심입니다.
	//    순서가 매우 중요합니다! (현재 상태 * 변화량) 이어야 로컬 축 기준으로 회전합니다.
	CachedRelativeTransform.SetRotation(CachedRelativeTransform.GetRotation() * DeltaQuat);

	// 3. 변환 정보가 변경되었음을 시스템에 알립니다.
	//    이것으로 다음 GetWorldMatrix() 호출 시 월드 행렬이 새로 계산됩니다.
	SetDirty();
}

FMatrix& USceneComponent::GetWorldMatrix()
{
	if (bIsDirty)
	{
		if (Attachment)
		{
			CachedWorldMatrix = Attachment->GetWorldMatrix() * CachedRelativeTransform.ToMatrixWithScale();
		}
		else
		{
			CachedWorldMatrix = CachedRelativeTransform.ToMatrixWithScale();
		}
		bIsDirty = false;
	}
	return CachedWorldMatrix;
}

void USceneComponent::SetWorldLocation(const FVector& InLocation)
{
	if (Attachment)
	{
		FMatrix ParentWorldMatrix = Attachment->GetWorldMatrix();
		FMatrix InverseParentMatrix = ParentWorldMatrix.InverseAffine();

		FVector LocalLocation = InLocation - FVector(ParentWorldMatrix[3][0], ParentWorldMatrix[3][1], ParentWorldMatrix[3][2]);
		LocalLocation = InverseParentMatrix.TransformVector(LocalLocation);

		CachedRelativeTransform.SetLocation(LocalLocation);
		CachedWorldTransform.SetLocation(InLocation);
	}
	else
	{
		CachedRelativeTransform.SetLocation(InLocation);
		CachedWorldTransform.SetLocation(InLocation);
	}
	SetDirty();
}

void USceneComponent::SetWorldRotation(const FVector& InRotation)
{
	if (Attachment)
	{
		FVector ParentWorldRotationVec = Attachment->GetWorldRotation();
		FQuaternion ParentWorldQuat = FQuaternion::FromYawPitchRollLH(ParentWorldRotationVec.Y, ParentWorldRotationVec.X, ParentWorldRotationVec.Z);

		FQuaternion TargetWorldQuat = FQuaternion::FromYawPitchRollLH(InRotation.Y, InRotation.X, InRotation.Z);

		// 상대 회전 = 부모의 역회전 * 목표 월드 회전
		FQuaternion RelativeQuat = ParentWorldQuat.Inverse() * TargetWorldQuat;

		CachedRelativeTransform.SetRotation(RelativeQuat);
	}
	else
	{
		CachedRelativeTransform.SetRotationFromEuler(InRotation);
		
	}
	FQuaternion TargetWorldQuat = FQuaternion::FromYawPitchRollLH(InRotation.Y, InRotation.X, InRotation.Z);
	CachedWorldTransform.SetRotation(TargetWorldQuat);

	bIsDirty = true;
}

void USceneComponent::SetWorldRotation(const FQuaternion& InRotation)
{
	CachedRelativeTransform.SetRotation(InRotation);
	bIsDirty = true;
}

void USceneComponent::SetWorldScale(const FVector& InScale)
{
	if (Attachment)
	{
		FVector ParentWorldScale = Attachment->GetWorldScale();
		FVector LocalScale = FVector(
			ParentWorldScale.X != 0 ? InScale.X / ParentWorldScale.X : InScale.X,
			ParentWorldScale.Y != 0 ? InScale.Y / ParentWorldScale.Y : InScale.Y,
			ParentWorldScale.Z != 0 ? InScale.Z / ParentWorldScale.Z : InScale.Z
		);
		//CachedWorldTransform.SetLocation(InScale);
		CachedRelativeTransform.SetScale(LocalScale);
	}
	else
	{
		CachedRelativeTransform.SetScale(InScale);
		CachedWorldTransform.SetScale(InScale);
	}
	SetDirty();
}

FMatrix USceneComponent::GetFinalMatrix()
{
	return FMatrix();
}

void USceneComponent::SetAttachment(USceneComponent* ParentComponent)
{
	if (Attachment != ParentComponent)
	{
		FVector WorldLocation = GetWorldLocation();
		FVector WorldRotation = GetWorldRotation();
		FVector WorldScale = GetWorldScale();

		Attachment = ParentComponent;
		Attachment->AddAttachedChild(this);

		SetWorldLocation(WorldLocation);
		SetWorldRotation(WorldRotation);
		SetWorldScale(WorldScale);

		SetDirty();
	}
}

void USceneComponent::AddAttachedChild(USceneComponent* Child)
{
	Children.push_back(Child);
}

void USceneComponent::SetDirty()
{
	bIsDirty = true;
	for (USceneComponent* Child : Children)
	{
		Child->SetDirty();
	}
}

bool USceneComponent::Raycast(const FRay& Ray, float TMax, FHitRecord& OutHit)
{
	if (BoundingVolume)
	{
		return BoundingVolume->RaycastHit(Ray, TMax, OutHit);
	}
	return false;
}

void USceneComponent::SetBoundingVolume(IBoundingVolume* InBoundingVolume)
{
	if (BoundingVolume)
	{
		delete BoundingVolume;
	}
	BoundingVolume = InBoundingVolume;
}