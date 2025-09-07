#include "SphereComp.h"
#include "MeshManager.h"
#include "Renderer.h"

USphereComp::USphereComp() : UPrimitiveComponent()
{
	MeshId = FMeshManager::Get()->RegisterMesh(URenderer::Get()->Device, EShapeType::Sphere);
}

void USphereComp::Render()
{
	URenderer* Renderer = URenderer::Get();
	FRenderProxy RenderProxy(GetWorldMatrix(), MeshId);
	Renderer->SubmitProxy(RenderProxy);
}
