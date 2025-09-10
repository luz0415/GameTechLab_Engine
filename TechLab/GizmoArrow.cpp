#include "GizmoArrow.h"
#include "Renderer.h"
#include "AABB.h"
#include "Shapes.h"

UGizmoArrow::UGizmoArrow()
{

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

void UGizmoArrow::SetAxis(EGizmoAxis InAxis)
{
    switch (InAxis)
    {
    case EGizmoAxis::X:
        SetBoundingVolume(new FAABB(Shapes::ArrowX_MeshData));
        SetMeshForPreciseRaycast(Shapes::ArrowX_MeshData); 
        SetName(FString("ArrowX"));
        break;
    case EGizmoAxis::Y:
        SetBoundingVolume(new FAABB(Shapes::ArrowY_MeshData));
        SetMeshForPreciseRaycast(Shapes::ArrowY_MeshData);
        SetName(FString("ArrowY"));
        break;
    case EGizmoAxis::Z:
        SetBoundingVolume(new FAABB(Shapes::ArrowZ_MeshData));
        SetMeshForPreciseRaycast(Shapes::ArrowZ_MeshData);
        SetName(FString("ArrowZ"));
        break;
    }
}

void UGizmoArrow::HandleDrag(int x, int y, int z)
{
    USceneComponent* Attach = GetAttachment();
    if (Attach != nullptr)
    {
        Attach->AddLocalRotation()
    }
}
