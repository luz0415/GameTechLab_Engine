#include "BoundingSphere.h"
#include "Core.h"
#include "ImGuiManager.h"

bool FBoundingSphere::RaycastHit(const FRay& Ray, float TMax, FHitRecord& OutHit) const
{
	FVector OC = Ray.GetOrigin() - Center;

	// Assume uniform scale
	float A = Ray.GetDirection().Dot(Ray.GetDirection());
	float B = 2.0f * OC.Dot(Ray.GetDirection());
	float C = OC.Dot(OC) - Radius * Radius;

	float Discriminant = B * B - 4 * A * C;

	if (Discriminant > 0)
	{
		float Temp = (-B - sqrt(Discriminant)) / (2.0f * A);
		if (Temp < TMax && Temp > 0.001f)	// 0.001f to avoid self-intersection
		{
			OutHit.Time = Temp;
			OutHit.Point = Ray.At(Temp);
			OutHit.normal = (OutHit.Point - Center) / Radius;
			UE_LOG("Sphere Hit!");
			return true;
		}
		Temp = (-B + sqrt(Discriminant)) / (2.0f * A);
		if (Temp < TMax && Temp > 0.001f)
		{
			OutHit.Time = Temp;
			OutHit.Point = Ray.At(Temp);
			OutHit.normal = (OutHit.Point - Center) / Radius;
			UE_LOG("Sphere Hit!");
			return true;
		}
	}
	return false;
}