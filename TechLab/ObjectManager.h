#pragma once
#include "Core.h"
#include "Object.h"

class FObjectManager
{
public:
    // Singleton
    static FObjectManager* Get()
    {
        static FObjectManager Instance;
        return &Instance;
    }

    UObject* ConstructObject(UClass* ClassToConstruct);

    template<typename T>
    T* ConstructObject()
    {
        return static_cast<T*>(ConstructObject(T::StaticClass()));
    }

    void RegisterObject(UObject* InObject)
    {
        InObject->InternalIndex = GUObjectArray.size();
        GUObjectArray.push_back(InObject);
    }

    void ReleaseObject(UObject* InObject)
    {
        if (InObject && InObject->InternalIndex < GUObjectArray.size() && GUObjectArray[InObject->InternalIndex] == InObject)
        {
            GUObjectArray[InObject->InternalIndex] = nullptr;
        }
    }

    const TArray<UObject*>& GetObjectArray() const
    {
        return GUObjectArray;
    }

private:
    FObjectManager() = default;
    ~FObjectManager() = default;
    FObjectManager(const FObjectManager&) = delete;
    FObjectManager& operator=(const FObjectManager&) = delete;

    TArray<UObject*> GUObjectArray;
};