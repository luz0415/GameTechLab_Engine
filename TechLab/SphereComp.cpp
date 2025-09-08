#include "SphereComp.h"
#include "Renderer.h"
#include "Ray.h"

USphereComp::USphereComp() : UPrimitiveComponent()
{
	SetPrimitiveType(EPrimitiveType::Sphere);
}

bool USphereComp::Raycast(const FRay& Ray, float TMax, FHitRecord& OutHit)
{
	FVector Center = GetWorldLocation();
	float Radius = GetWorldScale().X;	// Assume uniform scale

	FVector OC = Ray.GetOrigin() - Center;

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
			return true;
		}
		Temp = (-B + sqrt(Discriminant)) / (2.0f * A);
		if (Temp < TMax && Temp > 0.001f)
		{
			OutHit.Time = Temp;
			OutHit.Point = Ray.At(Temp);
			OutHit.normal = (OutHit.Point - Center) / Radius;
			return true;
		}
	}
	return false;
}

void USphereComp::OnSelected()
{
	bSelected = true;
}

void USphereComp::OnDeselected()
{
	bSelected = false;
}