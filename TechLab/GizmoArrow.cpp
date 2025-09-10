#include "GizmoArrow.h"
#include "Renderer.h"
#include "AABB.h"
#include "Shapes.h"
#include "TimeManager.h"
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
    if (Attach)
    {
        // 1. 현재 마우스 위치의 교차점을 구함
        FVector currentHitPoint = GetIntersectionWithMovementPlane(Camera, RayOrigin, RayDirection);
        if (Invalid == true)
        {
            Invalid = false;
            return;
        }

        // 2. 시작점과의 차이를 통해 '이동 벡터'를 계산
        FVector movementVector = currentHitPoint - InitialHitPoint;
        
        // 3. 이동 벡터를 해당 축으로 투영하여 최종 이동 거리를 구함
        FVector Rot = Attach->GetWorldRotationAsEuler();
        FVector Dir = FQuaternion::FromYawPitchRollLH(Rot.Y,Rot.X,Rot.Z).RotateVector(Direction);
        float distance = movementVector.Dot(Dir);

        // 4. 시작 위치에서 최종 이동 거리만큼 떨어진 곳으로 위치를 '설정'
        FVector newPosition = InitialObjectPosition + (Dir * distance);
        Attach->SetWorldLocation(newPosition);
    }
}
