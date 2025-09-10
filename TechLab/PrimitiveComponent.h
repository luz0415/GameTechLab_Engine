#pragma once
#include "SceneComponent.h"
#include "PrimitiveType.h"

class UPrimitiveComponent : public USceneComponent
{
// UObject Derived Class Must Declaration
public:
    static UObject* StaticUObjectFactory()
    {
        return new UPrimitiveComponent();
    }

    static UClass* StaticClass()
    {
        static UClass Class(FString("UPrimitiveComponent"), StaticUObjectFactory, USceneComponent::StaticClass());
        return &Class;
    }

    virtual UClass* GetClass() const
    {
        return StaticClass();
    }

public:
	UPrimitiveComponent();
	virtual void SubmitProxy();
    void SetMesh(struct FMeshResource* InMeshResource);
    EPrimitiveType GetPrimitiveType() const { return Type; }
    void SetPrimitiveType(EPrimitiveType InType);

private:
    EPrimitiveType Type = EPrimitiveType::Custom;
    FMeshResource* MeshResource = nullptr;
};
