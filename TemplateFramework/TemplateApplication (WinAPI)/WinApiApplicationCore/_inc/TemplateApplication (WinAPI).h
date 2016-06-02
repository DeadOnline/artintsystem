#pragma once

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

#include <Windows.h>

#define FULLSCREEN	(WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE)
#define WINDOWED	(WS_OVERLAPPED | WS_CAPTION)

enum WINDOWTYPES
	{
	Button
	};

enum AREATYPES
	{
	Client,
	Window,
	Screen
	};

namespace WINAPIAPPLICATIONCORE
{

	class APPLICATIONCORE
	{
	private:

		HINSTANCE   instance;

		HWND        hWnd;

		LPCSTR      wclass;
		LPCSTR		caption;

		WNDCLASSEX	wcex;

		DWORD       style;

		DEVMODE		devMode;

		BOOL		active;
		RECT		clientRect;
		RECT		windowRect;
		RECT		screenRect;

		int			sizeX;
		int			sizeY;

		bool		isCursorShown;
		bool		isCursorClipped;

		//-----------------------//

		struct FPS
			{
			__int64 Time_Start, Time_End;
			int FrameCnt;
			float TimeElapsed;
			FPS ();
			} TimeDelta;

	public:

		APPLICATIONCORE(LPCSTR _name, DWORD _style = WINDOWED, int _sizeX = 100, int _sizeY = 100);
		virtual ~APPLICATIONCORE();

		void				UpdateTimeDelta ();

		HWND				GethWnd();
		HINSTANCE			GethInst();
		BOOL				Error(BOOL _fatal);
		BOOL				Move(long _xPos, long _yPos);
		BOOL				Resize(long _width, long _height);
		virtual		HRESULT SetActive(BOOL _IsActive);

		virtual		HRESULT Init();
		virtual		HRESULT	Run();
		virtual		HRESULT Shutdown();
		virtual		HRESULT Frame();

		virtual		HRESULT AddWindow(WINDOWTYPES _type);
		virtual		HRESULT CursorShow(BOOL _IsShown);
		virtual		HRESULT CursorClip(RECT& _area);

		virtual		LRESULT MsgProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

		BOOL		CreateConsole ();

		RECT&		GetAreaRect(AREATYPES _type);
		void		SetAreaRect(AREATYPES _type, RECT& _area);

		int&		GetClientX();
		int&		GetClientY();

	};

};

static WINAPIAPPLICATIONCORE::APPLICATIONCORE *CurrentApplication = NULL;
static LRESULT FAR PASCAL AppWindowProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);