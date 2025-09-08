#pragma once
#include "Core.h"
#include "ImGuiConsole.h" 

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
	std::vector<IImGuiWindow*> GetImGuiArray() { return ImGuiArray; }

private:
	TArray<IImGuiWindow*> ImGuiArray;
	UImGuiConsole* Console = nullptr;
};