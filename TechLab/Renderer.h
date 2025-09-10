#pragma once

#pragma comment(lib,"user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")


#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#include "Core.h"
#include "Vector.h"
#include "Matrix.h"
#include "RenderProxy.h"
#include "PrimitiveType.h"
#include "GizmoRenderer.h"
class URenderer
{
public:
	// Singleton
	static URenderer* Get()
	{
		static URenderer Instance;
		return &Instance;
	}

public:
	void Create(HWND hWindow);
	void CreateVisualInterfaces();
	void Release();

	void SwapBuffer();

	void CreateShader();
	void ReleaseShader();

	void Prepare();
	void PrepareShader();

	void RenderScene(const class UCamera* SceneCamera);

	// Constant Buffer
	template<typename T>
	ID3D11Buffer* CreateConstantBuffer()
	{
		ID3D11Buffer* constbuffer;
		D3D11_BUFFER_DESC constantbufferdesc = {};
		constantbufferdesc.ByteWidth = sizeof(T) + 0xf & 0xfffffff0;
		constantbufferdesc.Usage = D3D11_USAGE_DYNAMIC;
		constantbufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantbufferdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		Device->CreateBuffer(&constantbufferdesc, nullptr, &constbuffer);
		return constbuffer;
	}
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
	void ReleaseConstantBuffer(ID3D11Buffer* ConstantBuffer);

	// Proxy
	void SubmitProxy(const FRenderProxy& InRenderProxy);

	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;
//Gizmo Renderer
public:
	//UGizmoRenderer* GetGizmoRenderer() { return GizmoRenderer; }

// Mesh Manager
public:
	void RegisterMesh(const FString& MeshKey, const FMeshData& MeshData, D3D_PRIMITIVE_TOPOLOGY Topology = D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	void UpdateMesh(const FString& MeshKey, const FMeshData& NewMeshData);
	FMeshResource* GetPrimitiveMeshResource(const EPrimitiveType Type);
	FMeshResource* GetMeshResource(const FString& MeshId);

private:
	// Helper Function
	void CreateDeviceAndSwapChain(HWND& hWindow);
	void ReleaseDeviceAndSwapChain();

	void CreateFrameBuffer();
	void ReleaseFrameBuffer();

	void CreateRasterizerState();
	void ReleaseRasterizerState();

	void CreateDepthStencilResources(HWND& Hwnd);
	void ReleaseDepthStencilResources();
	
	IDXGISwapChain* SwapChain = nullptr;

	ID3D11Texture2D* FrameBuffer = nullptr;
	ID3D11RenderTargetView* FrameBufferRTV = nullptr;
	ID3D11RasterizerState* RasterizerState = nullptr;
	ID3D11Buffer* VPConstantBuffer = nullptr;
	ID3D11Buffer* MConstantBuffer = nullptr;

	// Depth Stencil
	ID3D11DepthStencilState* DepthStencilState = nullptr;
	ID3D11Texture2D* DepthStencilBuffer = nullptr;
	ID3D11DepthStencilView* DepthStencilView = nullptr;

	FLOAT ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f };
	D3D11_VIEWPORT ViewportInfo;

	ID3D11VertexShader* SimpleVertexShader;
	ID3D11PixelShader* SimplePixelShader;
	ID3D11InputLayout* SimpleInputLayout;

	class FMeshManager* MeshManager = nullptr;

	TArray<class FVisualInterface*> VisualInterfaceList;
	TArray<FRenderProxy> RenderProxyList;

	ID3D11Debug* pDebug = nullptr;
};
