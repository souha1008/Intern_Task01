#pragma once

//==============================================================
// Filename: Task01_Main.h
// Description: 主要なヘッダーファイルやライブラリを読み込む
// Copyright (C)  Silicon Studio Co., Ltd. All rights reserved.
//==============================================================

/// DirectX12を使う場合は「USE_DX12」
/// DirectX11を使う場合は「USE_DX11」
/// OpenGLを使う場合は「USE_OPENGL」

#define USE_DX12
//#define USE_DX11
//#define USE_OPENGL

#include <windows.h>
#include <tchar.h>
#ifdef USE_DX11

#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>

#endif // USE_DX11
#ifdef USE_DX12

#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <DirectXMath.h>
#include <D3Dcompiler.h>

#endif // USE_DX12
#ifdef USE_OPENGL

#include <gl/GL.h>
#include <GL/GLU.h>

#endif // USE_OPENGL
#include <assert.h>
#include <vector>
#include <iostream>
#include <string>


#pragma warning(push)
#pragma warning(disable:4005)





#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)

#pragma comment (lib, "winmm.lib")

#ifdef USE_DX11

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")

#endif // USE_DX11

#ifdef USE_DX12

#pragma comment (lib, "d3d12.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")

#endif // USE_DX12

#ifdef USE_OPENGL

#pragma comment (lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#endif // USE_OPENGL



#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)


HWND GetWindow();
