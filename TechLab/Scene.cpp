#include "Scene.h"

UScene::UScene()
{
}

UScene::UScene(const USceneData& sceneData)
{

	for (auto& primitive : sceneData.PrimArray)
	{
		USceneComponent* obj;
		Objects.push_back(obj);
	}
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
	UPrimitiveComponent* pPrimComp = new UPrimitiveComponent();

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

