#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <commdlg.h> 

#include "json.hpp"

using namespace json;

struct Primitive
{
    int UUID;

    float Location[3];
    float Rotation[3];
    float Scale[3];

    string Type;
};

struct SceneData
{
    int Version;
    int NextUUID;

    std::vector<Primitive> PrimArray;
};

class USceneFileManager
{
private:
    USceneFileManager() = default;
    ~USceneFileManager();
    USceneFileManager(const USceneFileManager&) = delete;
    USceneFileManager& operator=(const USceneFileManager&) = delete;

public:
    static USceneFileManager* Get()
    {
        static USceneFileManager Instance;
        return &Instance;
    }

    JSON LoadScene(const std::string& path);
    void SaveScene(const std::string& path, const JSON& sceneJson);
    std::wstring OpenFileDialog();
    SceneData LoadSceneData(const std::string& path);
    Primitive ParsePrimitive(const json::JSON& j);

    JSON LoadSceneByExplorer();
    SceneData LoadSceneDataByExplorer();
    SceneData JSONToSceneData(JSON& j);
	
private:
};