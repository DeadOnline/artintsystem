#include "../_inc/DirectX9_Lights.h"

using namespace GRAPHCORE;

#pragma region DIRECTX9_LIGHTS
//-----------------------------------DIRECTX9_LIGHTS-----------------------------------//
DIRECTX9_LIGHTS::DIRECTX9_LIGHTS(int _iD) : iD(_iD) { ZeroMemory(&Light, sizeof(Light)); };
DIRECTX9_LIGHTS::~DIRECTX9_LIGHTS() { };
HRESULT DIRECTX9_LIGHTS::Change_radius(float _radius) { Light.Range = _radius; return S_OK; };
HRESULT DIRECTX9_LIGHTS::SwitchOff(LPDIRECT3DDEVICE9 _device) { _device->LightEnable(iD, false); return S_OK; };
HRESULT DIRECTX9_LIGHTS::SwitchOn(LPDIRECT3DDEVICE9 _device) { _device->LightEnable(iD, true); return S_OK; };
//-----------------------------------DIRECTX9_LIGHTS-----------------------------------//  
#pragma endregion