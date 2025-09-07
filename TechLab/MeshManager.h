#pragma once
#include "Core.h"
#include "MeshResource.h"
#include "ShapeType.h"
class FMeshManager
{
public:
	static FMeshManager* Get() 
	{
		static FMeshManager Singleton;
		return &Singleton;
	}

	int RegisterMesh(ID3D11Device* Device, const EShapeType Type);
	FMeshResource* GetMeshResource(int MeshId);
	ID3D11Buffer* CreateVertexBuffer(ID3D11Device* Device, FVertexSimple* vertices, UINT byteWidth);

private:
	FMeshManager() {}

	int NextId{ 0 };

	TMap<int, FMeshResource> MeshResourceMap;//meshId <-> Resource
	TMap<EShapeType, int> ExistMap;//이미 캐싱된 resource인지 확인
};