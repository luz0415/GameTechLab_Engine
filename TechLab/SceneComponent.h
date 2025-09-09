#pragma once
#include "Object.h"
#include "Transform.h"
#include "Pickable.h"
#include "Raycastable.h"

class USceneComponent : public UObject, public IPickable, public IRaycastable
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


// Relative Transform
public:    
    FVector GetRelativeLocation() const { return RelativeTransform.GetLocation(); }
    FVector GetRelativeRotation() const { return RelativeTransform.GetRotation(); }
    FVector GetRelativeRotationRadians() const { return RelativeTransform.GetRotationRadians(); }
    FVector GetRelativeScale() const { return RelativeTransform.GetScale(); }

    void Translate(const FVector& InTranslation) { SetDirty();  RelativeTransform.Translate(InTranslation); }
    void SetRelativeLocation(const FVector& InLocation) { SetDirty(); RelativeTransform.SetLocation(InLocation); }
    void SetRelativeRotation(const FVector& InRotation) { SetDirty(); RelativeTransform.SetRotation(InRotation); }
    void AddRelativeRotationX(const float& Degree) { SetDirty(); RelativeTransform.AddRotationX(Degree); }
    void AddRelativeRotationY(const float& Degree) { SetDirty(); RelativeTransform.AddRotationY(Degree); }
    void AddRelativeRotationZ(const float& Degree) { SetDirty(); RelativeTransform.AddRotationZ(Degree); }
    void SetRelativeScale(const FVector& InScale) { SetDirty(); RelativeTransform.SetScale(InScale); }

private:
    FTransform RelativeTransform;

// World Transform
public:
    FMatrix& GetWorldMatrix();
    FVector GetWorldLocation() { return CachedWorldTransform.GetLocation(); }
    FVector GetWorldRotation() { return CachedWorldTransform.GetRotation(); }
    FVector GetWorldScale() { return CachedWorldTransform.GetScale(); }

    void SetWorldLocation(const FVector& InLocation);
    void SetWorldRotation(const FVector& InRotation);
    void SetWorldScale(const FVector& InScale);

private:
    FMatrix CachedWorldMatrix;
    FTransform CachedWorldTransform;

// Attachment
public:
    void SetAttachment(USceneComponent* ParentComponent);
    USceneComponent* GetAttachment() const { return Attachment; }

private:
    void AddAttachedChild(USceneComponent* Child);
    void SetDirty();

    USceneComponent* Attachment = nullptr;
    TArray<USceneComponent*> Children;
    bool bIsDirty = true;
    bool bIsSelected = false;
// Picking
public:
    virtual void OnSelected() override { bIsSelected = true; };
    virtual void OnDeselected() override { bIsSelected = false; };
    virtual bool Raycast(const FRay& Ray, float TMax, FHitRecord& OutHit) override { return false; };
    bool RaycastLocal(const FRay& LocalRay, float TMax, FHitRecord& OutHit) override { return false; };
};
