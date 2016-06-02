#include "../_inc/DirectX9_Geometry.h"

#pragma region DIRECTX9_GEOMETRY
//------------------------------------DIRECTX9_GEOMETRY-----------------------------------//
using namespace GRAPHCORE;

#pragma region DIRECTX9_BUFFER
//----------------------------------DIRECTX9_BUFFER----------------------------------//
DIRECTX9_GEOMETRY::DIRECTX9_BUFFER::DIRECTX9_BUFFER( DIRECTX9_BUFFER_ATTRIBUTES ) : vBuffer( _vBuffer ), iBuffer( _iBuffer ), d3dPrimitiveType( _d3dPrimitiveType ) {};
DIRECTX9_GEOMETRY::DIRECTX9_BUFFER::~DIRECTX9_BUFFER()
	{
	OBJRELEASE ( vBuffer );
	OBJRELEASE ( iBuffer );
	};

LPDIRECT3DVERTEXBUFFER9&	DIRECTX9_GEOMETRY::DIRECTX9_BUFFER::GetVertexBuffer ()
	{
	return vBuffer;
	};
LPDIRECT3DINDEXBUFFER9&		DIRECTX9_GEOMETRY::DIRECTX9_BUFFER::GetIndexBuffer ()
	{
	return iBuffer;
	};
//---------------------------------~DIRECTX9_BUFFER----------------------------------//  
#pragma endregion
#pragma region DIRECTX9_VERTEXARRAYNATIVE
//----------------------------------DIRECTX9_VERTEXARRAYNATIVE----------------------------------//
DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAYNATIVE::DIRECTX9_VERTEXARRAYNATIVE( 
	VERTEX_ARRAY_NATIVE_ATTRIBUTES, 
	DIRECTX9_BUFFER_ATTRIBUTES ) : 
		VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT ), DIRECTX9_BUFFER( DIRECTX9_BUFFER_ATTRIBUTES_INIT )
		{};
DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAYNATIVE::~DIRECTX9_VERTEXARRAYNATIVE() {};

void DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAYNATIVE::Render( void * _renderer )
	{
	LPDIRECT3DDEVICE9 _device = *( LPDIRECT3DDEVICE9 *) &_renderer;

	_device->SetStreamSource( 0, vBuffer, 0, bytesNumberPerVertex );
	_device->SetIndices( iBuffer );

	if ( BufferType == index ) _device->DrawIndexedPrimitive ( d3dPrimitiveType, 0, 0, verticesQuantity, 0, indicesQuantity );
	else _device->DrawPrimitive ( d3dPrimitiveType, 0, elementsQuantity );
	};
//---------------------------------~DIRECTX9_VERTEXARRAYNATIVE----------------------------------//  
#pragma endregion
#pragma region DIRECTX9_VERTEXARRAY2DCOLOR_STORAGE
//----------------------------------DIRECTX9_VERTEXARRAY2DCOLOR_STORAGE----------------------------------//
DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY2DCOLOR_STORAGE::DIRECTX9_VERTEXARRAY2DCOLOR_STORAGE( 
	VERTEX_ARRAY_NATIVE_ATTRIBUTES, DIRECTX9_BUFFER_ATTRIBUTES ) :
		VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT ),
		DIRECTX9_VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT ),
		VERTEXARRAY2DCOLOR_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
		{};
void DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY2DCOLOR_STORAGE::Set_Vertices_Format( void * _renderer )
	{	
	( *( LPDIRECT3DDEVICE9 *) &_renderer)->SetFVF( VertexesFVF2DColor );
	};
//---------------------------------~DIRECTX9_VERTEXARRAY2DCOLOR_STORAGE----------------------------------//  
#pragma endregion
#pragma region DIRECTX9_VERTEXARRAY2DCOLORTEX_STORAGE
//----------------------------------DIRECTX9_VERTEXARRAY2DCOLORTEX_STORAGE----------------------------------//
DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY2DCOLORTEX_STORAGE::DIRECTX9_VERTEXARRAY2DCOLORTEX_STORAGE(
	VERTEX_ARRAY_NATIVE_ATTRIBUTES, 
	DIRECTX9_BUFFER_ATTRIBUTES) : 
		VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT ),
		DIRECTX9_VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT ),
		VERTEXARRAY2DCOLORTEX_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
		{};
void DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY2DCOLORTEX_STORAGE::Set_Vertices_Format( void * _renderer )
	{
	( *( LPDIRECT3DDEVICE9 *) &_renderer )->SetFVF( VertexexFVF2DColorTex );
	};
