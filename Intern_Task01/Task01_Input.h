#pragma once
//==============================================================
// Filename: Task01_Input.h
// Description: キーボード入力を受け付ける
// Copyright (C)  Silicon Studio Co., Ltd. All rights reserved.
//==============================================================
#define	NUM_KEY_MAX			(256)

class Task01_Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];

public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress(BYTE KeyCode);
	static bool GetKeyTrigger(BYTE KeyCode);
};

