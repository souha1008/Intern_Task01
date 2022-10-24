#pragma once
//==============================================================
// Filename: Task01_3DPolygon.h
// Description: 3DÉ|ÉäÉSÉìï`âÊ
// Copyright (C)  Silicon Studio Co., Ltd. All rights reserved.
//==============================================================


/// èÛë‘ëJà⁄ópÅ@åªç›ïœçXíÜÇÃêF
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

    D3DXVECTOR3 m_Position = {0.0f, 0.0f, 0.0f};    /// à íu
    D3DXVECTOR3 m_Rotation = { 0.0f, 0.0f, 0.0f };  /// âÒì]
    D3DXVECTOR3 m_Scale = { 0.0f, 0.0f, 0.0f };     /// ägëÂó¶

    ID3D11Buffer* m_VertexBuffer = NULL;

    ID3D11VertexShader* m_VertexShader = NULL;
    ID3D11PixelShader* m_PixelShader = NULL;
    ID3D11InputLayout* m_VertexLayout = NULL;

#endif // USE_DX11

#ifdef USE_DX12

    ID3D12Resource* m_VertexBuffer = nullptr;
    ID3D12Resource* m_IndexBuffer = nullptr;
    DirectX::XMFLOAT3* m_vertexMap = nullptr;
    ID3DBlob* m_vsBlob = nullptr;
    ID3DBlob* m_psBlob = nullptr;
    ID3DBlob* m_errorBlob = nullptr;
    ID3DBlob* m_RootSigBlob = nullptr;
    ID3D12PipelineState* m_PipelineState = nullptr;
    ID3D12RootSignature* m_RootSignature = nullptr;

    D3D12_VERTEX_BUFFER_VIEW m_vbview = {};
    D3D12_INDEX_BUFFER_VIEW m_ibview = {};

#endif // USE_DX12


    float m_red = 0.0f;    /// ê‘
    float m_green = 0.0f;  /// óŒ
    float m_blue = 1.0f;   /// ê¬

    NowColor m_NowColor = RED;
};


