#include "SceneManager.h"
#include "json.hpp"
#include "ObjectPicker.h"
#include "ObjectFactory.h"

using namespace json;

USceneManager::USceneManager()
{
    CurrentScene = new UScene();
    //CurrentScene->InitCamera();
    ObjectPicker = new UObjectPicker();

   
}

USceneManager::~USceneManager()
{
}

// Path에서 경로 받아와서 JSON 객체로 반환
JSON USceneManager::LoadScene(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("파일 열기 실패: " + path);
    }

    std::string content((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    return JSON::Load(content);
}

// JSON 객체를 Path에 저장
void USceneManager::SaveScene(const std::string& path, const JSON& sceneJson)
{
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("파일 쓰기 실패: " + path);
    }

    file << sceneJson.dump(1, "  "); // depth=1, tab="  " → 보기 좋은 포맷
}

// Path에서 Scene 파일을 열어서 USceneData로 반환
USceneData USceneManager::LoadUSceneData(const std::string& path)
{
    JSON root = LoadScene(path);

    USceneData scene;

    scene.Version = (int)root["Version"].ToInt();
    scene.NextUUID = (int)root["NextUUID"].ToInt();

    auto& prims = root["Primitives"];
    for (auto& kv : prims.ObjectRange())
    {
        int id = std::stoi(kv.first);

        Primitive p = ParsePrimitive(kv.second);

        p.UUID = id;

        scene.PrimArray.push_back(p);
    }

    return scene;
}

// 파일 탐색기를 염
std::wstring USceneManager::OpenFileDialog()
{
    wchar_t filename[MAX_PATH] = { 0 };

    OPENFILENAMEW ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr; // 부모 윈도우 핸들 (없으면 nullptr)
    ofn.lpstrFilter = L"Scene Files\0*.Scene\0All Files\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    ofn.lpstrDefExt = L"Scene";

    if (GetOpenFileNameW(&ofn))
    {
        return filename; // 사용자가 선택한 경로
    }
    return L""; // 취소 시
}

// JSON 객체를 Primitive 단위로 분해하여 Primitive로 반환
Primitive USceneManager::ParsePrimitive(const JSON& j)
{
    Primitive p;
    p.Type = j.at("Type").ToString();

    FVector loc =
    {
        (float)j.at("Location").at(0).ToFloat(),
        (float)j.at("Location").at(1).ToFloat(),
        (float)j.at("Location").at(2).ToFloat()
    };

    FVector rot =
    {
        (float)j.at("Rotation").at(0).ToFloat(),
        (float)j.at("Rotation").at(1).ToFloat(),
        (float)j.at("Rotation").at(2).ToFloat()
    };

    FVector sca =
    {
        (float)j.at("Scale").at(0).ToFloat(),
        (float)j.at("Scale").at(1).ToFloat(),
        (float)j.at("Scale").at(2).ToFloat()
    };

    p.Location = loc;
    p.Rotation = rot;
    p.Scale = sca;

    return p;
}

JSON USceneManager::LoadJSONByExplorer()
{
    JSON tempjson;

    std::wstring filepath = OpenFileDialog();
    if (!filepath.empty()) {
        // wstring → string 변환 (UTF-8 단순 변환)
        std::string path(filepath.begin(), filepath.end());

        try {
            tempjson = LoadScene(path);

            std::cout << tempjson << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "로드 실패: " << e.what() << "\n";
        }
    }
    else {
        std::cout << "파일 선택 취소됨\n";
    }
    return tempjson;
}

USceneData USceneManager::LoadUSceneDataByExplorer()
{
    JSON tempjson = LoadJSONByExplorer();
    USceneData USceneData = JSONToUSceneData(tempjson);

    return USceneData;
}

USceneData USceneManager::JSONToUSceneData(JSON& j)
{
    USceneData scene;

    scene.Version = (int)j["Version"].ToInt();
    scene.NextUUID = (int)j["NextUUID"].ToInt();

    auto& prims = j["Primitives"];
    for (auto& kv : prims.ObjectRange())
    {
        int id = std::stoi(kv.first);

        Primitive p = ParsePrimitive(kv.second);

        p.UUID = id;

        scene.PrimArray.push_back(p);
    }
    return scene;
}

json::JSON USceneManager::USceneDataToJSON(const USceneData& sceneData){

     JSON tempJSON;

     // 기본 정보
     tempJSON["Version"] = sceneData.Version;
     tempJSON["NextUUID"] = sceneData.NextUUID;

     JSON prims;

     for (auto& prim : sceneData.PrimArray)
     {
         JSON primJSON;

         // Type (클래스 이름이나 UPROPERTY로 저장된 문자열이라 가정)
         string type = prim.Type;

         primJSON["Type"] = type;

         // Location
         JSON loc = Array();
         loc.append(prim.Location.X);
         loc.append(prim.Location.Y);
         loc.append(prim.Location.Z);
         primJSON["Location"] = loc;

         // Rotation
         JSON rot = Array();
         rot.append(prim.Rotation.X);
         rot.append(prim.Rotation.Y);
         rot.append(prim.Rotation.Z);
         primJSON["Rotation"] = rot;

         // Scale
         JSON sca = Array();
         sca.append(prim.Scale.X);
         sca.append(prim.Scale.Y);
         sca.append(prim.Scale.Z);
         primJSON["Scale"] = sca;

         // UUID (컴포넌트에 UUID 필드가 있다고 가정)
         prims[std::to_string(prim.UUID)] = primJSON;
    }

    tempJSON["Primitives"] = prims;

    return tempJSON;
}

void USceneManager::LoadSceneByExplorer()
{
    json::JSON sceneJSON = LoadJSONByExplorer();

    FObjectFactory::Get()->ReleaseAllObjects();

    USceneData sceneData = JSONToUSceneData(sceneJSON);

    UScene* scene = new UScene(sceneData);

    Get()->CurrentScene = scene;
}

void USceneManager::SaveSceneByName(const string& path)
{
    SaveScene(path, USceneDataToJSON(USceneManager::Get()->GetCurrentScene()->MakeSceneData()));
}

void USceneManager::LoadNewScene()
{
    UScene* newScene = new UScene();
    delete ObjectPicker;
    delete CurrentScene;
    FObjectFactory::Get()->ReleaseAllObjects();
    CurrentScene = newScene;

    ObjectPicker = new UObjectPicker;
    GetCurrentScene()->InitCamera();
    newScene->InitCamera();
    SetObjectPickerCamera();
}

void USceneManager::SetObjectPickerCamera()
{
    ObjectPicker->SetCamera(CurrentScene->GetCurrentCamera());

    RECT Rect;
    GetClientRect(g_hWnd, &Rect);
    const int Width = Rect.right - Rect.left;
    const int Height = Rect.bottom - Rect.top;

    ObjectPicker->SetViewportSize(Width, Height);
}