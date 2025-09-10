#include "Scene.h"
#include "SphereComp.h"
#include "CubeComp.h"
#include "Camera.h"
#include "ObjectFactory.h"
#include "SceneManager.h"
#include "Math.h"
#include "EngineStatics.h"

UScene::UScene() : UObject()
{
	//FSceneData tempSceneData = USceneManager::LoadUSceneDataByExplorer();
	//
	//for (auto primitive : tempSceneData.PrimDatas)
	//{
	//	UPrimitiveComponent* obj = PrimToPrimComp(primitive);
	//	Objects.push_back(obj);
	//}
}

UScene::~UScene()
{
	for (auto& SceneComp : Primitives)
	{
		SceneComp->Destroy();
	}
	CurrentCamera->Destroy();
}

UPrimitiveComponent* UScene::PrimToPrimComp(const FPrimitiveData& PrimData)
{
	UPrimitiveComponent* PrimComp = SpawnActor(PrimData.Type);

	if (PrimData.Type == "Sphere")
	{
		PrimComp->SetPrimitiveType(EPrimitiveType::Sphere);
	}
	else if (PrimData.Type == "Cube")
	{
		PrimComp->SetPrimitiveType(EPrimitiveType::Cube);
	}
	else if (PrimData.Type == "Custom")
	{
		PrimComp->SetPrimitiveType(EPrimitiveType::Custom);
	}
	else
	{
		return nullptr;
	}

	PrimComp->SetWorldLocation(PrimData.Location);
	PrimComp->SetWorldRotation(PrimData.Rotation);
	PrimComp->SetWorldScale(PrimData.Scale);

	return PrimComp;
}

void UScene::CopyPrimComp(const FSceneData& SceneData)
{
	for (auto& PrimData : SceneData.PrimDatas)
	{
		 PrimToPrimComp(PrimData);
	}
}

void UScene::Render() 
{
	for (const auto& Prim : Primitives)
	{
		Prim->SubmitProxy();
	}
}

void UScene::InitCamera()
{
	RECT Rect;
	GetClientRect(USceneManager::Get()->GetHWND(), &Rect);
	const int Width = Rect.right - Rect.left;
	const int Height = Rect.bottom - Rect.top;
	const FVector Eye = FVector(0, 3, -5);
	const FVector At = FVector(0, 0, 0);
	const FVector Up = FVector(0, 1, 0);
	const float Angle = 90.f;
	const float RadAngle = DegreeToRadians(Angle);

	CurrentCamera = FObjectFactory::Get()->ConstructObject<UCamera>();
	CurrentCamera->Init(Eye, At, Up, RadAngle, (float)Width / (float)Height, 0.1f, 100.f);
}

UPrimitiveComponent* UScene::SpawnActor(const FString Type)
{
	if (Type == "Sphere")
	{
		USphereComp* SphComp = FObjectFactory::Get()->ConstructObject<USphereComp>();
		Primitives.push_back(SphComp);
		return SphComp;
	}
	else if (Type == "Cube")
	{
		UCubeComp* CubeComp = FObjectFactory::Get()->ConstructObject<UCubeComp>();
		Primitives.push_back(CubeComp);
		return CubeComp;
	}
	else
	{
		return nullptr;
	}
}

FSceneData UScene::MakeSceneData()
{
	FSceneData SceneData;

	SceneData.Version = 1;
	SceneData.NextUUID = UEngineStatics::NextUUID;

	for (auto& PrimComp : Primitives)
	{
		FPrimitiveData Prim;
		Prim.UUID = PrimComp->UUID;
		Prim.Location = PrimComp->GetWorldLocation();
		Prim.Rotation = PrimComp->GetWorldRotation();
		Prim.Scale = PrimComp->GetWorldScale();
		Prim.Type = PrimitiveTypeToString(PrimComp->GetPrimitiveType());
		SceneData.PrimDatas.push_back(Prim);
	}

	return SceneData;
}
