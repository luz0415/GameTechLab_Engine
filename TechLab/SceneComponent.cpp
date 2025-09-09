#include "SceneComponent.h"

USceneComponent::USceneComponent() : UObject()
{
}

USceneComponent::~USceneComponent()
{
}

FMatrix& USceneComponent::GetWorldMatrix()
{
	if (bIsDirty)
	{
		if (Attachment)
		{
			CachedWorldMatrix = Attachment->GetWorldMatrix() * RelativeTransform.ToMatrixWithScale();
		}
		else
		{
			CachedWorldMatrix = RelativeTransform.ToMatrixWithScale();
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

		RelativeTransform.SetLocation(LocalLocation);
		CachedWorldTransform.SetLocation(InLocation);
	}
	else
	{
		RelativeTransform.SetLocation(InLocation);
		CachedWorldTransform.SetLocation(InLocation);
	}
	bIsDirty = true;
}

void USceneComponent::SetWorldRotation(const FVector& InRotation)
{
	if (Attachment)
	{
		FVector ParentWorldRotation = Attachment->GetWorldRotation();
		FVector LocalRotation = InRotation - ParentWorldRotation;
		RelativeTransform.SetRotation(LocalRotation);
		CachedWorldTransform.SetLocation(InRotation);
	}
	else
	{
		RelativeTransform.SetRotation(InRotation);
		CachedWorldTransform.SetRotation(InRotation);
	}
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
		CachedWorldTransform.SetLocation(InScale);
		RelativeTransform.SetScale(LocalScale);
	}
	else
	{
		RelativeTransform.SetScale(InScale);
		CachedWorldTransform.SetScale(InScale);
	}
	bIsDirty = true;
}

void USceneComponent::SetAttachment(USceneComponent* ParentComponent)
{
	if (Attachment != ParentComponent)
	{
		Attachment = ParentComponent;
		Attachment->AddAttachedChild(this);
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
