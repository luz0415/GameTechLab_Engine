#pragma once
#include "Vector.h"

struct FHitRecord
{
	FVector Point;
	FVector normal;
	float Time;
};

struct FRay
{
public:
	FRay(const FVector& Origin, const FVector& Direction) : Origin(Origin), Direction(Direction), Time(0) {}

	FVector GetOrigin() const { return Origin; }
	FVector GetDirection() const { return Direction; }
	float GetTime() const { return Time; }

	// Same as function P(t)
	FVector At(float t) const { return Origin + t * Direction; }

private:
	FVector Origin;
	FVector Direction;
	float Time;
};