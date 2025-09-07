#pragma once
#include "Core.h"
#include "Vector.h"
#include "Vector4.h"

struct FVertex
{
	FVector XYZ;
	FVector4 RGBA;
};

struct FMeshData
{
	TArray<FVertex> Vertices;
	TArray<uint32> Indices;
};
