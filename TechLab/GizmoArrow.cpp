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

//void UGizmoArrow::SubmitProxy()
//{
//    URenderer* Renderer = URenderer::Get();
//    FRenderProxy RenderProxy(GetWorldMatrix(), Renderer->GetMeshResource(FString(Name)));
//    Renderer->SubmitProxy(RenderProxy);
//}

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
        // 1. 현재 마우스 위치의 교차점을 구합니다.
        FVector currentHitPoint = GetIntersectionWithMovementPlane(Camera, RayOrigin, RayDirection);
        if (Invalid == true)
        {
            Invalid = false;
            return;
        }

        // 2. 드래그 시작점과의 차이를 통해 '총 이동 벡터'를 계산합니다.
        FVector movementVector = currentHitPoint - InitialHitPoint;

        // 3. (핵심 수정) 쿼터니언을 사용해 월드 방향 벡터를 직접 계산합니다.
        FQuaternion worldRotation = Attach->GetWorldRotationAsQuaternion();

        // 'Direction'은 이 기즈모 화살표의 로컬 방향입니다.
        // 예를 들어, X축 화살표라면 FVector(1, 0, 0)가 됩니다.
        FVector worldDirection = worldRotation.RotateVector(Direction);
        worldDirection.Normalize(); // 정확한 방향 벡터를 위해 정규화합니다.

        // 4. 총 이동 벡터를 현재 객체의 축(worldDirection)으로 투영하여
        //    그 축 방향으로의 순수 이동 거리를 구합니다.
        float distance = movementVector.Dot(worldDirection);

        // 5. 드래그 시작 위치에서 계산된 방향과 거리만큼 떨어진 곳으로 위치를 '설정'합니다.
        FVector newPosition = InitialObjectPosition + (worldDirection * distance);
        Attach->SetWorldLocation(newPosition);
    }
}
