#include "Renderer.h"
#include "SimpleConstants.h"
#include "ImGuiManager.h"
#include "Camera.h"

void URenderer::Create(HWND hWindow)
{
	CreateDeviceAndSwapChain(hWindow);
	CreateFrameBuffer();
	CreateRasterizerState();
	VPConstantBuffer = CreateConstantBuffer<FViewProjConstant>();
	MConstantBuffer = CreateConstantBuffer<FModelConstant>();
	MeshManager = new FMeshManager(Device);
	GridRenderer = new FGridRenderer();
	GridRenderer->Init();
}

void URenderer::CreateDeviceAndSwapChain(HWND hWindow)
{
	D3D_FEATURE_LEVEL featurelevels[] = { D3D_FEATURE_LEVEL_11_0 };

	DXGI_SWAP_CHAIN_DESC swapchaindesc = {};
	swapchaindesc.BufferDesc.Width = 0;
	swapchaindesc.BufferDesc.Height = 0;
	swapchaindesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapchaindesc.SampleDesc.Count = 1;
	swapchaindesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchaindesc.BufferCount = 2;
	swapchaindesc.OutputWindow = hWindow;
	swapchaindesc.Windowed = TRUE;
	swapchaindesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG,
		featurelevels, ARRAYSIZE(featurelevels), D3D11_SDK_VERSION,
		&swapchaindesc, &SwapChain, &Device, nullptr, &DeviceContext);

	SwapChain->GetDesc(&swapchaindesc);

	ViewportInfo = { 0.0f, 0.0f, (float)swapchaindesc.BufferDesc.Width, (float)swapchaindesc.BufferDesc.Height, 0.0f, 1.0f };
}

void URenderer::ReleaseDeviceAndSwapChain()
{
	if (DeviceContext)
	{
		DeviceContext->Flush();
	}
	if (SwapChain)
	{
		SwapChain->Release();
		SwapChain = nullptr;
	}
	if (Device)
	{
		Device->Release();
		Device = nullptr;
	}
	if (DeviceContext)
	{
		DeviceContext->Release();
		DeviceContext = nullptr;
	}
}

void URenderer::CreateFrameBuffer()
{
	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&FrameBuffer);

	D3D11_RENDER_TARGET_VIEW_DESC framebufferRTVdesc = {};
	framebufferRTVdesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB; // ���� ����
	framebufferRTVdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; // 2D �ؽ�ó

	Device->CreateRenderTargetView(FrameBuffer, &framebufferRTVdesc, &FrameBufferRTV);
}

void URenderer::ReleaseFrameBuffer()
{
	if (FrameBuffer)
	{
		FrameBuffer->Release();
		FrameBuffer = nullptr;
	}
	if (FrameBufferRTV)
	{
		FrameBufferRTV->Release();
		FrameBufferRTV = nullptr;
	}
}

void URenderer::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerdesc = {};
	rasterizerdesc.FillMode = D3D11_FILL_SOLID;
	rasterizerdesc.CullMode = D3D11_CULL_BACK;
	

	Device->CreateRasterizerState(&rasterizerdesc, &RasterizerState);
}

void URenderer::ReleaseRasterizerState()
{
	if (RasterizerState)
	{
		RasterizerState->Release();
		RasterizerState = nullptr;
	}
}

void URenderer::Release()
{
	DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);

	ReleaseRasterizerState();
	ReleaseConstantBuffer(VPConstantBuffer);
	ReleaseConstantBuffer(MConstantBuffer);
	ReleaseShader(); // �߰�
	ReleaseFrameBuffer();
	ReleaseDeviceAndSwapChain();

	delete(MeshManager);
	delete(GridRenderer);
}

void URenderer::SwapBuffer()
{
	SwapChain->Present(1, 0);
}

void URenderer::CreateShader()
{
	ID3DBlob* VertexShaderCSO;
	ID3DBlob* PixelShaderCSO;

	D3DCompileFromFile(L"W2Shader.hlsl", nullptr, nullptr, "mainVS", "vs_5_0", 0, 0, &VertexShaderCSO, nullptr);
	Device->CreateVertexShader(VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), nullptr, &SimpleVertexShader);

	D3DCompileFromFile(L"W2Shader.hlsl", nullptr, nullptr, "mainPS", "ps_5_0", 0, 0, &PixelShaderCSO, nullptr);
	Device->CreatePixelShader(PixelShaderCSO->GetBufferPointer(), PixelShaderCSO->GetBufferSize(), nullptr, &SimplePixelShader);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	Device->CreateInputLayout(layout, ARRAYSIZE(layout), VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), &SimpleInputLayout);

	VertexShaderCSO->Release();
	PixelShaderCSO->Release();
}

