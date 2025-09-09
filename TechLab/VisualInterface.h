#pragma once
#include "Core.h"
#include "Matrix.h"
#include "VertexData.h"
class FVisualInterface
{
public:
	FVisualInterface();
	virtual ~FVisualInterface();
	virtual void Init() = 0;
	virtual void Update(const FVector& CameraPos) = 0;
	virtual void SubmitProxy(const FMatrix& WorldMatrix = FMatrix::Identity());

protected:
	TArray<FVertex> Vertices;
	TArray<uint32> Indices;
	FString Name;
};