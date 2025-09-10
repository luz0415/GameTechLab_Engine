#include "ImGuiPropertyWindow.h"
#include "SceneManager.h"
#include "Core.h"
#include "Object.h"
#include "Math.h"
#include "Quaternion.h"
#include "GizmoArrow.h"

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


	ColoredButton("Translation", EGizmoControlMode::Translation);

	// Rotation
	static FVector lastRotationEuler = { 0,0,0 };

	//FVector currentRotationEuler = RadiansToDegree(TargetSceneComponent->GetWorldRotation());
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RX", &TargetProp.Rotation.X, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetSceneComponent)
		{
			TargetSceneComponent->SetWorldRotation(TargetProp.Rotation);
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RY", &TargetProp.Rotation.Y, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetSceneComponent)
		{
			TargetSceneComponent->SetWorldRotation(TargetProp.Rotation);
		}
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RZ", &TargetProp.Rotation.Z, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		if (TargetSceneComponent)
		{
			TargetSceneComponent->SetWorldRotation(TargetProp.Rotation);
		}
	}
	ImGui::SameLine();

	ColoredButton("Rotation", EGizmoControlMode::Rotation);

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

	ColoredButton("Scale", EGizmoControlMode::Scale);

	IPickable* Pickable = USceneManager::Get()->GetObjectPicker()->GetCurrentSelection();
	if (Pickable)
	{
		USceneComponent* PickableSceneComponent = dynamic_cast<USceneComponent*>(Pickable);
		if (PickableSceneComponent && !PickableSceneComponent->IsA(UGizmoArrow::StaticClass()))
		{
			TargetSceneComponent = PickableSceneComponent;
		}
	}
	else
	{
		TargetSceneComponent = nullptr;			
		TargetProp = { FVector(), FVector(), FVector() };
	}
	
	if (TargetSceneComponent)
	{
		TargetProp =
		{
			TargetSceneComponent->GetWorldLocation(),
			RadiansToDegree(TargetSceneComponent->GetWorldRotationAsEuler()),
			TargetSceneComponent->GetWorldScale()
		};			

		ImGui::Text("UUID: %d", TargetSceneComponent->UUID);
	}

	ImGui::End();
}

void UImGuiPropertyWindow::ColoredButton(const char* Label, EGizmoControlMode Mode)
{
	bool bPushed = false;

	if (CurrentGizmoControlMode == Mode)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		bPushed = true;
	}

	if (ImGui::Button(Label))
	{
		CurrentGizmoControlMode = Mode;
	}

	if (bPushed)
	{
		ImGui::PopStyleColor();
	}

}
//void USceneManager::LoadNewScene()
//{
//	UScene* newScene = new UScene();
//	FObjectFactory::Get()->ReleaseAllObjects();
//	CurrentScene = newScene;
//	ResetResources();
//}