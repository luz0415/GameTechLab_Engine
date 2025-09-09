#include "SphereComp.h"
#include "BoundingSphere.h"

USphereComp::USphereComp() : UPrimitiveComponent()
{
	SetPrimitiveType(EPrimitiveType::Sphere);
	SetBoundingVolume(new FBoundingSphere(FVector(0.0f, 0.0f, 0.0f), 1.f));
}