#pragma once

#include "Vector.h"

#include "SphereComp.h"
#include "CubeComp.h"

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
	~UScene();

    UPrimitiveComponent* PrimToPrimComp(const Primitive& primitive);

private:
	TArray<USceneComponent*> Objects;
};