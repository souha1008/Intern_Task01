//==============================================================
// Filename: Task01_Camera.cpp
// Description: 空間ビュー用カメラ
// Copyright (C)  Silicon Studio Co., Ltd. All rights reserved.
//==============================================================

#include "Task01_Main.h"
#include "Task01_Manager.h"
#include "Task01_Renderer.h"
#include "Task01_Camera.h"

void Task01Camera::Init()
{
#ifdef USE_DX11

    m_Position = D3DXVECTOR3(0.0f, 2.0f, -5.0f);
    m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

#endif // USE_DX11
}

void Task01Camera::Uninit()
{
}

void Task01Camera::Update()
{
}

void Task01Camera::Draw()
{
#ifdef USE_DX11

    // ビューマトリクス設定
    D3DXMATRIX viewMatrix;
    D3DXVECTOR3 upvec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    D3DXMatrixLookAtLH(&viewMatrix, &m_Position, &m_Target,
        &upvec);
    Task01Renderer::SetViewMatrix(&viewMatrix);

    //プロジェクションマトリクス設定
    D3DXMATRIX projMatrix;
    D3DXMatrixPerspectiveFovLH(&projMatrix, 1.0f,
        (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
    Task01Renderer::SetProjectionMatrix(&projMatrix);

#endif // USE_DX11
}
