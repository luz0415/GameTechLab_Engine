#pragma once
#include "Core.h"
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
	TArray<IImGuiWindow*> ImGuiArray;
	UImGuiConsole* Console = nullptr;
};