#include "GizmoArrow.h"
#include "Renderer.h"
#include "AABB.h"
#include "Shapes.h"

UGizmoArrow::UGizmoArrow()
{
    SetWorldScale(FVector(3.f, 3.f, 3.f));
    SetBoundingVolume(new FAABB(Shapes::ArrowY_MeshData));
    //SetBoundingVolume(new FAABB(FVector(-0.3f, 0.0f, -0.3f), FVector(0.3f, 10.0f, 0.3f)));
}

UGizmoArrow::~UGizmoArrow()
{
}

void UGizmoArrow::SubmitProxy()
{
    URenderer* Renderer = URenderer::Get();
    FRenderProxy RenderProxy(GetWorldMatrix(), Renderer->GetMeshResource(FString(Name)));
    Renderer->SubmitProxy(RenderProxy);
}

void UGizmoArrow::SetName(const FString& InName)
{
    Name = InName;
}
