#pragma once
#include "PrimitiveComponent.h"

class USphereComp : public UPrimitiveComponent
{
    // UObject Derived Class Must Declaration
public:
    static UObject* StaticUObjectFactory()
    {
        return new USphereComp();
    }

    static UClass* StaticClass()
    {
        static UClass Class(FString("USphereComp"), StaticUObjectFactory, UPrimitiveComponent::StaticClass());
        return &Class;
    }

    virtual UClass* GetClass() const
    {
        return StaticClass();
    }

public:
    USphereComp();
};