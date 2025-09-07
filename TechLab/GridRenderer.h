#pragma once
#pragma comment(lib, "d3d11")
#include <d3d11.h>

#include "Core.h"
#include "Vector.h"
#include "MeshResource.h"

class FGridRenderer
{
public:
    FGridRenderer();
    void Init();
    void Update(const FVector& CameraPos);
    void Render();

private:
    void RegenerateGrid(const FVector& CameraPos);

private:
    float GridSize = 1.0f;
    int32 GridRadius = 80;
    FVector LastCameraPos = FVector();

    TArray<FVertex> Vertices;
    TArray<uint32> Indices;
};

