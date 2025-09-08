#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <commdlg.h> 

#include "Scene.h"

namespace json
{ 
    class JSON;
}

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

    static json::JSON LoadScene(const std::string& path);
    static void SaveScene(const std::string& path, const json::JSON& sceneJson);
    static std::wstring OpenFileDialog();
    static USceneData LoadUSceneData(const std::string& path);
    static Primitive ParsePrimitive(const json::JSON& j);

    static json::JSON LoadJSONByExplorer();
    static USceneData LoadUSceneDataByExplorer();
    static USceneData JSONToUSceneData(json::JSON& j);

    static void LoadSceneByExplorer();

    UScene* GetCurrentScene()
    {
        if (CurrentScene)
        {
            return CurrentScene;
        }

        CurrentScene = new UScene();

        return CurrentScene;
    }
	
private:
    UScene* CurrentScene = nullptr;
};