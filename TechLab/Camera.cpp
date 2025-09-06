#include "Camera.h"

Camera::Camera(
	const FVector& InPosition, const FVector& InTarget, const FVector& InUpDirection,
	float InFovYRad, float InAspectRatio, float InNearZ, float InFarZ) noexcept
	: Eye(InPosition)
	, At(InTarget)
	, Up(InUpDirection)
	, FovYRad(InFovYRad)
	, AspectRatio(InAspectRatio)
	, NearZ(InNearZ)
	, FarZ(InFarZ)
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void Camera::UpdateViewMatrix() noexcept
{
	ViewMatrix = FMatrix::ViewMatrix(Eye, At, Up);
}

void Camera::UpdateProjectionMatrix() noexcept
{
	ProjectionMatrix = FMatrix::ProjectionMatrix(FovYRad, AspectRatio, NearZ, FarZ);
}