//---------------------------------~DIRECTX9_VERTEXARRAY2DCOLORTEX_STORAGE----------------------------------//  
#pragma endregion
#pragma region DIRECTX9_VERTEXARRAY2DTEX_STORAGE
//----------------------------------DIRECTX9_VERTEXARRAY2DTEX_STORAGE----------------------------------//
DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY2DTEX_STORAGE::DIRECTX9_VERTEXARRAY2DTEX_STORAGE(
	VERTEX_ARRAY_NATIVE_ATTRIBUTES,
	DIRECTX9_BUFFER_ATTRIBUTES) :
		VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT ),
		DIRECTX9_VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT ),
		VERTEXARRAY2DTEX_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
		{};
void DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY2DTEX_STORAGE::Set_Vertices_Format( void * _renderer )
	{
	( *( LPDIRECT3DDEVICE9 *) &_renderer )->SetFVF( VertexexFVF2DTex );
	};
//---------------------------------~DIRECTX9_VERTEXARRAY2DTEX_STORAGE----------------------------------//  
#pragma endregion

#pragma region DIRECTX9_VERTEXARRAY3DCOLOR_STORAGE
//----------------------------------DIRECTX9_VERTEXARRAY3DCOLOR_STORAGE----------------------------------//
DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DCOLOR_STORAGE::DIRECTX9_VERTEXARRAY3DCOLOR_STORAGE(
	VERTEX_ARRAY_NATIVE_ATTRIBUTES,
	DIRECTX9_BUFFER_ATTRIBUTES) :
		VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT ),
		DIRECTX9_VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT ),
		VERTEXARRAY3DCOLOR_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
		{};
void DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DCOLOR_STORAGE::Set_Vertices_Format( void * _renderer )
	{
	( *( LPDIRECT3DDEVICE9 *) &_renderer )->SetFVF( VertexesFVF3DColor );
	};
//---------------------------------~DIRECTX9_VERTEXARRAY3DCOLOR_STORAGE----------------------------------//  
#pragma endregion
#pragma region DIRECTX9_VERTEXARRAY3DCOLORNORMAL_STORAGE
//----------------------------------DIRECTX9_VERTEXARRAY3DCOLORNORMAL_STORAGE----------------------------------//
DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DCOLORNORMAL_STORAGE::DIRECTX9_VERTEXARRAY3DCOLORNORMAL_STORAGE(
	VERTEX_ARRAY_NATIVE_ATTRIBUTES,
	DIRECTX9_BUFFER_ATTRIBUTES) :
		VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT ),
		DIRECTX9_VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT ),
		VERTEXARRAY3DCOLORNORMAL_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
		{};
void DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DCOLORNORMAL_STORAGE::Set_Vertices_Format( void * _renderer )
	{
	( *( LPDIRECT3DDEVICE9 *) &_renderer )->SetFVF( VertexesFVF3DColorNormal );
	};
//---------------------------------~DIRECTX9_VERTEXARRAY3DCOLORNORMAL_STORAGE----------------------------------//  
#pragma endregion
#pragma region DIRECTX9_VERTEXARRAY3DCOLORNORMALTEX_STORAGE
//----------------------------------DIRECTX9_VERTEXARRAY3DCOLORNORMALTEX_STORAGE----------------------------------//
DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DCOLORNORMALTEX_STORAGE::DIRECTX9_VERTEXARRAY3DCOLORNORMALTEX_STORAGE(
	VERTEX_ARRAY_NATIVE_ATTRIBUTES,
	DIRECTX9_BUFFER_ATTRIBUTES) :
		VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT ),
		DIRECTX9_VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT ),
		VERTEXARRAY3DCOLORNORMALTEX_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
		{};
void DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DCOLORNORMALTEX_STORAGE::Set_Vertices_Format( void * _renderer )
	{
	( *( LPDIRECT3DDEVICE9 *) &_renderer )->SetFVF( VertexexFVF3DColorNormalTex );
	};
//---------------------------------~DIRECTX9_VERTEXARRAY3DCOLORNORMALTEX_STORAGE----------------------------------//  
#pragma endregion
#pragma region DIRECTX9_VERTEXARRAY3DCOLORTEX_STORAGE
//----------------------------------DIRECTX9_VERTEXARRAY3DCOLORTEX_STORAGE----------------------------------//
DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DCOLORTEX_STORAGE::DIRECTX9_VERTEXARRAY3DCOLORTEX_STORAGE(
	VERTEX_ARRAY_NATIVE_ATTRIBUTES,
	DIRECTX9_BUFFER_ATTRIBUTES) :
		VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT ),
		DIRECTX9_VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT ),
		VERTEXARRAY3DCOLORTEX_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
		{};
void DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DCOLORTEX_STORAGE::Set_Vertices_Format( void * _renderer )
	{
	( *( LPDIRECT3DDEVICE9 *) &_renderer )->SetFVF( VertexexFVF3DColorTex );
	};
//---------------------------------~DIRECTX9_VERTEXARRAY3DCOLORTEX_STORAGE----------------------------------//  
#pragma endregion

#pragma region DIRECTX9_VERTEXARRAY3DNORMAL_STORAGE
//----------------------------------DIRECTX9_VERTEXARRAY3DNORMAL_STORAGE----------------------------------//
DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DNORMAL_STORAGE::DIRECTX9_VERTEXARRAY3DNORMAL_STORAGE(
	VERTEX_ARRAY_NATIVE_ATTRIBUTES,
	DIRECTX9_BUFFER_ATTRIBUTES) :
		VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT ),
		DIRECTX9_VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT ),
		VERTEXARRAY3DNORMAL_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
		{};
void DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DNORMAL_STORAGE::Set_Vertices_Format( void * _renderer )
	{
	( *( LPDIRECT3DDEVICE9 *) &_renderer )->SetFVF( VertexexFVF3DNormal );
	};
//---------------------------------~DIRECTX9_VERTEXARRAY3DNORMAL_STORAGE----------------------------------//  
#pragma endregion
#pragma region DIRECTX9_VERTEXARRAY3DNORMALTEX_STORAGE
//----------------------------------DIRECTX9_VERTEXARRAY3DNORMALTEX_STORAGE----------------------------------//
DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DNORMALTEX_STORAGE::DIRECTX9_VERTEXARRAY3DNORMALTEX_STORAGE(
	VERTEX_ARRAY_NATIVE_ATTRIBUTES,
	DIRECTX9_BUFFER_ATTRIBUTES) :
		VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT ),
		DIRECTX9_VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT ),
		VERTEXARRAY3DNORMALTEX_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
		{};
void DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DNORMALTEX_STORAGE::Set_Vertices_Format( void * _renderer )
	{
	( *( LPDIRECT3DDEVICE9 *) &_renderer )->SetFVF( VertexexFVF3DNormalTex );
	};
//---------------------------------~DIRECTX9_VERTEXARRAY3DNORMALTEX_STORAGE----------------------------------//  
#pragma endregion
#pragma region DIRECTX9_VERTEXARRAY3DTEX_STORAGE
//----------------------------------DIRECTX9_VERTEXARRAY3DTEX_STORAGE----------------------------------//
DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DTEX_STORAGE::DIRECTX9_VERTEXARRAY3DTEX_STORAGE(
	VERTEX_ARRAY_NATIVE_ATTRIBUTES,
	DIRECTX9_BUFFER_ATTRIBUTES) :
		VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT ),
		DIRECTX9_VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT ),
		VERTEXARRAY3DTEX_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
		{};
void DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DTEX_STORAGE::Set_Vertices_Format( void * _renderer )
	{
	( *( LPDIRECT3DDEVICE9 *) &_renderer )->SetFVF( VertexexFVF3DTex );
	};
//---------------------------------~DIRECTX9_VERTEXARRAY3DTEX_STORAGE----------------------------------//  
#pragma endregion

#pragma region DIRECTX9_VERTEXARRAY_X
//----------------------------------DIRECTX9_VERTEXARRAY_X----------------------------------//
DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY_X::DIRECTX9_VERTEXARRAY_X ( LPD3DXMESH _mesh, int _materialsQuantity, D3DMATERIAL9 *	_meshMaterials, vector<int> _textureIDSArray ) :
	VERTEXARRAYBASE ( vertex ), mesh ( _mesh ), materialsQuantity ( _materialsQuantity ), textureIDSArray ( _textureIDSArray )
	{};
void *	DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY_X::GetVerticesArray ()
	{
	return mesh;
	};
int		DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY_X::GetVerticesQuantity ()
	{
	return mesh->GetNumVertices ();
	};
unsigned int *	DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY_X::GetIndicesArray()
	{
	LPDIRECT3DINDEXBUFFER9	_iBuffer = NULL;
	mesh->GetIndexBuffer ( &_iBuffer );
	return 0;//TODO: _iBuffer->;
	};
unsigned int	DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY_X::GetIndicesQuantity()
	{
	return mesh->GetNumFaces (); //TODO: This can be elements count, not indices
	};
