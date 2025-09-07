#include "PrimitiveComponent.h"
#include "Renderer.h"

void UPrimitiveComponent::Render()
{
	if (MeshResource != nullptr)
	{
		URenderer* Renderer = URenderer::Get();
		FRenderProxy RenderProxy(GetWorldMatrix(), MeshResource);
		Renderer->SubmitProxy(RenderProxy);
	}
}

void UPrimitiveComponent::SetMesh(FMeshResource* InMeshResource)
{
	MeshResource = InMeshResource;
}
