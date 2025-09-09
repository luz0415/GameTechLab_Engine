#include "Scene.h"
#include "SphereComp.h"
#include "CubeComp.h"
#include "Camera.h"
#include "ObjectFactory.h"
#include "SceneManager.h"
#include "Math.h"
#include "EngineStatics.h"

UScene::UScene()
{
	//USceneData tempSceneData = USceneManager::LoadUSceneDataByExplorer();
	//
	//for (auto primitive : tempSceneData.PrimArray)
	//{
	//	UPrimitiveComponent* obj = PrimToPrimComp(primitive);
	//	Objects.push_back(obj);
	//}

	

	//UPrimitiveComponent* Sph1 = SpawnActor("Sphere");
	//Sph1->SetWorldLocation(FVector(0.f, 5.f, 0.f));
	//
	//UPrimitiveComponent* Cube1 = SpawnActor("Cube");
	//Cube1->SetWorldLocation(FVector(0.f, 0.f, 5.f));	
	//Cube1->SetWorldRotation(FVector(0.f, 40.f, 40.f));
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
	delete CurrentCamera;
}

UPrimitiveComponent* UScene::PrimToPrimComp(const Primitive& primitive)
{
	UPrimitiveComponent* pPrimComp = SpawnActor(primitive.Type);

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
	for (auto primitive : sceneData.PrimArray)
	{
		 PrimToPrimComp(primitive);
	}
}

void UScene::Render() 
{
	for (const auto& elem : Objects)
	{
		elem->SubmitProxy();
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

UPrimitiveComponent* UScene::SpawnActor(const string Type)
{
	if (Type == "Sphere")
	{
		USphereComp* SphComp = FObjectFactory::Get()->ConstructObject<USphereComp>();
		Objects.push_back(SphComp);
		return SphComp;
	}
	else if (Type == "Cube")
	{
		UCubeComp* CubeComp = FObjectFactory::Get()->ConstructObject<UCubeComp>();
		Objects.push_back(CubeComp);
		return CubeComp;
	}
	else
	{
		return nullptr;
	}
}

USceneData UScene::MakeSceneData()
{
	USceneData sceneData;

	sceneData.Version = 1;
	sceneData.NextUUID = UEngineStatics::NextUUID;

	for (auto& primComp : Objects)
	{
		Primitive prim;
		prim.UUID = primComp->UUID;
		prim.Location = primComp->GetWorldLocation();
		prim.Rotation = primComp->GetWorldRotation();
		prim.Scale = primComp->GetWorldScale();

		switch (primComp->GetPrimitiveType())
		{
		case EPrimitiveType::Sphere :
			prim.Type = "Sphere";
			break;
		case EPrimitiveType::Cube:
			prim.Type = "Cube";
			break;
		default:
			prim.Type = "What?";
		}

		sceneData.PrimArray.push_back(prim);
	}

	return sceneData;
}
