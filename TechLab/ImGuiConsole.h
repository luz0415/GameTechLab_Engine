#pragma once

#include <memory>

#include "ImGuiWindow.h"
#include "ImGuiAppConsole.h"
#include "ImGui/imgui.h"

class UImGuiConsole : public IImGuiWindow
{
public:
	UImGuiConsole();
	~UImGuiConsole();

	virtual void Render() override;
	void AddLog(const char* fmt, ...) IM_FMTARGS(2);
	void AddLogV(const char* fmt, va_list args);

	ImGuiAppConsole* GetAppConsole() { return AppConsole; }

private:
	ImGuiAppConsole* AppConsole = nullptr;
};