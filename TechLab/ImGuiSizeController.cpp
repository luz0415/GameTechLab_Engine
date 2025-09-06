#include "ImGuiSizeController.h"

void UImGuiSizeController::Render()
{
	static float Position[3] = { 0 };

	SizeArray[0] = Position[0];
	SizeArray[1] = Position[1];
	SizeArray[2] = Position[2];

	ImGui::Begin("Jungle Property Window");

	ImGui::InputFloat3("Position", Position);

	// 현재 값 출력
	ImGui::Text("X: %.3f, Y: %.3f, Z: %.3f", SizeArray[0], SizeArray[1], SizeArray[2]);

	ImGui::End();
}