int		DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY_X::GetMaterialsQuantity ()
	{
	return materialsQuantity;
	};
int		DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY_X::GetTextureID ( int _num )
	{
	return textureIDSArray[ _num ];
	};

void	DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY_X::Set_Vertices_Format( void * _renderer )
	{
	DWORD werf = mesh->GetFVF();
	( *( LPDIRECT3DDEVICE9 *) &_renderer )->SetFVF( werf );
	};
VERTEX_TYPES	DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY_X::Get_Vertices_Format()
	{
	return VERTEX_TYPES::v3dcolornormaltex;
	};
int		DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY_X::GetElementsType()
	{
	return D3DPT_TRIANGLELIST;
	};
unsigned int	DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY_X::GetElementsQuantity()
	{
	return mesh->GetNumVertices () / 3;
	};

void DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY_X::Render( void * _renderer )
	{
	if ( !mesh ) return;

	LPDIRECT3DDEVICE9		_device = NULL;
	LPDIRECT3DVERTEXBUFFER9 _vBuffer = NULL;
	LPDIRECT3DINDEXBUFFER9	_iBuffer = NULL;

	mesh->GetDevice ( &_device );
	mesh->GetVertexBuffer ( &_vBuffer );
	mesh->GetIndexBuffer ( &_iBuffer );

	_device->SetStreamSource( 0, _vBuffer, 0, mesh->GetNumBytesPerVertex() );
	_device->SetIndices( _iBuffer );
	
	for ( size_t i = 0; i < GetMaterialsQuantity(); i++ )
		{
		mesh->DrawSubset( i );
		}
	};
//---------------------------------~DIRECTX9_VERTEXARRAY_X----------------------------------//
#pragma endregion

DIRECTX9_GEOMETRY::DIRECTX9_GEOMETRY( 
	_charP _name,
	VERTEX_TYPES _type,
	VERTEX_ARRAY_NATIVE_ATTRIBUTES,
	DIRECTX9_BUFFER_ATTRIBUTES) :
		DIRECTX_GEOMETRY( _name )
		{
		switch ( _type )
			{
			case v2dcolor:
				VerticesBatch = new DIRECTX9_VERTEXARRAY2DCOLOR_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT );
				break;
			case v2dcolortex:
				VerticesBatch = new DIRECTX9_VERTEXARRAY2DCOLORTEX_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT );
				break;
			case v2dtex:
				VerticesBatch = new DIRECTX9_VERTEXARRAY2DTEX_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT );
				break;
			case v3dcolor:
				VerticesBatch = new DIRECTX9_VERTEXARRAY3DCOLOR_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT );
				break;
			case v3dcolornormal:
				VerticesBatch = new DIRECTX9_VERTEXARRAY3DCOLORNORMAL_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT );
				break;
			case v3dcolornormaltex:
				VerticesBatch = new DIRECTX9_VERTEXARRAY3DCOLORNORMALTEX_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT );
				break;
			case v3dcolortex:
				VerticesBatch = new DIRECTX9_VERTEXARRAY3DCOLORTEX_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT );
				break;
			case v3dnormal:
				VerticesBatch = new DIRECTX9_VERTEXARRAY3DNORMAL_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT );
				break;
			case v3dnormaltex:
				VerticesBatch = new DIRECTX9_VERTEXARRAY3DNORMALTEX_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT );
				break;
			case v3dtex:
				VerticesBatch = new DIRECTX9_VERTEXARRAY3DTEX_STORAGE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT, DIRECTX9_BUFFER_ATTRIBUTES_INIT );
				break;
			default:
				break;
			};
		};

/**
 * Constructor. Performs specific initialization process for loading resources depending on data format.
 *
 * @param [in]	_globals 			%Globals% is the main object keeper.
 * @param		_absoluteMeshPath	Full (absolute) pathname of the mesh file.
 * @param		_resFolder		 	Pathname of the resource folder (containin' materials).
 * @param		_type			 	File format.
 */

