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

    UCamera* GetCurrentCamera() { return CurrentCamera; }

private:
	TArray<UPrimitiveComponent*> Objects;
    UCamera* CurrentCamera = nullptr;
};