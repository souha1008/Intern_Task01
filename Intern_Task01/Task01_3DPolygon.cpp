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

VERTEX vertexs[] = 
{
	{{-0.1f,-0.1f, 0.0f}, {0.0f, 1.0f}} ,	//����
	{{-0.1f, 0.1f, 0.0f}, {0.0f, 0.0f}} ,	//����
	{{ 0.1f,-0.1f, 0.0f}, {1.0f, 1.0f}},	//�E��
	{{ 0.1f, 0.1f, 0.0f}, {1.0f, 0.0f}},	//�E��
};
D3D12_VIEWPORT g_Viewport = {};
D3D12_RECT g_ScissorRect = {};

std::vector<TEXRGBA> g_TextureDate(256 * 256);

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
	reDesc.Width = sizeof(vertexs); /// ���_�T�C�Y
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
	std::copy(std::begin(vertexs), std::end(vertexs), m_vertexMap);
	m_VertexBuffer->Unmap(0, nullptr);

	/// �o�b�t�@�[�r���[����
	m_vbview.BufferLocation = m_VertexBuffer->GetGPUVirtualAddress(); /// �o�b�t�@�[�̉��z�A�h���X
	m_vbview.SizeInBytes = sizeof(vertexs); /// �S�o�C�g��
	m_vbview.StrideInBytes = sizeof(vertexs[0]); /// 1���_������̃o�C�g��

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

	/// �e�N�X�`���o�b�t�@�[�쐬
	D3D12_HEAP_PROPERTIES texHeapProp;
	texHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	texHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	texHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	texHeapProp.CreationNodeMask = 0;
	texHeapProp.VisibleNodeMask = 0;

	reDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	reDesc.Width = 256;
	reDesc.Height = 256;
	reDesc.DepthOrArraySize = 1;	// 2D�z��ł��Ȃ��̂łP
	reDesc.SampleDesc.Count = 1;
	reDesc.SampleDesc.Quality = 0;
	reDesc.MipLevels = 1;
	reDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	reDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	reDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	result = Task01Renderer::GetDevice12()->CreateCommittedResource(
		&texHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&reDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		nullptr,
		IID_PPV_ARGS(&m_TextureBuffer)
	);

	result = m_TextureBuffer->WriteToSubresource(
		0,
		nullptr,
		g_TextureDate.data(),
		sizeof(TEXRGBA) * 256,
		sizeof(TEXRGBA) * g_TextureDate.size()
	);

	/// �萔�o�b�t�@�쐬
	DirectX::XMMATRIX matrix = DirectX::XMMatrixIdentity();

	Task01Renderer::GetDevice12()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(matrix) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&m_ConstBuffer)
	);

	DirectX::XMMATRIX MapMatrix;
	result = m_ConstBuffer->Map(0, nullptr, (void**)&MapMatrix);
	MapMatrix = matrix;

	/// �V�F�[�_�[���\�[�X�r���[�쐬
	///�f�B�X�N���v�^�q�[�v
	D3D12_DESCRIPTOR_HEAP_DESC dhd = {};
	dhd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	dhd.NodeMask = 0;
	dhd.NumDescriptors = 2;
	dhd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	result = Task01Renderer::GetDevice12()->CreateDescriptorHeap(&dhd, IID_PPV_ARGS(&m_BasicDescHeap));

	D3D12_SHADER_RESOURCE_VIEW_DESC srvd = {};
	srvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvd.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvd.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MipLevels = 1;
	auto basicHeapHandle = m_BasicDescHeap->GetCPUDescriptorHandleForHeapStart(); // �f�B�X�N���v�^�̐퓬�n���h�����擾
	Task01Renderer::GetDevice12()->CreateShaderResourceView(
		m_TextureBuffer,
		&srvd,
		basicHeapHandle
	);
	
	basicHeapHandle.ptr += Task01Renderer::GetDevice12()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
	cbvDesc.BufferLocation = m_ConstBuffer->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = m_ConstBuffer->GetDesc().Width;
	Task01Renderer::GetDevice12()->CreateConstantBufferView(&cbvDesc, basicHeapHandle);

	/// �C���v�b�g���C�A�E�g�ݒ�
	D3D12_INPUT_ELEMENT_DESC InputDesc[] =
	{
		/// ���W���
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},

		/// uv���W
		{
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
			0, D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
	};

	/// �O���t�B�b�N�p�C�v���C���X�e�[�g�쐬
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graPipeDesc = {};
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

	// �f�B�X�N���v�^�����W
	D3D12_DESCRIPTOR_RANGE dr[2] = {};
	// �e�N�X�`���p���W�X�^�[0��
	dr[0].NumDescriptors = 1;
	dr[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	dr[0].BaseShaderRegister = 0;
	dr[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// �萔�p���W�X�^�[1��
	dr[1].NumDescriptors = 1;
	dr[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	dr[1].BaseShaderRegister = 0;
	dr[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	/// ���[�g�p�����[�^�쐬
	D3D12_ROOT_PARAMETER rpram[2] = {};
	/// �s�N�Z���V�F�[�_�[
	rpram[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rpram[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rpram[0].DescriptorTable.pDescriptorRanges = &dr[0];
	rpram[0].DescriptorTable.NumDescriptorRanges = 1;

	/// ���_�V�F�[�_�[
	rpram[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rpram[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rpram[1].DescriptorTable.pDescriptorRanges = &dr[1];
	rpram[1].DescriptorTable.NumDescriptorRanges = 1;

	/// �X�^�e�B�b�N�T���v���[
	D3D12_STATIC_SAMPLER_DESC ssd = {};
	ssd.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	ssd.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	ssd.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	ssd.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	ssd.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	ssd.MaxLOD = D3D12_FLOAT32_MAX;
	ssd.MinLOD = 0.0f;
	ssd.ShaderVisibility = D3D12_SHADER_VISIBILITY_MESH;
	ssd.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;

	/// ���[�g�V�O�l�`���f�X�N
	D3D12_ROOT_SIGNATURE_DESC rsd = {};
	rsd.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rsd.pParameters = rpram;
	rsd.NumParameters = 2;
	rsd.pStaticSamplers = &ssd;
	rsd.NumStaticSamplers = 1;
	

	result = D3D12SerializeRootSignature(
		&rsd,	/// ���[�g�V�O�l�`��
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
	//Task01Renderer::SetPipelineState(m_PipelineState);

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


	/// �e�N�X�`���f�[�^����
	for (auto& rgba : g_TextureDate)
	{
		rgba.R = rand() & 256;
		rgba.G = rand() & 256;
		rgba.B = rand() & 256;
		rgba.A = rand() & 256;
	}

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

	if (Task01_Input::GetKeyPress(VK_LEFT))
	{
		m_Rot -= 1.0f;
	}

	if (Task01_Input::GetKeyPress(VK_RIGHT))
	{
		m_Rot += 1.0f;
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

	/// �f�B�X�N���v�^�[�q�[�v�Z�b�g
	Task01Renderer::GetGraphicsCommandList()->SetDescriptorHeaps(1, &m_BasicDescHeap);

	/// ���[�g�p�����[�^�[�Z�b�g
	Task01Renderer::GetGraphicsCommandList()->SetGraphicsRootDescriptorTable(0, m_BasicDescHeap->GetGPUDescriptorHandleForHeapStart());


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
		// ��]
		glRotatef(m_Rot, 0, 1, 0);

		glBegin(GL_TRIANGLE_STRIP);//�|���S���̕\���̎d�� STRIP
		{
			// ��
			glPushMatrix();
			{
				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�O�@���_�F
				glTexCoord2f(1, 0);				//		�e�N�X�`�����W
				glVertex3f(2.0f, 2.0f, -2.0f);		//		�\����ʍ��W

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�P
				glTexCoord2f(0, 0);
				glVertex3f(-2.0f, 2.0f, -2.0f);

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�Q
				glTexCoord2f(1, 1);
				glVertex3f(2.0f, 2.0f, 2.0f);

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�R
				glTexCoord2f(0, 1);
				glVertex3f(-2.0f, 2.0f, 2.0f);
			}
			glPopMatrix();

			// ��
			glPushMatrix();
			{
				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�O�@���_�F
				glTexCoord2f(1, 0);				//		�e�N�X�`�����W
				glVertex3f(-2.0f, -2.0f, 2.0f);		//		�\����ʍ��W

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�P
				glTexCoord2f(0, 0);
				glVertex3f(2.0f, -2.0f, 2.0f);

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�Q
				glTexCoord2f(1, 1);
				glVertex3f(-2.0f, -2.0f, -2.0f);

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�R
				glTexCoord2f(0, 1);
				glVertex3f(2.0f, -2.0f, -2.0f);
			}
			glPopMatrix();

			// �O
			glPushMatrix();
			{
				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�O�@���_�F
				glTexCoord2f(1, 0);				//		�e�N�X�`�����W
				glVertex3f(2.0f, 2.0f, 2.0f);		//		�\����ʍ��W

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�P
				glTexCoord2f(0, 0);
				glVertex3f(-2.0f, 2.0f, 2.0f);

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�Q
				glTexCoord2f(1, 1);
				glVertex3f(2.0f, -2.0f, 2.0f);

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�R
				glTexCoord2f(0, 1);
				glVertex3f(-2.0f, -2.0f, 2.0f);
			}
			glPopMatrix();

			// ���
			glPushMatrix();
			{
				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�O�@���_�F
				glTexCoord2f(1, 0);				//		�e�N�X�`�����W
				glVertex3f(-2.0f, 2.0f, -2.0f);		//		�\����ʍ��W

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�P
				glTexCoord2f(0, 0);
				glVertex3f(2.0f, 2.0f,-2.0f);

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�Q
				glTexCoord2f(1, 1);
				glVertex3f(-2.0f, -2.0f,-2.0f);

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�R
				glTexCoord2f(0, 1);
				glVertex3f(2.0f, -2.0f,-2.0f);
			}
			glPopMatrix();

			// �E
			glPushMatrix();
			{
				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�O�@���_�F
				glTexCoord2f(1, 0);				//		�e�N�X�`�����W
				glVertex3f(2.0f, 2.0f, -2.0f);		//		�\����ʍ��W

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�P
				glTexCoord2f(0, 0);
				glVertex3f(2.0f, 2.0f, 2.0f);

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�Q
				glTexCoord2f(1, 1);
				glVertex3f(2.0f, -2.0f, -2.0f);

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�R
				glTexCoord2f(0, 1);
				glVertex3f(2.0f, -2.0f, 2.0f);
			}
			glPopMatrix();

			// ��
			glPushMatrix();
			{
				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�O�@���_�F
				glTexCoord2f(1, 0);				//		�e�N�X�`�����W
				glVertex3f(-2.0f, 2.0f, 2.0f);		//		�\����ʍ��W

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�P
				glTexCoord2f(0, 0);
				glVertex3f(-2.0f, 2.0f,-2.0f);

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�Q
				glTexCoord2f(1, 1);
				glVertex3f(-2.0f, -2.0f, 2.0f);

				glColor4f(1.0, 1.0, 1.0, 1.0f);//���_�R
				glTexCoord2f(0, 1);
				glVertex3f(-2.0f, -2.0f,-2.0f);
			}
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
