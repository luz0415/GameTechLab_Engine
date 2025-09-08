#include "GridRenderer.h"
#include "VertexData.h"
#include "MeshManager.h"
#include "Renderer.h"

FGridRenderer::FGridRenderer()
{
    RegenerateGrid(FVector());
}

void FGridRenderer::Update(const FVector& CameraPos)
{
    float Distance = FVector::Dist(CameraPos, LastCameraPos);
    if (Distance > GridSize * 5)
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

    float AlignedCameraPosX = round(CameraPos.X / GridSize) * GridSize;
    float AlignedCameraPosZ = round(CameraPos.Z / GridSize) * GridSize;

    float StartX = AlignedCameraPosX - GridRadius * GridSize;
    float EndX = AlignedCameraPosX + GridRadius * GridSize;
    float StartZ = AlignedCameraPosZ - GridRadius * GridSize;
    float EndZ = AlignedCameraPosZ + GridRadius * GridSize;

    // X Lines
    for (int32 i = 0; i <= GridRadius * 2; ++i)
    {
        float X = StartX + i * GridSize;
        Vertices.push_back({ {X, 0.0f, StartZ}, {0.5f, 0.5f, 0.5f, 1.0f} });
        Vertices.push_back({ {X, 0.0f, EndZ }, {0.5f, 0.5f, 0.5f, 1.0f} });
    }

    // Z Lines
    for (int32 i = 0; i <= GridRadius * 2; ++i)
    {
        float Z = StartZ + i * GridSize;
        Vertices.push_back({ {StartX, 0.0f, Z}, {0.5f, 0.5f, 0.5f, 1.0f} });
        Vertices.push_back({ {EndX, 0.0f, Z }, {0.5f, 0.5f, 0.5f, 1.0f} });
    }

    if (URenderer::Get()->GetMeshResource(FString("Grid")) == nullptr)
    {
        URenderer::Get()->RegisterMesh(FString("Grid"), FMeshData{ Vertices, {} }, D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    }
    else
    {
        URenderer::Get()->UpdateMesh(FString("Grid"), FMeshData{ Vertices, {} });
    }
}
