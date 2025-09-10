#include "GizmoArrow.h"
#include "Renderer.h"
#include "AABB.h"
#include "Shapes.h"

UGizmoArrow::UGizmoArrow()
{
    SetWorldScale(FVector(3.f, 3.f, 3.f));
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

void UGizmoArrow::SetArrowAxis(EGizmoArrowAxis InAxis)
{
    switch (InAxis)
    {
    case EGizmoArrowAxis::X:
        SetBoundingVolume(new FAABB(Shapes::ArrowX_MeshData));
        SetMeshForPreciseRaycast(Shapes::ArrowX_MeshData); 
        SetName(FString("ArrowX"));
        break;
    case EGizmoArrowAxis::Y:
        SetBoundingVolume(new FAABB(Shapes::ArrowY_MeshData));
        SetMeshForPreciseRaycast(Shapes::ArrowY_MeshData);
        SetName(FString("ArrowY"));
        break;
    case EGizmoArrowAxis::Z:
        SetBoundingVolume(new FAABB(Shapes::ArrowZ_MeshData));
        SetMeshForPreciseRaycast(Shapes::ArrowZ_MeshData);
        SetName(FString("ArrowZ"));
        break;
    }
}

void UGizmoArrow::SetName(const FString& InName)
{
    Name = InName;
}
