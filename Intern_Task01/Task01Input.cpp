
#include "Task01_Main.h"
#include "Task01Input.h"


BYTE Task01_Input::m_OldKeyState[256];
BYTE Task01_Input::m_KeyState[256];


void Task01_Input::Init()
{

	memset(m_OldKeyState, 0, 256);
	memset(m_KeyState, 0, 256);

}

void Task01_Input::Uninit()
{


}

void Task01_Input::Update()
{

	memcpy(m_OldKeyState, m_KeyState, 256);

	GetKeyboardState(m_KeyState);

}

bool Task01_Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Task01_Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}
