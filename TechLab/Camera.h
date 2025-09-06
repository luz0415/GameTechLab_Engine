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

	void HandleInput(const struct FInput& Input, float DeltaTime);
	void Update();

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

	float Yaw;
	float Pitch;

	float MoveLeftRight;
	float MoveBackForward;
	float MoveUpDown;

	float MovementSpeed;
	float RotationSpeed;

	FVector CameraForward;
	FVector CameraRight;
	FVector CameraUp;
};

struct FInput
{
	bool bFront = false;
	bool bBack = false;
	bool bLeft = false;
	bool bRight = false;
	bool bUp = false;
	bool bDown = false;
	bool bMouseRightClick = false;
	long MouseX = 0;
	long MouseY = 0;
};