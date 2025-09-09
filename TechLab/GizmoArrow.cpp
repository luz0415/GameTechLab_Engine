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

void UGizmoArrow::SetAABB(EGizmoArrowAxis InAxis)
{
    switch (InAxis)
    {
    case EGizmoArrowAxis::X:
        SetBoundingVolume(new FAABB(Shapes::ArrowX_MeshData));
        break;
    case EGizmoArrowAxis::Y:
        SetBoundingVolume(new FAABB(Shapes::ArrowY_MeshData));
        break;
    case EGizmoArrowAxis::Z:
        SetBoundingVolume(new FAABB(Shapes::ArrowZ_MeshData));
        break;
    }
}