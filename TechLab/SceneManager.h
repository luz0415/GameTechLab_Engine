#pragma once

#include <iostream>
#include <fstream>
#include <windows.h>
#include <commdlg.h> 

#include "Core.h"
#include "Scene.h"
#include "ObjectPicker.h"

namespace json
{ 
    class JSON;
}

class USceneManager : public UObject
{
    // UObject Derived Class Must Declaration
public:
    static UObject* StaticUObjectFactory()
    {
        return new USceneManager();
    }

    static UClass* StaticClass()
    {
        static UClass Class(FString("USceneManager"), StaticUObjectFactory, UObject::StaticClass());
        return &Class;
    }

    virtual UClass* GetClass() const
    {
        return StaticClass();
    }

private:
    USceneManager();
    USceneManager(const USceneManager&) = delete;
    USceneManager& operator=(const USceneManager&) = delete;

public:
    ~USceneManager();
    static USceneManager* Get()
    {
        static USceneManager* Instance;
        if (Instance == nullptr) Instance = FObjectFactory::Get()->ConstructObject<USceneManager>();

        return Instance;
    }

    void Init();

    json::JSON LoadScene(const FString& path);
    void SaveScene(const FString& path, const json::JSON& sceneJson);
    std::wstring OpenFileDialog();
    FSceneData LoadUSceneData(const FString& path);
    FPrimitiveData ParsePrimitive(const json::JSON& j);

    json::JSON LoadJSONByExplorer();
    FSceneData LoadUSceneDataByExplorer();
    FSceneData JSONToUSceneData(json::JSON& j);
    json::JSON USceneDataToJSON(const FSceneData& sceneData);

    void LoadSceneByExplorer();
    void SaveSceneByName(const FString& path);
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
