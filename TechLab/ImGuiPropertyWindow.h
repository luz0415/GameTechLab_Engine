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

	FVector GetTranslation() const { return TargetProp.Translation; }
	FVector GetRotation() const { return TargetProp.Rotation; }
	FVector GetScale() const { return TargetProp.Scale; }

	void SetTranslation(const FVector& translation) { TargetProp.Translation = translation; }
	void SetRotation(const FVector& rotation) { TargetProp.Rotation = rotation; }
	void SetScale(const FVector& scale) { TargetProp.Scale = scale; }

private:
	class USceneComponent* TargetSceneComponent = nullptr;
	FObjectProperty TargetProp = {};
};