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
		if (TargetComp)
		{
			TargetComp->SetWorldLocation(TargetProp.Translation);
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##TY", &TargetProp.Translation.Y, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetComp)
		{
			TargetComp->SetWorldLocation(TargetProp.Translation);
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##TZ", &TargetProp.Translation.Z, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetComp)
		{
			TargetComp->SetWorldLocation(TargetProp.Translation);
		}
	}
	ImGui::SameLine();

	ImGui::Text("Translation");

	// Rotation
	static FVector lastRotationEuler = { 0,0,0 };

	//FVector currentRotationEuler = RadiansToDegree(TargetComp->GetWorldRotation());
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RX", &TargetProp.Rotation.X, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetComp)
		{
			FVector Radians = DegreeToRadians(TargetProp.Rotation);
			TargetComp->SetWorldRotation(FQuaternion::FromYawPitchRollLH(Radians.Y, Radians.X, Radians.Z));
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RY", &TargetProp.Rotation.Y, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetComp)
		{
			FVector Radians = DegreeToRadians(TargetProp.Rotation);
			TargetComp->SetWorldRotation(FQuaternion::FromYawPitchRollLH(Radians.Y, Radians.X, Radians.Z));
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RZ", &TargetProp.Rotation.Z, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetComp)
		{
			FVector Radians = DegreeToRadians(TargetProp.Rotation);
			TargetComp->SetWorldRotation(FQuaternion::FromYawPitchRollLH(Radians.Y, Radians.X, Radians.Z));
		}
	}
	ImGui::SameLine();

	ImGui::Text("Rotation");

	// Scale
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##SX", &TargetProp.Scale.X, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetComp)
		{
			TargetComp->SetWorldScale(TargetProp.Scale);
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##SY", &TargetProp.Scale.Y, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetComp)
		{
			TargetComp->SetWorldScale(TargetProp.Scale);
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##SZ", &TargetProp.Scale.Z, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetComp)
		{
			TargetComp->SetWorldScale(TargetProp.Scale);
		}
	}

	ImGui::SameLine();

	ImGui::Text("Scale");

	if (!USceneManager::Get()->GetObjectPicker()->GetCurrentSelection())
	{
		if (TargetObject != dynamic_cast<UObject*>(USceneManager::Get()->GetObjectPicker()->GetCurrentSelection()))
		{
			TargetObject = dynamic_cast<UObject*>(USceneManager::Get()->GetObjectPicker()->GetCurrentSelection());
			TargetComp = dynamic_cast<USceneComponent*>(TargetObject);
			TargetProp =
			{
				TargetComp->GetWorldLocation(),
				RadiansToDegree(TargetComp->GetWorldRotationAsEuler()),
				TargetComp->GetWorldScale()
			};
		}
	}
	
	if (TargetObject)
	{
		ImGui::Text("%d", TargetObject->UUID);
	}

	ImGui::End();
}
