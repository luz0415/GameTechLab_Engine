#pragma once

#include "ImGui/imgui.h"
#include "ImGuiWindow.h"
#include "PrimitiveType.h"
#include "Vector.h"

struct FSpawnObjectProperty
{
	string Type = "Sphere";
	int SpawnNum = 1;
};

struct FCameraProperty
{
	float FOV;
	FVector CameraLocation;
	FVector CameraRotation;
};

class UImGuiControlPanel : public IImGuiWindow
{
public:
	virtual void Render() override;

private:
	FSpawnObjectProperty SpawnProperty;
	FCameraProperty CameraProperty;
	char SceneNameBuffer[128] = "";
	string SceneNameStr = "";
	bool bOrthogonal = true;
};

