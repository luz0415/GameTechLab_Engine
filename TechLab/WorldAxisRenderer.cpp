#include "WorldAxisRenderer.h"
#include "Renderer.h"
FWorldAxisRenderer::FWorldAxisRenderer()
{

}

FWorldAxisRenderer::~FWorldAxisRenderer()
{

}

void FWorldAxisRenderer::Init()
{
	Vertices.push_back({ {0.f,0.f,0.f},{1.f,0.f,0.f,1.f} });
	Vertices.push_back({ {1000.f,0.f,0.f},{1.f,0.f,0.f,1.f} });//X
	Vertices.push_back({ {0.f,0.f,0.f},{0.f,1.f,0.f,1.f} });
	Vertices.push_back({ {0.f,1000.f,0.f},{0.f,1.f,0.f,1.f} });//Y
	Vertices.push_back({ {0.f,0.f,0.f},{0.f,0.f,1.f,1.f} });
	Vertices.push_back({ {0.f,0.f,1000.f},{0.f,0.f,1.f,1.f} });//Z

	Name = "WorldAxis";

	URenderer::Get()->RegisterMesh(Name, FMeshData{ Vertices,Indices }, D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}

void FWorldAxisRenderer::Update(const FVector& CameraPos)
{
}

void FWorldAxisRenderer::Render()
{
	VisualInterface::Render();
}
