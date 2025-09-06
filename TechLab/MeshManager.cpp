#include "MeshManager.h"
#include "Shapes.h"
int FMeshManager::RegisterMesh(ID3D11Device* Device, const EShapeType Type)
{
    //이미 캐싱되어있다면
    auto iter = ExistMap.find(Type);
    if (iter != ExistMap.end())
    {
        return iter->second;
    }

    int ID = NextId++;
    ExistMap[Type] = ID;
    FMeshResource Resource;
    UINT byteWidth = 0;
    switch(Type)
    {
            case EShapeType::Cube:
                Resource.Verticies = Shapes::cube_vertices;
                byteWidth = sizeof(Shapes::cube_vertices);
                break;
            case EShapeType::Sphere:
                Resource.Verticies = Shapes::sphere_vertices;
                byteWidth = sizeof(Shapes::sphere_vertices);
                break;
            default:
                break;
    }
    Resource.NumVerticies = byteWidth / sizeof(FVertexSimple);
    Resource.VertexBuffer = CreateVertexBuffer(Device, Resource.Verticies, byteWidth);
    Resource.Stride = sizeof(FVertexSimple);

    MeshResourceMap[ID] = Resource;
    return ID;
}

FMeshResource* FMeshManager::Get(int MeshId)
{
    auto iter = MeshResourceMap.find(MeshId);
    if (iter == MeshResourceMap.end())
    {
        return nullptr;
    }
    return &iter->second;
}

ID3D11Buffer* FMeshManager::CreateVertexBuffer(ID3D11Device* Device,FVertexSimple* vertices, UINT byteWidth)
{
    D3D11_BUFFER_DESC vertexbufferdesc = {};
    vertexbufferdesc.ByteWidth = byteWidth;
    vertexbufferdesc.Usage = D3D11_USAGE_IMMUTABLE;
    vertexbufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexbufferSRD = { vertices };

    ID3D11Buffer* vertexBuffer;
    Device->CreateBuffer(&vertexbufferdesc, &vertexbufferSRD, &vertexBuffer);

    return vertexBuffer;
}
