#include "GizmoRenderer.h"
#include "Shapes.h"
#include "Renderer.h"
#include "SceneComponent.h"
#include "Core.h"
#include "ImGuiManager.h"
#include "GizmoArrow.h"

UGizmoRenderer::UGizmoRenderer()
{
	//Init();
	URenderer::Get()->RegisterMesh(FString("ArrowZ"), Shapes::ArrowZ_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	URenderer::Get()->RegisterMesh(FString("ArrowY"), Shapes::ArrowY_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	URenderer::Get()->RegisterMesh(FString("ArrowX"), Shapes::ArrowX_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UGizmoArrow* ArrowZ = FObjectFactory::Get()->ConstructObject<UGizmoArrow>();
	ArrowZ->SetAxis(EGizmoAxis::Z);
	UGizmoArrow* ArrowY = FObjectFactory::Get()->ConstructObject<UGizmoArrow>();
	ArrowY->SetAxis(EGizmoAxis::Y);
	UGizmoArrow* ArrowX = FObjectFactory::Get()->ConstructObject<UGizmoArrow>();
	ArrowX->SetAxis(EGizmoAxis::X);

	Gizmos.push_back(ArrowZ);
	Gizmos.push_back(ArrowY);
	Gizmos.push_back(ArrowX);
}

UGizmoRenderer::~UGizmoRenderer()
{
	for (auto& Arrow : Gizmos)
	{
		if (FObjectFactory::Get()->IsObjectValid(Arrow))
		{
			Arrow->Destroy();
		}
	}
}

void UGizmoRenderer::SubmitProxy()
{
	if (GetAttachment() != nullptr)
	{
		//UE_LOG("PickedItem : [%f , %f , %f]", PickedItem->GetWorldLocation().X, PickedItem->GetWorldLocation().Y, PickedItem->GetWorldLocation().Z);
		for (auto& Arrow : Gizmos)
		{
			Arrow->SubmitProxy();
			//Arrow.SubmitProxy(FMatrix::ScaleMatrix(FVector(3.0f, 3.0f, 3.0f)));
		}
	}
}

void UGizmoRenderer::SetPickedItem(UObject* Item)
{
	if (Item && 
		(Item->IsA(UGizmoArrow::StaticClass())
			//(Item->IsA(UGizmoArrow::StaticClass())
		)) { return; }

	if (USceneComponent* Comp = Cast<USceneComponent>(Item))
	{
		UE_LOG("FGIZMORENDERER : PICKED");
		SetAttachment(Comp);
		for (auto& Arrow : Gizmos)
		{
			Arrow->SetWorldLocation(Comp->GetWorldLocation());
			Arrow->SetWorldScale(Comp->GetWorldScale() * 3);
			Arrow->SetPickedItem(Comp);
		}
	}
	else
	{
		UE_LOG("FGIZMORENDERER : No SceneComponent");
		Detach();
		for (auto& Arrow : Gizmos)
		{
			Arrow->Detach();
		}
		return;
	}
}
