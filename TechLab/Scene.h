#pragma once

#include "Core.h"
#include "Vector.h"
#include "SphereComp.h"
#include "CubeComp.h"
#include "Camera.h"

struct FPrimitiveData
{
    int UUID;

    FVector Location;
    FVector Rotation;
    FVector Scale;

    string Type;
};

struct FSceneData
{
    int Version;
    int NextUUID;

    TArray<FPrimitiveData> PrimDatas;
};

class UScene : public UObject
{
    // UObject Derived Class Must Declaration
public:
    static UObject* StaticUObjectFactory()
    {
        return new UScene();
    }

    static UClass* StaticClass()
    {
        static UClass Class(FString("UScene"), StaticUObjectFactory, UObject::StaticClass());
        return &Class;
    }

    virtual UClass* GetClass() const
    {
        return StaticClass();
    }

public:
	UScene();
	~UScene();

    UPrimitiveComponent* PrimToPrimComp(const FPrimitiveData& primitive);
    void CopyPrimComp(const FSceneData& sceneData);
    void Render();

    void InitCamera();
    UPrimitiveComponent* SpawnActor(const FString Type);

    UCamera* GetCurrentCamera() { return CurrentCamera; }

    FSceneData MakeSceneData();

private:
	TArray<UPrimitiveComponent*> Primitives;
    UCamera* CurrentCamera = nullptr;
};