#pragma once

#include "ImGuiConsole.h"
#include "ImGuiPropertyWindow.h"
#include "ImGuiControlPanel.h"

class UImGuiManager
{
private:
	UImGuiManager();
    ~UImGuiManager();
    UImGuiManager(const UImGuiManager&) = delete;
    UImGuiManager& operator=(const UImGuiManager&) = delete;

public:
	static UImGuiManager* Get()
    {
        static UImGuiManager Instance;
        return &Instance;
    }

	void Init();
	void Release();
	void Render();

	UImGuiConsole* GetConsole() { return Console; }
	UImGuiControlPanel* GetControlPanel() { return ControlPanel; }
	UImGuiPropertyWindow* GetPropertyWindow() { return PropertyWindow; }
	TArray<IImGuiWindow*> GetImGuiArray() { return ImGuiArray; }

private:
	TArray< IImGuiWindow*> ImGuiArray;
	UImGuiConsole* Console = nullptr;
	UImGuiControlPanel* ControlPanel = nullptr;
	UImGuiPropertyWindow* PropertyWindow = nullptr;
};