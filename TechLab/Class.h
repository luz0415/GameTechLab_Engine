#pragma once
#include "Core.h"

class UClass
{
public:
    UClass(const FString& InName, StaticUObjectFactory InConstructor, UClass* InParentClass = nullptr)
        : ClassName(InName), Constructor(InConstructor), ParentClass(InParentClass) {}

    inline FString GetClassName() const { return ClassName; }
    inline StaticUObjectFactory GetConstructor() const { return Constructor; }
    inline UClass* GetParentClass() const { return ParentClass; }

private:
    FString ClassName;
    StaticUObjectFactory Constructor;
    UClass* ParentClass;
};
