#include "Gizmo.h"
#include "Renderer.h"


UGizmo::UGizmo()
{
	SetWorldScale(FVector(3.f, 3.f, 3.f));
}

UGizmo::~UGizmo()
{
}

void UGizmo::SetName(const FString& InName)
{
	Name = InName;
}


/// <summary>
/// Virtual
/// </summary>
void UGizmo::SubmitProxy()
{
    URenderer* Renderer = URenderer::Get();
    FRenderProxy RenderProxy(GetWorldMatrix(), Renderer->GetMeshResource(FString(Name)));
    Renderer->SubmitProxy(RenderProxy);
}

void UGizmo::SetAxis(EGizmoAxis InAxis)
{
}

void UGizmo::HandleDrag(UCamera* Camera, const FVector& RayOrigin, const FVector& RayDirection)
{
}

FVector UGizmo::GetIntersectionWithMovementPlane(UCamera* Camera, FVector RayOrigin, FVector RayDirection)
{
    USceneComponent* Attach = GetAttachment();
    FVector PlaneOrigin = Attach->GetWorldLocation();
    FVector AttachToCamera = RayOrigin - PlaneOrigin;
    FVector TempVec = AttachToCamera.Cross(Direction);
    FVector PlaneNormal = TempVec.Cross(Direction);
    float numerator = ((PlaneOrigin - RayOrigin).Dot(PlaneNormal));//분자
    float denominator = (RayDirection.Dot(PlaneNormal));
    if (denominator < 0.000001f)
    {
        Invalid = true;
        return FVector();
    }
    //denom이 0에 가까우면 예외처리
    float DistanceToPlane = numerator / denominator;

    FVector IntersectionPoint = RayOrigin + (RayDirection * DistanceToPlane);
    return IntersectionPoint;
}

void UGizmo::OnDragStart(UCamera* Camera, const FVector& RayOrigin, const FVector& RayDirection)
{
    USceneComponent* Attach = GetAttachment();
    if (Attach)
    {
        InitialObjectPosition = Attach->GetWorldLocation();
        InitialHitPoint = GetIntersectionWithMovementPlane(Camera, RayOrigin, RayDirection);
    }
}
