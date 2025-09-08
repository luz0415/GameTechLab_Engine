#pragma once

struct FRay;
struct FHitRecord;
class IRaycastable
{
public:
    virtual ~IRaycastable() = default;

    virtual bool Raycast(const FRay& Ray, float TMax, FHitRecord& OutHit) = 0;
};