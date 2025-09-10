#include "PrimitiveComponent.h"
#include "Renderer.h"

UPrimitiveComponent::UPrimitiveComponent() : USceneComponent()
{
}

void UPrimitiveComponent::SubmitProxy()
{
	if (MeshResource != nullptr)
	{
		URenderer* Renderer = URenderer::Get();
		FRenderProxy RenderProxy(GetWorldMatrix(), MeshResource, IsSelected());
		Renderer->SubmitProxy(RenderProxy);
	}
}

void UPrimitiveComponent::SetMesh(FMeshResource* InMeshResource)
{
	MeshResource = InMeshResource;
}

void UPrimitiveComponent::SetPrimitiveType(EPrimitiveType InType)
{
	Type = InType;
	if (Type != EPrimitiveType::Custom)
	{
		SetMesh(URenderer::Get()->GetPrimitiveMeshResource(GetPrimitiveType()));
	}
}
