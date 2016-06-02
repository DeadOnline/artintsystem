#pragma once
#ifndef DirectX9EngineHeader
#define DirectX9EngineHeader

#include "../_inc/DirectX9.h"

#include "DirectX9_Globals.h"

namespace GRAPHCORE
{
	class DIRECTX9_ENGINE : public SINGLETONS
	{
	public:
		static	SINGLETONS *	Instance();
		virtual	void			deleteInstance();

		void Render( void * _globals );

	private:

		static DIRECTX9_ENGINE * Object;

		LPDIRECT3DDEVICE9 * Device;
		struct BASE { int Start, Duration; BASE(); };
		struct LIGHT_ON : public BASE
		{
			HRESULT(DIRECTX9_LIGHTS::*Function)(LPDIRECT3DDEVICE9);
			LIGHT_ON();
		} LightOnP;
		struct UPSCREEN_DOWN : public BASE
		{
			HRESULT(DIRECTX9::*Function)(int);
			UPSCREEN_DOWN();
		} UpScreenDownP;
		struct GAS_FOG_ON : public BASE
		{
			HRESULT(DIRECTX9_EFFECTS::*Function)(LPDIRECT3DDEVICE9);
			GAS_FOG_ON();
		} GasFogOnP;
		struct GAS_FOG_DENSITY_UP : public BASE
		{
			HRESULT(DIRECTX9_EFFECTS::*Function)(DWORD, LPDIRECT3DDEVICE9);
			GAS_FOG_DENSITY_UP();
		} GasFogDensityUpP;
		struct RENDER_TEXT : public BASE
		{
			HRESULT(DIRECTX9_TEXTSTRINGS::*Function)(RECT);
			RENDER_TEXT();
		} RenderTextP[7];
		struct PLAY_SOUND : public BASE
		{
			HRESULT(DIRECTX9_TEXTSTRINGS::*Function)(RECT);
			PLAY_SOUND();
		} PlaySoundP[6];

		struct RAY
		{
			D3DXVECTOR3 origin;
			D3DXVECTOR3 direction;
			RAY(D3DXVECTOR3 _origin, D3DXVECTOR3 _direction);
		} PickingRay;

		struct FPS
		{
			float FrameCnt;
			float TimeElapsed, fps, Time_Start, Time_End;
			FPS();
		} FPS;

		DIRECTX9_ENGINE();
		DIRECTX9_ENGINE(LPDIRECT3DDEVICE9* device);
		~DIRECTX9_ENGINE();

		//LPCSTR DoRayProcedure(int _x, int _y, LPDIRECT3DDEVICE9 _device, DIRECTX::DIRECTX_OBJECTS * _object);

		HRESULT CalculatePickingRay(int _x, int _y, LPDIRECT3DDEVICE9 _device);
		HRESULT TransformPickingRay(LPDIRECT3DDEVICE9 _device);

		//bool RaySphereIntersectionTest(DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGSPHERE * _sphere);
		//float * RayCubeIntersectionTest(DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGBOX * _box, float * _res);
	};
};

#endif