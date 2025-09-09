#pragma once
#include "Core.h"
#include "Class.h"

class UObject;

class FObjectFactory
{
private:
    FObjectFactory() = default;
    ~FObjectFactory();
    FObjectFactory(const FObjectFactory&) = delete;
    FObjectFactory& operator=(const FObjectFactory&) = delete;

public:
    // Singleton
    static FObjectFactory* Get()
    {
        static FObjectFactory Instance;
        return &Instance;
    }

    UObject* ConstructObject(UClass* ClassToConstruct);
    template<typename T>
    T* ConstructObject()
    {
        return static_cast<T*>(ConstructObject(T::StaticClass()));
    }
    void ReleaseObject(UObject* InObject);

    const TArray<UObject*>& GetObjectArray() const { return GUObjectArray; }
    void ReleaseAllObjects();

    void TickObjects(float DeltaTimes);

private:

    TArray<UObject*> GUObjectArray;
};
