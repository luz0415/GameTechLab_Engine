#pragma once
#include "Core.h"
#include "Class.h"
#include "ObjectFactory.h"

class UObject
{
public:
	UObject();
	virtual ~UObject();

    uint32 UUID;
    uint32 InternalIndex;

// UObject Derived Class Must Declaration
public:
    static UObject* StaticUObjectFactory()
    {
        return new UObject();
    }

    static UClass* StaticClass() 
    {
        static UClass Class(FString("UObject"), StaticUObjectFactory);
        return &Class;
    }

    virtual UClass* GetClass() const 
    {
        return StaticClass();
    }

public:
    bool IsA(UClass* Class) const;
    virtual void Tick(float DeltaTimes);
    void Destroy();

    bool ShouldBeDestroyed() const { return bShouldBeDestroyed; }

private:
    bool bShouldBeDestroyed = false;
};

// UObject Cast
template<typename T>
T* Cast(UObject* Object)
{
    if (!Object)
        return nullptr;

    if (Object->IsA(T::StaticClass()))
        return static_cast<T*>(Object);

    return nullptr;
}
