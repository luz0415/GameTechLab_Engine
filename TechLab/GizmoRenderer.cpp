#include "GizmoRenderer.h"
#include "Shapes.h"
#include "Renderer.h"
#include "SceneComponent.h"
#include "Core.h"
#include "ImGuiManager.h"

UGizmoRenderer::UGizmoRenderer()
{
	//Init();
	UGizmoArrow* ArrowZ = FObjectFactory::Get()->ConstructObject<UGizmoArrow>();
	ArrowZ->SetName(FString("ArrowZ"));
	URenderer::Get()->RegisterMesh(ArrowZ->GetName(), Shapes::ArrowZ_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	UGizmoArrow* ArrowY = FObjectFactory::Get()->ConstructObject<UGizmoArrow>();
	ArrowY->SetName(FString("ArrowY"));
	URenderer::Get()->RegisterMesh(ArrowY->GetName(), Shapes::ArrowY_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	UGizmoArrow* ArrowX = FObjectFactory::Get()->ConstructObject<UGizmoArrow>();
	ArrowX->SetName(FString("ArrowX"));
	URenderer::Get()->RegisterMesh(ArrowX->GetName(), Shapes::ArrowX_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Arrows.push_back(ArrowZ);
	Arrows.push_back(ArrowY);
	Arrows.push_back(ArrowX);
}

UGizmoRenderer::~UGizmoRenderer()
{
}


void UGizmoRenderer::SubmitProxy()
{
	if (GetAttachment() != nullptr)
	{
		//UE_LOG("PickedItem : [%f , %f , %f]", PickedItem->GetWorldLocation().X, PickedItem->GetWorldLocation().Y, PickedItem->GetWorldLocation().Z);
		for (auto& Arrow : Arrows)
		{
			Arrow->SubmitProxy();
			//Arrow.SubmitProxy(FMatrix::ScaleMatrix(FVector(3.0f, 3.0f, 3.0f)));
		}
	}
}

void UGizmoRenderer::SetPickedItem(UObject* Item)
{
	USceneComponent* Comp = Cast<USceneComponent>(Item);
	if (Comp == nullptr)
	{
		UE_LOG("FGIZMORENDERER : NOT A USCeneComponent!");
		return;
	}
	UE_LOG("FGIZMORENDERER : PICKED");
	SetAttachment(Comp);
	for (auto& Arrow : Arrows)
	{
		Arrow->SetPickedItem(Comp);
		//Arrow.SubmitProxy(FMatrix::ScaleMatrix(FVector(3.0f, 3.0f, 3.0f)));
	}
}
