#include "MeshManager.h"
#include "Shapes.h"

void FMeshManager::RegisterMesh(const FString& MeshKey, const FMeshData& MeshData, D3D_PRIMITIVE_TOPOLOGY Topology)
{
    auto iter = MeshResourceMap.find(MeshKey);
    if (iter != MeshResourceMap.end())
    {
        return;
    }

    MeshResourceMap[MeshKey] = CreateMeshResource(MeshData, Topology);
}

void FMeshManager::UpdateMesh(const FString& MeshKey, const FMeshData& NewMeshData)
{
    auto iter = MeshResourceMap.find(MeshKey);
    if (iter != MeshResourceMap.end())
    {
        FMeshResource* OldResource = iter->second;
        D3D_PRIMITIVE_TOPOLOGY Toplogy = OldResource->Topology;
        if (OldResource)
        {
            if (OldResource->VertexBuffer) { OldResource->VertexBuffer->Release(); }
            if (OldResource->IndexBuffer) { OldResource->IndexBuffer->Release(); }
            delete OldResource;
        }

        iter->second = CreateMeshResource(NewMeshData, Toplogy);
    }
}

FMeshResource* FMeshManager::GetPrimitiveMeshResource(const EPrimitiveType Type)
{
    if (Type == EPrimitiveType::Custom) { return nullptr; }

    // Alreay Cached
    auto iter = PrimitiveMap.find(Type);
    if (iter != PrimitiveMap.end())
    {
        return GetMeshResource(iter->second);
    }
    
    FString Key = PrimitiveTypeToString(Type);
    FMeshData MeshData;
    switch(Type)
    {
            case EPrimitiveType::Cube:
                MeshData = Shapes::CubeMeshData;
                break;
            case EPrimitiveType::Sphere:
                MeshData = Shapes::SphereMeshData;
                break;
            default:
                break;
    }
    RegisterMesh(Key, MeshData);
    PrimitiveMap[Type] = Key;
    return MeshResourceMap[Key];
}

FMeshResource* FMeshManager::GetMeshResource(const FString& MeshId)
{
    auto iter = MeshResourceMap.find(MeshId);
    if (iter == MeshResourceMap.end())
    {
        return nullptr;
    }
    return iter->second;
}

void FMeshManager::Release()
{
    for (auto& Elem : MeshResourceMap)
    {
        FMeshResource* Resource = Elem.second;
        if (Resource)
        {
            if (Resource->VertexBuffer)
            {
                Resource->VertexBuffer->Release();
                Resource->VertexBuffer = nullptr;
            }
            if (Resource->IndexBuffer)
            {
                Resource->IndexBuffer->Release();
                Resource->IndexBuffer = nullptr;
            }
            delete Resource;
        }
    }

    MeshResourceMap.clear();
}

FMeshResource* FMeshManager::CreateMeshResource(const FMeshData& MeshData, D3D_PRIMITIVE_TOPOLOGY Topology)
{
    FMeshResource* NewMeshResource = new FMeshResource();
    NewMeshResource->Topology = Topology;

    NewMeshResource->VertexCount = MeshData.Vertices.size();
    NewMeshResource->IndexCount = MeshData.Indices.size();
    NewMeshResource->Stride = sizeof(FVertex);

    // Vertex Buffer
    D3D11_BUFFER_DESC VertexBufferDesc = {};
    VertexBufferDesc.ByteWidth = sizeof(FVertex) * NewMeshResource->VertexCount;
    VertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexBufferSRD = { MeshData.Vertices.data() };
    HRESULT hr = Device->CreateBuffer(&VertexBufferDesc, &vertexBufferSRD, &NewMeshResource->VertexBuffer);
    if (FAILED(hr))
    {
        NewMeshResource->VertexBuffer->Release();
        delete NewMeshResource;
        return nullptr;
    }

    // Index Buffer
    if (NewMeshResource->IndexCount > 0)
    {
        D3D11_BUFFER_DESC IndexBufferDesc = {};
        IndexBufferDesc.ByteWidth = sizeof(uint32) * NewMeshResource->IndexCount;
        IndexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA IndexBufferSRD = { MeshData.Indices.data() };
        hr = Device->CreateBuffer(&IndexBufferDesc, &IndexBufferSRD, &NewMeshResource->IndexBuffer);
        if (FAILED(hr))
        {
            NewMeshResource->IndexBuffer->Release();
            delete NewMeshResource;
            return nullptr;
        }
    }
    else
    {
        NewMeshResource->IndexBuffer = nullptr;
    }

    return NewMeshResource;
}
