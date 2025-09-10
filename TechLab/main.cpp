#pragma comment(lib,"user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma once

#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "imGui/imgui_impl_win32.h"
#include "ImGuiManager.h"

#include "Core.h"
#include "Math.h"
#include "Renderer.h"
#include "ObjectFactory.h"
#include "Camera.h"
#include "SceneManager.h"
#include "SphereComp.h"
#include "CubeComp.h"
#include "ObjectPicker.h"
#include "TimeManager.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Debug

FInput GInput;
POINT GLastMousePosition;

// Object Picker (TEMP)
UObjectPicker* GObjectPicker = nullptr;

// Mouse Position (TEMP)
int GMouseX = 0;
int GMouseY = 0;

// Picking Debug Info (TEMP)
FVector GRayOrigin = { 0,0,0 };
FVector GRayDirection = { 0,0,0 };
int GTotalObjectCount = 0;
int GSuccessfulCastCount = 0;
float GLastBestT = 0.0f;
uint32_t GNewSelectionID = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
	{
		return true;
	}
	switch (message)
	{
	case WM_RBUTTONDOWN:
		GInput.bMouseRightClick = true;
		GetCursorPos(&GLastMousePosition);
		ScreenToClient(hWnd, &GLastMousePosition);
		break;
	case WM_RBUTTONUP:
		GInput.bMouseRightClick = false;
		break;
	case WM_LBUTTONUP:
		GInput.bMouseLeftClick = false;
		break;
	case WM_MOUSEMOVE:
		if (GInput.bMouseRightClick)
		{
			POINT currentMousePos;
			GetCursorPos(&currentMousePos);
			ScreenToClient(hWnd, &currentMousePos);
			GInput.MouseX = currentMousePos.x - GLastMousePosition.x;
			GInput.MouseY = GLastMousePosition.y - currentMousePos.y;
			GLastMousePosition = currentMousePos;
		}
		else
		{
			GInput.MouseX = 0;
			GInput.MouseY = 0;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			GInput.bMouseLeftClick = true;
			ImGuiIO& io = ImGui::GetIO();
			if (!io.WantCaptureMouse && USceneManager::Get()->GetObjectPicker())
			{
				POINT currentMousePos;
				GetCursorPos(&currentMousePos);
				ScreenToClient(hWnd, &currentMousePos);
				GMouseX = currentMousePos.x;
				GMouseY = currentMousePos.y;
				USceneManager::Get()->GetObjectPicker()->HandleMouseClick(static_cast<float>(currentMousePos.x), static_cast<float>(currentMousePos.y));
				USceneManager::Get()->GetObjectPicker()->HandleMouseDrag(static_cast<float>(currentMousePos.x), static_cast<float>(currentMousePos.y));
			}
			break;
		}
	case WM_KEYDOWN:
		switch (wParam)
		{
		 case 'W': GInput.bFront = true; break;
		 case 'S': GInput.bBack = true; break;
		 case 'A': GInput.bLeft = true; break;
		 case 'D': GInput.bRight = true; break;
		 case 'E': GInput.bUp = true; break;
		 case 'Q': GInput.bDown = true; break;
		default: break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		 case 'W': GInput.bFront = false; break;
		 case 'S': GInput.bBack = false; break;
		 case 'A': GInput.bLeft = false; break;
		 case 'D': GInput.bRight = false; break;
		 case 'E': GInput.bUp = false; break;
		 case 'Q': GInput.bDown = false; break;
		default: break;
		}
		break;
	case WM_SIZE:
	{
		WPARAM ResizeType = wParam;
		if (ResizeType == SIZE_MINIMIZED)
			return 0;
		UINT Width = LOWORD(lParam);
		UINT Height = HIWORD(lParam);

		URenderer::Get()->Resize(Width, Height);

		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WCHAR WindowClass[] = L"JungleWindowClass";
	WCHAR Title[] = L"Game Tech Lab";

	WNDCLASSW wndclass = { 0, WndProc, 0, 0, 0, 0, 0, 0, 0, WindowClass };
	RegisterClassW(&wndclass);

	HWND hWnd = CreateWindowExW(0, WindowClass, Title, WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080,
		nullptr, nullptr, hInstance, nullptr);

	URenderer* Renderer = URenderer::Get();
	Renderer->Create(hWnd);
	Renderer->CreateShader();

	USceneManager::Get()->Init();
	USceneManager::Get()->SetHWND(hWnd);
	USceneManager::Get()->GetCurrentScene()->InitCamera();
	USceneManager::Get()->SetObjectPickerCamera();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplWin32_Init((void*)hWnd);
	ImGui_ImplDX11_Init(Renderer->Device, Renderer->DeviceContext);

	ImGuiAppConsole* App = new ImGuiAppConsole();
	bool bIsExit = false;

	FTimeManager::Get()->Init();
	while (bIsExit == false)
	{
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				bIsExit = true;
				break;
			}
		}
		
		// Time Update
		FTimeManager::Get()->Update();
		float DeltaTime = FTimeManager::Get()->GetDeltaTime();

		// Camera Update
		UCamera* CurrentCamera = USceneManager::Get()->GetCurrentScene()->GetCurrentCamera();
		CurrentCamera->HandleInput(GInput, DeltaTime);
		CurrentCamera->Update();
		GInput.MouseX = 0; GInput.MouseY = 0;

		// Render
		Renderer->Prepare();

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		FObjectFactory::Get()->TickObjects(DeltaTime);
		USceneManager::Get()->GetCurrentScene()->Render();
		USceneManager::Get()->GetObjectPicker()->SubmitProxy();
		Renderer->RenderScene(CurrentCamera);

		UImGuiManager::Get()->Render();
		Renderer->SwapBuffer();
	}
	delete App;
	UImGuiManager::Get()->Release();
	Renderer->Release();

	return 0;
}
