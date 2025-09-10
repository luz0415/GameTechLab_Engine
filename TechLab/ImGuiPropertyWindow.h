#pragma once

#include "ImGuiWindow.h"
#include "ImGui/imgui.h"
#include "Vector.h"
#include "GizmoControlMode.h"

struct FObjectProperty
{
	FVector Translation;
	FVector Rotation;
	FVector Scale;
};

class UImGuiPropertyWindow : public IImGuiWindow
{
public:
	virtual void Render() override;
	void ColoredButton(const char* Label, EGizmoControlMode Mode);

private:
	class USceneComponent* TargetSceneComponent = nullptr;
	FObjectProperty TargetProp = {};
	EGizmoControlMode CurrentGizmoControlMode = EGizmoControlMode::Translation;
};