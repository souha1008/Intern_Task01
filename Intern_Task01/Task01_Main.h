#pragma once

//==============================================================
// Filename: Task01_Main.h
// Description: 主要なヘッダーファイルやライブラリを読み込む
// Copyright (C)  Silicon Studio Co., Ltd. All rights reserved.
//==============================================================

/// DirectX12を使う場合は「USE_DX12」
/// DirectX11を使う場合は「USE_DX11」

#define USE_DX12
//#define USE_DX11

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <vector>
#include <iostream>
#include <list>


#pragma warning(push)
#pragma warning(disable:4005)

#ifdef USE_DX11

#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>

#endif // USE_DX11

#ifdef USE_DX12

#include <d3d12.h>
#include <dxgi1_6.h>

#endif // USE_DX12

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

#endif // USE_DX12


#define SCREEN_WIDTH	(960)
#define SCREEN_HEIGHT	(540)


HWND GetWindow();
