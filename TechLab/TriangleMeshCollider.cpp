#include "TriangleMeshCollider.h"
#include <limits>

FTriangleMeshCollider::FTriangleMeshCollider(const FMeshData& InMeshData)
    : Vertices(InMeshData.Vertices.begin(), InMeshData.Vertices.end())
{
    for (size_t i = 0; i < InMeshData.Indices.size(); i += 3)
    {
        Triangles.push_back({(int)InMeshData.Indices[i], (int)InMeshData.Indices[i+1], (int)InMeshData.Indices[i+2]});
    }
}

bool FTriangleMeshCollider::RaycastHit(const FRay& Ray, float TMax, FHitRecord& OutHit) const
{
    bool bHit = false;
    float ClosestT = TMax; // Initialize with the maximum allowed distance

    for (const FTriangle& Triangle : Triangles)
    {
        const FVector& V0 = Vertices[Triangle.V0].XYZ;
        const FVector& V1 = Vertices[Triangle.V1].XYZ;
        const FVector& V2 = Vertices[Triangle.V2].XYZ;

        FHitRecord CurrentHit;
        if (RayTriangleIntersect(Ray, V0, V1, V2, ClosestT, CurrentHit))
        {
            if (CurrentHit.Time < ClosestT)
            {
                ClosestT = CurrentHit.Time;
                OutHit = CurrentHit;
                bHit = true;
            }
        }
    }
    return bHit;
}

// Möller–Trumbore intersection algorithm
bool FTriangleMeshCollider::RayTriangleIntersect(const FRay& Ray, const FVector& V0, const FVector& V1, const FVector& V2, float TMax, FHitRecord& OutHit) const
{
    const float EPSILON = 0.0000001f; // A small epsilon value for floating point comparisons

    FVector Edge1 = V1 - V0;
    FVector Edge2 = V2 - V0;
    FVector P = Ray.GetDirection().Cross(Edge2);
    float Determinant = Edge1.Dot(P);

    // Check for back-facing or parallel triangles
    // If Determinant is close to 0, ray is parallel to triangle plane
    if (Determinant > -EPSILON && Determinant < EPSILON)
    {
        return false;
    }

    float InvDeterminant = 1.0f / Determinant;

    FVector T = Ray.GetOrigin() - V0;
    float U = T.Dot(P) * InvDeterminant;

    if (U < 0.0f || U > 1.0f)
    {
        return false;
    }

    FVector Q = T.Cross(Edge1);
    float V = Ray.GetDirection().Dot(Q) * InvDeterminant;

    if (V < 0.0f || U + V > 1.0f)
    {
        return false;
    }

    float Time = Edge2.Dot(Q) * InvDeterminant;

    if (Time > EPSILON && Time < TMax) // Ray intersection
    {
        OutHit.Time = Time;
        OutHit.Point = Ray.At(Time);
        // Calculate normal (optional, but good for shading/reflection)
        OutHit.normal = Edge1.Cross(Edge2).GetNormalized();
        return true;
    }

    return false;
}