//==============================================================
// Filename: Task01_Renderer.cpp
// Description: 3D��Ԃ̃����_�[
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
ID3D12Fence* Task01Renderer::m_Fence = NULL;
UINT64 Task01Renderer::m_FenceVal = NULL;
ID3D12PipelineState* Task01Renderer::m_PipelineState = NULL;
D3D12_RESOURCE_BARRIER Task01Renderer::m_Barrier = {};

/// �O���[�o���錾
DXGI_SWAP_CHAIN_DESC g_swcDesc = {};
std::vector<ID3D12Resource*> g_BackBuffers;


#endif // USE_DX12

#ifdef USE_OPENGL

HGLRC Task01Renderer::m_GLRC;
HDC	Task01Renderer::m_DC;

float	Task01Renderer::CameraPositionX;
float	Task01Renderer::CameraPositionY;
float	Task01Renderer::CameraPositionZ;

float	Task01Renderer::CameraAtPositionX;
float	Task01Renderer::CameraAtPositionY;
float	Task01Renderer::CameraAtPositionZ;

#endif // USE_OPENGL



float g_red, g_green, g_blue;


void Task01Renderer::Init()
{
#ifdef USE_DX11


	HRESULT hr = S_OK;

	// �f�o�C�X�A�X���b�v�`�F�[���쐬
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


	// �����_�[�^�[�Q�b�g�r���[�쐬
	ID3D11Texture2D* renderTarget = NULL;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	m_Device->CreateRenderTargetView(renderTarget, NULL, &m_RenderTargetView);
	renderTarget->Release();


	// �f�v�X�X�e���V���o�b�t�@�쐬
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

	// �f�v�X�X�e���V���r���[�쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	m_Device->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &m_DepthStencilView);
	depthStencile->Release();


	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);


	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)SCREEN_WIDTH;
	viewport.Height = (FLOAT)SCREEN_HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &viewport);


	// ���X�^���C�U�X�e�[�g�ݒ�
	D3D11_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.MultisampleEnable = FALSE;

	ID3D11RasterizerState* rs;
	m_Device->CreateRasterizerState(&rasterizerDesc, &rs);

	m_DeviceContext->RSSetState(rs);


	// �u�����h�X�e�[�g�ݒ�
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


	// �f�v�X�X�e���V���X�e�[�g�ݒ�
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateEnable);//�[�x�L���X�e�[�g

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateDisable);//�[�x�����X�e�[�g

	m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);


	// �T���v���[�X�e�[�g�ݒ�
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	ID3D11SamplerState* samplerState = NULL;
	m_Device->CreateSamplerState(&samplerDesc, &samplerState);

	m_DeviceContext->PSSetSamplers(0, 1, &samplerState);


	// �萔�o�b�t�@����
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


	// ���C�g������
	LIGHT light{};
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetLight(light);


	// �}�e���A��������
	MATERIAL material{};
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

#endif // USE_DX11

#ifdef USE_DX12

#ifdef _DEBUG

	/// �f�o�b�O���C���[���I��
	EnableDebugLayer();

