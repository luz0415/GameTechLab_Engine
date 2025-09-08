#include "ImGuiPropertyWindow.h"

#define INPUT_BOX_WIDTH 70

void UImGuiPropertyWindow::Render()
{
	ImGui::SetNextWindowPos(ImVec2(600, 0), ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Appearing);

	ImGui::Begin("Jungle Property Window");

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##TX", &Translation.X, 0, 0, "%.3f");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##TY", &Translation.X, 0, 0, "%.3f");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##TZ", &Translation.X, 0, 0, "%.3f");
	ImGui::SameLine();
	ImGui::Text("Translation");

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RX", &Translation.X, 0, 0, "%.3f");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RY", &Translation.X, 0, 0, "%.3f");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##RZ", &Translation.X, 0, 0, "%.3f");
	ImGui::SameLine();
	ImGui::Text("Rotation");

	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##SX", &Translation.X, 0, 0, "%.3f");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##SY", &Translation.X, 0, 0, "%.3f");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(INPUT_BOX_WIDTH);
	ImGui::InputFloat("##SZ", &Translation.X, 0, 0, "%.3f");
	ImGui::SameLine();
	ImGui::Text("Scale");

	ImGui::End();
}
