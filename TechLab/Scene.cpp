#include "Scene.h"
#include "ObjectFactory.h"
#include "SceneManager.h"

UScene::UScene()
{
	//USceneData tempSceneData = USceneManager::LoadUSceneDataByExplorer();
	//
	//for (auto primitive : tempSceneData.PrimArray)
	//{
	//	UPrimitiveComponent* obj = PrimToPrimComp(primitive);
	//	Objects.push_back(obj);
	//}
}

UScene::UScene(const USceneData& sceneData)
{
	CopyPrimComp(sceneData);
}

UScene::UScene(const std::string& path)
{
	USceneData sceneData = USceneManager::LoadUSceneData(path);
	CopyPrimComp(sceneData);
}

UScene::~UScene()
{
	for (auto& sceneComp : Objects)
	{
		delete sceneComp;
		sceneComp = nullptr;
	}
}

UPrimitiveComponent* UScene::PrimToPrimComp(const Primitive& primitive)
{
	UPrimitiveComponent* pPrimComp = FObjectFactory::Get()->ConstructObject<UPrimitiveComponent>();

	if (primitive.Type == "Sphere")
	{
		pPrimComp->SetPrimitiveType(EPrimitiveType::Sphere);
	}
	else if (primitive.Type == "Cube")
	{
		pPrimComp->SetPrimitiveType(EPrimitiveType::Cube);
	}
	else if (primitive.Type == "Custom")
	{
		pPrimComp->SetPrimitiveType(EPrimitiveType::Custom);
	}
	else
	{
		return nullptr;
	}

	pPrimComp->SetWorldLocation(primitive.Location);
	pPrimComp->SetWorldRotation(primitive.Rotation);
	pPrimComp->SetWorldScale(primitive.Scale);

	return pPrimComp;
}

void UScene::CopyPrimComp(const USceneData& sceneData)
{
	for (auto& primitive : sceneData.PrimArray)
	{
		UPrimitiveComponent* obj;
		Objects.push_back(obj);
	}
}

void UScene::Render() 
{
	for (const auto& elem : Objects)
	{
		elem->Render();
	}
}
