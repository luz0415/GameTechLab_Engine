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
//#include "Shapes.h"
#include "SimpleConstants.h"
#include "MeshManager.h"

#include <memory>
#include "Object.h"
#include "ImGuiManager.h"
#include "Core.h"
#include "ImGuiAppConsole.h"
#include "ImGuiSizeController.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
	{
		return true;
	}
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
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

	URenderer renderer;
	renderer.Create(hWnd);
	renderer.CreateShader();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init((void*)hWnd);
	ImGui_ImplDX11_Init(renderer.Device, renderer.DeviceContext);

	UImGuiManager* ImGuiManager = new UImGuiManager();
	ImGuiAppConsole* App = new ImGuiAppConsole();
	UImGuiSizeController* SC = dynamic_cast<UImGuiSizeController*>((ImGuiManager->GetImGuiArray())[0]);

	int idCube = FMeshManager::Instance()->RegisterMesh(renderer.Device, EShapeType::Cube);
	FMeshResource* CubeResource = FMeshManager::Instance()->Get(idCube);
	int idSphere = FMeshManager::Instance()->RegisterMesh(renderer.Device, EShapeType::Sphere);
	FMeshResource* SphereResource = FMeshManager::Instance()->Get(idSphere);
	ID3D11Buffer* CubeConstant = renderer.CreateConstantBuffer<FSimpleConstant>();
	float xpos = 0; //trans
	float ypos = 0;
	float rotz = 2; //rot
	float roty = 2; //rot
	float scale = 1;
	float tmp = 0;
	float eyepos = -5.f;

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

		renderer.Prepare();

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		UE_LOG("xpos: %f", xpos);
		UE_LOG("ypos: %f ", ypos);

		if (ImGuiManager)
			ImGuiManager->GetConsole()->GetAppConsole()->Draw("Console", nullptr);

		if (SC)
			xpos = SC->GetSize()[0];

		xpos += 0.1f;
		ypos += 0.1f;
		if (xpos > 2.f)
		{
			xpos = -2.f;
		}
		if (ypos > 2.f)
		{
			ypos = -2.f;
		}
		rotz += 0.05f;
		roty += 0.05f;
		tmp += 1;
		scale += sin(tmp);


		FMatrix trans = FMatrix::TransformMatrix(FVector(xpos, 0, 0));
		FMatrix rot = FMatrix::RotateMatrixZ(rotz)*FMatrix::RotateMatrixY(roty);
		FMatrix sc = FMatrix::ScaleMatrix(FVector(1,1,1));
		FMatrix model = sc * rot * trans;

		//model
		//eyepos += 0.01f;
		FVector eye = FVector(0, 0, -5);
		FVector at = FVector(0, 0, 0);
		FVector up = FVector(0, 1, 0);
		FMatrix view = FMatrix::ViewMatrix(eye, at, up);
		float angle = 90.f;
		float radangle = angle * 3.1415926535f / 180.f;
		RECT rect;
		GetClientRect(hWnd, &rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		FMatrix projection = FMatrix::ProjectionMatrix(radangle,(float)width/(float)height , 0.1f, 100.f);

		renderer.UpdateConstantBuffer(CubeConstant, model,view,projection);
		renderer.PrepareShader(CubeConstant);
		renderer.RenderPrimitive(CubeResource->VertexBuffer, CubeResource->NumVerticies);

		trans = FMatrix::TransformMatrix(FVector(0, ypos, 0));
		model = sc * rot * trans;

		renderer.UpdateConstantBuffer(CubeConstant, model, view, projection);
		renderer.PrepareShader(CubeConstant);
		renderer.RenderPrimitive(SphereResource->VertexBuffer, SphereResource->NumVerticies);

		ImGuiManager->Render();
		
		renderer.SwapBuffer();
	}
	renderer.ReleaseShader();
	renderer.Release();

	ImGuiManager->Release();


	return 0;
}
