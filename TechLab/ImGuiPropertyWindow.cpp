#include "ImGuiPropertyWindow.h"
#include "SceneManager.h"

#define INPUT_BOX_WIDTH 70

void UImGuiPropertyWindow::Render()
{
	ImGui::SetNextWindowPos(ImVec2(600, 0), ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Appearing);

	ImGui::Begin("Jungle Property Window");

	// Translation
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##TX", &Translation.X, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		USceneManager::Get()->GetCurrentScene()->GetCurrentCamera()->SetEyeX(Translation.X);
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##TY", &Translation.Y, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		USceneManager::Get()->GetCurrentScene()->GetCurrentCamera()->SetEyeY(Translation.Y);
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##TZ", &Translation.Z, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		USceneManager::Get()->GetCurrentScene()->GetCurrentCamera()->SetEyeZ(Translation.Z);
	}
	ImGui::SameLine();

	ImGui::Text("Translation");

	// Rotation
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RX", &Rotation.X, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		USceneManager::Get()->GetCurrentScene()->GetCurrentCamera()->SetEyeX(Translation.X);
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RY", &Rotation.Y, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		USceneManager::Get()->GetCurrentScene()->GetCurrentCamera()->SetEyeX(Translation.X);
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RZ", &Rotation.Z, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		USceneManager::Get()->GetCurrentScene()->GetCurrentCamera()->SetEyeX(Translation.X);
	}
	ImGui::SameLine();

	ImGui::Text("Rotation");

	// Scale
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##SX", &Scale.X, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		USceneManager::Get()->GetCurrentScene()->GetCurrentCamera()->SetEyeX(Translation.X);
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##SY", &Scale.Y, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		USceneManager::Get()->GetCurrentScene()->GetCurrentCamera()->SetEyeX(Translation.X);
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##SZ", &Scale.Z, 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		USceneManager::Get()->GetCurrentScene()->GetCurrentCamera()->SetEyeX(Translation.X);
	}
	ImGui::SameLine();

	ImGui::Text("Scale");

	ImGui::End();
}