DIRECTX9_GEOMETRY::DIRECTX9_GEOMETRY ( DIRECTX9_GLOBALS * _globals, _charP _absoluteMeshPath, _charP _resFolder, DIRECTX_SUPPORTED_FILE_FORMATS _type ) : DIRECTX_GEOMETRY ( _absoluteMeshPath )
	{
	LPDIRECT3DDEVICE9 device = _globals->GetD3DDevice ();
	LPD3DXMESH Mesh = NULL;
	LPD3DXBUFFER buffer = NULL;
	vector<int> Textures;
	DWORD materialsQuantity = 0;
	D3DXMATERIAL * d3dxMaterials = NULL;
	D3DMATERIAL9 * meshMaterials = NULL;

	switch ( _type )
		{
		case GRAPHCORE::_x:

			//This is loader for import class X, which possesses 1 object, but may contain a couple of meshes at once. Not recommended for usage.

			if ( !SUCCEEDED ( D3DXLoadMeshFromX ( _absoluteMeshPath, D3DXMESH_SYSTEMMEM, device, NULL, &buffer, NULL, &materialsQuantity, &Mesh ) ) )
				{
				OBJDELETE ( Mesh );
				}
			else
				{
				d3dxMaterials = ( D3DXMATERIAL* ) buffer->GetBufferPointer ();
				if ( materialsQuantity )
					{
					meshMaterials = new D3DMATERIAL9[ materialsQuantity ];
					if ( meshMaterials )
						{
						ZeroMemory ( meshMaterials, sizeof ( D3DMATERIAL9 )* materialsQuantity );
						char * TextureFilename = NULL; int fullPathLength = 0;

						for ( DWORD i = 0; i < materialsQuantity; i++ )
							{
							d3dxMaterials[ i ].pTextureFilename = ( !d3dxMaterials[ i ].pTextureFilename )
								? ( DEFAULT_PATH_MATERIAL )
								: (
									fullPathLength = strlen ( _resFolder ) + strlen ( d3dxMaterials[ i ].pTextureFilename ) + 1,
									TextureFilename = new char[ fullPathLength ],
									sprintf_s ( TextureFilename, fullPathLength, "%s%s", _resFolder, d3dxMaterials[ i ].pTextureFilename ),
									TextureFilename
									);
							meshMaterials[ i ] = d3dxMaterials[ i ].MatD3D;
							Textures.push_back( _globals->LoadTexture( d3dxMaterials[ i ].pTextureFilename, RECT() ) );
							};

						OBJRELEASE ( buffer );
						}
					}
				VerticesBatch = new DIRECTX9_VERTEXARRAY_X ( Mesh, materialsQuantity, meshMaterials, Textures );
				}
			break;
		case GRAPHCORE::_obj:
			break;
		case GRAPHCORE::_g:
			break;
		default:
			break;
		};
	};

DIRECTX9_GEOMETRY::DIRECTX9_GEOMETRY ( LPDIRECT3DDEVICE9 _device, _charP _name, GEOMETRY_TYPES _geometryType ) : DIRECTX_GEOMETRY ( _name )
	{
	switch ( _geometryType )
		{
		case Cube:
			Initiate_Cube3DColor_DX9 ( _device, GENERATED_GEOMETRY_SIZE );
			break;
		case Ball:
			Initiate_Sphere_DX9 ( _device, GENERATED_GEOMETRY_SIZE, GENERATED_GEOMETRY_SIZE );
			break;
		case Plane:
			Initiate_Plane ( _device, GENERATED_GEOMETRY_SIZE, GENERATED_GEOMETRY_SIZE );
			break;
		default:
			break;
		};
	};
DIRECTX9_GEOMETRY::~DIRECTX9_GEOMETRY ()
	{
	OBJDELETE ( VerticesBatch );
	};
