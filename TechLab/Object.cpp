#include "Object.h"
#include "EngineStatics.h"

UObject::UObject() : UUID(UEngineStatics::GenUUID()), InternalIndex(0)
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