#endif // _DEBUG
	D3D_FEATURE_LEVEL levels[] = {
	D3D_FEATURE_LEVEL_12_1,
	D3D_FEATURE_LEVEL_12_0,
	D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL_11_0,
	};
	auto Result = CreateDXGIFactory1(IID_PPV_ARGS(&m_DXGIFactry));
	// ����̖��O�����A�_�v�^�[�I�u�W�F�N�g������
	std::vector<IDXGIAdapter*> adapters;
	IDXGIAdapter* tmpAdapter = nullptr;
	for (int i = 0; m_DXGIFactry->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		adapters.push_back(tmpAdapter);
	}
	// Description�����o�[�ϐ�����A�A�_�v�^�[�̖��O��������
	for (auto adpt : adapters)
	{
		DXGI_ADAPTER_DESC adesc = {};
		adpt->GetDesc(&adesc);
		
		std::wstring strDesc = adesc.Description;

		/// �T�������A�_�v�^�[�̖��O���m�F
		if (strDesc.find(L"NVIDIA") != std::string::npos)
		{
			tmpAdapter = adpt;
			break;
		}
	}

	D3D_FEATURE_LEVEL FeatureLevel;
	for (auto l : levels)
	{
		if (D3D12CreateDevice(tmpAdapter, l, IID_PPV_ARGS(&m_D12Device)) == S_OK)
		{
			FeatureLevel = l;
			break;
		}
	}

	/// �R�}���h�A���P�[�^����
	Result = m_D12Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_CmdAllocator));

	/// �R�}���h���X�g����
	Result = m_D12Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_CmdAllocator, nullptr, IID_PPV_ARGS(&m_GCmdList));

	///  COMMAND_QUEUE�̐ݒ�
	D3D12_COMMAND_QUEUE_DESC qDesc = {};
	qDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;	/// �^�C���A�E�g����
	qDesc.NodeMask = 0;	/// �A�_�v�^�[��������g��Ȃ��Ƃ��͂O
	qDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;	/// �v���C�I���e�B�͓��Ɏw��Ȃ�
	qDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;	/// �R�}���h���X�g�ƍ��킹��
	Result = m_D12Device->CreateCommandQueue(&qDesc, IID_PPV_ARGS(&m_CmdQueue));


	/// SwapChain�쐬
	DXGI_SWAP_CHAIN_DESC1 swapDesc = {};

	swapDesc.Width = SCREEN_WIDTH;
	swapDesc.Height = SCREEN_HEIGHT;
	swapDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.Stereo = false;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapDesc.BufferCount = 2;
	swapDesc.Scaling = DXGI_SCALING_STRETCH;		/// �o�b�N�o�b�t�@�[�͐L�яk�݉\
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;	/// �t���b�v��͑��₩�ɔj��
	swapDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;	/// ���Ɏw��Ȃ�
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	/// �E�B���h�E�@�t���X�N���[���ؑ։\

	/// SwapChain����
	Result = m_DXGIFactry->CreateSwapChainForHwnd(
		m_CmdQueue,
		GetWindow(),
		&swapDesc,
		nullptr,
		nullptr,
		(IDXGISwapChain1**)&m_SwapChain4
	);


	/// �f�B�X�N���v�^�q�[�v�쐬
	D3D12_DESCRIPTOR_HEAP_DESC hd = {};

	hd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;  /// �����_�[�^�[�Q�b�g�r���[�Ȃ̂�RTV
	hd.NodeMask = 0;
	hd.NumDescriptors = 2; /// ���\�̂Q��
	hd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	
	/// �f�B�X�N���v�^�q�[�v����
	Result = m_D12Device->CreateDescriptorHeap(&hd, IID_PPV_ARGS(&m_DescHeap));


	/// �f�B�X�N���v�^�ƃX���b�v�`�F�[����R�Â�
	Result = m_SwapChain4->GetDesc(&g_swcDesc);
	static std::vector<ID3D12Resource*> backBuffers(g_swcDesc.BufferCount);

	D3D12_CPU_DESCRIPTOR_HANDLE deschandle = m_DescHeap->GetCPUDescriptorHandleForHeapStart();
	for (size_t index = 0; index < g_swcDesc.BufferCount; ++index)
	{
		Result = m_SwapChain4->GetBuffer(static_cast<UINT>(index), IID_PPV_ARGS(&backBuffers[index])); /// BackBuffers�̒��ɃX���b�v�`�F�[����̃o�b�N�o�b�t�@�[���擾
		m_D12Device->CreateRenderTargetView(backBuffers[index], nullptr, deschandle);
		deschandle.ptr += m_D12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}
	g_BackBuffers = backBuffers;

	//g_Result = m_CmdAllocator->Reset();

	/// �t�F���X�쐬
	Result = m_D12Device->CreateFence(m_FenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_Fence));




#endif // USE_DX12

#ifdef USE_OPENGL

	// �s�N�Z���t�H�[�}�b�g
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	m_DC = GetDC(GetWindow());

	int pixelFormat = ChoosePixelFormat(m_DC, &pfd);
	SetPixelFormat(m_DC, pixelFormat, &pfd);

	/// GL�R���e�L�X�g�쐬
	m_GLRC = wglCreateContext(m_DC);
	wglMakeCurrent(m_DC, m_GLRC);

	/// OpenGL�`��ݒ�
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	/// �ϐ�������
	//�J�������W
	CameraPositionX = 0.0f;
	CameraPositionY = 5.0f;
	CameraPositionZ = 10.0f;
	//�J���������_
	CameraAtPositionX = 0.0f;
	CameraAtPositionY = 0.0f;
	CameraAtPositionZ = 0.0f;

#endif // USE_OPENGL


	// Color������
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
	m_PipelineState->Release();
	m_Fence->Release();
	m_D12Device->Release();

