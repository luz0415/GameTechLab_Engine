#pragma once
#include "Object.h"
#include "Transform.h"
#include "Pickable.h"
#include "BoundingVolume.h"

class USceneComponent : public UObject, public IPickable
{
public:
    static UObject* StaticUObjectFactory()
    {
        return new USceneComponent();
    }

    static UClass* StaticClass()
    {
        static UClass Class(FString("USceneComponent"), StaticUObjectFactory, UObject::StaticClass());
        return &Class;

    }

    virtual UClass* GetClass() const override
    {
        return StaticClass();
    }

    USceneComponent();
    ~USceneComponent();

    virtual void Destroy() override;

// Local
public:   
    FVector GetRelativeLocation() const { return CachedRelativeTransform.GetLocation(); }
    FVector GetRelativeRotation() const { return CachedRelativeTransform.GetRotationAsEuler(); }
    FVector GetRelativeRotationRadians() const { return CachedRelativeTransform.GetRotationRadians(); }
    FVector GetRelativeScale() const { return CachedRelativeTransform.GetScale(); }

    void Translate(const FVector& InTranslation) { SetDirty();  CachedRelativeTransform.Translate(InTranslation); }
    void SetRelativeLocation(const FVector& InLocation);
    void SetRelativeRotation(const FVector& InRotation);
    void SetRelativeRotation(const FQuaternion& InRotation);
    void SetRelativeScale(const FVector& InScale);
    void AddLocalRotation(const FVector& InRotationDelta);
    void AddRelativeRotationX(const float& Degree) { SetDirty(); CachedRelativeTransform.AddRotationX(Degree); }
    void AddRelativeRotationY(const float& Degree) { SetDirty(); CachedRelativeTransform.AddRotationY(Degree); }
    void AddRelativeRotationZ(const float& Degree) { SetDirty(); CachedRelativeTransform.AddRotationZ(Degree); }

private:
    FMatrix CachedLocalMatrix;
    FTransform CachedRelativeTransform;

// World Transform
public:
    FMatrix& GetWorldMatrix();
    FVector GetWorldLocation() { return CachedWorldTransform.GetLocation(); }
    FVector GetWorldRotation() { return CachedWorldTransform.GetRotationAsEuler(); }
    FVector GetWorldRotationAsEuler() { return CachedWorldTransform.GetRotationAsEuler(); }
    FVector GetWorldScale() { return CachedWorldTransform.GetScale(); }

    void SetWorldLocation(const FVector& InLocation);
    void SetWorldRotation(const FVector& InRotation);
    void SetWorldRotation(const FQuaternion& InRotation);
    void SetWorldScale(const FVector& InScale);

private:
    FMatrix CachedWorldMatrix;
    FTransform CachedWorldTransform;


// World*v*Local
public:
    FMatrix GetFinalMatrix();
// Attachment
public:
    void SetAttachment(USceneComponent* ParentComponent);
    USceneComponent* GetAttachment() const { return Attachment; }
    void Detach();

private:
    void AddAttachedChild(USceneComponent* Child);
    void RemoveAttachedChild(USceneComponent* Child);
    void SetDirty();

    USceneComponent* Attachment = nullptr;
    TArray<USceneComponent*> Children;
    bool bIsDirty = true;
    bool bIsSelected = false;
// Picking
public:
    virtual void OnSelected() override { bIsSelected = true; };
    virtual void OnDeselected() override { bIsSelected = false; };

    bool Raycast(const FRay& Ray, float TMax, FHitRecord& OutHit);
    void SetBoundingVolume(IBoundingVolume* InBoundingVolume);

private:
    IBoundingVolume* BoundingVolume = nullptr;
};
