#include "GizmoArrow.h"
#include "Renderer.h"

UGizmoArrow::UGizmoArrow()
{
}

UGizmoArrow::~UGizmoArrow()
{
}


void UGizmoArrow::SubmitProxy()
{
    URenderer* Renderer = URenderer::Get();
    FRenderProxy RenderProxy(FMatrix::ScaleMatrix(FVector(3.f,3.f,3.f))*GetAttachment()->GetWorldMatrix(), Renderer->GetMeshResource(FString(Name)));
    Renderer->SubmitProxy(RenderProxy);
}
