#pragma once

#include <vector>

#include "ImGuiConsole.h"
#include "ImGuiSizeController.h"

class UImGuiManager
{
public:
	UImGuiManager();
	~UImGuiManager();

	void Init();
	void Release();

	void Render();

	UImGuiConsole* GetConsole() { return Console; }
	std::vector<IImGuiWindow*> GetImGuiArray() { return ImGuiArray; }

private:
	std::vector<IImGuiWindow*> ImGuiArray;
	UImGuiConsole* Console = nullptr;
};