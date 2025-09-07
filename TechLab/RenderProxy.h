#pragma once
#include "Core.h"
#include "Matrix.h"

struct FRenderProxy
{
	FRenderProxy() = default;
	FRenderProxy(FMatrix InModelWorldMatrix, uint32 InMeshId) 
		: ModelWorldMatrix(InModelWorldMatrix), MeshId(InMeshId) {}

	FMatrix ModelWorldMatrix; //Model->World
	uint32 MeshId; //MeshManager의 Register를 통해서 ID발급, 이후 Get을 사용하면 실제 MeshResource로드가능
};
