#pragma once
#ifndef Grw
#define Grw

#include <Windows.h>
#include <cstring>
#include <string>

#include "TowerDefenceMacroses.h"
#include "../../../TemplateFramework/TemplateApplication (WinAPI)/WinApiApplicationCore/_inc/TemplateApplication (WinAPI).h"
#include "../../../TemplateFramework/TemplateGraph (DIRECTX 9-11, OPENGL)/GraphCore/_inc/GraphCore.h"
#include "../../../TemplateFramework/TemplateGraph (DIRECTX 9-11, OPENGL)/GraphCore/_inc/WorldPosition.h"
#include "../../../TemplateFramework/TemplateGraph (DIRECTX 9-11, OPENGL)/GraphCore/_inc/TemplateMatrix.h"
#include "../../../TemplateFramework/TemplateGraph (DIRECTX 9-11, OPENGL)/GraphCore/Renderer/_inc/SceneController.h"
#include "../../../TemplateFramework/TemplateInput (DirectX 9-11)/InputCore/_inc/TemplateInputCore.h"
#include "../../../TemplateFramework/TemplateCommon/CommonCore/_inc/Logger.h"
#include <vld.h>
#include <mysql.h>

#define WINDOWED	(WS_OVERLAPPED | WS_CAPTION)
#define FULLSCREEN	(WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE)

namespace APP
	{
	class APPLICATION : public WINAPIAPPLICATIONCORE::APPLICATIONCORE, public GRAPHCORE::GRAPHICSCORE, public INPUTCORE::INOUTSHELL
		{
		public:
	
	APPLICATION(LPCSTR caption, DWORD style = FULLSCREEN, int sizeX = 500, int sizeY = 500, GRAPHCORE::RENDERER_TYPES _renderType = GRAPHCORE::DirectX9);
	virtual ~APPLICATION();

		//Virtual Overrides
		//GraphCore
		HRESULT Init();
		HRESULT Frame();
		HRESULT Shutdown();
		//InputCore
		HRESULT	SendInputData( );

		private:

			MYSQL * ObjectsDataBase;
		};
	}

#endif