HRESULT DIRECTX9_GEOMETRY::Initiate_Cube3DColor_DX9( LPDIRECT3DDEVICE9 _device, int _side ) //TODO: unsigned int
	{
#pragma region Working
	//int vertexQuantity = 8, indicesQuantity = 36;
	//VERTEXPOINT3DCOLOR * VertexArray = new VERTEXPOINT3DCOLOR[ vertexQuantity ];
	//short * cubeIndices = new short[ indicesQuantity ];

	//DWORD color = D3DCOLOR_RGBA ( 21, 96, 189, 120 );

	//VertexArray[ 0 ].X = -_side;	VertexArray[ 0 ].Y = -_side;	VertexArray[ 0 ].Z = -_side; VertexArray[ 0 ].COLOR = color;
	//VertexArray[ 1 ].X = -_side;	VertexArray[ 1 ].Y = _side;	VertexArray[ 1 ].Z = -_side; VertexArray[ 1 ].COLOR = color;
	//VertexArray[ 2 ].X = _side;	VertexArray[ 2 ].Y = _side;	VertexArray[ 2 ].Z = -_side; VertexArray[ 2 ].COLOR = color;
	//VertexArray[ 3 ].X = _side;	VertexArray[ 3 ].Y = -_side;	VertexArray[ 3 ].Z = -_side; VertexArray[ 3 ].COLOR = color;
	//VertexArray[ 4 ].X = -_side;	VertexArray[ 4 ].Y = -_side;	VertexArray[ 4 ].Z = _side; VertexArray[ 4 ].COLOR = color;
	//VertexArray[ 5 ].X = -_side;	VertexArray[ 5 ].Y = _side;	VertexArray[ 5 ].Z = _side; VertexArray[ 5 ].COLOR = color;
	//VertexArray[ 6 ].X = _side;	VertexArray[ 6 ].Y = _side;	VertexArray[ 6 ].Z = _side; VertexArray[ 6 ].COLOR = color;
	//VertexArray[ 7 ].X = _side;	VertexArray[ 7 ].Y = -_side;	VertexArray[ 7 ].Z = _side; VertexArray[ 7 ].COLOR = color;

	//short indices [] = {
	//	0, 1, 2, 0, 2, 3, //RIGHT
	//	4, 5, 1, 4, 1, 0, //BOTTOM
	//	3, 2, 6, 3, 6, 7, //TOP
	//	1, 5, 6, 1, 6, 2, //FAR
	//	4, 0, 3, 4, 3, 7, //CLOSE
	//	4, 6, 5, 4, 7, 6, //LEFT ??????????????????????????
	//	};

	//for ( short i = 0; i < indicesQuantity; i++ )
	//	{
	//	cubeIndices[ i ] = indices[ i ];
	//	}

	//LPDIRECT3DVERTEXBUFFER9 vBuffer = NULL;
	//LPDIRECT3DINDEXBUFFER9	iBuffer = NULL;

	//_device->CreateVertexBuffer ( sizeof ( VERTEXPOINT3DCOLOR ) * vertexQuantity, 0, VertexesFVF3DColor, D3DPOOL_MANAGED, &vBuffer, NULL );
	//_device->CreateIndexBuffer ( sizeof ( short ) * indicesQuantity, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &iBuffer, NULL );

	//VOID * pData1 = NULL, *pData2 = NULL;
	//vBuffer->Lock ( 0, sizeof ( pData1 ), ( void** ) &pData1, 0 );
	//memcpy ( pData1, VertexArray, sizeof ( VERTEXPOINT3DCOLOR ) * vertexQuantity );
	//vBuffer->Unlock ();

	//iBuffer->Lock ( 0, sizeof ( pData2 ), ( void** ) &pData2, 0 );		//lock buffer
	//memcpy ( pData2, cubeIndices, sizeof ( short ) * indicesQuantity );	//copy data
	//iBuffer->Unlock ();													//unlock buffer

	//VerticesBatch = new DIRECTX9_VERTEXARRAY3DCOLOR_STORAGE (
	//	VertexArray, vertexQuantity,
	//	cubeIndices, indicesQuantity,
	//	16, index, indicesQuantity / 3,
	//	vBuffer, iBuffer, D3DPT_TRIANGLELIST );
#pragma endregion

	int vertexQuantity = 8, indicesQuantity = 36;
	VERTEXPOINT3DCOLOR * VertexArray = new VERTEXPOINT3DCOLOR[ vertexQuantity ];
	UINT * cubeIndices = new UINT[ indicesQuantity ];

	DWORD color = D3DCOLOR_RGBA ( 21, 96, 189, 120 );

	VertexArray[ 0 ].X = -_side;	VertexArray[ 0 ].Y = -_side;	VertexArray[ 0 ].Z = -_side; VertexArray[ 0 ].COLOR = color;
	VertexArray[ 1 ].X = -_side;	VertexArray[ 1 ].Y = _side;	VertexArray[ 1 ].Z = -_side; VertexArray[ 1 ].COLOR = color;
	VertexArray[ 2 ].X = _side;	VertexArray[ 2 ].Y = _side;	VertexArray[ 2 ].Z = -_side; VertexArray[ 2 ].COLOR = color;
	VertexArray[ 3 ].X = _side;	VertexArray[ 3 ].Y = -_side;	VertexArray[ 3 ].Z = -_side; VertexArray[ 3 ].COLOR = color;
	VertexArray[ 4 ].X = -_side;	VertexArray[ 4 ].Y = -_side;	VertexArray[ 4 ].Z = _side; VertexArray[ 4 ].COLOR = color;
	VertexArray[ 5 ].X = -_side;	VertexArray[ 5 ].Y = _side;	VertexArray[ 5 ].Z = _side; VertexArray[ 5 ].COLOR = color;
	VertexArray[ 6 ].X = _side;	VertexArray[ 6 ].Y = _side;	VertexArray[ 6 ].Z = _side; VertexArray[ 6 ].COLOR = color;
	VertexArray[ 7 ].X = _side;	VertexArray[ 7 ].Y = -_side;	VertexArray[ 7 ].Z = _side; VertexArray[ 7 ].COLOR = color;

	UINT indices [] = {
		0, 1, 2, 0, 2, 3, //RIGHT
		4, 5, 1, 4, 1, 0, //BOTTOM
		3, 2, 6, 3, 6, 7, //TOP
		1, 5, 6, 1, 6, 2, //FAR
		4, 0, 3, 4, 3, 7, //CLOSE
		4, 6, 5, 4, 7, 6, //LEFT ??????????????????????????
		};

	for ( UINT i = 0; i < indicesQuantity; i++ )
		{
		cubeIndices[ i ] = indices[ i ];
		}

	LPDIRECT3DVERTEXBUFFER9 vBuffer = NULL;
	LPDIRECT3DINDEXBUFFER9	iBuffer = NULL;

	_device->CreateVertexBuffer ( sizeof ( VERTEXPOINT3DCOLOR ) * vertexQuantity, 0, VertexesFVF3DColor, D3DPOOL_MANAGED, &vBuffer, NULL );
	_device->CreateIndexBuffer ( sizeof ( UINT ) * indicesQuantity, D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &iBuffer, NULL );

	VOID * pData1 = NULL, *pData2 = NULL;
	vBuffer->Lock ( 0, sizeof ( pData1 ), ( void** ) &pData1, 0 );
	memcpy ( pData1, VertexArray, sizeof ( VERTEXPOINT3DCOLOR ) * vertexQuantity );
	vBuffer->Unlock ();

	iBuffer->Lock ( 0, sizeof ( pData2 ), ( void** ) &pData2, 0 );		//lock buffer
	memcpy ( pData2, cubeIndices, sizeof ( UINT ) * indicesQuantity );	//copy data
	iBuffer->Unlock ();													//unlock buffer

	VerticesBatch = new DIRECTX9_VERTEXARRAY3DCOLOR_STORAGE (
		VertexArray, vertexQuantity,
		cubeIndices, indicesQuantity,
		16, index, indicesQuantity / 3,
		vBuffer, iBuffer, D3DPT_TRIANGLELIST );

	return S_OK;
	};
