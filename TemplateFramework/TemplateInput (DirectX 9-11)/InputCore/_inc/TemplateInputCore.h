#ifndef cinput_h
#define cinput_h

#include <dinput.h>            //DirectInput header (NEW)
#include <mutex>
#include <vector>
#include "../../../TemplateCommon/CommonCore/_inc/Logger.h"
#include "../../../TemplateCommon/CommonCore/Macroses.h"

#define DIMOUSE_LEFTBUTTON		0
#define DIMOUSE_RIGHTBUTTON		1
#define DIMOUSE_MIDDLEBUTTON	2
#define DIMOUSE_4BUTTON			3
#define DIMOUSE_5BUTTON			4
#define DIMOUSE_6BUTTON			5
#define DIMOUSE_7BUTTON			6
#define DIMOUSE_8BUTTON			7

#define INPUTTHREADSLEEPTIME	16

using namespace std;

namespace INPUTCORE
	{
	DWORD InputThread( LPVOID lpdwThreadParam );

	extern mutex InputCoreMutex;
	
	class INOUTSHELL;

	class INOUTCORE
		{
	private:
		HWND					m_pHandle;

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
		RECT					CursorClip;           	// новая область для ClipCursor
		RECT					CursorOldClip;        	// предыдущая область для ClipCursor

	public:
		INOUTCORE();
		virtual ~INOUTCORE();
		HRESULT					Initiate_DINPUT(HWND hwd);
		HRESULT					Initiate_InputDevice(HWND hwd);
	private:
		HRESULT					Initiate_Keyboard(HWND hwd);
		HRESULT					Initiate_Mouse(HWND hwd);
	public:
		HRESULT					Update(HWND hWnd);

		HRESULT					KeyPressed(int);

		void					DrawCursor(void);
		void					SetCursor(int, int, DWORD);
		void					SetAttributes(bool, float);
		void					SetCursorPosition(float, float);

		float					GetRelativeX(void);
		float					GetRelativeY(void);
		float					GetRelativeZ(void);
		float					GetAbsoluteX(void);
		float					GetAbsoluteY(void);
		HRESULT					MouseButtonDown(int);

		const HWND&				GetHandle() const;
		};
	
	struct TPARAM
	{
		INOUTSHELL * InOutShell = NULL;
		bool inputCoreThreadActive = false;
		int isThreadLaunched = 0; //0 - Didn't launch, 1 - launched right now, 2 - died
	};

	class INOUTSHELL
	{
		DWORD		inputThreadId;
		HANDLE		inputThreadHandle;
		INOUTCORE * Inputter;
		//DEBUGLOG	TempLog;

		TPARAM		Agent;
	public:
		INOUTSHELL( HWND _hWnd );
		~INOUTSHELL();

		HRESULT				Scan_Start( HWND hWnd );
		HRESULT				Scan_Stop( HWND hWnd );
		virtual HRESULT		SendInputData( ) = 0;
		INOUTCORE *			GetInputter();
		};

	};

#endif