#include "SceneManager.h"
#include "json.hpp"

using namespace json;

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

    p.Location.X = (float)j.at("Location").at(0).ToFloat();
    p.Location.Y = (float)j.at("Location").at(1).ToFloat();
    p.Location.Z = (float)j.at("Location").at(2).ToFloat();
    p.Rotation.X = (float)j.at("Rotation").at(0).ToFloat();
    p.Rotation.Y = (float)j.at("Rotation").at(1).ToFloat();
    p.Rotation.Z = (float)j.at("Rotation").at(2).ToFloat();
    p.Scale.X = (float)j.at("Scale").at(0).ToFloat();
    p.Scale.Y = (float)j.at("Scale").at(1).ToFloat();
    p.Scale.Z = (float)j.at("Scale").at(2).ToFloat();
    
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

void USceneManager::LoadSceneByExplorer()
{
    json::JSON sceneJSON = LoadJSONByExplorer();
    UScene* scene = new UScene(JSONToUSceneData(sceneJSON));

    Get()->CurrentScene = scene;
}