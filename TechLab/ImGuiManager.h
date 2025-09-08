#pragma once

#include <vector>

#include "ImGuiConsole.h" 

class UImGuiManager
{
private:
	UImGuiManager() = default;
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

private:
	std::vector<IImGuiWindow*> ImGuiArray;
	UImGuiConsole* Console = nullptr;
};