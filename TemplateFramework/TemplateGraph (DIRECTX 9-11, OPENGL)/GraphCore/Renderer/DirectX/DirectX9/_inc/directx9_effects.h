#pragma once
#ifndef DirectX9EffectsHeader
#define DirectX9EffectsHeader

#include "../../_inc/DirectX_Effects.h"

#include "DirectX9_Globals.h"

namespace GRAPHCORE
{
	class DIRECTX9_EFFECTS : public DIRECTX_EFFECTS
	{
	public:
		struct FOG
		{
			enum TYPES { EXP, EXP2, LINEAR } Type;
			float start;
			float end;
			DWORD density;
			DWORD color;
			FOG();
		} Fog;
		DIRECTX9_EFFECTS(LPDIRECT3DDEVICE9 _device);
		~DIRECTX9_EFFECTS();
		HRESULT Change_Fog_Color(DWORD _color, LPDIRECT3DDEVICE9 _device);
		HRESULT Change_Fog_Density(DWORD _density, LPDIRECT3DDEVICE9 _device);
		HRESULT Switch_On_Fog(LPDIRECT3DDEVICE9 _device);
		HRESULT Switch_Off_Fog(LPDIRECT3DDEVICE9 _device);
	};
};

#endif