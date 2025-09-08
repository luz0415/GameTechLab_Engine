#pragma comment(lib,"user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

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

#include "SphereComp.h"
#include "CubeComp.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

Camera* MainCamera;
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
	case WM_SIZE:
	{
		WPARAM ResizeType = wParam;
		if (ResizeType == SIZE_MINIMIZED)
			return 0;
		UINT Width = LOWORD(lParam);
		UINT Height = HIWORD(lParam);
		float AspectRatio = (float)Width / (float)Height;

		if (MainCamera) { MainCamera->UpdateAspectRatio(AspectRatio); }

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
	// Test
	USceneComponent* Test = FObjectFactory::Get()->ConstructObject<USphereComp>();
	FObjectFactory::Get()->ConstructObject<UCubeComp>()->Translate(FVector(2.7f, 0.0f, 0.0f));
	FObjectFactory::Get()->ConstructObject<UCubeComp>()->Translate(FVector(0.0f, 5.0f, 5.0f));

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init((void*)hWnd);
	ImGui_ImplDX11_Init(Renderer->Device, Renderer->DeviceContext);

	ImGuiAppConsole* App = new ImGuiAppConsole();

	RECT Rect;
	GetClientRect(hWnd, &Rect);
	const int Width = Rect.right - Rect.left;
	const int Height = Rect.bottom - Rect.top;
	const FVector Eye = FVector(0, 0, -5);
	const FVector At = FVector(0, 0, 0);
	const FVector Up = FVector(0, 1, 0);
	const float Angle = 90.f;
	const float RadAngle = DegreeToRadians(Angle);
	MainCamera = new Camera(Eye, At, Up, RadAngle, (float)Width / (float)Height, 0.1f, 100.f);

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
		float DeltaTime = static_cast<float>(currentTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart;
		lastTime = currentTime;

		// Update Camera
		MainCamera->HandleInput(GInput, DeltaTime);
		MainCamera->Update();
		// Reset mouse delta after processing
		GInput.MouseX = 0;
		GInput.MouseY = 0;

		Renderer->Prepare();

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		UImGuiManager::Get()->GetConsole()->GetAppConsole()->Draw("Console", nullptr);

		Test->AddRelativeRotationZ(10);
		FObjectFactory::Get()->TickObjects(DeltaTime);

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		Renderer->RenderScene(MainCamera);
		Renderer->SwapBuffer();
	}
	Renderer->ReleaseShader();
	Renderer->Release();
	
	delete App;
	delete MainCamera;

	return 0;
}
