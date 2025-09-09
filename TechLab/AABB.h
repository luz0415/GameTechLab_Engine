#include "BoundingVolume.h"
#include "Vector.h"

struct FRay;
struct FMeshData;
struct FAABB : public IBoundingVolume
{
    FVector Min;
    FVector Max;

    FAABB(const FVector& InMin, const FVector& InMax) : Min(InMin), Max(InMax) {}
    FAABB(const FMeshData& MeshData);

    bool RaycastHit(const FRay& Ray, float TMax, FHitRecord& OutHit) const override;
    EBoundingVolumeType GetType() const override { return EBoundingVolumeType::AABB; }
};