#pragma once
//==============================================================
// Filename: Task01_3DPolygon.h
// Description: 3Dƒ|ƒŠƒSƒ“•`‰æ
// Copyright (C)  Silicon Studio Co., Ltd. All rights reserved.
//==============================================================


/// ó‘Ô‘JˆÚ—p@Œ»İ•ÏX’†‚ÌF
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

#ifdef USE_DX11

    D3DXVECTOR3 m_Position = {0.0f, 0.0f, 0.0f};    /// ˆÊ’u
    D3DXVECTOR3 m_Rotation = { 0.0f, 0.0f, 0.0f };  /// ‰ñ“]
    D3DXVECTOR3 m_Scale = { 0.0f, 0.0f, 0.0f };     /// Šg‘å—¦

    ID3D11Buffer* m_VertexBuffer = NULL;

    ID3D11VertexShader* m_VertexShader = NULL;
    ID3D11PixelShader* m_PixelShader = NULL;
    ID3D11InputLayout* m_VertexLayout = NULL;

#endif // USE_DX11

    float m_red = 0.0f;    /// Ô
    float m_green = 0.0f;  /// —Î
    float m_blue = 1.0f;   /// Â

    NowColor m_NowColor = RED;
};


