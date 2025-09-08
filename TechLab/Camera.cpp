#include "Camera.h"
#include "Math.h"

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
	, Yaw(0.0f)
	, Pitch(0.0f)
	, MoveLeftRight(0.0f)
	, MoveBackForward(0.0f)
	, MoveUpDown(0.0f)
	, MovementSpeed(10.0f)
	, RotationSpeed(0.002f)
	, CameraForward(FVector(0.f, 0.f, 1.f))
	, CameraRight(FVector(1.f, 0.f, 0.f))
	, CameraUp(FVector(0.f, 1.f, 0.f))
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void Camera::HandleInput(const FInput& Input, float DeltaTime)
{
	if (Input.bFront)
	{
		MoveBackForward += MovementSpeed * DeltaTime;
	}
	if (Input.bBack)
	{
		MoveBackForward -= MovementSpeed * DeltaTime;
	}
	if (Input.bLeft)
	{
		MoveLeftRight -= MovementSpeed * DeltaTime;
	}
	if (Input.bRight)
	{
		MoveLeftRight += MovementSpeed * DeltaTime;
	}
	if (Input.bUp)
	{
		MoveUpDown += MovementSpeed * DeltaTime;
	}
	if (Input.bDown)
	{
		MoveUpDown -= MovementSpeed * DeltaTime;
	}

	if (Input.bMouseRightClick)
	{
		if (Input.MouseX != 0 || Input.MouseY != 0)
		{
			Yaw += static_cast<float>(Input.MouseX) * RotationSpeed;
			Pitch += static_cast<float>(Input.MouseY) * RotationSpeed;
			// Clamp pitch
			Pitch = Max(-PI / 2.0f, Min(PI / 2.0f, Pitch));
		}
	}
}

void Camera::UpdateAspectRatio(float InAspectRatio)
{
	AspectRatio = InAspectRatio;
	UpdateProjectionMatrix();
}

void Camera::Update()
{
	FMatrix RotationMatrix = FMatrix::RotateMatrixX(-Pitch) * FMatrix::RotateMatrixY(Yaw);
	At = RotationMatrix.TransformVector(FVector(0.f, 0.f, 1.f));
	At.Normalize();

	CameraForward = At;
	CameraRight = RotationMatrix.TransformVector(FVector(1.f, 0.f, 0.f));
	CameraUp = RotationMatrix.TransformVector(FVector(0.f, 1.f, 0.f));

	Eye += CameraRight * MoveLeftRight;
	Eye += CameraForward * MoveBackForward;
	Eye += CameraUp * MoveUpDown;

	MoveLeftRight = 0.0f;
	MoveBackForward = 0.0f;
	MoveUpDown = 0.0f;

	At = Eye + At;
	Up = CameraUp;

	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix() noexcept
{
	ViewMatrix = FMatrix::ViewMatrix(Eye, At, Up);
}

void Camera::UpdateProjectionMatrix() noexcept
{
	ProjectionMatrix = FMatrix::ProjectionMatrix(FovYRad, AspectRatio, NearZ, FarZ);
}
