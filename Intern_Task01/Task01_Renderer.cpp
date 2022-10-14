//==============================================================
// Filename: Task01_Renderer.cpp
// Description: 3D空間のレンダー
// Copyright (C)  Silicon Studio Co., Ltd. All rights reserved.
//==============================================================

#include "Task01_Main.h"
#include "Task01_Renderer.h"
#include <io.h>

#ifdef USE_DX11
D3D_FEATURE_LEVEL       Task01Renderer::m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device* Task01Renderer::m_Device = NULL;
ID3D11DeviceContext* Task01Renderer::m_DeviceContext = NULL;
IDXGISwapChain* Task01Renderer::m_SwapChain = NULL;
ID3D11RenderTargetView* Task01Renderer::m_RenderTargetView = NULL;
ID3D11DepthStencilView* Task01Renderer::m_DepthStencilView = NULL;

ID3D11Buffer* Task01Renderer::m_WorldBuffer = NULL;
ID3D11Buffer* Task01Renderer::m_ViewBuffer = NULL;
ID3D11Buffer* Task01Renderer::m_ProjectionBuffer = NULL;
ID3D11Buffer* Task01Renderer::m_MaterialBuffer = NULL;
ID3D11Buffer* Task01Renderer::m_LightBuffer = NULL;


ID3D11DepthStencilState* Task01Renderer::m_DepthStateEnable = NULL;
ID3D11DepthStencilState* Task01Renderer::m_DepthStateDisable = NULL;

#endif // USE_DX11

#ifdef USE_DX12

ID3D12Device* Task01Renderer::m_D12Device = NULL;
IDXGIFactory6* Task01Renderer::m_DXGIFactry = NULL;
IDXGISwapChain4* Task01Renderer::m_SwapChain4 = NULL;
ID3D12CommandAllocator* Task01Renderer::m_CmdAllocator = NULL;
ID3D12GraphicsCommandList* Task01Renderer::m_GCmdList = NULL;
ID3D12CommandQueue* Task01Renderer::m_CmdQueue = NULL;
ID3D12DescriptorHeap* Task01Renderer::m_DescHeap = NULL;

#endif // USE_DX12


float g_red, g_green, g_blue;


void Task01Renderer::Init()
{
#ifdef USE_DX11


	HRESULT hr = S_OK;

	// デバイス、スワップチェーン作成
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;
	swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = GetWindow();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_SwapChain,
		&m_Device,
		&m_FeatureLevel,
		&m_DeviceContext);


	// レンダーターゲットビュー作成
	ID3D11Texture2D* renderTarget = NULL;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	m_Device->CreateRenderTargetView(renderTarget, NULL, &m_RenderTargetView);
	renderTarget->Release();


	// デプスステンシルバッファ作成
	ID3D11Texture2D* depthStencile = NULL;
	D3D11_TEXTURE2D_DESC textureDesc{};
	textureDesc.Width = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	m_Device->CreateTexture2D(&textureDesc, NULL, &depthStencile);

	// デプスステンシルビュー作成
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	m_Device->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &m_DepthStencilView);
	depthStencile->Release();


	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);


	// ビューポート設定
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)SCREEN_WIDTH;
	viewport.Height = (FLOAT)SCREEN_HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &viewport);


	// ラスタライザステート設定
	D3D11_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.MultisampleEnable = FALSE;

	ID3D11RasterizerState* rs;
	m_Device->CreateRasterizerState(&rasterizerDesc, &rs);

	m_DeviceContext->RSSetState(rs);


	// ブレンドステート設定
	D3D11_BLEND_DESC blendDesc{};
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	ID3D11BlendState* blendState = NULL;
	m_Device->CreateBlendState(&blendDesc, &blendState);
	m_DeviceContext->OMSetBlendState(blendState, blendFactor, 0xffffffff);


	// デプスステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateEnable);//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateDisable);//深度無効ステート

	m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);


	// サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	ID3D11SamplerState* samplerState = NULL;
	m_Device->CreateSamplerState(&samplerDesc, &samplerState);

	m_DeviceContext->PSSetSamplers(0, 1, &samplerState);


	// 定数バッファ生成
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_WorldBuffer);
	m_DeviceContext->VSSetConstantBuffers(0, 1, &m_WorldBuffer);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_ViewBuffer);
	m_DeviceContext->VSSetConstantBuffers(1, 1, &m_ViewBuffer);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_ProjectionBuffer);
	m_DeviceContext->VSSetConstantBuffers(2, 1, &m_ProjectionBuffer);


	bufferDesc.ByteWidth = sizeof(MATERIAL);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_MaterialBuffer);
	m_DeviceContext->VSSetConstantBuffers(3, 1, &m_MaterialBuffer);


	bufferDesc.ByteWidth = sizeof(LIGHT);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_LightBuffer);
	m_DeviceContext->VSSetConstantBuffers(4, 1, &m_LightBuffer);
	m_DeviceContext->PSSetConstantBuffers(4, 1, &m_LightBuffer);


	// ライト初期化
	LIGHT light{};
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetLight(light);


	// マテリアル初期化
	MATERIAL material{};
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

