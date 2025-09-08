#pragma once
#include "Matrix.h"
#include "Vector.h"

class UCamera
{
public:
	UCamera(
		const FVector& InPosition,
		const FVector& InTarget,
		const FVector& InUpDirection,
		float InFovYRad,
		float InAspectRatio,
		float InNearZ,
		float InFarZ
	) noexcept;

	virtual ~UCamera() = default;

	const FMatrix& GetViewMatrix() const noexcept { return ViewMatrix; }
	const FMatrix& GetProjectionMatrix() const noexcept { return ProjectionMatrix; }
	const FVector& GetEye() const noexcept { return Eye; }

	const float GetRoll() { return Roll; }
	const float GetPitch() { return Pitch; }
	const float GetYaw() { return Yaw; }	
	const float GetFOVInAngle();

	void SetEye(const FVector eye) { Eye = eye; }
	void SetEyeX(const float x) { Eye.X = x; }
	void SetEyeY(const float y) { Eye.Y = y; }
	void SetEyeZ(const float z) { Eye.Z = z; }
	void SetRoll(const float roll) { Roll = roll; }
	void SetPitch(const float pitch) { Pitch = pitch; }
	void SetYaw(const float yaw) { Yaw = yaw; }
	void SetFOVWithAngle(const float fov);

	void HandleInput(const struct FInput& Input, float DeltaTime);
	void UpdateAspectRatio(float InAspectRatio);
	void Update();

	void UpdateEventByImGui();

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

	float Roll;
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