//==============================================================
// Filename: Task01_3DPolygon.cpp
// Description: 3D�|���S���`��
// Copyright (C)  Silicon Studio Co., Ltd. All rights reserved.
//==============================================================


#include "Task01_Main.h"
#include "Task01_Manager.h"
#include "Task01_Renderer.h"
#include "Task01_3DPolygon.h"
#include "Task01_Input.h"

#ifdef USE_OPENGL

#include "Task01_Vector.h"

#endif // USE_OPENGL

/// �}�N����`

#define	SIZE_X			(10.0f)					/// �n�ʂ̃T�C�Y(X����)
#define SIZE_Y			(10.0f)					/// �n�ʂ̃T�C�Y(Y����)
#define	SIZE_Z			(10.0f)					/// �n�ʂ̃T�C�Y(Z����)

#define VERTEX_NUM	4							/// ���_��


#ifdef USE_DX11
#define	VALUE_ROTATE	(D3DX_PI * 0.006f)			/// ��]��

/// ���_�z��
static VERTEX_3D g_VertexArray[VERTEX_NUM] = {
	/// ��
	{D3DXVECTOR3(-SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f)},
	{D3DXVECTOR3(SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0, 0.0f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},
	{D3DXVECTOR3(SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f)},
	{D3DXVECTOR3(SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},

	/// ��
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.75f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.75f, 1.0f)},
	{D3DXVECTOR3(SIZE_X, -SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.5f, 0.5f)},
	{D3DXVECTOR3(SIZE_X, -SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.5f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.75f, 1.0f)},
	{D3DXVECTOR3(SIZE_X, -SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.5f, 1.0f)},

	/// ����
	{D3DXVECTOR3(-SIZE_X,  SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.25f, 0.0f)},
	{D3DXVECTOR3(SIZE_X,  SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.5f, 0.0f)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.25f, 0.5f)},
	{D3DXVECTOR3(SIZE_X,  SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.5f, 0.0f)},
	{D3DXVECTOR3(SIZE_X, -SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.5f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.25f, 0.5f)},

	/// ��
	{D3DXVECTOR3(-SIZE_X,  SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.5f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.5f, 1.0f)},
	{D3DXVECTOR3(SIZE_X,  SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.25f, 0.5f)},
	{D3DXVECTOR3(SIZE_X,  SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.25f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.5f, 1.0f)},
	{D3DXVECTOR3(SIZE_X, -SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.25f, 1.0f)},

	/// ��
	{D3DXVECTOR3(-SIZE_X,  SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},
	{D3DXVECTOR3(-SIZE_X,  SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.25f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.25f, 1.0f)},
	{D3DXVECTOR3(-SIZE_X,  SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.25f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X, -SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},

	/// �E
	{D3DXVECTOR3(SIZE_X,  SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.5f, 0.0f)},
	{D3DXVECTOR3(SIZE_X,  SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.75f, 0.0f)},
	{D3DXVECTOR3(SIZE_X, -SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.5f, 0.5f)},
	{D3DXVECTOR3(SIZE_X, -SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.75f, 0.5f)},
	{D3DXVECTOR3(SIZE_X, -SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.5f, 0.5f)},
	{D3DXVECTOR3(SIZE_X,  SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.75f, 0.0f)},

};

#endif // USE_DX11

#ifdef USE_DX12

DirectX::XMFLOAT3 vertex[] = 
{
	{-0.5f,-0.5f, 0.0f} ,	//����
	{-0.5f, 0.5f, 0.0f} ,	//����
	{ 0.5f,-0.5f, 0.0f} ,	//�E��
	{ 0.5f, 0.5f, 0.0f} ,	//�E��
};
D3D12_VIEWPORT g_Viewport = {};
D3D12_RECT g_ScissorRect = {};

#endif // USE_DX12

#ifdef USE_OPENGL

VECTOR3D g_CameraPos(0.0f, 5.0f, 10.0f);

#endif // USE_OPENGL


HRESULT result;


void Task013DPolygon::Init()
{
#ifdef USE_DX11

	for (int i = 0; i < VERTEX_NUM; i++)
	{
		g_VertexArray[i].Diffuse.r = 0.0f;
		g_VertexArray[i].Diffuse.g = 0.0f;
		g_VertexArray[i].Diffuse.b = 1.0f;
	}


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * VERTEX_NUM;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = g_VertexArray;

	Task01Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	Task01Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitColorVS.cso");

	Task01Renderer::CreatePixelShader(&m_PixelShader, "unlitColorPS.cso");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);

#endif // USE_DX11

#ifdef USE_DX12

	/// ���_�o�b�t�@�[�̐���
	D3D12_HEAP_PROPERTIES heapprop = {};
	heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
	heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

	D3D12_RESOURCE_DESC reDesc = {};
	reDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	reDesc.Width = sizeof(vertex); /// ���_�T�C�Y
	reDesc.Height = 1;
	reDesc.DepthOrArraySize = 1;
	reDesc.MipLevels = 1;
	reDesc.Format = DXGI_FORMAT_UNKNOWN;
	reDesc.SampleDesc.Count = 1;
	reDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	reDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	result = Task01Renderer::GetDevice12()->CreateCommittedResource(
		&heapprop,
		D3D12_HEAP_FLAG_NONE,
		&reDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&m_VertexBuffer)
	);

	/// �}�b�v
	result = m_VertexBuffer->Map(0, nullptr, (void**)&m_vertexMap);
	std::copy(std::begin(vertex), std::end(vertex), m_vertexMap);
	m_VertexBuffer->Unmap(0, nullptr);

	/// �o�b�t�@�[�r���[����
	m_vbview.BufferLocation = m_VertexBuffer->GetGPUVirtualAddress(); /// �o�b�t�@�[�̉��z�A�h���X
	m_vbview.SizeInBytes = sizeof(vertex); /// �S�o�C�g��
	m_vbview.StrideInBytes = sizeof(vertex[0]); /// 1���_������̃o�C�g��

	/// �C���f�b�N�X�o�b�t�@�[
	unsigned short indices[] = { 0, 1, 2, 2, 1, 3 };
	reDesc.Width = sizeof(indices);
	result = Task01Renderer::GetDevice12()->CreateCommittedResource(
		&heapprop,
		D3D12_HEAP_FLAG_NONE,
		&reDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&m_IndexBuffer)
	);

	unsigned short* mappendIdx = nullptr;
	m_IndexBuffer->Map(0, nullptr, (void**)&mappendIdx);
	std::copy(std::begin(indices), std::end(indices), mappendIdx);
	m_IndexBuffer->Unmap(0, nullptr);

	/// �C���f�b�N�X�o�b�t�@�[�r���[�쐬
	m_ibview.BufferLocation = m_IndexBuffer->GetGPUVirtualAddress();
	m_ibview.Format = DXGI_FORMAT_R16_UINT;
	m_ibview.SizeInBytes = sizeof(indices);


	/// ���_�V�F�[�_�[�R���p�C��
	result = D3DCompileFromFile(
		L"VertexShader.hlsl",	/// �V�F�[�_�[��
		nullptr,	/// define�Ȃ�
		D3D_COMPILE_STANDARD_FILE_INCLUDE, /// �C���N���[�h�̓f�t�H���g
		"BasicVS", "vs_5_0", /// �֐��̓C���N���[�h����V�F�[�_�[���̂���
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, /// �f�o�b�O�p����эœK���Ȃ�
		0,
		&m_vsBlob, &m_errorBlob
	);

	if (FAILED(result))
	{
		if (result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
		{
			::OutputDebugStringA("�t�@�C������������܂���");
		}
		else
		{
			std::string errstr;
			errstr.resize(m_errorBlob->GetBufferSize());

			std::copy_n((char*)m_errorBlob->GetBufferPointer(), m_errorBlob->GetBufferSize(), errstr.begin());
			errstr += "\n";

			::OutputDebugStringA(errstr.c_str());
		}
		exit(1);
	}

	/// �s�N�Z���V�F�[�_�[�R���p�C��
	result = D3DCompileFromFile(
		L"PixelShader.hlsl",	/// �V�F�[�_�[��
		nullptr,	/// define�Ȃ�
		D3D_COMPILE_STANDARD_FILE_INCLUDE, /// �C���N���[�h�̓f�t�H���g
		"BasicPS", "ps_5_0", /// �֐��̓C���N���[�h����V�F�[�_�[���̂���
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, /// �f�o�b�O�p����эœK���Ȃ�
		0,
		&m_psBlob, &m_errorBlob
	);
	if (FAILED(result))
	{
		if (result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
		{
			::OutputDebugStringA("�t�@�C������������܂���");
		}
		else
		{
			std::string errstr;
			errstr.resize(m_errorBlob->GetBufferSize());

			std::copy_n((char*)m_errorBlob->GetBufferPointer(), m_errorBlob->GetBufferSize(), errstr.begin());
			errstr += "\n";

			::OutputDebugStringA(errstr.c_str());
		}
		exit(1);
	}

	/// �C���v�b�g���C�A�E�g�ݒ�
	D3D12_INPUT_ELEMENT_DESC InputDesc[] =
	{
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
	};

	/// �O���t�B�b�N�p�C�v���C���X�e�[�g�쐬
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graPipeDesc = {};
	graPipeDesc.pRootSignature = nullptr;
	graPipeDesc.VS.pShaderBytecode = m_vsBlob->GetBufferPointer();
	graPipeDesc.VS.BytecodeLength = m_vsBlob->GetBufferSize();
	graPipeDesc.PS.pShaderBytecode = m_psBlob->GetBufferPointer();
	graPipeDesc.PS.BytecodeLength = m_psBlob->GetBufferSize();

	/// �f�t�H���g�̃T���v���}�X�N��\���萔
	graPipeDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	/// �܂��A���`�G�C���A�X�͎g��Ȃ�
	graPipeDesc.RasterizerState.MultisampleEnable = false;
	graPipeDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; /// �J�����O���Ȃ�
	graPipeDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; /// ���g��h��Ԃ�
	graPipeDesc.RasterizerState.DepthClipEnable = true; /// �[�x�����̃N���b�s���O�͗L����


	/// �u�����h�X�e�[�g�̐ݒ�
	graPipeDesc.BlendState.AlphaToCoverageEnable = false;
	graPipeDesc.BlendState.IndependentBlendEnable = false;

	D3D12_RENDER_TARGET_BLEND_DESC rtbdesc = {};
	rtbdesc.BlendEnable = false;
	rtbdesc.LogicOpEnable = false;
	rtbdesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	graPipeDesc.BlendState.RenderTarget[0] = rtbdesc;

	/// �c��
	graPipeDesc.RasterizerState.FrontCounterClockwise = false;
	graPipeDesc.RasterizerState.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
	graPipeDesc.RasterizerState.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
	graPipeDesc.RasterizerState.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	graPipeDesc.RasterizerState.AntialiasedLineEnable = false;
	graPipeDesc.RasterizerState.ForcedSampleCount = 0;
	graPipeDesc.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	graPipeDesc.DepthStencilState.DepthEnable = false;
	graPipeDesc.DepthStencilState.StencilEnable = false;

	/// ���C�A�E�g�擪�A�h���X
	graPipeDesc.InputLayout.pInputElementDescs = InputDesc;
	/// ���C�A�E�g�z��̗v�f��
	graPipeDesc.InputLayout.NumElements = _countof(InputDesc);

	graPipeDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;

	/// �v���~�e�B�u�g�|���W�ݒ�
	graPipeDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	/// �����_�[�^�[�Q�b�g�ݒ�
	graPipeDesc.NumRenderTargets = 1;
	graPipeDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

	// AA�ݒ�
	graPipeDesc.SampleDesc.Count = 1;
	graPipeDesc.SampleDesc.Quality = 0;

	/// ���[�g�V�O�l�`���쐬
	D3D12_ROOT_SIGNATURE_DESC rsDesc = {};
	rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	result = D3D12SerializeRootSignature(
		&rsDesc,	/// ���[�g�V�O�l�`��
		D3D_ROOT_SIGNATURE_VERSION_1_0,		/// ���[�g�V�O�l�`���o�[�W����
		&m_RootSigBlob,		/// �V�F�[�_�[��������Ƃ��Ɠ���
		&m_errorBlob		/// �G���[����������
	);

	/// ���[�g�V�O�l�`���I�u�W�F�N�g�̍쐬
	result = Task01Renderer::GetDevice12()->CreateRootSignature(
		0,
		m_RootSigBlob->GetBufferPointer(),
		m_RootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&m_RootSignature)
	);
	/// ���
	m_RootSigBlob->Release();
	graPipeDesc.pRootSignature = m_RootSignature;

	/// �O���t�B�b�N�p�C�v���C���쐬
	result = Task01Renderer::GetDevice12()->CreateGraphicsPipelineState(&graPipeDesc, IID_PPV_ARGS(&m_PipelineState));
	Task01Renderer::SetPipelineState(m_PipelineState);

	/// �r���[�|�[�g�ݒ�
	g_Viewport.Width = SCREEN_WIDTH;
	g_Viewport.Height = SCREEN_HEIGHT;
	g_Viewport.TopLeftX = 0;
	g_Viewport.TopLeftY = 0;
	g_Viewport.MaxDepth = 1.0f;
	g_Viewport.MinDepth = 0.0f;


	/// �V�U�[��`
	g_ScissorRect.top = 0;	/// �؂蔲������W
	g_ScissorRect.left = 0;	/// �؂蔲�������W
	g_ScissorRect.right = g_ScissorRect.left + SCREEN_WIDTH;	/// �؂蔲���E���W
	g_ScissorRect.bottom = g_ScissorRect.top + SCREEN_HEIGHT;	/// �؂蔲������W


#endif // USE_DX12

#ifdef USE_OPENGL



#endif // USE_OPENGL

}

