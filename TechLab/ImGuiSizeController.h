#pragma once

#include "ImGuiWindow.h"
#include "ImGui/imgui.h"
#include <array>

class UImGuiSizeController : public IImGuiWindow
{
public:
	virtual void Render() override;
	std::array<float, 3> GetSize() { return SizeArray; }

private:
	std::array<float, 3> SizeArray = { 0 };
};