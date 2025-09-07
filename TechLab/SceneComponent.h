#pragma once
#include "Object.h"
#include "Transform.h"

class USceneComponent : public UObject
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

    void Translate(const FVector& InTranslation) { RelativeTransform.Translate(InTranslation); }
    void SetRelativeLocation(const FVector& InLocation) { RelativeTransform.SetLocation(InLocation); }
    void SetRelativeRotationX(const float& Degree) { RelativeTransform.AddRotationX(Degree); }
    void SetRelativeRotationY(const float& Degree) { RelativeTransform.AddRotationY(Degree); }
    void SetRelativeRotationZ(const float& Degree) { RelativeTransform.AddRotationZ(Degree); }
    void SetRelativeScale(const FVector& InScale) { RelativeTransform.SetScale(InScale); }

private:
    FTransform RelativeTransform;

// World Transform
public:
    FMatrix& GetWorldMatrix();
    FVector GetWorldLocation() { return GetWorldMatrix().GetTranslation(); }
    FVector GetWorldRotation() { return GetWorldMatrix().GetRotation(); }
    FVector GetWorldScale() { return GetWorldMatrix().GetScale(); }

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
};
