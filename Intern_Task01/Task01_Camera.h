#pragma once
//==============================================================
// Filename: Task01_Camera.cpp
// Description: 空間ビュー用カメラ
// Copyright (C)  Silicon Studio Co., Ltd. All rights reserved.
//==============================================================

class Task01Camera
{
public:
    void Init();
    void Uninit();
    void Update();
    void Draw();

private:

#ifdef USE_DX11

    D3DXVECTOR3 m_Position;
    D3DXVECTOR3 m_Target;

#endif // USE_DX11
};

