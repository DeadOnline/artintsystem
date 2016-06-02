#pragma once
#ifndef DirectX9SceneControllerHeader
#define DirectX9SceneControllerHeader

#include "../../_inc/DirectX_SceneController.h"

#include "DirectX9_Globals.h"

namespace GRAPHCORE
	{
	class DIRECTX9_SCENECONTROLLER : public DIRECTX_SCENECONTROLLER
		{
		private:
			//class DIRECTX9_MWP : public DIRECTX_MWP
			//	{
			//	D3DXMATRIX * matrix;
			//public:
			//	void * Get_Matrix ();
			//	};
		public:
			DIRECTX9_SCENECONTROLLER();
			~DIRECTX9_SCENECONTROLLER();
		};
	};

#endif