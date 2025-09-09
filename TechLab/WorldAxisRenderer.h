#pragma once
#include "VisualInterface.h"
#include "Core.h"
#include "MeshResource.h"
class FWorldAxisRenderer : public FVisualInterface
{
public:
    FWorldAxisRenderer();
    ~FWorldAxisRenderer() override;
    void Init() override;
    void Update(const FVector& CameraPos) override;
    void SubmitProxy(const FMatrix& WorldMatrix = FMatrix::Identity()) override;
};