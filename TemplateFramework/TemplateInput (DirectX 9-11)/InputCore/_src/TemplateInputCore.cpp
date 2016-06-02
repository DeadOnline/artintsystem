#include "../_inc/TemplateInputCore.h"
#include "../../../TemplateCommon/CommonCore/_inc/Logger.h"

using namespace INPUTCORE;
using namespace DEBUGLOGCODE;

mutex INPUTCORE::InputCoreMutex;

DWORD INPUTCORE::InputThread( LPVOID lpdwThreadParam )
	{
	INOUTSHELL * InputShell = ( ( TPARAM * ) lpdwThreadParam )->InOutShell;
	bool * inputCoreThreadActive = &( ( TPARAM * ) lpdwThreadParam )->inputCoreThreadActive;
	int * isThreadLaunched = &( ( TPARAM * ) lpdwThreadParam )->isThreadLaunched;
	INOUTCORE * Inputter = InputShell->GetInputter();
	
	*isThreadLaunched = 1;

	while ( *inputCoreThreadActive )
		{
		Inputter->Update( Inputter->GetHandle() );
		InputShell->SendInputData();
		Sleep( INPUTTHREADSLEEPTIME );
		}

	*isThreadLaunched = 2;

	return 0;
	};
#pragma region INOUTCORE
INOUTCORE::INOUTCORE() : m_pHandle( NULL ), m_pDIObject( NULL ), m_pDIKeyboardDevice( NULL ), m_pDIMouseDevice( NULL ), m_fSensitivity( .005f )
	{
	ZeroMemory( m_KeyBuffer, sizeof( char ) * 256 );
	m_fCursorX = ( float ) GetSystemMetrics( SM_CXSCREEN ) / 2;
	m_fCursorY = ( float ) GetSystemMetrics( SM_CYSCREEN ) / 2;
	m_dwScreenWidth = ( DWORD ) GetSystemMetrics( SM_CXSCREEN );
	m_dwScreenHeight = ( DWORD ) GetSystemMetrics( SM_CYSCREEN );
	};
INOUTCORE::~INOUTCORE( void )
	{
	if ( m_pDIKeyboardDevice != NULL )
		{
		m_pDIKeyboardDevice->Unacquire();
		m_pDIKeyboardDevice->Release();
		m_pDIKeyboardDevice = NULL;
		}
	if ( m_pDIMouseDevice != NULL )
		{
		m_pDIMouseDevice->Unacquire();
		m_pDIMouseDevice->Release();
		m_pDIMouseDevice = NULL;
		}
	if ( m_pDIObject != NULL )
		{
		m_pDIObject->Release();
		m_pDIObject = NULL;
		}
	ClipCursor( &CursorOldClip );
	};
HRESULT INOUTCORE::Initiate_DINPUT( HWND _hWnd )
	{
	if ( FAILED( DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION, IID_IDirectInput8, ( void** ) &m_pDIObject, NULL ) ) )
		{
		MessageBox( _hWnd, "Failed to create m_pDIObject...", "Program exit", 0 ); exit( 1 );
		};
	return S_OK;
	};
HRESULT INOUTCORE::Initiate_InputDevice( HWND _hWnd )
	{
	Initiate_Keyboard( _hWnd );
	Initiate_Mouse( _hWnd );
	return S_OK;
	};
HRESULT INOUTCORE::Initiate_Keyboard( HWND _hWnd )
	{
	if ( FAILED( m_pDIObject->CreateDevice( GUID_SysKeyboard, &m_pDIKeyboardDevice, NULL ) ) )
		{
		MessageBox( _hWnd, "Failed to create keyboard m_pDIObject->CreateDevice...", "Program exit", 0 ); return E_FAIL;
		};
	if ( FAILED( m_pDIKeyboardDevice->SetDataFormat( &c_dfDIKeyboard ) ) )
		{
		MessageBox( _hWnd, "Failed to set data format m_pDIKeyboardDevice->SetDataFormat...", "Program exit", 0 ); return E_FAIL;
		};
	return S_OK;
	};
HRESULT INOUTCORE::Initiate_Mouse( HWND _hWnd )
	{
	DIDEVCAPS MouseCapabilities;

	if ( FAILED( m_pDIObject->CreateDevice( GUID_SysMouse, &m_pDIMouseDevice, NULL ) ) )
		{
		MessageBox( _hWnd, "Failed to create mouse m_pDIObject->CreateDevice...", "Program exit", 0 ); return E_FAIL;
		};
	if ( FAILED( m_pDIMouseDevice->SetDataFormat( &c_dfDIMouse2 ) ) )
		{
		MessageBox( _hWnd, "Failed to set data format m_pDIMouseDevice->SetDataFormat...", "Program exit", 0 ); return E_FAIL;
		};

	MouseCapabilities.dwSize = sizeof( MouseCapabilities );
	m_pDIMouseDevice->GetCapabilities( &MouseCapabilities );

	m_dwAxes = MouseCapabilities.dwAxes;
	m_dwButtons = MouseCapabilities.dwButtons;

	SetCursor( 0, 0, 0xffffffff );
	SetAttributes( false, 0.005f );

	return S_OK;
	};
