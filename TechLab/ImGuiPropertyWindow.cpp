#include "ImGuiPropertyWindow.h"
#include "SceneManager.h"
#include "Core.h"
#include "Object.h"
#include "Math.h"
#include "Quaternion.h"

#define INPUT_BOX_WIDTH 70

void UImGuiPropertyWindow::Render()
{
	ImGui::SetNextWindowPos(ImVec2(600, 0), ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Appearing);

	ImGui::Begin("Jungle Property Window");

	// Translation
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##TX", &TargetProp.Translation.X, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetSceneComponent)
		{
			TargetSceneComponent->SetWorldLocation(TargetProp.Translation);
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##TY", &TargetProp.Translation.Y, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetSceneComponent)
		{
			TargetSceneComponent->SetWorldLocation(TargetProp.Translation);
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##TZ", &TargetProp.Translation.Z, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetSceneComponent)
		{
			TargetSceneComponent->SetWorldLocation(TargetProp.Translation);
		}
	}
	ImGui::SameLine();

	ImGui::Text("Translation");

	// Rotation
	static FVector lastRotationEuler = { 0,0,0 };

	//FVector currentRotationEuler = RadiansToDegree(TargetSceneComponent->GetWorldRotation());
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RX", &TargetProp.Rotation.X, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetSceneComponent)
		{
			FVector Radians = DegreeToRadians(TargetProp.Rotation);
			TargetSceneComponent->SetWorldRotation(FQuaternion::FromYawPitchRollLH(Radians.Y, Radians.X, Radians.Z));
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RY", &TargetProp.Rotation.Y, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetSceneComponent)
		{
			FVector Radians = DegreeToRadians(TargetProp.Rotation);
			TargetSceneComponent->SetWorldRotation(FQuaternion::FromYawPitchRollLH(Radians.Y, Radians.X, Radians.Z));
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RZ", &TargetProp.Rotation.Z, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetSceneComponent)
		{
			FVector Radians = DegreeToRadians(TargetProp.Rotation);
			TargetSceneComponent->SetWorldRotation(FQuaternion::FromYawPitchRollLH(Radians.Y, Radians.X, Radians.Z));
		}
	}
	ImGui::SameLine();

	ImGui::Text("Rotation");

	// Scale
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##SX", &TargetProp.Scale.X, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetSceneComponent)
		{
			TargetSceneComponent->SetWorldScale(TargetProp.Scale);
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##SY", &TargetProp.Scale.Y, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetSceneComponent)
		{
			TargetSceneComponent->SetWorldScale(TargetProp.Scale);
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##SZ", &TargetProp.Scale.Z, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetSceneComponent)
		{
			TargetSceneComponent->SetWorldScale(TargetProp.Scale);
		}
	}

	ImGui::SameLine();

	ImGui::Text("Scale");

	IPickable* Pickable = USceneManager::Get()->GetObjectPicker()->GetCurrentSelection();
	if (Pickable)
	{
		USceneComponent* PickableSceneComponent = dynamic_cast<USceneComponent*>(Pickable);
		if (PickableSceneComponent)
		{
			TargetSceneComponent = PickableSceneComponent;
			TargetProp =
			{
				TargetSceneComponent->GetWorldLocation(),
				RadiansToDegree(TargetSceneComponent->GetWorldRotationAsEuler()),
				TargetSceneComponent->GetWorldScale()
			};
		}
	}
	else
	{
		TargetSceneComponent = nullptr;			
		TargetProp = { FVector(), FVector(), FVector() };
	}
	
	if (TargetSceneComponent)
	{
		ImGui::Text("UUID: %d", TargetSceneComponent->UUID);
	}

	ImGui::End();
}
//void USceneManager::LoadNewScene()
//{
//	UScene* newScene = new UScene();
//	FObjectFactory::Get()->ReleaseAllObjects();
//	CurrentScene = newScene;
//	ResetResources();
//}