void Task013DPolygon::Uninit()
{
#ifdef USE_DX11

	m_VertexBuffer->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

#endif // USE_DX11

#ifdef USE_DX12

	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_vsBlob->Release();
	m_psBlob->Release();
	m_RootSignature->Release();

#endif // USE_DX12

}

void Task013DPolygon::Update()
{
#ifdef USE_DX11

	/// ��]
	{
		if (Task01_Input::GetKeyPress('W')) /// W�L�[�ŏ�
		{
			m_Rotation.y += VALUE_ROTATE;
		}
		if (Task01_Input::GetKeyPress('S')) /// S�L�[�ŉ�
		{
			m_Rotation.y -= VALUE_ROTATE;
		}
		if (Task01_Input::GetKeyPress('A')) /// A�L�[�ō�
		{
			m_Rotation.x += VALUE_ROTATE;
		}
		if (Task01_Input::GetKeyPress('D')) /// D�L�[�ŉE
		{
			m_Rotation.x -= VALUE_ROTATE;
		}
	}

#endif // USE_DX11

#ifdef USE_OPENGL

	if (Task01_Input::GetKeyPress('W')) /// W�L�[�ŏ�
	{
		g_CameraPos.y += 0.5f;
	}
	if (Task01_Input::GetKeyPress('S')) /// W�L�[�ŏ�
	{
		g_CameraPos.y += -0.5f;
	}

#endif // USE_OPENGL

	
	/// �ԐF��ύX
	if (m_NowColor == RED)
	{
		m_blue -= 0.01f;
		m_red += 0.01f;

		/// ���̐F
		if (m_red >= 1.0f)
		{
			m_NowColor = GREEN;
		}
	}

	/// �ΐF��ύX
	if (m_NowColor == GREEN)
	{
		m_red -= 0.01f;
		m_green += 0.01f;

		/// ���̐F
		if (m_green >= 1.0f)
		{
			m_NowColor = BLUE;
		}
	}

	/// �ΐF��ύX
	if (m_NowColor == BLUE)
	{
		m_green -= 0.01f;
		m_blue += 0.01f;

		/// ���̐F
		if (m_blue >= 1.0f)
		{
			m_NowColor = RED;
		}
	}

#ifdef USE_DX11
	/// �F�ύX
	{
		for (int i = 0; i < VERTEX_NUM; i++)
		{
			g_VertexArray[i].Diffuse.r = m_red;
			g_VertexArray[i].Diffuse.g = m_green;
			g_VertexArray[i].Diffuse.b = m_blue;
		}

		// ���_�o�b�t�@����
		D3D11_BUFFER_DESC bd{};
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * VERTEX_NUM;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd{};
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = g_VertexArray;

		Task01Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	}
#endif // USE_DX11

}

