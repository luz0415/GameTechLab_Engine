#pragma once
#pragma comment(lib,"user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <d3d11.h>
#include <d3dcompiler.h>

#include "VertexSimple.h"

struct FMeshResource
{
	ID3D11Buffer* VertexBuffer;
//	ID3D11Buffer* IndexBuffer;
	UINT Stride = 0;
	//UINT IndexCount = 0;
	D3D_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	FVertexSimple* Verticies;
	UINT NumVertices = 0;
	UINT Offset = 0;
};
