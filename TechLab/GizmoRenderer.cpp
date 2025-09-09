#include "GizmoRenderer.h"
#include "Shapes.h"
#include "Renderer.h"
#include "SceneComponent.h"
#include "Core.h"
#include "ImGuiManager.h"

UGizmoRenderer::UGizmoRenderer()
{
	//Init();
	URenderer::Get()->RegisterMesh(FString("ArrowZ"), Shapes::ArrowZ_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	URenderer::Get()->RegisterMesh(FString("ArrowY"), Shapes::ArrowY_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	URenderer::Get()->RegisterMesh(FString("ArrowX"), Shapes::ArrowX_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UGizmoArrow* ArrowZ = FObjectFactory::Get()->ConstructObject<UGizmoArrow>();
	ArrowZ->SetName(FString("ArrowZ"));
	ArrowZ->SetAABB(EGizmoArrowAxis::Z);
	UGizmoArrow* ArrowY = FObjectFactory::Get()->ConstructObject<UGizmoArrow>();
	ArrowY->SetName(FString("ArrowY"));
	ArrowY->SetAABB(EGizmoArrowAxis::Y);
	UGizmoArrow* ArrowX = FObjectFactory::Get()->ConstructObject<UGizmoArrow>();
	ArrowX->SetName(FString("ArrowX"));
	ArrowX->SetAABB(EGizmoArrowAxis::X);

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
	if (Item && Item->GetClass() == UGizmoArrow::StaticClass()) { return; }
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
