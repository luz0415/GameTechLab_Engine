#include "ObjectPicker.h"
#include "Pickable.h"
#include "Camera.h"
#include "Ray.h"
#include "Vector4.h"
#include "Matrix.h"
#include "Core.h"
#include "ObjectFactory.h"
#include "SceneComponent.h"
#include "ImGuiManager.h"
#include "ImGuiAppConsole.h"
#include "Renderer.h"
#include "GizmoRenderer.h"
UObjectPicker::UObjectPicker() {
	GizmoRenderer = new UGizmoRenderer;
}

// Debug Info (TEMP)
extern FVector GRayOrigin;
extern FVector GRayDirection;
extern int GTotalObjectCount;
extern int GSuccessfulCastCount;
extern float GLastBestT;
extern uint32_t GNewSelectionID;

void UObjectPicker::HandleMouseClick(float ScreenX, float ScreenY)
{
	// Reset debug info
	GSuccessfulCastCount = 0;
	GLastBestT = 0.0f;
	GNewSelectionID = 0;

	//UE_LOG("(%f %f)", ScreenX, ScreenY);

	FRay Ray = CreateRayFromScreen(ScreenX, ScreenY);
	GRayOrigin = Ray.GetOrigin();
	GRayDirection = Ray.GetDirection();

	/*UE_LOG("[%f , %f , %f]", GRayOrigin.X, GRayOrigin.Y, GRayOrigin.Z);
	UE_LOG("[%f , %f , %f]", GRayDirection.X, GRayDirection.Y, GRayDirection.Z);*/

	// TODO: check Gizmo interaction

	IPickable* NewSelection = nullptr;
	float BestT = std::numeric_limits<float>::infinity();

	// Ray casting !!
	const TArray<UObject*> Objects = FObjectFactory::Get()->GetObjectArray();
	GTotalObjectCount = Objects.size();

	for (UObject* Object : Objects)
	{
		if (!Object)	continue;

		if (auto* RayTarget = Cast<USceneComponent>(Object))
		{
			FMatrix WorldTransform = RayTarget->GetWorldMatrix();
			FRay LocalRay = TransformRayToLocalSpace(Ray, WorldTransform);

			FHitRecord Hit;
			if (RayTarget->Raycast(LocalRay, BestT, Hit) && Hit.Time < BestT) {
				GSuccessfulCastCount++;
				BestT = Hit.Time;
				NewSelection = RayTarget;
			}
		}
	}

	GLastBestT = BestT;
	if (NewSelection)
	{
		if (auto* SelectedObject = dynamic_cast<UObject*>(NewSelection))
		{
			GNewSelectionID = SelectedObject->UUID;
		}
	}

	UpdateSelection(NewSelection);
}

const std::vector<IPickable*>& UObjectPicker::GetCurrentSelection() const
{
	return CurrentSelections;
}

void UObjectPicker::SetCamera(UCamera* camera)
{
	Camera = camera;
}

void UObjectPicker::SubmitProxy()
{
	GizmoRenderer->SubmitProxy();
}

FRay UObjectPicker::CreateRayFromScreen(float ScreenX, float ScreenY) const
{
	const float NDCx = (2.0f * ScreenX) / static_cast<float>(ViewportWidth) - 1.0f;
	const float NDCy = -(2.0f * ScreenY) / static_cast<float>(ViewportHeight) + 1.0f;

	//UE_LOG("Screen : %f %f", ScreenX, ScreenY);

	const FMatrix View = Camera->GetViewMatrix();
	const FMatrix Proj = Camera->GetProjectionMatrix();

	// 1. Unproject from NDC to View Space using inverse of Projection Matrix
	const FMatrix InvProj = Proj.Inverse();

	const FVector4 pNearNDC(NDCx, NDCy, 0.0f, 1.0f);
	const FVector4 pFarNDC(NDCx, NDCy, 1.0f, 1.0f);

	FVector4 pNearVS = InvProj * pNearNDC;
	FVector4 pFarVS = InvProj * pFarNDC;

	// Perspective division for view space points
	pNearVS.X /= pNearVS.W; pNearVS.Y /= pNearVS.W; pNearVS.Z /= pNearVS.W; pNearVS.W = 1.0f;
	pFarVS.X /= pFarVS.W;  pFarVS.Y /= pFarVS.W;  pFarVS.Z /= pFarVS.W;  pFarVS.W = 1.0f;

	// 2. Unproject from View Space to World Space using inverse of View Matrix
	const FMatrix InvView = View.InverseAffine();

	FVector4 pNearH = InvView * pNearVS;
	FVector4 pFarH = InvView * pFarVS;

	// No perspective divide needed here as View matrix is affine and W should remain 1.0

	const FVector OriginWS(pNearH.X, pNearH.Y, pNearH.Z);

	FVector DirWS = FVector(pFarH.X - pNearH.X, pFarH.Y - pNearH.Y, pFarH.Z - pNearH.Z);
	DirWS.Normalize();
	UE_LOG("(%f %f %f)", DirWS.X, DirWS.Y, DirWS.Z);

	return FRay(OriginWS, DirWS);
}

FRay UObjectPicker::TransformRayToLocalSpace(const FRay& WorldRay, const FMatrix& WorldTransform) const
{
    FMatrix InvWorld = WorldTransform.Inverse();

    // Ray origin
    FVector4 OriginLS4 = InvWorld * FVector4(WorldRay.GetOrigin(), 1.0f);
    FVector OriginLS(OriginLS4.X, OriginLS4.Y, OriginLS4.Z);

    // Ray direction
    FVector4 LocalDirection4 = InvWorld * FVector4(WorldRay.GetDirection(), 0.0f);
    FVector DirLS(LocalDirection4.X, LocalDirection4.Y, LocalDirection4.Z);
	DirLS.Normalize();

    return FRay(OriginLS, DirLS);
}

void UObjectPicker::UpdateSelection(IPickable* NewSelection)
{
	// TODO: enable multiple selection (bool bIsCtrlPressed)
	// Current: single ~

	ClearSelection();

	if (NewSelection)
	{
		CurrentSelections.push_back(NewSelection);
		NewSelection->OnSelected();

		if (auto* SelectedObject = dynamic_cast<UObject*>(NewSelection))
		{
			extern uint32_t GPickedObjectID;
			GPickedObjectID = SelectedObject->UUID;
			GizmoRenderer->SetPickedItem(SelectedObject);
		}
	}
	
}

void UObjectPicker::ClearSelection()
{
	for (IPickable* Selected : CurrentSelections)
	{
		if (Selected)
		{
			Selected->OnDeselected();
	
		}
	}
	CurrentSelections.clear();
}