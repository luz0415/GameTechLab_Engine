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
	UPrimitiveComponent* primComp;
	
	if (primitive.Type == "Sphere")
	{
		primComp->Type
	}
	else if (primitive.Type == "Cube")
	{
		primComp->
	}

	primitive.Location;

	pUSceneComp = new SphereComponent()
	return nullptr;
}