void URenderer::ReleaseShader()
{
	if (SimpleInputLayout)
	{
		SimpleInputLayout->Release();
		SimpleInputLayout = nullptr;
	}
	if (SimplePixelShader)
	{
		SimplePixelShader->Release();
		SimplePixelShader = nullptr;
	}
	if (SimpleVertexShader)
	{
		SimpleVertexShader->Release();
		SimpleVertexShader = nullptr;
	}
}

void URenderer::Prepare()
{
	DeviceContext->ClearRenderTargetView(FrameBufferRTV, ClearColor);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DeviceContext->RSSetViewports(1, &ViewportInfo);
	DeviceContext->RSSetState(RasterizerState);
	DeviceContext->OMSetRenderTargets(1, &FrameBufferRTV, nullptr);
	DeviceContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
}

void URenderer::PrepareShader()
{
	DeviceContext->VSSetShader(SimpleVertexShader, nullptr, 0);
	DeviceContext->PSSetShader(SimplePixelShader, nullptr, 0);
	DeviceContext->IASetInputLayout(SimpleInputLayout);
}

void URenderer::RenderScene(const UCamera& SceneCamera)
{
	PrepareShader();

	FViewProjConstant VPConstant{ SceneCamera.GetViewMatrix(), SceneCamera.GetProjectionMatrix() };
	UpdateConstantBuffer<FViewProjConstant>(VPConstantBuffer, &VPConstant);
	DeviceContext->VSSetConstantBuffers(1, 1, &VPConstantBuffer);

	GridRenderer->Update(SceneCamera.GetEye());
	GridRenderer->Render();

	for (const auto& RenderProxy : RenderProxyList)
	{
		FMeshResource* Res = RenderProxy.MeshResource;
		if (!Res) { continue; }

		DeviceContext->IASetPrimitiveTopology(RenderProxy.MeshResource->Topology);

		FModelConstant MConstant{ RenderProxy.ModelWorldMatrix };
		UpdateConstantBuffer<FModelConstant>(MConstantBuffer, &MConstant);
		DeviceContext->VSSetConstantBuffers(0, 1, &MConstantBuffer);	
		DeviceContext->IASetVertexBuffers(0, 1, &Res->VertexBuffer, &Res->Stride, &Res->Offset);

		if (Res->IndexBuffer)
		{
			DeviceContext->IASetIndexBuffer(Res->IndexBuffer, DXGI_FORMAT_R32_UINT, Res->Offset);
			DeviceContext->DrawIndexed(Res->IndexCount, 0, 0);
		}
		else
		{
			DeviceContext->Draw(Res->VertexCount, 0);
		}
	}

	RenderProxyList.clear();

}

void URenderer::ReleaseConstantBuffer(ID3D11Buffer* ConstantBuffer)
{
	if (ConstantBuffer)
	{
		ConstantBuffer->Release();
		ConstantBuffer = nullptr;
	}
}

void URenderer::SubmitProxy(const FRenderProxy& InRenderProxy)
{
	RenderProxyList.push_back(InRenderProxy);
}

void URenderer::RegisterMesh(const FString& MeshKey, const FMeshData& MeshData, D3D_PRIMITIVE_TOPOLOGY Topology)
{
	if (MeshManager) { MeshManager->RegisterMesh(MeshKey, MeshData, Topology); }
}

void URenderer::UpdateMesh(const FString& MeshKey, const FMeshData& NewMeshData)
{
	if (MeshManager) { MeshManager->UpdateMesh(MeshKey, NewMeshData); }
}

FMeshResource* URenderer::GetPrimitiveMeshResource(const EPrimitiveType Type)
{
	if (MeshManager) { return MeshManager->GetPrimitiveMeshResource(Type); }
	return nullptr;
}

FMeshResource* URenderer::GetMeshResource(const FString& MeshId)
{
	if (MeshManager) { return MeshManager->GetMeshResource(MeshId); }
	return nullptr;
}
