#pragma once
#include "Core.h"
#include "Matrix.h"
#include "MeshResource.h"

struct FRenderProxy
{
	FRenderProxy() = default;
	FRenderProxy(FMatrix InModelWorldMatrix, FMeshResource* InMeshResource)
		: ModelWorldMatrix(InModelWorldMatrix), MeshResource(InMeshResource) {}

	FMatrix ModelWorldMatrix; //Model->World
	FMeshResource* MeshResource;
};
