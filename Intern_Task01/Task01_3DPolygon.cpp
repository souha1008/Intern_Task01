//==============================================================
// Filename: Task01_3DPolygon.cpp
// Description: 3D�|���S���`��
// Copyright (C)  Silicon Studio Co., Ltd. All rights reserved.
//==============================================================


#include "Task01_Main.h"
#include "Task01_Manager.h"
#include "Task01_Renderer.h"
#include "Task01_3DPolygon.h"
#include "Task01Input.h"


/// 
/// �}�N����`
///
#define	VALUE_ROTATE	(D3DX_PI * 0.006f)			// ��]��

#define	SIZE_X			(10.0f)					// �n�ʂ̃T�C�Y(X����)
#define SIZE_Y			(10.0f)					// �n�ʂ̃T�C�Y(Y����)
#define	SIZE_Z			(10.0f)					// �n�ʂ̃T�C�Y(Z����)

#define VERTEX_NUM	36

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

void Task013DPolygon::Init()
{
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
}

void Task013DPolygon::Uninit()
{
	m_VertexBuffer->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Task013DPolygon::Update()
{
	if (Task01_Input::GetKeyPress('W'))
	{
		m_Rotation.y += VALUE_ROTATE;
	}
	if (Task01_Input::GetKeyPress('S'))
	{
		m_Rotation.y -= VALUE_ROTATE;
	}
	if (Task01_Input::GetKeyPress('A'))
	{
		m_Rotation.x += VALUE_ROTATE;
	}
	if (Task01_Input::GetKeyPress('D'))
	{
		m_Rotation.x -= VALUE_ROTATE;
	}

	if (Task01_Input::GetKeyPress('1'))
	{
		for (int i = 0; i < VERTEX_NUM; i++)
		{
			g_VertexArray[i].Diffuse.r = 1.0f;
			g_VertexArray[i].Diffuse.g = 0.0f;
			g_VertexArray[i].Diffuse.b = 0.0f;
		}

	}

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
}

void Task013DPolygon::Draw()
{
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
}
