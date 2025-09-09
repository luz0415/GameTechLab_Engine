#include "VisualInterface.h"
#include "Renderer.h"
FVisualInterface::FVisualInterface()
{
}

FVisualInterface::~FVisualInterface()
{
}

void FVisualInterface::SubmitProxy(const FMatrix& WorldMatrix)
{
    URenderer* Renderer = URenderer::Get();
    FRenderProxy RenderProxy(WorldMatrix, Renderer->GetMeshResource(FString(Name)));
    Renderer->SubmitProxy(RenderProxy);
}
