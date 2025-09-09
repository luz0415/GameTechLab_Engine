#include "ImGuiControlPanel.h"
#include "SceneManager.h"

#define CURRENT_CAMERA USceneManager::Get()->GetCurrentScene()->GetCurrentCamera()

void UImGuiControlPanel::Render()
{
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_Appearing);

	static int currentItem = 0;
	const char* items[] = { "Sphere", "Cube" };

	CameraProperty.CameraLocation = CURRENT_CAMERA->GetEye();
	CameraProperty.CameraRotation = { CURRENT_CAMERA->GetRoll(), CURRENT_CAMERA->GetYaw(),CURRENT_CAMERA->GetPitch() };
	CameraProperty.FOV = CURRENT_CAMERA->GetFOVInAngle();

	//ImGuiStyle& style = ImGui::GetStyle();
	//style.ButtonTextAlign = ImVec2(0.5, 0.5);

	ImGui::Begin("Jungle Control Panel");
	
	ImGui::Text("Hello Jungle World!");

	ImGui::Text("FPS = %d (0 ms)");

	ImGui::Separator(); // ------------------

	if (ImGui::BeginCombo("Primitive", items[currentItem]))
	{
		for (int n = 0; n < IM_ARRAYSIZE(items); n++)
		{
			bool isSelected = (currentItem == n);
			if (ImGui::Selectable(items[n], isSelected))
				currentItem = n;

			if (isSelected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	
	ImGui::Button("Spawn", ImVec2(100, 0));
	ImGui::SameLine();

	ImGui::SetNextItemWidth(218);
	ImGui::InputScalar("Number of spawn", ImGuiDataType_S32, &(SpawnProperty.SpawnNum));

	ImGui::Separator(); // ------------------

	strncpy(SceneNameBuffer, SceneNameStr.c_str(), sizeof(SceneNameBuffer));
	SceneNameBuffer[sizeof(SceneNameBuffer) - 1] = '\0';

	if (ImGui::InputText("Scene Name", SceneNameBuffer, ImGuiInputTextFlags_EnterReturnsTrue))
	{
		SceneNameStr = SceneNameBuffer;
	}

	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		SceneNameStr = SceneNameBuffer;
	}

	if (ImGui::Button("New Scene"))
	{
		USceneManager::Get()->LoadNewScene();
	}

	if (ImGui::Button("Save Scene"))
	{
		//USceneManager::SaveScene(SceneNameBuffer);
		USceneManager::Get()->SaveSceneByName(SceneNameStr + ".Scene");
	}

	if (ImGui::Button("Load Scene"))
	{
		USceneManager::LoadSceneByExplorer();
		USceneManager::Get()->GetCurrentScene()->InitCamera();
	}

	ImGui::Separator(); // ------------------

	{
		USceneManager::Get()->GetCurrentScene()->GetCurrentCamera();
	}

	bool isp = USceneManager::Get()->GetCurrentScene()->GetCurrentCamera()->IsOrthogonal();

	if (ImGui::Checkbox("Orthogonal", &isp))
	{
		CURRENT_CAMERA->UpdateEventByImGui();
	}


	ImGui::SetNextItemWidth(286);
	ImGui::InputFloat("FOV", &(CameraProperty.FOV), 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		CURRENT_CAMERA->SetFOVWithAngle(CameraProperty.FOV);
		CURRENT_CAMERA->UpdateEventByImGui();
	}

	// Camera Location
	ImGui::SetNextItemWidth(90);
	ImGui::InputFloat("##CLX", &(CameraProperty.CameraLocation.X), 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		CURRENT_CAMERA->SetEyeX(CameraProperty.CameraLocation.X);
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(90);
	ImGui::InputFloat("##CLY", &(CameraProperty.CameraLocation.Y), 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		CURRENT_CAMERA->SetEyeY(CameraProperty.CameraLocation.Y);
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(90);
	ImGui::InputFloat("##CLZ", &(CameraProperty.CameraLocation.Z), 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		CURRENT_CAMERA->SetEyeZ(CameraProperty.CameraLocation.Z);
	}
	ImGui::SameLine();

	ImGui::Text("Camera Location");
	
	// Camera Rotation
	ImGui::SetNextItemWidth(90);
	ImGui::InputFloat("##CRX", &(CameraProperty.CameraRotation.X), 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		CURRENT_CAMERA->SetRoll(CameraProperty.CameraRotation.X);
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(90);
	ImGui::InputFloat("##CRY", &(CameraProperty.CameraRotation.Y), 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		CURRENT_CAMERA->SetYaw(CameraProperty.CameraRotation.Y);
	}
	ImGui::SameLine();

	ImGui::SetNextItemWidth(90);
	ImGui::InputFloat("##CRZ", &(CameraProperty.CameraRotation.Z), 0, 0, "%.3f");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		CURRENT_CAMERA->SetPitch(CameraProperty.CameraRotation.Z);
	}
	ImGui::SameLine();
	ImGui::Text("Camera Rotation");
	
	//if (io.WantCaptureKeyboard || io.WantCaptureMouse)
	//{
	//	여기서 게임 입력 처리 스킵
	//	continue;
	//}
	// 나중에 폴리싱할때 고려해보기
	

	ImGui::End();
}


void UImGuiControlPanel::SpawnActor()
{
}

