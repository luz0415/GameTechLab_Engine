#include "AABB.h"
#include "VertexData.h"
#include "Core.h"
#include "ImGuiManager.h"

FAABB::FAABB(const FMeshData& MeshData)
{
    FVector ScaledPos = MeshData.Vertices[0].XYZ;
    Min = ScaledPos;
    Max = ScaledPos;

    for (int i = 1; i < MeshData.Vertices.size(); i++)
    {
        const FVector& Pos = MeshData.Vertices[i].XYZ;

        Min.X = min(Min.X, Pos.X);
        Min.Y = min(Min.Y, Pos.Y);
        Min.Z = min(Min.Z, Pos.Z);

        Max.X = max(Max.X, Pos.X);
        Max.Y = max(Max.Y, Pos.Y);
        Max.Z = max(Max.Z, Pos.Z);
    }
}

bool FAABB::RaycastHit(const FRay& Ray, float TMax, FHitRecord& OutHit) const
{
    /*FVector Center = FVector(0.0f, 0.0f, 0.0f);
    FVector HalfSize = FVector(1.0f, 1.0f, 1.0f);
    FVector MinBounds = Center - HalfSize;
    FVector MaxBounds = Center + HalfSize;*/

    FVector Center = FVector((Max + Min).X / 2, (Max + Min).Y / 2, (Max + Min).Z / 2);
    FVector HalfSize = FVector((Max - Min).X / 2, (Max - Min).Y / 2, (Max - Min).Z / 2);
    FVector MinBounds = Min;
    FVector MaxBounds = Max;

    // Slab Method
    float Tmin = 0.001f; // Preventing self-intersection
    float Tmax = TMax;

    const FVector RayOrigin = Ray.GetOrigin();
    const FVector RayDirection = Ray.GetDirection();

    for (int Axis = 0; Axis < 3; Axis++)
    {
        // Test if ray is parallel to the current axis
        if (std::fabs(RayDirection[Axis]) < KINDA_SMALL_NUMBER)
        {
            // If the ray's origin is outside the current slab, there's no intersection
            if (RayOrigin[Axis] < MinBounds[Axis] || RayOrigin[Axis] > MaxBounds[Axis])
            {
                return false;
            }
        }
        else {
            // Calculate the intersection parameters(t - values) for the current axis's planes. (slap?)
            float t1 = (MinBounds[Axis] - RayOrigin[Axis]) / RayDirection[Axis];
            float t2 = (MaxBounds[Axis] - RayOrigin[Axis]) / RayDirection[Axis];

            // Ensure T1 is always the smaller t-value and T2 is the larger. (T1 is closer intersection)
            if (t1 > t2)    std::swap(t1, t2);

            // Update the overall intersection interval [tmin, tmax] to the overlapping part ~
            Tmin = max(Tmin, t1);
            Tmax = min(Tmax, t2);

            // If there's no overlapping interval -> the ray has missed the cube. ~~
            if (Tmin >= Tmax)
            {
                return false;
            }
        }
    }

    UE_LOG("  L %f %f %f", Center.X, Center.Y, Center.Z);
    UE_LOG("  L %f %f %f", HalfSize.X, HalfSize.Y, HalfSize.Z);
    UE_LOG("  L %f %f %f", MinBounds.X, MinBounds.Y, MinBounds.Z);
    UE_LOG("  L %f %f %f", MaxBounds.X, MaxBounds.Y, MaxBounds.Z);

    // Hit confirmed ~!~!
    OutHit.Time = Tmin;     // closest hit
    OutHit.Point = Ray.At(Tmin);

    // Calculate hit normal
    FVector HitPointLocal = OutHit.Point - Center;
    FVector AbsHitPoint = HitPointLocal.GetAbs();

    if (AbsHitPoint.X > AbsHitPoint.Y && AbsHitPoint.X > AbsHitPoint.Z)
    {
        OutHit.normal = FVector(Sign(HitPointLocal.X), 0.0f, 0.0f);
    }
    else if (AbsHitPoint.Y > AbsHitPoint.Z)
    {
        OutHit.normal = FVector(0.0f, Sign(HitPointLocal.Y), 0.0f);
    }
    else
    {
        OutHit.normal = FVector(0.0f, 0.0f, Sign(HitPointLocal.Z));
    }

    UE_LOG("Cube Hit!");
    return true;
}