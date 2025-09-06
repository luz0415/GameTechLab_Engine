#include "SceneFileManager.h"

USceneFileManager::~USceneFileManager()
{

}

// Path에서 경로 받아와서 JSON 객체로 반환
JSON USceneFileManager::LoadScene(const std::string& path)
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
void USceneFileManager::SaveScene(const std::string& path, const JSON& sceneJson)
{
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("파일 쓰기 실패: " + path);
    }

    file << sceneJson.dump(1, "  "); // depth=1, tab="  " → 보기 좋은 포맷
}

// Path에서 Scene 파일을 열어서 SceneData로 반환
SceneData USceneFileManager::LoadSceneData(const std::string& path)
{
    json::JSON root = LoadScene(path);

    SceneData scene;
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
std::wstring USceneFileManager::OpenFileDialog()
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
Primitive USceneFileManager::ParsePrimitive(const json::JSON& j)
{
    Primitive p;
    p.Type = j.at("Type").ToString();

    for (int i = 0; i < 3; i++) {
        p.Location[i] = (float)j.at("Location").at(i).ToFloat();
        p.Rotation[i] = (float)j.at("Rotation").at(i).ToFloat();
        p.Scale[i] = (float)j.at("Scale").at(i).ToFloat();
    }
    return p;
}

JSON USceneFileManager::LoadSceneByExplorer()
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

SceneData USceneFileManager::LoadSceneDataByExplorer()
{
    JSON tempjson = LoadSceneByExplorer();
    SceneData scenedata = JSONToSceneData(tempjson);

    return scenedata;
}

SceneData USceneFileManager::JSONToSceneData(JSON& j)
{
    SceneData scene;

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
    return SceneData();
}