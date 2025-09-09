#pragma once

#include "ImGui/imgui.h"
#include "ImGuiWindow.h"
#include "PrimitiveType.h"
#include "Vector.h"

struct FSpawnObjectProperty
{
	EPrimitiveType Type;
	int SpawnNum;
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
	void SpawnActor();

private:
	FSpawnObjectProperty SpawnProperty;
	FCameraProperty CameraProperty;
	char SceneNameBuffer[128] = "";
	//bool bOrthogonal = true;
};

