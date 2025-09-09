#include "Scene.h"
#include "SphereComp.h"
#include "CubeComp.h"
#include "Camera.h"
#include "ObjectFactory.h"
#include "SceneManager.h"
#include "Math.h"

UScene::UScene()
{
	//USceneData tempSceneData = USceneManager::LoadUSceneDataByExplorer();
	//
	//for (auto primitive : tempSceneData.PrimArray)
	//{
	//	UPrimitiveComponent* obj = PrimToPrimComp(primitive);
	//	Objects.push_back(obj);
	//}

	USphereComp* Sph1 = FObjectFactory::Get()->ConstructObject<USphereComp>();
	Sph1->SetWorldLocation(FVector(0.f, 5.f, 0.f));

	UCubeComp* Cube1 = FObjectFactory::Get()->ConstructObject<UCubeComp>();
	Cube1->SetWorldLocation(FVector(0.f, 0.f, 5.f));	
	Cube1->SetWorldRotation(FVector(0.f, 40.f, 40.f));

	Objects.push_back(Sph1);
	Objects.push_back(Cube1);
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

void UScene::InitCamera()
{
	RECT Rect;
	//USceneManager* SManager = USceneManager::Get();
	GetClientRect(USceneManager::Get()->GetHWND(), &Rect);
	const int Width = Rect.right - Rect.left;
	const int Height = Rect.bottom - Rect.top;
	const FVector Eye = FVector(0, 3, -5);
	const FVector At = FVector(0, 0, 0);
	const FVector Up = FVector(0, 1, 0);
	const float Angle = 90.f;
	const float RadAngle = DegreeToRadians(Angle);

	CurrentCamera = new UCamera(Eye, At, Up, RadAngle, (float)Width / (float)Height, 0.1f, 100.f);
}