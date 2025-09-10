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

// UGizmoRotation.cpp
FVector UGizmoRotation::GetIntersectionWithMovementPlane(UCamera* Camera, FVector RayOrigin, FVector RayDirection)
{
	USceneComponent* Attach = GetAttachment();
	if (!Attach) { Invalid = true; return FVector(); }

	FVector PlaneOrigin = Attach->GetWorldLocation();

	// (수정) 로컬 Direction을 현재 객체의 회전에 맞게 월드 방향으로 변환합니다.
	FQuaternion worldRotation = Attach->GetWorldRotationAsQuaternion();
	FVector PlaneNormal = worldRotation.RotateVector(Direction);

	float numerator = ((PlaneOrigin - RayOrigin).Dot(PlaneNormal));
	float denominator = (RayDirection.Dot(PlaneNormal));

	if (abs(denominator) < 0.0001f)
	{
		Invalid = true;
		return FVector();
	}

	float DistanceToPlane = numerator / denominator;
	FVector IntersectionPoint = RayOrigin + (RayDirection * DistanceToPlane);
	return IntersectionPoint;
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
		FVector currentHitPoint = GetIntersectionWithMovementPlane(Camera, RayOrigin, RayDirection);
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
		InitialObjectRotation = Attach->GetWorldRotationAsQuaternion();
		const FVector objectLocation = Attach->GetWorldLocation();

		// RotationAxis 계산은 원래대로 완벽합니다.
		RotationAxis = InitialObjectRotation.RotateVector(Direction);

		FVector hitPoint = GetIntersectionWithMovementPlane(Camera, RayOrigin, RayDirection);
		if (Invalid) {
			return;
		}

		// (수정) 반드시 objectLocation을 빼서 회전 중심으로부터의 방향 벡터로 만들어야 합니다.
		InitialVectorOnPlane = hitPoint - objectLocation;
		InitialVectorOnPlane.Normalize();
	}
}