HRESULT DIRECTX9_GEOMETRY::Initiate_Sphere_DX9 ( LPDIRECT3DDEVICE9 _device, float _radius, int _dimension )
	{
	////Create sphere having normals and tex coords
	LPD3DXMESH SphereObj;

	D3DXCreateSphere ( _device, _radius, _dimension, _dimension, &SphereObj, NULL );

	VerticesBatch = new DIRECTX9_VERTEXARRAY_X ( SphereObj, 1, NULL, vector<int> ( 1 ) );

	return S_OK;
	};
HRESULT DIRECTX9_GEOMETRY::Initiate_Plane ( LPDIRECT3DDEVICE9 _device, float _sizeX, float _sizeY )
	{
	int verticesQ = 4, indicesQuantity = 6;
	VERTEXPOINT3DCOLOR * VertexArray = new VERTEXPOINT3DCOLOR[ verticesQ ];
	UINT * planeIndices = new UINT[ indicesQuantity ];

	DWORD color = D3DCOLOR_RGBA( 21, 96, 189, 120 );

	VertexArray[ 0 ].X = -_sizeX; VertexArray[ 0 ].Y = 0.0f; VertexArray[ 0 ].Z = -_sizeY; VertexArray[ 0 ].COLOR = color;
	VertexArray[ 1 ].X = -_sizeX; VertexArray[ 1 ].Y = 0.0f; VertexArray[ 1 ].Z = _sizeY; VertexArray[ 1 ].COLOR = color;
	VertexArray[ 2 ].X = _sizeX; VertexArray[ 2 ].Y = 0.0f; VertexArray[ 2 ].Z = -_sizeY; VertexArray[ 2 ].COLOR = color;
	VertexArray[ 3 ].X = _sizeX; VertexArray[ 3 ].Y = 0.0f; VertexArray[ 3 ].Z = _sizeY; VertexArray[ 3 ].COLOR = color;

	planeIndices[ 0 ] = 0; planeIndices[ 1 ] = 1; planeIndices[ 2 ] = 2;
	planeIndices[ 3 ] = 1; planeIndices[ 4 ] = 3; planeIndices[ 5 ] = 2;

	LPDIRECT3DVERTEXBUFFER9 vBuffer = NULL;
	LPDIRECT3DINDEXBUFFER9	iBuffer = NULL;

	_device->CreateVertexBuffer( sizeof( VERTEXPOINT3DCOLOR ) * verticesQ, 0, VertexesFVF3DColor, D3DPOOL_MANAGED, &vBuffer, NULL );
	_device->CreateIndexBuffer( sizeof( UINT ) * indicesQuantity, D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &iBuffer, NULL );

	VOID* pData = NULL;
	vBuffer->Lock( 0, sizeof( pData ), ( void** ) &pData, 0 );
	memcpy( pData, VertexArray, sizeof( VERTEXPOINT3DCOLOR ) * verticesQ );
	vBuffer->Unlock();

	iBuffer->Lock( 0, sizeof( pData ), ( void** ) &pData, 0 );	//lock buffer
	memcpy( pData, planeIndices, sizeof( UINT ) * indicesQuantity );	//copy data
	iBuffer->Unlock();									//unlock buffer

	VerticesBatch = new DIRECTX9_VERTEXARRAY3DCOLOR_STORAGE( 
		VertexArray, verticesQ, 
		planeIndices, indicesQuantity, 
		16, index, indicesQuantity / 3, 
		vBuffer, iBuffer, D3DPT_TRIANGLELIST );

	return S_OK;
	};
