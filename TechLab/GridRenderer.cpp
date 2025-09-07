#include "GridRenderer.h"
#include "VertexData.h"
#include "MeshManager.h"
#include "Renderer.h"

FGridRenderer::FGridRenderer()
{
}

void FGridRenderer::Init()
{
    RegenerateGrid(FVector());
}

void FGridRenderer::Update(const FVector& CameraPos)
{
    // TODO - 정확히 GridSize*5 단위로 만들어야함
    float distance = FVector::Dist(CameraPos, LastCameraPos);
    if (distance > GridSize * 5)
    {
        RegenerateGrid(CameraPos);
        LastCameraPos = CameraPos;
    }
}

void FGridRenderer::Render()
{
    URenderer* Renderer = URenderer::Get();
    FRenderProxy RenderProxy(FMatrix::Identity(), Renderer->GetMeshResource(FString("Grid")));
    Renderer->SubmitProxy(RenderProxy);
}

void FGridRenderer::RegenerateGrid(const FVector& CameraPos)
{
    Vertices.clear();
    Indices.clear();

    float StartX = CameraPos.X - GridRadius * GridSize;
    float EndX = CameraPos.X + GridRadius * GridSize;
    float StartZ = CameraPos.Z - GridRadius * GridSize;
    float EndZ = CameraPos.Z + GridRadius * GridSize;

    for (int32 i = 0; i <= GridRadius * 2; ++i)
    {
        float X = StartX + i * GridSize;
        Vertices.push_back({ {X, 0.0f, StartZ}, {0.5f, 0.5f, 0.5f, 1.0f} });
        Vertices.push_back({ {X, 0.0f, EndZ }, {0.5f, 0.5f, 0.5f, 1.0f} });

        Indices.push_back(Vertices.size() - 2);
        Indices.push_back(Vertices.size() - 1);
    }

    for (int32 i = 0; i <= GridRadius * 2; ++i)
    {
        float Z = StartZ + i * GridSize;
        Vertices.push_back({ {StartX, 0.0f, Z}, {0.5f, 0.5f, 0.5f, 1.0f} });
        Vertices.push_back({ {EndX, 0.0f, Z }, {0.5f, 0.5f, 0.5f, 1.0f} });

        Indices.push_back(Vertices.size() - 2);
        Indices.push_back(Vertices.size() - 1);
    }

    if (URenderer::Get()->GetMeshResource(FString("Grid")) == nullptr)
    {
        URenderer::Get()->RegisterMesh(FString("Grid"), FMeshData{ Vertices, Indices }, D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    }
    else
    {
        URenderer::Get()->UpdateMesh(FString("Grid"), FMeshData{ Vertices, Indices });
    }
}
