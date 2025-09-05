#pragma once
#include "Core.h"

class UClass
{
public:
    UClass(const FString& InName, StaticClassFactory InConstructor, UClass* InParentClass = nullptr)
        : ClassName(InName), Constructor(InConstructor), ParentClass(InParentClass) {}

    inline FString GetClassName() const { return ClassName; }
    inline StaticClassFactory GetConstructor() const { return Constructor; }
    inline UClass* GetParentClass() const { return ParentClass; }

private:
    FString ClassName;
    StaticClassFactory Constructor;
    UClass* ParentClass;
};
