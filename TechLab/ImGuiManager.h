#pragma once

#include <vector>

#include "ImGuiConsole.h" 

class UImGuiManager
{
public:
	UImGuiManager();
	~UImGuiManager();

	void Init();
	void Release();

	void Render();

	UImGuiConsole* GetConsole() { return Console; }

private:
	std::vector<IImGuiWindow*> ImGuiArray;
	UImGuiConsole* Console = nullptr;
};