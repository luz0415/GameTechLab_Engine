#pragma once
#include "PrimitiveComponent.h"

class UCubeComp : public UPrimitiveComponent
{
    // UObject Derived Class Must Declaration
public:
    static UObject* StaticUObjectFactory()
    {
        return new UCubeComp();
    }

    static UClass* StaticClass()
    {
        static UClass Class(FString("UCubeComp"), StaticUObjectFactory, UPrimitiveComponent::StaticClass());
        return &Class;
    }

    virtual UClass* GetClass() const
    {
        return StaticClass();
    }

public:
    UCubeComp();
};