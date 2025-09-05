#pragma once

#pragma comment(lib,"user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <d3d11.h>
#include <d3dcompiler.h>
#include <Windows.h> // HWND 타입을 위해 추가
#include "Vector.h"
#include "VertexSimple.h"

class URenderer
{
public:
	// 멤버 변수
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;
	IDXGISwapChain* SwapChain = nullptr;

	ID3D11Texture2D* FrameBuffer = nullptr;
	ID3D11RenderTargetView* FrameBufferRTV = nullptr;
	ID3D11RasterizerState* RasterizerState = nullptr;
	ID3D11Buffer* ConstantBuffer = nullptr;

	FLOAT ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f };
	D3D11_VIEWPORT ViewportInfo;

	ID3D11VertexShader* SimpleVertexShader;
	ID3D11PixelShader* SimplePixelShader;
	ID3D11InputLayout* SimpleInputLayout;
	unsigned int Stride;

	struct FConstants
	{
		FVector Offset;
		float Radius;
		float Pad;
	};

public:
	// 생성 및 해제 함수
	void Create(HWND hWindow);
	void Release();

	// 버퍼 스왑
	void SwapBuffer();

	// 셰이더 관련 함수
	void CreateShader();
	void ReleaseShader();

	// 렌더링 준비 함수
	void Prepare();
	void PrepareShader();

	// 렌더링 함수
	void RenderPrimitive(ID3D11Buffer* pBuffer, UINT numVertices);

	// 버퍼 생성 및 해제 함수
	ID3D11Buffer* CreateVertexBuffer(FVertexSimple* vertices, UINT byteWidth);
	void ReleaseVertexBuffer(ID3D11Buffer* vertexBuffer);
	void CreateConstantBuffer();
	void ReleaseConstantBuffer();

	// 상수 버퍼 업데이트
	void UpdateConstant(FVector Offset, float Radius);

private:
	// 내부 헬퍼 함수
	void CreateDeviceAndSwapChain(HWND hWindow);
	void ReleaseDeviceAndSwapChain();

	void CreateFrameBuffer();
	void ReleaseFrameBuffer();

	void CreateRasterizerState();
	void ReleaseRasterizerState();
};