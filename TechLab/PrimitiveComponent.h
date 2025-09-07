#pragma once
#include "SceneComponent.h"

class UPrimitiveComponent : public USceneComponent
{
// UObject Derived Class Must Declaration
public:
    static UClass* StaticClass()
    {
        static UClass Class(FString("UPrimitiveComponent"), nullptr, USceneComponent::StaticClass());
        return &Class;
    }

    virtual UClass* GetClass() const
    {
        return StaticClass();
    }

public:
	UPrimitiveComponent() {};
	virtual void Render() = 0;
};

