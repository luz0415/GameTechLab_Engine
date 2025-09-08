#include "ImGuiManager.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGuiPropertyWindow.h"

UImGuiManager::UImGuiManager()
{
    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO();
    // ImGui_ImplWin32_Init((void*)hWnd);
    // ImGui_ImplDX11_Init(renderer.Device, renderer.DeviceContext);

    // 위 코드는 hWnd, renderer 등을 필요로 하므로 WinMain에 추가하기

    Console = new UImGuiConsole();
    ControlPanel = new UImGuiControlPanel();
    PropertyWindow = new UImGuiPropertyWindow();

    Init();

}

UImGuiManager::~UImGuiManager()
{
}


void UImGuiManager::Init()
{
    // renderer.Prepare 다음에 추가

    //UImGuiPropertyWindow* PW = new UImGuiPropertyWindow();
    //
    //ImGuiArray.push_back(PW);
}

void UImGuiManager::Release()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    // main loop 후에 추가
}

void UImGuiManager::Render()
{
    //for (int i = 0; i < ImGuiArray.size(); i++)
    //{
    //    ImGuiArray[i]->Render();
    //}
    Console->GetAppConsole()->Draw("Console", nullptr);
    PropertyWindow->Render();
    ControlPanel->Render();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}