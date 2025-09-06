#pragma once
#include "Object.h"

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

public:
    // FVector GetWorldLocation() const;
    // FVector GetWorldRotation() const;
    // FVector GetWorldScale3D() const;

    // void SetWorldLocation(const FVector& InLocation) const;
    // void SetWorldRotation(const FVector& InRotation) const;
    // void SetWorldScale3D(const FVector& InScale3D) const;
    
    // FVector GetRelativeLocation() const;
    // FVector GetRelativeRotation() const;
    // FVector GetRelativeScale3D() const;
 
    // void SetRelativeLocation(const FVector& InLocation) const;
    // void SetRelativeRotation(const FVector& InRotation) const;
    // void SetRelativeScale3D(const FVector& InScale3D) const;

private:
    USceneComponent* Attachment = nullptr;

    // FVector Location;
    // FVector Rotation;
    // FVector Scale3D;
};
