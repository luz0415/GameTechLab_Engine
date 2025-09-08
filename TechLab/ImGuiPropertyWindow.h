#pragma once

#include "ImGuiWindow.h"
#include "ImGui/imgui.h"
#include "Vector.h"

class UImGuiPropertyWindow : public IImGuiWindow
{
public:
	virtual void Render() override;

	FVector GetTranslation() const { return Translation; }
	FVector GetRotation() const { return Rotation; }
	FVector GetScale() const { return Scale; }

	void SetTranslation(const FVector& translation) { Translation = translation; }
	void SetRotation(const FVector& rotation) { Rotation = rotation; }
	void SetScale(const FVector& scale) { Scale = scale; }

private:
	FVector Translation;
	FVector Rotation;
	FVector Scale;
};