#pragma once
#include "Core.h"
#include "Matrix.h"
#include "MeshResource.h"

struct FRenderProxy
{
	FRenderProxy() = default;
	FRenderProxy(FMatrix InModelWorldMatrix, FMeshResource* InMeshResource, bool IsHighlighted = false)
		: ModelWorldMatrix(InModelWorldMatrix), MeshResource(InMeshResource), bIsHighlighted(IsHighlighted) {}

	FMatrix ModelWorldMatrix; //Model->World
	FMeshResource* MeshResource;
	bool bIsHighlighted = false;
};
