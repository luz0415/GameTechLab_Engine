#pragma once

#include "ImGuiWindow.h"
#include "ImGui/imgui.h"
#include "Vector.h"

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

private:
	class USceneComponent* TargetSceneComponent = nullptr;
	FObjectProperty TargetProp = {};
};