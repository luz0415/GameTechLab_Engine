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
	ArrowZ->SetArrowAxis(EGizmoArrowAxis::Z);
	UGizmoArrow* ArrowY = FObjectFactory::Get()->ConstructObject<UGizmoArrow>();
	ArrowY->SetArrowAxis(EGizmoArrowAxis::Y);
	UGizmoArrow* ArrowX = FObjectFactory::Get()->ConstructObject<UGizmoArrow>();
	ArrowX->SetArrowAxis(EGizmoArrowAxis::X);

	Arrows.push_back(ArrowZ);
	Arrows.push_back(ArrowY);
	Arrows.push_back(ArrowX);
}

UGizmoRenderer::~UGizmoRenderer()
{
	for (auto& Arrow : Arrows)
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
		for (auto& Arrow : Arrows)
		{
			Arrow->SubmitProxy();
			//Arrow.SubmitProxy(FMatrix::ScaleMatrix(FVector(3.0f, 3.0f, 3.0f)));
		}
	}
}

void UGizmoRenderer::SetPickedItem(UObject* Item)
{
	if (Item && Item->IsA(UGizmoArrow::StaticClass())) { return; }

	if (USceneComponent* Comp = Cast<USceneComponent>(Item))
	{
		UE_LOG("FGIZMORENDERER : PICKED");
		SetAttachment(Comp);
		for (auto& Arrow : Arrows)
		{
			Arrow->SetPickedItem(Comp);
		}
	}
	else
	{
		UE_LOG("FGIZMORENDERER : No SceneComponent");
		Detach();
		for (auto& Arrow : Arrows)
		{
			Arrow->Detach();
		}
		return;
	}
}
