#include "GizmoRotation.h"
#include "Renderer.h"
#include "AABB.h"
#include "Shapes.h"
#include "TimeManager.h"
#include "Camera.h"


UGizmoRotation::UGizmoRotation()
{
}

UGizmoRotation::~UGizmoRotation()
{
}


void UGizmoRotation::SetAxis(EGizmoAxis InAxis)
{
	float R = 1.f;
	float r = .1f;

	FVector minPoint;
	FVector maxPoint;
	switch (InAxis)
	{
	case EGizmoAxis::Y:
		minPoint = FVector(-(R + r), -r, -(R + r));
		maxPoint = FVector((R + r), r, (R + r));
		SetBoundingVolume(new FAABB(FVector(minPoint),FVector(maxPoint)));
		Direction = FVector(0.f, 1.f, 0.f);
		SetName(FString("TorusY"));
		break;
	case EGizmoAxis::X:
		minPoint = FVector(-r, -(R + r), -(R + r));
		maxPoint = FVector(r, (R + r), (R + r));
		SetBoundingVolume(new FAABB(FVector(minPoint), FVector(maxPoint)));
		Direction = FVector(1.f, 0.f, 0.f);
		SetName(FString("TorusX"));
		break;
	case EGizmoAxis::Z:
		minPoint = FVector(-(R + r), -(R + r), -r);
		maxPoint = FVector((R + r), (R + r), r);
		SetBoundingVolume(new FAABB(FVector(minPoint), FVector(maxPoint)));
		Direction = FVector(0.f, 0.f, 1.f);
		SetName(FString("TorusZ"));
		break;
	}

}

void UGizmoRotation::HandleDrag(UCamera* Camera, const FVector& RayOrigin, const FVector& RayDirection)
{
	USceneComponent* Attach = GetAttachment();
	if (Attach)
	{
		// 1. 현재 마우스 위치의 교차점을 구함
		FVector currentHitPoint = GetIntersectionWithMovementPlane(Camera, RayOrigin, RayDirection);

		// 2. 교차점 계산이 실패했는지 Invalid 플래그로 확인
		if (Invalid == true)
		{
			Invalid = false;
			return;
		}


		// 3. '현재 벡터' 계산
		FVector currentVectorOnPlane = currentHitPoint - Attach->GetWorldLocation();
		currentVectorOnPlane.Normalize();

		// 4. 시작 벡터와 현재 벡터 사이의 각도 계산
		float dotProduct = InitialVectorOnPlane.Dot(currentVectorOnPlane);
		float angle = acos(Clamp(dotProduct, -1.0f, 1.0f));

		// 5. 회전 방향 결정
		FVector crossProduct = InitialVectorOnPlane.Cross(currentVectorOnPlane);
		if (crossProduct.Dot(RotationAxis) < 0.f)
		{
			angle = +angle;
		}

		// 6. 델타 회전 생성
		FQuaternion deltaRotation = FQuaternion(RotationAxis.X, RotationAxis.Y, RotationAxis.Z, angle);

		// 7. 최종 회전값 계산 및 적용
		FQuaternion newRotation = deltaRotation * InitialObjectRotation;
		Attach->SetWorldRotation(newRotation);
	}
}

void UGizmoRotation::OnDragStart(UCamera* Camera, const FVector& RayOrigin, const FVector& RayDirection)
{
	USceneComponent* Attach = GetAttachment();
	if (Attach)
	{
		// 1. 드래그 시작 시점의 객체 회전값과 위치를 가져옴
		InitialObjectRotation = Attach->GetWorldRotationAsQuaternion();
		const FVector objectLocation = Attach->GetWorldLocation();

		// 2. (핵심) 로컬 축 방향을 월드 축으로 변환하여 '고정된 회전축'으로 설정
		// LocalAxisDirection은 이 기즈모 핸들이 담당하는 축입니다 (예: X축 핸들이면 FVector(1,0,0))
		RotationAxis = InitialObjectRotation.RotateVector(Direction);

		// 2. 교차점을 구하고, Invalid 플래그를 확인
		FVector hitPoint = GetIntersectionWithMovementPlane(Camera, RayOrigin, RayDirection);

		// 3. 만약 교차점 계산에 실패했다면(Invalid == true), 시작 벡터를 계산하지 않음
		//    이 경우 드래그가 시작되지 않도록 막는 것이 좋음
		if (Invalid) {
			// 필요하다면 여기서 드래그 취소 로직을 넣을 수 있습니다.
			return;
		}

		// 4. 성공 시에만 시작 벡터 계산 및 저장
		InitialVectorOnPlane = hitPoint - Attach->GetWorldLocation();
		InitialVectorOnPlane.Normalize();
	}
}