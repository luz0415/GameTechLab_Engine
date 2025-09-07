#pragma once
#include "Core.h"
#include "MeshResource.h"
#include "ShapeType.h"

class FMeshManager
{
public:
	FMeshManager(ID3D11Device* InDevice) : Device(InDevice) {}
	~FMeshManager() { Release(); }

	void RegisterMesh(const FString& MeshKey, const FMeshData& MeshData, D3D_PRIMITIVE_TOPOLOGY Topology = D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	void UpdateMesh(const FString& MeshKey, const FMeshData& NewMeshData);
	FMeshResource* GetPrimitiveMeshResource(const EPrimitiveType Type);
	FMeshResource* GetMeshResource(const FString& MeshId);
	void Release();

private:
	FMeshResource* CreateMeshResource(const FMeshData& MeshData, D3D_PRIMITIVE_TOPOLOGY Topology);

	ID3D11Device* Device = nullptr;

	TMap<FString, FMeshResource*> MeshResourceMap; // { MeshId, MeshResource }
	TMap<EPrimitiveType, FString> PrimitiveMap; // Primitive Type 별로 ID 저장
};
