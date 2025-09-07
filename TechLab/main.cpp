#include <windows.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "imGui/imgui_impl_win32.h"

#pragma comment(lib,"user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <d3d11.h>
#include <d3dcompiler.h>
#include "Renderer.h"
#include "SimpleConstants.h"
#include "MeshManager.h"

#include <memory>
#include "ObjectFactory.h"
#include "SphereComp.h"
#include "ImGuiManager.h"
#include "Core.h"
#include "Math.h"
#include "ImGuiAppConsole.h"

#include "Camera.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

FInput GInput;
POINT GLastMousePosition;

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
	case WM_KEYDOWN:
		switch (wParam)
		{
		case'w': case 'W': GInput.bFront = true; break;
		case's': case 'S': GInput.bBack = true; break;
		case'a': case 'A': GInput.bLeft = true; break;
		case'd': case 'D': GInput.bRight = true; break;
		case'e': case 'E': GInput.bUp = true; break;
		case'q': case 'Q': GInput.bDown = true; break;
		default: break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case'w': case 'W': GInput.bFront = false; break;
		case's': case 'S': GInput.bBack = false; break;
		case'a': case 'A': GInput.bLeft = false; break;
		case'd': case 'D': GInput.bRight = false; break;
		case'e': case 'E': GInput.bUp = false; break;
		case'q': case 'Q': GInput.bDown = false; break;
		default: break;
		}
		break;
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
	// Test
	USceneComponent* Test = FObjectFactory::Get()->ConstructObject<USphereComp>();
	FObjectFactory::Get()->ConstructObject<USphereComp>()->Translate(FVector(5.0f, 0.0f, 0.0f));
	auto& Objects = FObjectFactory::Get()->GetObjectArray();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init((void*)hWnd);
	ImGui_ImplDX11_Init(Renderer->Device, Renderer->DeviceContext);

	UImGuiManager* ImGuiManager = new UImGuiManager();
	ImGuiAppConsole* App = new ImGuiAppConsole();

	RECT rect;
	GetClientRect(hWnd, &rect);
	const int width = rect.right - rect.left;
	const int height = rect.bottom - rect.top;

	const FVector eye = FVector(0, 0, -5);
	const FVector at = FVector(0, 0, 0);
	const FVector up = FVector(0, 1, 0);
	const float angle = 90.f;
	const float radangle = angle * PI / 180.f;

	Camera MyCamera(eye, at, up, radangle, (float)width / (float)height, 0.1f, 100.f);

	// DeltaTime Calculation
	LARGE_INTEGER lastTime, currentTime, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&lastTime);

	bool bIsExit = false;
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

		// Calculate DeltaTime
		QueryPerformanceCounter(&currentTime);
		float deltaTime = static_cast<float>(currentTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart;
		lastTime = currentTime;

		// Update Camera
		MyCamera.HandleInput(GInput, deltaTime);
		MyCamera.Update();
		// Reset mouse delta after processing
		GInput.MouseX = 0;
		GInput.MouseY = 0;

		Renderer->Prepare();

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		float xpos = 0;
		float ypos = 0;
		float roty = 0;
		float rotz = 0;
		float scale = 1;

		if (ImGuiManager)
			ImGuiManager->GetConsole()->GetAppConsole()->Draw("Console", nullptr);

		FObjectFactory::Get()->TickObjects(deltaTime);
		Test->AddRelativeRotationZ(10);
		const TArray<UObject*> Objects = FObjectFactory::Get()->GetObjectArray();
		for (UObject* Object : Objects)
		{
			if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Object))
			{
				PrimComp->Render();
			}
		}

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		Renderer->RenderScene(MyCamera);
		Renderer->SwapBuffer();
	}
	Renderer->ReleaseShader();
	Renderer->Release();

	return 0;
}
