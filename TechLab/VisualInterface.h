#pragma once
#include "Vector.h"
#include "Core.h"
#include "VertexData.h"
class VisualInterface
{
public:
	VisualInterface();
	virtual ~VisualInterface();
	virtual void Init() = 0;
	virtual void Update(const FVector& CameraPos) = 0;
	virtual void Render();

protected:
	TArray<FVertex> Vertices;
	TArray<uint32> Indices;
	FString Name;
};