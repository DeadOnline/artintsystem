#include "../_inc/TemplateApplication (WinAPI).h"

#include "../../../TemplateCommon/CommonCore/_inc/Logger.h"

#include <io.h>
#include <fcntl.h>
#include <stdio.h>

using namespace WINAPIAPPLICATIONCORE;
using namespace DEBUGLOGCODE;

#define BACKGROUND_COLOR RGB(135, 163, 187)

APPLICATIONCORE::FPS::FPS() { FrameCnt = TimeElapsed = Time_Start = Time_End = 0; };

APPLICATIONCORE::APPLICATIONCORE(LPCSTR _name, DWORD _style, int _sizeX, int _sizeY) :
hWnd(NULL), wclass("Default Class"), caption(_name), style(_style), active(true), isCursorShown(true), isCursorClipped(true)
	{
	LOG(NULL, "LOG APPLICATIONCORE START");

	CurrentApplication = this;
	instance = GetModuleHandle(NULL);

	screenRect.left = screenRect.top = 0;
	screenRect.right = GetSystemMetrics(SM_CXSCREEN);
	screenRect.bottom = GetSystemMetrics(SM_CYSCREEN);

	if (style == WINDOWED)
		{
		windowRect.left = (GetSystemMetrics(SM_CXSCREEN) - _sizeX) / 2;
		windowRect.top = (GetSystemMetrics(SM_CYSCREEN) - _sizeY) / 2;
		windowRect.right = windowRect.left + _sizeX;
		windowRect.bottom = windowRect.top + _sizeY;
		}
	else
		{
		windowRect = screenRect;
		};

	clientRect.left = windowRect.left + 8; clientRect.right = windowRect.right - 8;
	clientRect.top = windowRect.top + 30; clientRect.bottom = windowRect.bottom - 8;

	sizeX = clientRect.right - clientRect.left;
	sizeY = clientRect.bottom - clientRect.top;

	memset(&devMode, 0, sizeof(DEVMODE));
	devMode.dmSize = sizeof(DEVMODE);
	devMode.dmPelsHeight = windowRect.bottom - windowRect.top;
	devMode.dmPelsWidth = windowRect.right - windowRect.left;
	devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = AppWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = instance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush( BACKGROUND_COLOR );
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = wclass;
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if ( RegisterClassEx( &wcex ) )
		{
		hWnd = CreateWindowEx( NULL, wclass, caption, style, windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL, instance, NULL );
		ShowWindow( hWnd, 1 ); UpdateWindow( hWnd );
		}
	};
APPLICATIONCORE::~APPLICATIONCORE()
	{
	LOG(NULL, "LOG APPLICATIONCORE END");
	LOG_STOP ();
	}
void		APPLICATIONCORE::UpdateTimeDelta()
	{
	TimeDelta.Time_End = GetTickCount64() - TimeDelta.Time_Start; TimeDelta.Time_Start = GetTickCount64();
	TimeDelta.FrameCnt++; TimeDelta.TimeElapsed += (TimeDelta.Time_End * .001f);
	if(TimeDelta.TimeElapsed >= 1.0f)
		{
		//TimeDelta.fps = (float)FPS.FrameCnt / FPS.TimeElapsed;
		TimeDelta.TimeElapsed = 0.0f;
		TimeDelta.FrameCnt = 0;
		}
	};

HWND		APPLICATIONCORE::GethWnd() { return hWnd; };
HINSTANCE	APPLICATIONCORE::GethInst() { return instance; };

//Launch function()
HRESULT		APPLICATIONCORE::Run()
	{
	if ( !hWnd ) return S_FALSE;

	if ( Init() == S_OK ) 
		{
		MSG Msg; ZeroMemory(&Msg, sizeof(MSG));
	
		while (Msg.message != WM_QUIT)
			{
			if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
				{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
				}
			else
				{
				if (active)
					{
					//CursorShow(0);
					CursorClip(GetAreaRect(Client));
					UpdateTimeDelta ();
					if (Frame()) break;
					};
				};
			};
		};

	Shutdown();
	UnregisterClass(wclass, instance);
	return S_OK;
	};

HRESULT		APPLICATIONCORE::Init() { return S_OK; };
HRESULT		APPLICATIONCORE::Frame() { return S_OK; };
HRESULT		APPLICATIONCORE::Shutdown() { return S_OK; };

LRESULT		APPLICATIONCORE::MsgProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
	{
	return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
	};

BOOL		APPLICATIONCORE::CreateConsole()
	{
	FreeConsole(); //на всякий случай
	if ( AllocConsole() )
		{
		int hCrt = _open_osfhandle((long)
									GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
		*stdout = *(::_fdopen(hCrt, "w"));
		::setvbuf(stdout, NULL, _IONBF, 0);
		*stderr = *(::_fdopen(hCrt, "w"));
		::setvbuf(stderr, NULL, _IONBF, 0);

		printf("Welcome to ArtIntSys!\n\n");
		return TRUE;
		}
	return FALSE;
	}

HRESULT		APPLICATIONCORE::AddWindow(WINDOWTYPES _type)
	{
	HWND hButton;
	(_type == Button) ?
		hButton = CreateWindowEx(0, "button", "button", WS_EX_TOPMOST | WS_VISIBLE | WS_CHILD, 0, 0, 100, 20, hWnd, NULL, NULL, 0)
		: 0;
	return S_OK;
	};
HRESULT		APPLICATIONCORE::CursorShow(BOOL _IsShown)
	{
	ShowCursor(_IsShown);
	return S_OK;
	};
HRESULT		APPLICATIONCORE::CursorClip(RECT& _area)
	{
	ClipCursor(&_area);
	return S_OK;
	};
HRESULT		APPLICATIONCORE::SetActive(BOOL _IsActive)
	{
	CurrentApplication->active = _IsActive;
	return S_OK;
	};

RECT&		APPLICATIONCORE::GetAreaRect(AREATYPES _type)
	{
	return (_type == Client) ? clientRect : (_type == Window) ? windowRect : screenRect;
	};
void		APPLICATIONCORE::SetAreaRect(AREATYPES _type, RECT& _area)
	{
	(_type == Client) ? clientRect = _area : (_type == Window) ? windowRect = _area : screenRect = _area;
	};

int&		APPLICATIONCORE::GetClientX()
	{
	return sizeX;
	};
int&		APPLICATIONCORE::GetClientY()
	{
	return sizeY;
	};

LRESULT FAR PASCAL AppWindowProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
	{
	switch (_uMsg)
		{
		case WM_KILLFOCUS:
			CurrentApplication->SetActive(false);
			CurrentApplication->CursorClip(CurrentApplication->GetAreaRect(Screen));
			break;

		case WM_SETFOCUS:
			CurrentApplication->SetActive(true);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:
			switch (_wParam)
				{
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;

				case VK_SPACE:
					CurrentApplication->AddWindow(Button); //Works bad
					break;

				case VK_RETURN:
					break;
				}
			break;

		default:
			return CurrentApplication->MsgProc(_hWnd, _uMsg, _wParam, _lParam);
		};
	return 0;
	};