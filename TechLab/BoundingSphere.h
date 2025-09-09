#include "BoundingVolume.h"
#include "Vector.h"

struct FBoundingSphere : public IBoundingVolume
{
    FVector Center;
    float Radius;

    FBoundingSphere(const FVector& InCenter, float InRadius) : Center(InCenter), Radius(InRadius) {}

    bool RaycastHit(const FRay& Ray, float TMax, FHitRecord& OutHit) const override;
    EBoundingVolumeType GetType() const override { return EBoundingVolumeType::Sphere; }
};