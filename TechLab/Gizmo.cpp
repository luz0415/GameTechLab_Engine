#include "Gizmo.h"



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
}

void UGizmo::SetAxis(EGizmoAxis InAxis)
{
}

void UGizmo::HandleDrag(UCamera* Camera, const FVector& RayOrigin, const FVector& RayDirection)
{
}
