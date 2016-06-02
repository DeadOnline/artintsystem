#include "stdafx.h"
#include "ALL.h"

INPUTCORE::INPUTCORE(DWORD dwWidth,DWORD dwHeight): m_pDIObject(NULL), m_pDIKeyboardDevice(NULL), m_pDIMouseDevice(NULL)
{
m_fCursorX = (float)dwWidth / 2;
m_fCursorY = (float)dwHeight / 2;
m_dwScreenWidth = dwWidth;
m_dwScreenHeight = dwHeight;
};

INPUTCORE::~INPUTCORE(void)
{
if(m_pDIKeyboardDevice != NULL)
 {
 m_pDIKeyboardDevice->Unacquire();
 m_pDIKeyboardDevice->Release();
 m_pDIKeyboardDevice = NULL;
 }

if(m_pDIMouseDevice != NULL)
 {
 m_pDIMouseDevice->Unacquire();
 m_pDIMouseDevice->Release();
 m_pDIMouseDevice = NULL;
 }

if(m_pDIObject != NULL)
 {
 m_pDIObject->Release();
 m_pDIObject = NULL;
 }
}//~INPUTCORE
HRESULT INPUTCORE::InitDirectInput(HWND hwd) { DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&m_pDIObject,NULL); InitKeyboard(hwd); InitMouse(hwd); return S_OK; };
HRESULT INPUTCORE::InitKeyboard(HWND hwd) {
m_pDIObject->CreateDevice(GUID_SysKeyboard,&m_pDIKeyboardDevice,NULL);
m_pDIKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
m_pDIKeyboardDevice->SetCooperativeLevel(hwd,DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
m_pDIKeyboardDevice->Acquire();
 return S_OK; };
HRESULT INPUTCORE::InitMouse(HWND hwd)
{
DIDEVCAPS MouseCapabilities;

m_pDIObject->CreateDevice(GUID_SysMouse,&m_pDIMouseDevice,NULL);
m_pDIMouseDevice->SetDataFormat(&c_dfDIMouse2);
m_pDIMouseDevice->SetCooperativeLevel(hwd,DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
m_pDIMouseDevice->Acquire();
MouseCapabilities.dwSize = sizeof(MouseCapabilities);
m_pDIMouseDevice->GetCapabilities(&MouseCapabilities);

MouseCapabilities.dwFlags & DIDC_ATTACHED;

m_dwAxes = MouseCapabilities.dwAxes;
m_dwButtons = MouseCapabilities.dwButtons;

//SetCursor("arrow.bmp",0,0,0xffffffff);
SetAttributes(false,1.0f);

return S_OK;
};
HRESULT INPUTCORE::Update(HWND hWnd)
{
if(m_pDIKeyboardDevice->GetDeviceState(sizeof(m_KeyBuffer),(LPVOID)&m_KeyBuffer) == DIERR_INPUTLOST) m_pDIKeyboardDevice->Acquire();
if(m_pDIMouseDevice->GetDeviceState(sizeof(m_MouseState),(LPVOID)&m_MouseState) == DIERR_INPUTLOST)	m_pDIMouseDevice->Acquire();
POINT corxy; GetCursorPos(&corxy); //ScreenToClient (hWnd, &corxy);

m_fCursorX = corxy.x;/*m_MouseState.lX*/ /** m_fSensitivity*/; //if(m_fCursorX < 0) m_fCursorX = 0; else if(m_fCursorX > m_dwScreenWidth) m_fCursorX = (float)m_dwScreenWidth;
m_fCursorY = corxy.y/*m_MouseState.lY*/ /** m_fSensitivity*/; //else m_fCursorY = corxy.y/*m_MouseState.lY * m_fSensitivity*/; //if(m_fCursorY < 0) m_fCursorY = 0; else if(m_fCursorY > m_dwScreenHeight) m_fCursorY = (float)m_dwScreenHeight;

return S_OK;
};
HRESULT INPUTCORE::KeyPressed(int Key)
{
if(m_KeyBuffer[Key] & 0x80) 
{ return S_OK; }
return E_FAIL;
};

void INPUTCORE::DrawCursor(void)
{
//D3DCURSORVERTEX aCursorVertices[4];
//
//aCursorVertices[0].fX = m_fCursorX - m_iHotSpotX;
//aCursorVertices[0].fY = m_fCursorY - m_iHotSpotY;
//aCursorVertices[0].fZ = 0.0f;
//aCursorVertices[0].fRHW = 1.0f;
//aCursorVertices[0].dwColor = m_dwCursorColor;
//aCursorVertices[0].fU = 0.0f;
//aCursorVertices[0].fV = 0.0f;
//
//aCursorVertices[1].fX = m_fCursorX - m_iHotSpotX;
//aCursorVertices[1].fY = m_fCursorY + 32.0f - m_iHotSpotY;
//aCursorVertices[1].fZ = 0.0f;
//aCursorVertices[1].fRHW = 1.0f;
//aCursorVertices[1].dwColor = m_dwCursorColor;
//aCursorVertices[1].fU = 0.0f;
//aCursorVertices[1].fV = 1.0f;
//
//aCursorVertices[2].fX = m_fCursorX + 32.0f - m_iHotSpotX;
//aCursorVertices[2].fY = m_fCursorY - m_iHotSpotY;
//aCursorVertices[2].fZ = 0.0f;
//aCursorVertices[2].fRHW = 1.0f;
//aCursorVertices[2].dwColor = m_dwCursorColor;
//aCursorVertices[2].fU = 1.0f;
//aCursorVertices[2].fV = 0.0f;
//
//aCursorVertices[3].fX = m_fCursorX + 32.0f - m_iHotSpotX;
//aCursorVertices[3].fY = m_fCursorY + 32.0f - m_iHotSpotY;
//aCursorVertices[3].fZ = 0.0f;
//aCursorVertices[3].fRHW = 1.0f;
//aCursorVertices[3].dwColor = m_dwCursorColor;
//aCursorVertices[3].fU = 1.0f;
//aCursorVertices[3].fV = 1.0f;
//
//g_App.GetDevice()->SetFVF(D3DFVF_CURSORVERTEX);
//
//g_App.GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
//g_App.GetDevice()->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
//g_App.GetDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
//
//g_App.GetDevice()->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
//
//g_App.GetDevice()->SetTexture(0,m_pCursorTexture);
//g_App.GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,&aCursorVertices[0],sizeof(D3DCURSORVERTEX));
//
//g_App.GetDevice()->SetFVF(D3DFVF_CUSTOMVERTEX);
}//DrawCursor
void INPUTCORE::SetCursor(const char* strFilename,int iCursorHotSpotX,int iCursorHotSpotY,DWORD dwColor)
{
//D3DXCreateTextureFromFileExA(g_App.GetDevice(),strFilename,D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,NULL,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,0xff000000,NULL,NULL,&m_pCursorTexture);
//
//m_iHotSpotX = iCursorHotSpotX;
//m_iHotSpotY = iCursorHotSpotY;
//m_dwCursorColor = dwColor;
}

void INPUTCORE::SetAttributes(bool bInvert,float fNewSensitivity) { m_bInverted = bInvert; m_fSensitivity = fNewSensitivity; };
void INPUTCORE::SetCursorPosition(float fNewX,float fNewY) { m_fCursorX = fNewX; m_fCursorY = fNewY; };

float INPUTCORE::GetRelativeX(void) { return (float)m_MouseState.lX * m_fSensitivity; };
float INPUTCORE::GetRelativeY(void) { return (float)m_MouseState.lY * m_fSensitivity; };
float INPUTCORE::GetRelativeZ(void) { return (float)m_MouseState.lZ * m_fSensitivity; };
float INPUTCORE::GetAbsoluteX(void) { return m_fCursorX; };
float INPUTCORE::GetAbsoluteY(void) { return m_fCursorY; };
HRESULT INPUTCORE::MouseButtonDown(int Button) { if(m_MouseState.rgbButtons[Button] & 0x80) { return S_OK; } return E_FAIL; };