#endif // USE_DX12

#ifdef USE_OPENGL

	wglMakeCurrent(NULL, NULL);
	ReleaseDC(GetWindow(), m_DC);
	wglDeleteContext(m_GLRC);

#endif // USE_OPENGL


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

	/// ���\�[�X�o���A����
	m_Barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	m_Barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	m_Barrier.Transition.pResource = g_BackBuffers[bbIdx];
	m_Barrier.Transition.Subresource = 0;
	m_Barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	m_Barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

	m_GCmdList->ResourceBarrier(1, &m_Barrier);

	

	/// �����_�[�^�[�Q�b�g���w��
	auto rtvH = m_DescHeap->GetCPUDescriptorHandleForHeapStart();
	rtvH.ptr += bbIdx * m_D12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	m_GCmdList->OMSetRenderTargets(1, &rtvH, false, nullptr);	/// �R�}���h���X�g�ɖ��߂𒙂߂Ă���

	float clearColor[4] = { g_red, g_green, g_blue, 1.0f };

	/// ��ʃN���A
	m_GCmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);



#endif // USE_DX12

#ifdef USE_OPENGL

	// ��ʃN���A
	glClearColor(0.0f, 0.5f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#endif // USE_OPENGL


}



void Task01Renderer::End()
{
#ifdef USE_DX11

	m_SwapChain->Present(1, 0);

#endif // USE_DX11

#ifdef USE_DX12
	static D3D12_RESOURCE_BARRIER Barrier;

	/// �O�ゾ������ւ���
	m_Barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	m_Barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	m_GCmdList->ResourceBarrier(1, &m_Barrier);

	/// ���߂̃N���[�Y
	m_GCmdList->Close();

	/// �R�}���h���X�g�̎��s
	ID3D12CommandList* cmdlists[] = { m_GCmdList };
	m_CmdQueue->ExecuteCommandLists(1, cmdlists);

	/// �t�F���X�Ŋm���߂�
	m_CmdQueue->Signal(m_Fence, ++m_FenceVal);

	if (m_Fence->GetCompletedValue() != m_FenceVal)
	{
		/// �C�x���g�n���h���̎擾
		auto Event = CreateEvent(nullptr, false, false, nullptr);

		m_Fence->SetEventOnCompletion(m_FenceVal, Event);

		/// �C�x���g����������܂ő҂�������
		WaitForSingleObject(Event, INFINITE);

		/// �C�x���g�n���h�������
		CloseHandle(Event);
	}
	

	/// �L���[�̃N���A
	m_CmdAllocator->Reset();
	/// �ĂуR�}���h���X�g�𒙂߂鏀��
	m_GCmdList->Reset(m_CmdAllocator, m_PipelineState);

	m_SwapChain4->Present(1, 0);

#endif // USE_DX12

#ifdef USE_OPENGL

	// �t�����g�o�b�t�@�E�o�b�N�o�b�t�@����ւ�
	SwapBuffers(m_DC);

#endif // USE_OPENGL

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

	auto g_Result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));

	debugLayer->EnableDebugLayer();
	debugLayer->Release();
}

#endif // USE_DX12

#ifdef USE_OPENGL

void Task01Renderer::OpenGLSet2D()
{
	// 2D�p�}�g���N�X�ݒ�
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);
}

void Task01Renderer::OpenGLSet3D()
{
	//��p�̐ݒ�
#define		VIEW_ANGLE		(45.0f)
//�ߖʃN���b�v����
#define		VIEW_NEAR_Z		(1.0f)
//���ʃN���b�v����
#define		VIEW_FAR_Z		(5000.0f)

	//�r���[�|�[�g�̐ݒ� �E�B���h�E�T�C�Y�����ς�
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//�A�X�y�N�g��  �����c
	double	aspect = (double)SCREEN_WIDTH /
		(double)SCREEN_HEIGHT;
	//�v���W�F�N�V�����s��̕ύX
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(VIEW_ANGLE, aspect,
		VIEW_NEAR_Z, VIEW_FAR_Z);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//�J�����s��쐬
	gluLookAt(
		CameraPositionX,//�J�������W
		CameraPositionY,
		CameraPositionZ,
		CameraAtPositionX,//�J���������_
		CameraAtPositionY,
		CameraAtPositionZ,
		0.0f, 1.0f, 0.0f	//������x�N�g��
	);
}

#endif // USE_OPENGL
