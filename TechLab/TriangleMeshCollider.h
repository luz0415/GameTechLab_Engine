#pragma once

#include "Core.h"
#include "BoundingVolume.h"
#include "VertexData.h"
#include "Vector.h"
#include "Ray.h"

struct FTriangle
{
    int V0, V1, V2; // Indices into the vertex array
};

struct FTriangleMeshCollider
{
public:
    FTriangleMeshCollider(const FMeshData& InMeshData);
    ~FTriangleMeshCollider() = default;

    bool RaycastHit(const FRay& Ray, float TMax, FHitRecord& OutHit) const;

private:
    TArray<FVertex> Vertices;
    TArray<FTriangle> Triangles;

    bool RayTriangleIntersect(const FRay& Ray, const FVector& V0, const FVector& V1, const FVector& V2, float TMax, FHitRecord& OutHit) const;
};