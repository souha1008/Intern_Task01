//==============================================================
// Filename: Task01_Camera.cpp
// Description: ��ԃr���[�p�J����
// Copyright (C)  Silicon Studio Co., Ltd. All rights reserved.
//==============================================================

#include "Task01_Main.h"
#include "Task01_Manager.h"
#include "Task01_Renderer.h"
#include "Task01_Camera.h"

void Task01Camera::Init()
{
    m_Position = D3DXVECTOR3(0.0f, 2.0f, -5.0f);
    m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Task01Camera::Uninit()
{
}

void Task01Camera::Update()
{
}

void Task01Camera::Draw()
{
    // �r���[�}�g���N�X�ݒ�
    D3DXMATRIX viewMatrix;
    D3DXVECTOR3 upvec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    D3DXMatrixLookAtLH(&viewMatrix, &m_Position, &m_Target,
        &upvec);
    Task01Renderer::SetViewMatrix(&viewMatrix);

    //�v���W�F�N�V�����}�g���N�X�ݒ�
    D3DXMATRIX projMatrix;
    D3DXMatrixPerspectiveFovLH(&projMatrix, 1.0f,
        (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
    Task01Renderer::SetProjectionMatrix(&projMatrix);
}
