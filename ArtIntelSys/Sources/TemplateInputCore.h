#pragma once

#include "ALL.h"

#ifndef cinput_h
#define cinput_h

#define DIMOUSE_LEFTBUTTON		0
#define DIMOUSE_RIGHTBUTTON		1
#define DIMOUSE_MIDDLEBUTTON	2
#define DIMOUSE_4BUTTON		3
#define DIMOUSE_5BUTTON		4
#define DIMOUSE_6BUTTON		5
#define DIMOUSE_7BUTTON		6
#define DIMOUSE_8BUTTON		7

class INPUTCORE
{
public:
							INPUTCORE(DWORD=1280,DWORD=800);
							~INPUTCORE(void);
	HRESULT					InitDirectInput(HWND hwd);
	HRESULT					InitKeyboard(HWND hwd);
	HRESULT					InitMouse(HWND hwd);
	HRESULT					Update(HWND hWnd);

	HRESULT					KeyPressed(int);

	void					DrawCursor(void);
	void					SetCursor(const char*,int,int,DWORD);
	void					SetAttributes(bool,float);
	void					SetCursorPosition(float,float);

	float					GetRelativeX(void);
	float					GetRelativeY(void);
	float					GetRelativeZ(void);
	float					GetAbsoluteX(void);
	float					GetAbsoluteY(void);
	HRESULT					MouseButtonDown(int);

	LPDIRECTINPUT8			m_pDIObject;
	LPDIRECTINPUTDEVICE8	m_pDIKeyboardDevice;
	LPDIRECTINPUTDEVICE8	m_pDIMouseDevice;

	char					m_KeyBuffer[256];

	DIMOUSESTATE2			m_MouseState;
	HRESULT					m_bInverted;
	float					m_fSensitivity,
							m_fCursorX,
							m_fCursorY;
	int						m_iHotSpotX,
							m_iHotSpotY;
	DWORD					m_dwAxes,
							m_dwButtons,
							m_dwCursorColor,
							m_dwScreenWidth,
							m_dwScreenHeight;
};

#endif