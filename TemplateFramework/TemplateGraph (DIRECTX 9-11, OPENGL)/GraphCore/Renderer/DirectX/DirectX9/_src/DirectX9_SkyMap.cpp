#include "../_inc/DirectX9_SkyMap.h"

using namespace GRAPHCORE;

#pragma region DIRECTX9_SKYMAP
//-----------------------------------DIRECTX9_SKYMAP-----------------------------------//
int DIRECTX9_SKYMAP::geometryID = MAPNONEXISTANTID;

DIRECTX9_SKYMAP * DIRECTX9_SKYMAP::Instance()
	{
	/*if ( !Object ) Object = new DIRECTX9_SKYMAP();
	return ( DIRECTX9_SKYMAP * ) Object;*/
	return NULL;
	}
void DIRECTX9_SKYMAP::deleteInstance ()
	{};
void DIRECTX9_SKYMAP::Set_SkyMap( LPDIRECT3DDEVICE9 _device )
	{
	if ( !_device ) return;
	//VERTEX_BASE * UpScreenBase = Geometry->Get_Verteces("UPSCREEN");

	//if ( !UpScreenBase )
	//	{
	//	VERTEXDEFINITECOLOR UpScreen[ 4 ];

	//	UpScreen[ 0 ].X = 0; UpScreen[ 0 ].Y = 0; UpScreen[ 0 ].Z = 0.5; UpScreen[ 0 ].RHW = 1; UpScreen[ 0 ].COLOR = _newColor;
	//	UpScreen[ 1 ].X = _D3DM.Width; UpScreen[ 1 ].Y = 0; UpScreen[ 1 ].Z = 0.5; UpScreen[ 1 ].RHW = 1; UpScreen[ 1 ].COLOR = _newColor;
	//	UpScreen[ 2 ].X = 0; UpScreen[ 2 ].Y = _D3DM.Height; UpScreen[ 2 ].Z = 0.5; UpScreen[ 2 ].RHW = 1; UpScreen[ 2 ].COLOR = _newColor;
	//	UpScreen[ 3 ].X = _D3DM.Width; UpScreen[ 3 ].Y = _D3DM.Height; UpScreen[ 3 ].Z = 0.5; UpScreen[ 3 ].RHW = 1; UpScreen[ 3 ].COLOR = _newColor;

	//	Geometry->Add_Verteces("UPSCREEN", UpScreen);
	//	}
	//else
	//	{
	//	VERTEXDEFINITECOLOR * UpScreen = ( VERTEXDEFINITECOLOR * ) UpScreenBase;

	//	UpScreen[ 0 ].COLOR = UpScreen[ 1 ].COLOR = UpScreen[ 2 ].COLOR = UpScreen[ 3 ].COLOR = _newColor;

	//	Geometry->Set_Verteces("UPSCREEN", UpScreen);
	//	}

	//VERTEXDEFINITECOLOR * UpScreen = ( VERTEXDEFINITECOLOR * ) Geometry->Get_Verteces("UPSCREEN");
	//if ( !UPSCREENBUFFER )
	//	_device->CreateVertexBuffer(sizeof( VERTEXDEFINITECOLOR ) * 4, 0, VertexesFVF2D, D3DPOOL_MANAGED, &UPSCREENBUFFER, NULL);
	//VOID* pData = NULL;
	//UPSCREENBUFFER->Lock(0, sizeof( pData ), ( void** ) &pData, 0);
	//memcpy(pData, UpScreen, sizeof( VERTEXDEFINITECOLOR ) * 4);
	//UPSCREENBUFFER->Unlock();
	}
void DIRECTX9_SKYMAP::Render( void * _globals ) const
	{
	
	};

DIRECTX9_SKYMAP::DIRECTX9_SKYMAP() {};
DIRECTX9_SKYMAP::DIRECTX9_SKYMAP( const DIRECTX9_SKYMAP& root ) {};
DIRECTX9_SKYMAP::~DIRECTX9_SKYMAP()	{}
DIRECTX9_SKYMAP & DIRECTX9_SKYMAP::operator=( const DIRECTX9_SKYMAP & )
	{
	return *this;
	}
//-----------------------------------DIRECTX9_UPSCREEN-----------------------------------//  
#pragma endregion