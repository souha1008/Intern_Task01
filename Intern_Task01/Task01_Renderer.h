#pragma once
//==============================================================
// Filename: Task01_Renderer.h
// Description: 3D��Ԃ̃����_�[
// Copyright (C)  Silicon Studio Co., Ltd. All rights reserved.
//==============================================================

#ifdef USE_DX11


/// ���_���
struct VERTEX_3D
{
	D3DXVECTOR3 Position;	/// �ʒu
	D3DXVECTOR3 Normal;		/// �@��
	D3DXCOLOR Diffuse;		/// �F
	D3DXVECTOR2 TexCoord;	/// �e�N�X�`�����W
};


/// �}�e���A�����
struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	float		Dummy[3];
};


/// ���C�g���
struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	D3DXVECTOR4	Direction;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Ambient;
};

#endif // USE_DX11


class Task01Renderer
{
public:

	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

#ifdef USE_DX11

	static void SetDepthEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);

	static ID3D11Device* GetDevice(void) { return m_Device; }
	static ID3D11DeviceContext* GetDeviceContext(void) { return m_DeviceContext; }



	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

#endif // USE_DX11

#ifdef USE_DX12

	static void EnableDebugLayer();

#endif // USE_DX12


private:
#ifdef USE_DX11

	/// DX11
	static D3D_FEATURE_LEVEL       m_FeatureLevel;

	static ID3D11Device* m_Device;
	static ID3D11DeviceContext* m_DeviceContext;
	static IDXGISwapChain* m_SwapChain;
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;

	static ID3D11Buffer* m_WorldBuffer;
	static ID3D11Buffer* m_ViewBuffer;
	static ID3D11Buffer* m_ProjectionBuffer;
	static ID3D11Buffer* m_MaterialBuffer;
	static ID3D11Buffer* m_LightBuffer;


	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;

#endif // USE_DX11


#ifdef USE_DX12

	static ID3D12Device* m_D12Device;
	static IDXGIFactory6* m_DXGIFactry;
	static IDXGISwapChain4* m_SwapChain4;
	static ID3D12CommandAllocator* m_CmdAllocator;
	static ID3D12GraphicsCommandList* m_GCmdList;
	static ID3D12CommandQueue* m_CmdQueue;
	static ID3D12DescriptorHeap* m_DescHeap;

	static ID3D12Fence* m_Fence;

#endif // USE_DX12

};