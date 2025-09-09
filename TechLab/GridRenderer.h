#pragma once
#pragma comment(lib, "d3d11")
#include <d3d11.h>

#include "Core.h"
#include "MeshResource.h"
#include "VisualInterface.h"

class FGridRenderer : public FVisualInterface 
{
public:
    FGridRenderer();
    ~FGridRenderer() override;
    void Init() override;
    void Update(const FVector& CameraPos) override;
    void SubmitProxy(const FMatrix& WorldMatrix = FMatrix::Identity()) override;

private:
    void RegenerateGrid(const FVector& CameraPos);

private:
    float GridSize = 1.0f;
    int32 GridRadius = 80;
    FVector LastCameraPos = FVector();
};