#endif // USE_DX11

#ifdef USE_DX12

#ifdef _DEBUG

	/// デバッグレイヤーをオン
	EnableDebugLayer();

#endif // _DEBUG


	auto result = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_D12Device));

	result = CreateDXGIFactory1(IID_PPV_ARGS(&m_DXGIFactry));

	std::vector<IDXGIAdapter*> adapters;

	// 特定の名前を持つアダプターオブジェクトが入る
	IDXGIAdapter* tmpAdapter = nullptr;

	for (int i = 0; m_DXGIFactry->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		adapters.push_back(tmpAdapter);
	}

	// Descriptionメンバー変数から、アダプターの名前を見つける
	for (auto adpt : adapters)
	{
		DXGI_ADAPTER_DESC adesc = {};
		adpt->GetDesc(&adesc);
		
		std::wstring strDesc = adesc.Description;

		/// 探したいアダプターの名前を確認
		if (strDesc.find(L"NVIDIA") != std::string::npos)
		{
			tmpAdapter = adpt;
			break;
		}
	}

	/// コマンドアロケータ生成
	result = m_D12Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_CmdAllocator));

	/// コマンドリスト生成
	result = m_D12Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_CmdAllocator, nullptr, IID_PPV_ARGS(&m_GCmdList));

	///  COMMAND_QUEUEの設定
	D3D12_COMMAND_QUEUE_DESC qDesc = {};

	/// タイムアウト無し
	qDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	/// アダプターを一つしか使わないときは０
	qDesc.NodeMask = 0;

	/// プライオリティは特に指定なし
	qDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;

	/// コマンドリストと合わせる
	qDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	result = m_D12Device->CreateCommandQueue(&qDesc, IID_PPV_ARGS(&m_CmdQueue));


	/// SwapChain作成
	DXGI_SWAP_CHAIN_DESC1 swapDesc = {};

	swapDesc.Width = SCREEN_WIDTH;
	swapDesc.Height = SCREEN_HEIGHT;
	swapDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.Stereo = false;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapDesc.BufferCount = 2;

	/// バックバッファーは伸び縮み可能
	swapDesc.Scaling = DXGI_SCALING_STRETCH;

	/// フリップ後は速やかに破棄
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	/// 特に指定なし
	swapDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

	/// ウィンドウ　フルスクリーン切替可能
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	/// SwapChain生成
	result = m_DXGIFactry->CreateSwapChainForHwnd(
		m_CmdQueue,
		GetWindow(),
		&swapDesc,
		nullptr,
		nullptr,
		(IDXGISwapChain1**)&m_SwapChain4
	);


	/// ディスクリプタヒープ作成
	D3D12_DESCRIPTOR_HEAP_DESC hd = {};

	hd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;  /// レンダーターゲットビューなのでRTV
	hd.NodeMask = 0;
	hd.NumDescriptors = 2; /// 裏表の２つ
	hd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	
	/// ディスクリプタヒープ生成
	result = m_D12Device->CreateDescriptorHeap(&hd, IID_PPV_ARGS(&m_DescHeap));


	/// ディスクリプタとスワップチェーンを紐づけ
	DXGI_SWAP_CHAIN_DESC swcDesc = {};

	result = m_SwapChain4->GetDesc(&swcDesc);

	std::vector<ID3D12Resource*> backBuffers(swcDesc.BufferCount);
	for (int index = 0; index < swcDesc.BufferCount; ++index)
	{
		result = m_SwapChain4->GetBuffer(index, IID_PPV_ARGS(&backBuffers[index])); /// BackBuffersの中にスワップチェーン上のバックバッファーを取得

		D3D12_CPU_DESCRIPTOR_HANDLE deschandle = m_DescHeap->GetCPUDescriptorHandleForHeapStart();
		deschandle.ptr += index * m_D12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		m_D12Device->CreateRenderTargetView(backBuffers[index], nullptr, deschandle);
	}

	result = m_CmdAllocator->Reset();


#endif // USE_DX12


	// Color初期化
	g_red = 0.0f;
	g_green = 0.0f;
	g_blue = 0.0f;

}



