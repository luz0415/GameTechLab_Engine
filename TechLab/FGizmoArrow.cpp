#include "FGizmoArrow.h"
#include "Renderer.h"
FGizmoArrow::FGizmoArrow()
{
}

FGizmoArrow::~FGizmoArrow()
{
}


void FGizmoArrow::SubmitProxy()
{
    URenderer* Renderer = URenderer::Get();
    FRenderProxy RenderProxy(FMatrix::ScaleMatrix(FVector(3.f,3.f,3.f))*GetAttachment()->GetWorldMatrix(), Renderer->GetMeshResource(FString(Name)));
    Renderer->SubmitProxy(RenderProxy);
}
