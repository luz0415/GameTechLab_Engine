#include "VisualInterface.h"
#include "Renderer.h"
VisualInterface::VisualInterface()
{
}

VisualInterface::~VisualInterface()
{
}

void VisualInterface::Render()
{
    URenderer* Renderer = URenderer::Get();
    FRenderProxy RenderProxy(FMatrix::Identity(), Renderer->GetMeshResource(FString(Name)));
    Renderer->SubmitProxy(RenderProxy);
}
