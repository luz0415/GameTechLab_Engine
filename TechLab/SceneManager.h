#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <commdlg.h> 

#include "json.hpp"
#include "Scene.h"

using namespace json;

class USceneManager
{
private:
    USceneManager() = default;
    ~USceneManager();
    USceneManager(const USceneManager&) = delete;
    USceneManager& operator=(const USceneManager&) = delete;

public:
    static USceneManager* Get()
    {
        static USceneManager Instance;
        return &Instance;
    }

    JSON LoadScene(const std::string& path);
    void SaveScene(const std::string& path, const JSON& sceneJson);
    std::wstring OpenFileDialog();
    USceneData LoadUSceneData(const std::string& path);
    Primitive ParsePrimitive(const json::JSON& j);

    JSON LoadSceneByExplorer();
    USceneData LoadUSceneDataByExplorer();
    USceneData JSONToUSceneData(JSON& j);
	
private:
};