void Task013DPolygon::Draw()
{
#ifdef USE_DX11

	/// ���̓��C�A�E�g�ݒ�
	Task01Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	/// �V�F�[�_�ݒ�
	Task01Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Task01Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	/// ���[���h�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Task01Renderer::SetWorldMatrix(&world);

	/// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Task01Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	/// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Task01Renderer::SetMaterial(material);

	/// �e�N�X�`���ݒ�
	///Task01Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	/// �v���~�e�B�u�g�|���W�ݒ�
	Task01Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	/// �|���S���`��
	Task01Renderer::GetDeviceContext()->Draw(VERTEX_NUM, 0);

#endif // USE_DX11

#ifdef USE_DX12

	/// �p�C�v���C���Z�b�g
	Task01Renderer::GetGraphicsCommandList()->SetPipelineState(m_PipelineState);

	/// �r���[�|�[�g�Z�b�g
	Task01Renderer::GetGraphicsCommandList()->RSSetViewports(1, &g_Viewport);
	Task01Renderer::GetGraphicsCommandList()->RSSetScissorRects(1, &g_ScissorRect);

	/// ���[�g�V�O�l�`���Z�b�g
	Task01Renderer::GetGraphicsCommandList()->SetGraphicsRootSignature(m_RootSignature);

	/// �v���~�e�B�u�g�|���W�ݒ�
	Task01Renderer::GetGraphicsCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	/// ���_�o�b�t�@�[�Z�b�g
	Task01Renderer::GetGraphicsCommandList()->IASetVertexBuffers(0, 1, &m_vbview);

	/// �C���f�b�N�X�o�b�t�@�[�Z�b�g
	Task01Renderer::GetGraphicsCommandList()->IASetIndexBuffer(&m_ibview);

	/// �`�施��
	//Task01Renderer::GetGraphicsCommandList()->DrawInstanced(VERTEX_NUM, 1, 0, 0);	/// ���_���A�C���X�^���X���A���_�f�[�^�̃I�t�Z�b�g�A�C���X�^���X�̃I�t�Z�b�g
	Task01Renderer::GetGraphicsCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);

#endif // USE_DX12

#ifdef USE_OPENGL

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// ���C�e�B���O����
	glDisable(GL_LIGHTING);
	{
		//���f���̃��[���h�s����쐬
		glTranslatef(0.0f, 0.0f, 0.0f);

		glBegin(GL_TRIANGLE_STRIP);//�|���S���̕\���̎d�� STRIP
		{
			glPushMatrix();

			glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�O�@���_�F
			glTexCoord2f(1, 0);				//		�e�N�X�`�����W
			glVertex3f(0.9f, 0, -0.9f);		//		�\����ʍ��W

			glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�P
			glTexCoord2f(0, 0);
			glVertex3f(-0.9f, 0, -0.9f);

			glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�Q
			glTexCoord2f(1, 1);
			glVertex3f(0.9f, 0, 0.9f);

			glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�R
			glTexCoord2f(0, 1);
			glVertex3f(-0.9f, 0, 0.9f);

			glPopMatrix();
		}
		glEnd();
	}
	// ���C�e�B���O�L��
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

#endif // USE_OPENGL


}
