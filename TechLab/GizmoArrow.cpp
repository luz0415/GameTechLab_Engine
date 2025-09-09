#include "GizmoArrow.h"
#include "Renderer.h"
#include "Shapes.h"

UGizmoArrow::UGizmoArrow()
{
    SetWorldScale(FVector(3, 3, 3));
}

UGizmoArrow::~UGizmoArrow()
{
}


void UGizmoArrow::SubmitProxy()
{
    URenderer* Renderer = URenderer::Get();
    FRenderProxy RenderProxy(GetWorldMatrix(), Renderer->GetMeshResource(GetName()));
    Renderer->SubmitProxy(RenderProxy);
}

void UGizmoArrow::SetName(const FString& InName)
{
    Name = InName;
}
