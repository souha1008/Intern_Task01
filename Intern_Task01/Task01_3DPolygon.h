#pragma once
//==============================================================
// Filename: Task01_3DPolygon.h
// Description: 3Dポリゴン描画
// Copyright (C)  Silicon Studio Co., Ltd. All rights reserved.
//==============================================================


/// 状態遷移用　現在変更中の色
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
    D3DXVECTOR3 m_Position = {0.0f, 0.0f, 0.0f};    /// 位置
    D3DXVECTOR3 m_Rotation = { 0.0f, 0.0f, 0.0f };  /// 回転
    D3DXVECTOR3 m_Scale = { 0.0f, 0.0f, 0.0f };     /// 拡大率

    ID3D11Buffer* m_VertexBuffer = NULL;

    ID3D11VertexShader* m_VertexShader = NULL;
    ID3D11PixelShader* m_PixelShader = NULL;
    ID3D11InputLayout* m_VertexLayout = NULL;

    float m_red = 0.0f;    /// 赤
    float m_green = 0.0f;  /// 緑
    float m_blue = 1.0f;   /// 青

    NowColor m_NowColor = RED;
};