HRESULT INOUTCORE::Update( HWND _hWnd )
	{
	ZeroMemory( m_KeyBuffer, sizeof( char ) * 256 );

	if ( m_pDIKeyboardDevice->GetDeviceState( sizeof( m_KeyBuffer ), ( LPVOID ) &m_KeyBuffer ) == DIERR_INPUTLOST )
		{
		if ( FAILED( m_pDIKeyboardDevice->SetCooperativeLevel( _hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
			{
			MessageBox( _hWnd, "Failed to set cooperarative level m_pDIKeyboardDevice->SetCooperativeLevel...", "Program exit", 0 ); return E_FAIL;
			};
		}
	else if ( FAILED( m_pDIKeyboardDevice->Acquire() ) )
		{
		MessageBox( _hWnd, "Failed to apply keyboard for usage m_pDIKeyboardDevice->Acquire...", "Program exit", 0 ); return E_FAIL;
		};

	if ( m_pDIMouseDevice->GetDeviceState( sizeof( m_MouseState ), ( LPVOID ) &m_MouseState ) == DIERR_INPUTLOST )
		{
		if ( FAILED( m_pDIMouseDevice->SetCooperativeLevel( _hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
			{
			MessageBox( _hWnd, "Failed to set cooperarative level m_pDIMouseDevice->SetCooperativeLevel...", "Program exit", 0 ); return E_FAIL;
			}
		}
	else if ( FAILED( m_pDIMouseDevice->Acquire() ) )
		{
		MessageBox( _hWnd, "Failed to apply mouse for usage m_pDIMouseDevice->Acquire...", "Program exit", 0 );
		};

	m_fCursorX += m_MouseState.lX * m_fSensitivity; //m_fCursorX<0 ? m_fCursorX = 0.0f : m_fCursorX>xSize ? m_fCursorX = (float)xSize : m_fCursorX = m_fCursorX;
	m_fCursorY += m_MouseState.lY * m_fSensitivity; //m_fCursorY<0 ? m_fCursorY = 0.0f : m_fCursorY>ySize ? m_fCursorY = (float)ySize : m_fCursorY = m_fCursorY;

	return S_OK;
	};
HRESULT INOUTCORE::KeyPressed( int Key )
	{
	return ( m_KeyBuffer[ Key ] & 0x80 ) ? S_OK : E_FAIL;
	};
HRESULT INOUTCORE::MouseButtonDown( int Button )
	{
	return ( m_MouseState.rgbButtons[ Button ] & 0x80 ) ? S_OK : E_FAIL;
	};
void	INOUTCORE::SetCursor( int iCursorHotSpotX, int iCursorHotSpotY, DWORD dwColor )
	{
	m_iHotSpotX = iCursorHotSpotX;
	m_iHotSpotY = iCursorHotSpotY;
	m_dwCursorColor = dwColor;
	}
void	INOUTCORE::SetAttributes( bool bInvert, float fNewSensitivity )
	{
	m_bInverted = bInvert; m_fSensitivity = fNewSensitivity;
	};
void	INOUTCORE::SetCursorPosition( float fNewX, float fNewY )
	{
	m_fCursorX = fNewX; m_fCursorY = fNewY;
	};
float	INOUTCORE::GetRelativeX( void )
	{
	float m_deltaX = m_MouseState.lX * m_fSensitivity;
	m_MouseState.lX = 0;
	return m_deltaX;
	};
float	INOUTCORE::GetRelativeY( void )
	{
	float m_deltaY = m_MouseState.lY * m_fSensitivity;
	m_MouseState.lY = 0;
	return m_deltaY;
	};
float	INOUTCORE::GetRelativeZ( void )
	{
	return ( float ) m_MouseState.lZ * m_fSensitivity;
	};
float	INOUTCORE::GetAbsoluteX( void )
	{
	return m_fCursorX;
	};
float	INOUTCORE::GetAbsoluteY( void )
	{
	return m_fCursorY;
	};
const	HWND&	INOUTCORE::GetHandle() const
	{
	return m_pHandle;
	};
#pragma endregion
#pragma region INOUTSHELL
INOUTSHELL::INOUTSHELL( HWND _hWnd ) : Inputter( NULL ), inputThreadId( 0 ), inputThreadHandle( NULL )
	{
	LOG(_hWnd, "LOG INOUTSHELL START");
	Inputter = new INOUTCORE();
	Inputter->Initiate_DINPUT( _hWnd );
	Inputter->Initiate_InputDevice( _hWnd );

	Agent.InOutShell = this;
	Agent.inputCoreThreadActive = true;

	inputThreadHandle = CreateThread( NULL, 0, ( LPTHREAD_START_ROUTINE ) &::InputThread, ( LPVOID ) &Agent, 0, &inputThreadId );
	};
INOUTSHELL::~INOUTSHELL()
	{
	Agent.inputCoreThreadActive = false;

	while ( Agent.isThreadLaunched != 2 )
		{
		Sleep( 100 );
		}

	InputCoreMutex.lock();
	OBJDELETE( Inputter );
	LOG(NULL, "LOG INOUTSHELL END");
	LOG_STOP ();
	InputCoreMutex.unlock();
	};
HRESULT INOUTSHELL::Scan_Start( HWND hWnd )
	{
	InputCoreMutex.lock();
	ResumeThread( inputThreadHandle );
	InputCoreMutex.unlock();
	
	return ( !inputThreadHandle ) ? E_FAIL : S_OK;
	}
HRESULT INOUTSHELL::Scan_Stop( HWND hWnd )
{
	InputCoreMutex.lock();
	SuspendThread( inputThreadHandle );
	InputCoreMutex.unlock();

	return ( !inputThreadHandle ) ? E_FAIL : S_OK;
}
INOUTCORE * INOUTSHELL::GetInputter()
	{
	return Inputter;
	};
#pragma endregion