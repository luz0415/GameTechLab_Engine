#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <commdlg.h> 

#include "Scene.h"
#include "ObjectPicker.h"

namespace json
{ 
    class JSON;
}

class USceneManager
{
private:
    USceneManager();
    ~USceneManager();
    USceneManager(const USceneManager&) = delete;
    USceneManager& operator=(const USceneManager&) = delete;

public:
    static USceneManager* Get()
    {
        static USceneManager Instance;
        return &Instance;
    }

    json::JSON LoadScene(const std::string& path);
    void SaveScene(const std::string& path, const json::JSON& sceneJson);
    std::wstring OpenFileDialog();
    USceneData LoadUSceneData(const std::string& path);
    Primitive ParsePrimitive(const json::JSON& j);

    json::JSON LoadJSONByExplorer();
    USceneData LoadUSceneDataByExplorer();
    USceneData JSONToUSceneData(json::JSON& j);
    json::JSON USceneDataToJSON(const USceneData& sceneData);

    void LoadSceneByExplorer();
    void SaveSceneByName(const string& path);
    void LoadNewScene();

    void ResetResources();

    void SetHWND(HWND hWnd) { g_hWnd = hWnd; }
    HWND GetHWND() { return g_hWnd; }

    UScene* GetCurrentScene() { 
        if (CurrentScene)
        {
            return CurrentScene;
        }

        CurrentScene = new UScene();
        return CurrentScene; 
    }

    void SetObjectPickerCamera();
    UObjectPicker* GetObjectPicker() const { return ObjectPicker; }

private:
    UObjectPicker* ObjectPicker = nullptr;
    UScene* CurrentScene = nullptr;
    HWND g_hWnd;
};