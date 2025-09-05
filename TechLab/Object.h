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

// 
public:
    static UObject* StaticClassFactory()
    {
        return new UObject();
    }

    static UClass* StaticClass() 
    {
        static UClass Class(FString("UObject"), StaticClassFactory);
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
