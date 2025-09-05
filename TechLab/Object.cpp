#include "Object.h"

UObject::UObject()
{

}

UObject::~UObject()
{
}

bool UObject::IsA(UClass* Class) const
{
    UClass* MyClass = GetClass();
    while (MyClass != nullptr)
    {
        if (MyClass == Class)
        {
            return true;
        }
        MyClass = MyClass->GetParentClass();
    }
    return false;
}

void UObject::Tick(float DeltaTimes)
{
}

void UObject::Destroy()
{
    bShouldBeDestroyed = true;
}
