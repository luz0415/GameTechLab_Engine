#pragma once
#include "Matrix.h"
#include "Vector.h"

class Camera
{
public:
	Camera(
		const FVector& InPosition,
		const FVector& InTarget,
		const FVector& InUpDirection,
		float InFovYRad,
		float InAspectRatio,
		float InNearZ,
		float InFarZ
	) noexcept;

	virtual ~Camera() = default;

	const FMatrix& GetViewMatrix() const noexcept { return ViewMatrix; }
	const FMatrix& GetProjectionMatrix() const noexcept { return ProjectionMatrix; }

private:
	void UpdateViewMatrix() noexcept;
	void UpdateProjectionMatrix() noexcept;

private:
	FVector Eye;
	FVector At;
	FVector Up;

	float FovYRad;
	float AspectRatio;
	float NearZ;
	float FarZ;

	FMatrix ViewMatrix;
	FMatrix ProjectionMatrix;
};
