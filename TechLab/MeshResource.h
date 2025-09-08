#pragma once
#pragma comment(lib,"user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <d3d11.h>
#include <d3dcompiler.h>

#include "VertexData.h"

/**
* Vertex,Index buffer에 대한 정보 소유
*/
struct FMeshResource
{
    ID3D11Buffer* VertexBuffer = nullptr;
    ID3D11Buffer* IndexBuffer = nullptr;

    UINT     VertexCount = 0;
    UINT     Stride = 0;
    UINT     Offset = 0;

    UINT IndexCount = 0;

    // 렌더링 설정
    D3D_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};
