#include "GizmoArrow.h"
#include "Renderer.h"
#include "AABB.h"
#include "Shapes.h"
#include "Camera.h"
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
        Direction = FVector(1.f, 0.f, 0.f);
        break;
    case EGizmoAxis::Y:
        SetBoundingVolume(new FAABB(Shapes::ArrowY_MeshData));
        SetMeshForPreciseRaycast(Shapes::ArrowY_MeshData);
        SetName(FString("ArrowY"));
        Direction = FVector(0.f, 1.f, 0.f);
        break;
    case EGizmoAxis::Z:
        SetBoundingVolume(new FAABB(Shapes::ArrowZ_MeshData));
        SetMeshForPreciseRaycast(Shapes::ArrowZ_MeshData);
        SetName(FString("ArrowZ"));
        Direction = FVector(0.f, 0.f, 1.f);
        break;
    }
}

void UGizmoArrow::HandleDrag(UCamera* Camera, const FVector& RayOrigin, const FVector& RayDirection)
{
    USceneComponent* Attach = GetAttachment();
    if (Attach != nullptr)
    {
        if (Name == "ArrowX")
        {
            Attach->AddRelativeLocationX(Direction.Dot(GetIntersectionWithMovementPlane(Camera, RayOrigin, RayDirection)));
        }
        else if (Name == "ArrowY")
        {
            Attach->AddRelativeLocationY(Direction.Dot(GetIntersectionWithMovementPlane(Camera, RayOrigin, RayDirection)));
        }
        else if (Name == "ArrowZ")
        {
            Attach->AddRelativeLocationZ(Direction.Dot(GetIntersectionWithMovementPlane(Camera, RayOrigin, RayDirection)));
        }
    }
}

FVector UGizmoArrow::GetIntersectionWithMovementPlane(UCamera* Camera, FVector RayOrigin,FVector RayDirection)
{

    USceneComponent* Attach = GetAttachment();
    FVector PlaneOrigin = Attach->GetWorldLocation();
    FVector AttachToCamera = RayOrigin - PlaneOrigin;
    FVector TempVec = AttachToCamera.Cross(Direction);
    FVector PlaneNormal = TempVec.Cross(Direction);
    float numerator = ((PlaneOrigin - RayOrigin).Dot(PlaneNormal));//분자
    float denominator = (RayDirection.Dot(PlaneNormal));
    //denom이 0에 가까우면 예외처리
    float DistanceToPlane = numerator / denominator;

    FVector IntersectionPoint = RayOrigin + (RayDirection * DistanceToPlane);
    return IntersectionPoint;
}