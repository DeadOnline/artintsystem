#include "../_inc/DirectX9_Grid.h"

using namespace GRAPHCORE;

#pragma region DIRECTX9_GRID
//------------------------------------DIRECTX9_GRID------------------------------------//
DIRECTX9_GRID * DIRECTX9_GRID::Instance()
	{
	if ( !Object ) Object = new DIRECTX9_GRID();
	return ( DIRECTX9_GRID * ) Object;
	}
void DIRECTX9_GRID::deleteInstance ()
	{
	GRID::deleteInstance();
	};
void DIRECTX9_GRID::Render( void * const _globals ) const
	{
	if (!_globals) return;

	DIRECTX9_GLOBALS * Globals = ( DIRECTX9_GLOBALS * ) _globals;

	LPDIRECT3DDEVICE9 device = Globals->GetD3DDevice();
	DIRECTX9_GEOMETRY * Geometry = ( DIRECTX9_GEOMETRY * ) Globals->GetGeometry( geometryID );
	DIRECTX9_ANIMATION_X * Animation = ( DIRECTX9_ANIMATION_X * ) Globals->GetAnimation( 0 );
	
	Animation->SetWorldMatrix(device, DEFAULT, TEMPLATEMATRIX(), 0);

	if (!Geometry) return;
	Geometry->Render( device );
	};
void DIRECTX9_GRID::Fill_Grid( GLOBALS * _globals, int _width, float _cellSize, DWORD _newColor )
	{
	if ( ( !( ( DIRECTX9_GLOBALS * ) _globals )->GetD3DDevice() ) || ( !_width ) || (!_cellSize) ) return;
	int shiftF = (_width * 2 + 1) * 2, shiftS = (_width * 2 + 1) * 2 + 1;
	long vertcolor3DQuantity = 0;

	VERTEXPOINT3DCOLOR * Grid = new VERTEXPOINT3DCOLOR[ shiftF*2 ];

	for ( int i = -_width; i <= _width; ++i )
		{
		Grid[ vertcolor3DQuantity * 2 ].X = i*_cellSize; Grid[ vertcolor3DQuantity * 2 ].Y = 0; Grid[ vertcolor3DQuantity * 2 ].Z = -_width * _cellSize;
		Grid[ vertcolor3DQuantity * 2 + 1 ].X = i*_cellSize; Grid[ vertcolor3DQuantity * 2 + 1 ].Y = 0; Grid[ vertcolor3DQuantity * 2 + 1 ].Z = _width * _cellSize;
		Grid[ vertcolor3DQuantity * 2 + shiftF ].X = _width * _cellSize; Grid[ vertcolor3DQuantity * 2 + shiftF ].Y = 0; Grid[ vertcolor3DQuantity * 2 + shiftF ].Z = i*_cellSize;
		Grid[ vertcolor3DQuantity * 2 + shiftS ].X = -_width * _cellSize; Grid[ vertcolor3DQuantity * 2 + shiftS ].Y = 0; Grid[ vertcolor3DQuantity * 2 + shiftS ].Z = i*_cellSize;
		Grid[ vertcolor3DQuantity * 2 ].COLOR = Grid[ vertcolor3DQuantity * 2 + 1 ].COLOR = Grid[ vertcolor3DQuantity * 2 + shiftF ].COLOR = Grid[ vertcolor3DQuantity * 2 + shiftS ].COLOR = _newColor;
		++vertcolor3DQuantity;
		}

	vertcolor3DQuantity *= 4;

	LPDIRECT3DVERTEXBUFFER9 vBuffer = NULL;
	( ( DIRECTX9_GLOBALS * ) _globals )->GetD3DDevice()->CreateVertexBuffer( sizeof( VERTEXPOINT3DCOLOR ) * vertcolor3DQuantity, 0, VertexesFVF3DColor, D3DPOOL_MANAGED, &vBuffer, NULL );
	void* pData = NULL;
	vBuffer->Lock(0, sizeof( pData ), ( void** ) &pData, 0);
	memcpy( pData, Grid, sizeof( VERTEXPOINT3DCOLOR ) * vertcolor3DQuantity );
	vBuffer->Unlock();

	if (geometryID != -1) _globals->DestroyGeometry( geometryID ); //TODO Set const ID
	geometryID = ( ( DIRECTX9_GLOBALS * ) _globals )->CreateGeometry( "_GRID", v3dcolor, Grid, vertcolor3DQuantity, NULL, 0, sizeof( VERTEXPOINT3DCOLOR ), BUFFER_CONTENT_TYPES::vertex, shiftF, vBuffer, NULL, D3DPT_LINELIST );
	};

DIRECTX9_GRID::DIRECTX9_GRID() { };
DIRECTX9_GRID::DIRECTX9_GRID(const DIRECTX9_GRID& root) { };
DIRECTX9_GRID::~DIRECTX9_GRID() { }
DIRECTX9_GRID & DIRECTX9_GRID::operator=( const DIRECTX9_GRID & )
	{
	return *this;
	}
//-----------------------------------~DIRECTX9_GRID------------------------------------//  
#pragma endregion