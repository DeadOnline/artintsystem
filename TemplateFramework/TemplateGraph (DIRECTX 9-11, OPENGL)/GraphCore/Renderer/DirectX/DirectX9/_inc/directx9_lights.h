#pragma once
#ifndef DirectX9LightsHeader
#define DirectX9LightsHeader

#include "../../_inc/DirectX_Lights.h"

#include "DirectX9_Globals.h"

namespace GRAPHCORE
{
	class DIRECTX9_LIGHTS : public DIRECTX_LIGHTS
	{
	public:
		const int iD;
		D3DLIGHT9 Light;
		DIRECTX9_LIGHTS(int _iD);
		~DIRECTX9_LIGHTS();
		HRESULT Change_radius(float _radius);
		HRESULT SwitchOff(LPDIRECT3DDEVICE9 _device);
		HRESULT SwitchOn(LPDIRECT3DDEVICE9 _device);
	};
};

#endif