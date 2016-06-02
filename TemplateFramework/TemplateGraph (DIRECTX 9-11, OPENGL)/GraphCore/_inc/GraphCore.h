#pragma once
#ifndef GraphCoreHeader
#define GraphCoreHeader

#include <vector>
#include <map>
#include <mutex>
#include <Windows.h>

#include "../Renderer/_inc/Renderer.h"
#include "../Renderer/DirectX/_inc/DirectX.h"
#include "../Renderer/DirectX/DirectX9/_inc/DirectX9.h"
#include "../Renderer/DirectX/DirectX11/_inc/DirectX11.h"
#include "../Renderer/OpenGL/_inc/OpenGL.h"
#include "../_inc/Enums.h"

using namespace std;

#define GRAPHTHREADSLEEPTIME	1

namespace GRAPHCORE
{
	DWORD RenderThread( LPVOID lpdwThreadParam );

	extern mutex GraphicsCoreMutex;
	extern CRITICAL_SECTION GraphicsCoreCriticalSection; //объявление критической секции
	
	struct TPARAM
	{
		RENDERER * Renderer = NULL;
		bool graphicsCoreThreadActive = false;
		int isThreadLaunched = 0; //0 - Didn't launch, 1 - launched right now, 2 - died
	};

	class GRAPHICSCORE
	{
	private:
		DWORD		renderThreadId;
		HANDLE		renderThreadHandle;
		RENDERER *	Renderer;

		TPARAM		Agent;

	public:
		GRAPHICSCORE( HWND _hWnd, DWORD _style, int _sizeX = 50, int _sizeY = 50, RENDERER_TYPES _renderer = DirectX9);
		virtual ~GRAPHICSCORE();

		static vector<string> TempLog;
		static void AddLog(string _message);

		HRESULT Render_Start( HWND _hWnd, DWORD _style, int _sizeX, int _sizeY );
		HRESULT Render_Stop( HWND _hWnd, DWORD _style, int _sizeX, int _sizeY );
		RENDERER * GetRenderer();
	};
};

#endif