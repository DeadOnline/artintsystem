#include "../_inc/DirectX9_Effects.h"

#pragma region DIRECTX9_EFFECTS
//-----------------------------------DIRECTX9_EFFECTS-----------------------------------//
using namespace GRAPHCORE;

DIRECTX9_EFFECTS::DIRECTX9_EFFECTS(LPDIRECT3DDEVICE9 _device)
{
	_device->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
	_device->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP2);
	_device->SetRenderState(D3DRS_FOGCOLOR, Fog.color);
	_device->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&Fog.start));
	_device->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&Fog.end));
	_device->SetRenderState(D3DRS_FOGDENSITY, Fog.density);
	_device->SetRenderState(D3DRS_RANGEFOGENABLE, 1);
};
DIRECTX9_EFFECTS::~DIRECTX9_EFFECTS() { };
HRESULT DIRECTX9_EFFECTS::Change_Fog_Color(DWORD _color, LPDIRECT3DDEVICE9 _device)
{
	Fog.color = _color;
	_device->SetRenderState(D3DRS_FOGCOLOR, Fog.color);
	return S_OK;
};
HRESULT DIRECTX9_EFFECTS::Change_Fog_Density(DWORD _density, LPDIRECT3DDEVICE9 _device)
{
	Fog.density = _density;
	_device->SetRenderState(D3DRS_FOGDENSITY, Fog.density);
	return S_OK;
};
HRESULT DIRECTX9_EFFECTS::Switch_On_Fog(LPDIRECT3DDEVICE9 _device)
{
	_device->SetRenderState(D3DRS_FOGENABLE, true);
	return S_OK;
};
HRESULT DIRECTX9_EFFECTS::Switch_Off_Fog(LPDIRECT3DDEVICE9 _device)
{
	_device->SetRenderState(D3DRS_FOGENABLE, false);
	return S_OK;
};

#pragma region DIRECTX9_EFFECTS:COLLISIONS
//------------------------------------DIRECTX9_EFFECTS:COLLISIONS------------------------------------//
DIRECTX9_EFFECTS::FOG::FOG() : start(4.0f), end(137.0f), density(0), color(D3DCOLOR_XRGB(30, 180, 60)) { };
//-----------------------------------~DIRECTX9_EFFECTS:COLLISIONS------------------------------------//
#pragma endregion

//-----------------------------------DIRECTX9_EFFECTS-----------------------------------//  
#pragma endregion