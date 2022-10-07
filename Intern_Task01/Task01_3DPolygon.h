#pragma once
//==============================================================
// Filename: Task01_3DPolygon.h
// Description: 3D�|���S���`��
// Copyright (C)  Silicon Studio Co., Ltd. All rights reserved.
//==============================================================


/// ��ԑJ�ڗp�@���ݕύX���̐F
enum NowColor
{
    RED = 0,
    GREEN,
    BLUE
};


class Task013DPolygon
{
public:
    void Init();
    void Uninit();
    void Update();
    void Draw();

private:
    D3DXVECTOR3 m_Position = {0.0f, 0.0f, 0.0f};    /// �ʒu
    D3DXVECTOR3 m_Rotation = { 0.0f, 0.0f, 0.0f };  /// ��]
    D3DXVECTOR3 m_Scale = { 0.0f, 0.0f, 0.0f };     /// �g�嗦

    ID3D11Buffer* m_VertexBuffer = NULL;

    ID3D11VertexShader* m_VertexShader = NULL;
    ID3D11PixelShader* m_PixelShader = NULL;
    ID3D11InputLayout* m_VertexLayout = NULL;

    float m_red = 0.0f;    /// ��
    float m_green = 0.0f;  /// ��
    float m_blue = 1.0f;   /// ��

    NowColor m_NowColor = RED;
};


