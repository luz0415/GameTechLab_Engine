#include "GizmoRenderer.h"
#include "Shapes.h"
#include "Renderer.h"
#include "SceneComponent.h"
#include "Core.h"
#include "ImGuiManager.h"
FGizmoRenderer::FGizmoRenderer()
{
	//Init();
	FGizmoArrow ArrowZ;
	ArrowZ.SetName("ArrowZ");
	URenderer::Get()->RegisterMesh(ArrowZ.GetName(), Shapes::ArrowZ_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	FGizmoArrow ArrowY;
	ArrowY.SetName("ArrowY");
	URenderer::Get()->RegisterMesh(ArrowY.GetName(), Shapes::ArrowY_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	FGizmoArrow ArrowX;
	ArrowX.SetName("ArrowX");
	URenderer::Get()->RegisterMesh(ArrowX.GetName(), Shapes::ArrowX_MeshData, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Arrows.push_back(ArrowZ);
	Arrows.push_back(ArrowY);
	Arrows.push_back(ArrowX);
}

FGizmoRenderer::~FGizmoRenderer()
{
}


void FGizmoRenderer::SubmitProxy()
{
	if (GetAttachment() != nullptr)
	{
		//UE_LOG("PickedItem : [%f , %f , %f]", PickedItem->GetWorldLocation().X, PickedItem->GetWorldLocation().Y, PickedItem->GetWorldLocation().Z);
		for (auto& arrow : Arrows)
		{
			arrow.SubmitProxy();
			//arrow.SubmitProxy(FMatrix::ScaleMatrix(FVector(3.0f, 3.0f, 3.0f)));
		}
	}
}

void FGizmoRenderer::SetPickedItem(UObject* Item)
{
	USceneComponent* comp = dynamic_cast<USceneComponent*>(Item);
	if (comp == nullptr)
	{
		UE_LOG("FGIZMORENDERER : NOT A USCeneComponent!");
		return;
	}
	UE_LOG("FGIZMORENDERER : PICKED");
	SetAttachment(comp);
	for (auto& arrow : Arrows)
	{
		arrow.SetPickedItem(comp);
		//arrow.SubmitProxy(FMatrix::ScaleMatrix(FVector(3.0f, 3.0f, 3.0f)));
	}
}
