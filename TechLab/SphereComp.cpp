#include "SphereComp.h"
#include "MeshManager.h"
#include "Renderer.h"
#include "ShapeType.h"

USphereComp::USphereComp() : UPrimitiveComponent()
{
	SetMesh(URenderer::Get()->GetPrimitiveMeshResource(EPrimitiveType::Sphere));
}
