#pragma once

#include "Vector.h"

#include "SphereComp.h"
#include "CubeComp.h"
#include "Camera.h"

struct Primitive
{
    int UUID;

    FVector Location;
    FVector Rotation;
    FVector Scale;

    string Type;
};

struct USceneData
{
    int Version;
    int NextUUID;

    TArray<Primitive> PrimArray;
};

class UScene
{
public:
	UScene();
    UScene(const USceneData& sceneData);
    UScene(const std::string&);
	~UScene();

    UPrimitiveComponent* PrimToPrimComp(const Primitive& primitive);
    void CopyPrimComp(const USceneData& sceneData);
    void Render();

    void InitCamera();
    UPrimitiveComponent* SpawnActor(const string Type);

    UCamera* GetCurrentCamera() { return CurrentCamera; }

    USceneData MakeSceneData();

private:
	TArray<UPrimitiveComponent*> Objects;
    UCamera* CurrentCamera = nullptr;
};