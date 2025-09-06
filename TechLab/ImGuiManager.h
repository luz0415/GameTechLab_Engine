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

private:
	std::vector<IImGuiWindow*> ImGuiArray;
	unique_ptr<UImGuiConsole> Console = nullptr;
};