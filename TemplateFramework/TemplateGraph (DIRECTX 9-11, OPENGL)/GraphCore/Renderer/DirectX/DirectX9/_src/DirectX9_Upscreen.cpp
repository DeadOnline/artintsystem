#include "../_inc/DirectX9_Upscreen.h"

using namespace GRAPHCORE;

#pragma region DIRECTX9_UPSCREEN
//-----------------------------------DIRECTX9_UPSCREEN-----------------------------------//

void DIRECTX9_UPSCREEN::deleteInstance ()
	{
	UPSCREEN::deleteInstance ();
	}

DIRECTX9_UPSCREEN * DIRECTX9_UPSCREEN::Instance()
	{
	if ( !Object ) Object = new DIRECTX9_UPSCREEN();
	return ( DIRECTX9_UPSCREEN * ) Object;
	};
void DIRECTX9_UPSCREEN::Fill_UpScreen(GLOBALS * _globals, const int _clientWidth, const int _clientHeight, const int _textureID)
	{
	//Temporary
	//float X = ((DIRECTX9_GLOBALS *)_globals)->GetD3DDisplayMode().Width, Y = ((DIRECTX9_GLOBALS *)_globals)->GetD3DDisplayMode().Height;
	float X = _clientWidth, Y = _clientHeight;

	if (!_globals) return;

	int verticesQ = 4;
	VERTEXPOINT2DTEX * VertexArray = new VERTEXPOINT2DTEX[ verticesQ ];

	VertexArray[0].X = 0.0f; VertexArray[0].Y = 0.0f; VertexArray[0].Z = 0.45f; VertexArray[0].RHW = 1.0f; VertexArray[0].fU = 0.0f; VertexArray[0].fV = 0.0f;
	VertexArray[1].X = X; VertexArray[1].Y = 0.0f; VertexArray[1].Z = 0.45f; VertexArray[1].RHW = 1.0f; VertexArray[ 1 ].fU = 1.0f; VertexArray[ 1 ].fV = 0.0f;
	VertexArray[2].X = 0.0f; VertexArray[2].Y = Y; VertexArray[2].Z = 0.45f; VertexArray[2].RHW = 1.0f; VertexArray[ 2 ].fU = 0.0f; VertexArray[ 2 ].fV = 1.0f;
	VertexArray[3].X = X; VertexArray[3].Y = Y; VertexArray[3].Z = 0.45f; VertexArray[3].RHW = 1.0f; VertexArray[ 3 ].fU = 1.0f; VertexArray[ 3 ].fV = 1.0f;

	LPDIRECT3DVERTEXBUFFER9 vBuffer = NULL;

	( ( DIRECTX9_GLOBALS * ) _globals )->GetD3DDevice()->CreateVertexBuffer( sizeof( VERTEXPOINT2DTEX ) * verticesQ, 0, VertexesFVF3DColor, D3DPOOL_MANAGED, &vBuffer, NULL );

	VOID* pData = NULL;
	vBuffer->Lock( 0, sizeof( pData ), ( void** ) &pData, 0 );
	memcpy( pData, VertexArray, sizeof( VERTEXPOINT2DTEX ) * verticesQ );
	vBuffer->Unlock();
	
	if (geometryID != -1) _globals->DestroyGeometry( geometryID ); //TODO Set const ID
	geometryID = ( ( DIRECTX9_GLOBALS * ) _globals )->CreateGeometry( "_UPSCREEN", v2dtex, VertexArray, verticesQ, NULL, 0, sizeof( VERTEXPOINT2DTEX ), BUFFER_CONTENT_TYPES::vertex, 2, vBuffer, NULL, D3DPT_TRIANGLESTRIP );
	}
void DIRECTX9_UPSCREEN::Change_UpScreenAlpha( int alpha )
	{
	/*for (int i = 0; i < 4; i++) upScreen[i].COLOR = D3DCOLOR_RGBA(0, 0, 0, alpha);
	((DIRECTX9_GLOBALS *)Global)->GetD3DUpScreenBuffer()->Release();
	((DIRECTX9_GLOBALS *)Global)->GetD3DDevice()->CreateVertexBuffer(sizeof(upScreen), 0, VertexesFVF2DColor, D3DPOOL_MANAGED, &((DIRECTX9_GLOBALS *)Global)->GetD3DUpScreenBuffer(), NULL);
	VOID* pData = NULL;
	((DIRECTX9_GLOBALS *)Global)->GetD3DUpScreenBuffer()->Lock(0, sizeof(pData), (void**)&pData, 0);
	memcpy(pData, upScreen, sizeof(upScreen));
	((DIRECTX9_GLOBALS *)Global)->GetD3DUpScreenBuffer()->Unlock();*/
	return;
	};

void DIRECTX9_UPSCREEN::Render( void * const _globals ) const
	{
	if (!_globals) return;

	DIRECTX9_MATERIALS * Material = NULL, *tempMaterial = NULL;

	DIRECTX9_GLOBALS * Globals = ( DIRECTX9_GLOBALS * ) _globals;

	LPDIRECT3DDEVICE9 device = Globals->GetD3DDevice();
	DIRECTX9_GEOMETRY * Geometry = ( DIRECTX9_GEOMETRY * ) Globals->GetGeometry( geometryID );
	DIRECTX9_TEXTURES * Texture = ( DIRECTX9_TEXTURES * ) Globals->GetTexture( textureID );

	if (Texture)
		Texture->SetTexture( device ); //TODO: generate procedurial texture

	if (!Geometry) return;
	Geometry->Render( device );
	};

DIRECTX9_UPSCREEN::DIRECTX9_UPSCREEN() { };
DIRECTX9_UPSCREEN::DIRECTX9_UPSCREEN(const DIRECTX9_UPSCREEN& root) { };
DIRECTX9_UPSCREEN::~DIRECTX9_UPSCREEN()
	{
	//Geometry->Remove_Verteces("UPSCREEN");
	}
DIRECTX9_UPSCREEN & GRAPHCORE::DIRECTX9_UPSCREEN::operator=( const DIRECTX9_UPSCREEN & )
	{
	return *this;
	}
//-----------------------------------DIRECTX9_UPSCREEN-----------------------------------//  
#pragma endregion