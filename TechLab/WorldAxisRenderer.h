#pragma once
#include "VisualInterface.h"
#include "Core.h"
#include "MeshResource.h"
class FWorldAxisRenderer : public VisualInterface
{
public:
    FWorldAxisRenderer();
    ~FWorldAxisRenderer() override;
    void Init() override;
    void Update(const FVector& CameraPos) override;
    void Render() override;
};