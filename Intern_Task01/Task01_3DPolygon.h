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

#ifdef USE_DX12
typedef struct
{
    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT2 uv;
}VERTEX;
#endif // USE_DX12

typedef struct
{
    unsigned char R, G, B, A;
}TEXRGBA;

class Task013DPolygon
{
public:
    void Init();
    void Uninit();
    void Update();
    void Draw();

private:

#ifdef USE_DX11

    D3DXVECTOR3 m_Position = { 0.0f, 0.0f, 0.0f };    /// à íu
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
    ID3D12Resource* m_TextureBuffer = nullptr;
    ID3D12Resource* m_ConstBuffer = nullptr;
    ID3DBlob* m_vsBlob = nullptr;
    ID3DBlob* m_psBlob = nullptr;
    ID3DBlob* m_errorBlob = nullptr;
    ID3DBlob* m_RootSigBlob = nullptr;
    ID3D12PipelineState* m_PipelineState = nullptr;
    ID3D12RootSignature* m_RootSignature = nullptr;
    ID3D12DescriptorHeap* m_BasicDescHeap = nullptr;
    
    VERTEX* m_vertexMap = nullptr;

    D3D12_VERTEX_BUFFER_VIEW m_vbview = {};
    D3D12_INDEX_BUFFER_VIEW m_ibview = {};

    

#endif // USE_DX12

#ifdef USE_OPENGL

    float m_PosX, m_PosY;
    float m_Rot;

#endif // USE_OPENGL



    float m_red = 0.0f;    /// ê‘
    float m_green = 0.0f;  /// óŒ
    float m_blue = 1.0f;   /// ê¬

    NowColor m_NowColor = RED;
};


