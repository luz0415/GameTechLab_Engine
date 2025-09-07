#pragma once

#pragma comment(lib,"user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <d3d11.h>
#include <d3dcompiler.h>
#include <Windows.h> // HWND 타입을 위해 추가
#include "Vector.h"
#include "VertexSimple.h"
#include "Matrix.h"
#include "Core.h"
#include "RenderProxy.h"

class URenderer
{
public:
	// Singleton
	static URenderer* Get()
	{
		static URenderer Instance;
		return &Instance;
	}

	// 멤버 변수
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;
	IDXGISwapChain* SwapChain = nullptr;

	ID3D11Texture2D* FrameBuffer = nullptr;
	ID3D11RenderTargetView* FrameBufferRTV = nullptr;
	ID3D11RasterizerState* RasterizerState = nullptr;
	ID3D11Buffer* VPConstantBuffer = nullptr;
	ID3D11Buffer* MConstantBuffer = nullptr;

	FLOAT ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f };
	D3D11_VIEWPORT ViewportInfo;

	ID3D11VertexShader* SimpleVertexShader;
	ID3D11PixelShader* SimplePixelShader;
	ID3D11InputLayout* SimpleInputLayout;

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
	void RenderScene(const class Camera& SceneCamera);

	// 버퍼 생성 및 해제 함수
	ID3D11Buffer* CreateVertexBuffer(FVertexSimple* vertices, UINT byteWidth);
	void ReleaseVertexBuffer(ID3D11Buffer* vertexBuffer);
	void ReleaseConstantBuffer(ID3D11Buffer* ConstantBuffer);
	template<typename T>
	void UpdateConstantBuffer(ID3D11Buffer* ConstantBuffer, const T* Input)
	{
		if (ConstantBuffer)
		{
			D3D11_MAPPED_SUBRESOURCE ConstantBufferMSR;

			DeviceContext->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ConstantBufferMSR);
			T* Constants = (T*)ConstantBufferMSR.pData;
			memcpy(Constants, Input, sizeof(T));
			DeviceContext->Unmap(ConstantBuffer, 0);
		}
	}

	template<typename T>
	ID3D11Buffer* CreateConstantBuffer()
	{
		ID3D11Buffer* constbuffer;
		D3D11_BUFFER_DESC constantbufferdesc = {};
		constantbufferdesc.ByteWidth = sizeof(T) + 0xf & 0xfffffff0; // 16바이트 배수로 맞춤
		constantbufferdesc.Usage = D3D11_USAGE_DYNAMIC;
		constantbufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantbufferdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		Device->CreateBuffer(&constantbufferdesc, nullptr, &constbuffer);
		return constbuffer;
	}

	void SubmitProxy(const FRenderProxy& InRenderProxy);

private:
	// 내부 헬퍼 함수
	void CreateDeviceAndSwapChain(HWND hWindow);
	void ReleaseDeviceAndSwapChain();

	void CreateFrameBuffer();
	void ReleaseFrameBuffer();

	void CreateRasterizerState();
	void ReleaseRasterizerState();

	TArray<FRenderProxy> RenderProxyList;
};