void Task01Renderer::Uninit()
{
#ifdef USE_DX11

	m_WorldBuffer->Release();
	m_ViewBuffer->Release();
	m_ProjectionBuffer->Release();
	m_LightBuffer->Release();
	m_MaterialBuffer->Release();


	m_DeviceContext->ClearState();
	m_RenderTargetView->Release();
	m_SwapChain->Release();
	m_DeviceContext->Release();
	m_Device->Release();

#endif // USE_DX11

#ifdef USE_DX12

	m_CmdAllocator->Release();
	m_CmdQueue->Release();
	m_DescHeap->Release();
	m_DXGIFactry->Release();
	m_GCmdList->Release();
	m_SwapChain4->Release();
	m_D12Device->Release();

#endif // USE_DX12

}




void Task01Renderer::Begin()
{
#ifdef USE_DX11

	float clearColor[4] = { g_red, g_green, g_blue, 1.0f };
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, clearColor);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

#endif // USE_DX11

#ifdef USE_DX12

	auto bbIdx = m_SwapChain4->GetCurrentBackBufferIndex();

	auto rtvH = m_DescHeap->GetCPUDescriptorHandleForHeapStart();

	rtvH.ptr += bbIdx * m_D12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	m_GCmdList->OMSetRenderTargets(1, &rtvH, true, nullptr);	/// コマンドリストに命令を貯めていく

	float clearColor[4] = { g_red, g_green, g_blue, 1.0f };

	/// 画面クリア
	m_GCmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);



#endif // USE_DX12
}



void Task01Renderer::End()
{
#ifdef USE_DX11

	m_SwapChain->Present(1, 0);

#endif // USE_DX11

#ifdef USE_DX12

	/// 命令のクローズ
	m_GCmdList->Close();

	/// コマンドリストの実行
	ID3D12CommandList* cmdlists[] = { m_GCmdList };
	m_CmdQueue->ExecuteCommandLists(1, cmdlists);

	/// キューのクリア
	m_CmdAllocator->Reset();
	/// 再びコマンドリストを貯める準備
	m_GCmdList->Reset(m_CmdAllocator, nullptr);

	m_SwapChain4->Present(1, 0);

#endif // USE_DX12
}

void Update()
{

}

#ifdef USE_DX11

void Task01Renderer::SetDepthEnable(bool Enable)
{

	if (Enable)
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);
	else
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateDisable, NULL);

}

void Task01Renderer::SetWorldViewProjection2D()
{
#ifdef USE_DX11

	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixTranspose(&world, &world);

	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);

	D3DXMATRIX view;
	D3DXMatrixIdentity(&view);
	D3DXMatrixTranspose(&view, &view);
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);

	D3DXMATRIX projection;
	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
	D3DXMatrixTranspose(&projection, &projection);
	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);

#endif // USE_DX11
}


void Task01Renderer::SetWorldMatrix(D3DXMATRIX* WorldMatrix)
{
#ifdef USE_DX11

	D3DXMATRIX world;
	D3DXMatrixTranspose(&world, WorldMatrix);
	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);

#endif // USE_DX11
}

void Task01Renderer::SetViewMatrix(D3DXMATRIX* ViewMatrix)
{
#ifdef USE_DX11

	D3DXMATRIX view;
	D3DXMatrixTranspose(&view, ViewMatrix);
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);

#endif // USE_DX11
}

void Task01Renderer::SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix)
{
#ifdef USE_DX11

	D3DXMATRIX projection;
	D3DXMatrixTranspose(&projection, ProjectionMatrix);
	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);

#endif // USE_DX11
}



void Task01Renderer::SetMaterial(MATERIAL Material)
{
#ifdef USE_DX11

	m_DeviceContext->UpdateSubresource(m_MaterialBuffer, 0, NULL, &Material, 0, 0);

#endif // USE_DX11
}

void Task01Renderer::SetLight(LIGHT Light)
{
#ifdef USE_DX11

	m_DeviceContext->UpdateSubresource(m_LightBuffer, 0, NULL, &Light, 0, 0);

#endif // USE_DX11
}





void Task01Renderer::CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName)
{
#ifdef USE_DX11

	FILE* file;
	long int fsize;

	file = fopen(FileName, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	m_Device->CreateVertexShader(buffer, fsize, NULL, VertexShader);


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	m_Device->CreateInputLayout(layout,
		numElements,
		buffer,
		fsize,
		VertexLayout);

	delete[] buffer;

#endif // USE_DX11
}



void Task01Renderer::CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName)
{
#ifdef USE_DX11

	FILE* file;
	long int fsize;

	file = fopen(FileName, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	m_Device->CreatePixelShader(buffer, fsize, NULL, PixelShader);

	delete[] buffer;

#endif // USE_DX11
}

#endif // USE_DX11


#ifdef USE_DX12

void Task01Renderer::EnableDebugLayer()
{
	ID3D12Debug* debugLayer = nullptr;

	auto result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));

	debugLayer->EnableDebugLayer();
	debugLayer->Release();
}

#endif // USE_DX12