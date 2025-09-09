#pragma once
#include "Ray.h" // Use the existing Ray.h
#include "Math.h" // For Min/Max and other math utilities if needed

// Möller–Trumbore intersection algorithm
// Returns true if intersection occurs, and sets outT to the distance along the ray
inline bool RayTriangleIntersection(
    const FRay& Ray,
    const FVector& V0,
    const FVector& V1,
    const FVector& V2,
    float& OutT)
{
    const float EPSILON = 0.0000001f;
    FVector Edge1, Edge2, H, S, Q;
    float A, F, U, V;

    Edge1 = V1 - V0;
    Edge2 = V2 - V0;

    H = Ray.GetDirection().Cross(Edge2);
    A = Edge1.Dot(H);

    if (A > -EPSILON && A < EPSILON) // Ray is parallel to triangle
        return false;

    F = 1.0f / A;
    S = Ray.GetOrigin() - V0;
    U = F * (S.Dot(H));

    if (U < 0.0f || U > 1.0f)
        return false;

    Q = S.Cross(Edge1);
    V = F * (Ray.GetDirection().Dot(Q));

    if (V < 0.0f || U + V > 1.0f)
        return false;

    // At this stage, we can compute t to find out where the intersection point is on the line.
    OutT = F * (Edge2.Dot(Q));

    if (OutT > EPSILON) // Ray intersection
        return true;

    return false; // No hit, or hit behind the ray
}
