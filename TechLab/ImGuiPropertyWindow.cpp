#include "ImGuiPropertyWindow.h"
#include "SceneManager.h"
#include "Core.h"
#include "Object.h"

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
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RX", &TargetProp.Rotation.X, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetComp)
		{
			TargetComp->SetWorldRotation(TargetProp.Rotation);
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RY", &TargetProp.Rotation.Y, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		{
			TargetComp->SetWorldRotation(TargetProp.Rotation);
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RZ", &TargetProp.Rotation.Z, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		{
			TargetComp->SetWorldRotation(TargetProp.Rotation);
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

	if (!USceneManager::Get()->GetObjectPicker()->GetCurrentSelection().empty())
	{
		if (TargetObject != dynamic_cast<UObject*>(USceneManager::Get()->GetObjectPicker()->GetCurrentSelection()[0]))
		{
			TargetObject = dynamic_cast<UObject*>(USceneManager::Get()->GetObjectPicker()->GetCurrentSelection()[0]);
			TargetComp = dynamic_cast<USceneComponent*>(TargetObject);
			TargetProp =
			{
				TargetComp->GetWorldLocation(),
				TargetComp->GetWorldRotation(),
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
