#include "CubeComp.h"
#include "AABB.h"

UCubeComp::UCubeComp() : UPrimitiveComponent()
{
	SetPrimitiveType(EPrimitiveType::Cube);
	SetBoundingVolume(new FAABB(FVector(-1.0f, -1.0f, -1.0f), FVector(1.0f, 1.0f, 1.0f)));
}