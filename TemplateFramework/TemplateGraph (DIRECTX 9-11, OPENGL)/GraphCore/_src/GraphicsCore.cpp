#include "../_inc/GraphCore.h"

#include <assert.h>
#include "../../../TemplateCommon/CommonCore/_inc/Logger.h"

#pragma region GRAPHCORE
//-----------------------------------------------------------------------------GRAPHCORE------------------------------------------------------------------------------//
using namespace GRAPHCORE;
using namespace DEBUGLOGCODE;

bool GraphicsCoreActive = TRUE;

mutex GRAPHCORE::GraphicsCoreMutex;
CRITICAL_SECTION GRAPHCORE::GraphicsCoreCriticalSection;

DWORD GRAPHCORE::RenderThread(LPVOID lpdwThreadParam)
	{
	RENDERER * Renderer = ( ( TPARAM * ) lpdwThreadParam )->Renderer;
	bool * graphicsCoreThreadActive = &( ( TPARAM * ) lpdwThreadParam )->graphicsCoreThreadActive;
	int * isThreadLaunched = &( ( TPARAM * ) lpdwThreadParam )->isThreadLaunched;

	*isThreadLaunched = 1;

	while ( *graphicsCoreThreadActive )
		{
		EnterCriticalSection( &GraphicsCoreCriticalSection ); //функция входа в критическую секцию
		Renderer->CalculateFPS ();
		Renderer->Render();
		LeaveCriticalSection( &GraphicsCoreCriticalSection ); //функция выхода из критической секции
		}
	
	*isThreadLaunched = 2;

	return 0;
	};

vector<string> GRAPHICSCORE::TempLog = vector<string>();

#pragma region GRAPHICSCORE
GRAPHICSCORE::GRAPHICSCORE( HWND _hWnd, DWORD _style, int _sizeX, int _sizeY, RENDERER_TYPES _renderer) : Renderer(NULL)
	{
	LOG(_hWnd, "LOG GRAPHICSCORE START");
	switch (_renderer)
		{
		case DirectX9: Renderer = new DIRECTX9();
			break;
			//case DirectX11: Renderer = new DIRECTX11(); break;
			//case OpenGL: Renderer = new OPENGL(); break;
		};
	Renderer->Initiate(_hWnd, _sizeX, _sizeY);

	Agent.Renderer = Renderer;
	Agent.graphicsCoreThreadActive = true;

	InitializeCriticalSection( &GraphicsCoreCriticalSection ); //инициализациия критической секции

	renderThreadHandle = CreateThread( NULL, 0, ( LPTHREAD_START_ROUTINE ) &::RenderThread, ( LPVOID ) &Agent, 0, &renderThreadId );
	};
GRAPHICSCORE::~GRAPHICSCORE()
	{
	Agent.graphicsCoreThreadActive = false;

	while ( Agent.isThreadLaunched != 2 )
		{
		Sleep( 100 );
		}

	OBJDELETE( Renderer );
	LOG(NULL, "LOG GRAPHICSCORE END");
	LOG_STOP ();

	DeleteCriticalSection( &GraphicsCoreCriticalSection ); //Удаление(деинициализация) критической секции
	};
HRESULT GRAPHICSCORE::Render_Start(HWND _hWnd, DWORD _style, int _sizeX, int _sizeY)
	{
	ResumeThread( renderThreadHandle );
	return ( !renderThreadHandle ) ? E_FAIL : S_OK;
	}
HRESULT GRAPHCORE::GRAPHICSCORE::Render_Stop( HWND _hWnd, DWORD _style, int _sizeX, int _sizeY )
	{
	SuspendThread( renderThreadHandle );
	return ( !renderThreadHandle ) ? E_FAIL : S_OK;
	}
RENDERER * GRAPHICSCORE::GetRenderer()
	{
	return Renderer;
	};
#pragma endregion

void GRAPHICSCORE::AddLog(string _message)
	{
	TempLog.push_back(_message);
	};
//----------------------------------------------------------------------------~GRAPHCORE------------------------------------------------------------------------------//  
#pragma endregion