HRESULT DIRECTX9_GEOMETRY::Initiate_Plane_UpScreen ( LPDIRECT3DDEVICE9 _device, float _sizeX, float _sizeY )
	{
	int verticesQ = 4, indicesQuantity = 6;

	VERTEXPOINT2DCOLOR * VertexArray = new VERTEXPOINT2DCOLOR[ verticesQ ];
	UINT * upScreenIndices = new UINT[ indicesQuantity ];

	DWORD color = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	VertexArray[ 0 ].X = 0; VertexArray[ 0 ].Y = 0; VertexArray[ 0 ].Z = 0.5f; VertexArray[ 0 ].RHW = 1; VertexArray[ 0 ].COLOR = color;
	VertexArray[ 1 ].X = _sizeX; VertexArray[ 1 ].Y = 0; VertexArray[ 1 ].Z = 0.5f; VertexArray[ 1 ].RHW = 1; VertexArray[ 1 ].COLOR = color;
	VertexArray[ 2 ].X = 0; VertexArray[ 2 ].Y = _sizeX; VertexArray[ 2 ].Z = 0.5f; VertexArray[ 2 ].RHW = 1; VertexArray[ 2 ].COLOR = color;
	VertexArray[ 3 ].X = _sizeX; VertexArray[ 3 ].Y = _sizeX; VertexArray[ 3 ].Z = 0.5f; VertexArray[ 3 ].RHW = 1; VertexArray[ 3 ].COLOR = color;

	upScreenIndices[ 0 ] = 0; upScreenIndices[ 1 ] = 1; upScreenIndices[ 2 ] = 2;
	upScreenIndices[ 3 ] = 1; upScreenIndices[ 4 ] = 2; upScreenIndices[ 5 ] = 3;

	LPDIRECT3DVERTEXBUFFER9 vBuffer = NULL;
	LPDIRECT3DINDEXBUFFER9	iBuffer = NULL;

	_device->CreateVertexBuffer( sizeof( VertexArray ) * verticesQ, 0, VertexesFVF3DColor, D3DPOOL_MANAGED, &vBuffer, NULL );
	_device->CreateIndexBuffer( sizeof( upScreenIndices ) * indicesQuantity, D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &iBuffer, NULL );

	VOID* pData = NULL;
	vBuffer->Lock( 0, sizeof( pData ), ( void** ) &pData, 0 );
	memcpy( pData, VertexArray, sizeof( VERTEXPOINT2DCOLOR ) * verticesQ );
	vBuffer->Unlock();

	iBuffer->Lock( 0, sizeof( pData ), ( void** ) &pData, 0 );		//lock buffer
	memcpy( pData, upScreenIndices, sizeof( UINT ) * indicesQuantity );	//copy data
	iBuffer->Unlock();										//unlock buffer

	VerticesBatch = new DIRECTX9_VERTEXARRAY2DCOLOR_STORAGE ( VertexArray, 4, upScreenIndices, 6, 20, index, 2, vBuffer, iBuffer, D3DPT_TRIANGLELIST );

	return S_OK;
	};
//-----------------------------------~DIRECTX9_GEOMETRY-----------------------------------//  
#pragma endregion