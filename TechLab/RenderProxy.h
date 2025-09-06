#pragma once
#include "Matrix.h"

struct FRenderProxy
{
	FMatrix World;//Model->World
	unsigned MeshId;//MeshManager의 Register를 통해서 ID발급, 이후 Get을 사용하면 실제 MeshResource로드가능
};