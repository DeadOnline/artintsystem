#include "../_inc/DirectX9_Globals.h"

#pragma region DIRECTX9_GLOBALS
//---------------------------------------------------------------DIRECTX9_GLOBALS---------------------------------------------------------------//
using namespace GRAPHCORE;

#define CREATE_ARRAY(arr, arrclass, arrsize) arr = new arrclass[arrsize];



DIRECTX9_GLOBALS::DIRECTX9_GLOBALS() : d3d( NULL ), d3dDevice( NULL ), d3dSurface( NULL )
	{
	ZeroMemory( &d3dPresentParameters, sizeof( D3DPRESENT_PARAMETERS ) );
	ZeroMemory( &d3dDisplayMode, sizeof( D3DDISPLAYMODE ) );

	classCode[ VertexesFVF2DColor ] = CLASSCODE ( sizeof ( VERTEXPOINT2DCOLOR ), sizeof ( DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY2DCOLOR_STORAGE ), v2dcolor );
	classCode[ VertexexFVF2DColorTex ] = CLASSCODE ( sizeof ( VERTEXPOINT2DCOLORTEX ), sizeof ( DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY2DCOLORTEX_STORAGE ), v2dcolortex );
	classCode[ VertexexFVF2DTex ] = CLASSCODE ( sizeof ( VERTEXPOINT2DTEX ), sizeof ( DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY2DTEX_STORAGE ), v2dtex );
	classCode[ VertexesFVF3DColor ] = CLASSCODE ( sizeof ( VERTEXPOINT3DCOLOR ), sizeof ( DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DCOLOR_STORAGE ), v3dcolor );
	classCode[ VertexesFVF3DColorNormal ] = CLASSCODE ( sizeof ( VERTEXPOINT3DCOLORNORMAL ), sizeof ( DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DCOLORNORMAL_STORAGE ), v3dcolornormal );
	classCode[ VertexexFVF3DColorNormalTex ] = CLASSCODE ( sizeof ( VERTEXPOINT3DCOLORNORMALTEX ), sizeof ( DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DCOLORNORMALTEX_STORAGE ), v3dcolornormaltex );
	classCode[ VertexexFVF3DColorTex ] = CLASSCODE ( sizeof ( VERTEXPOINT3DCOLORTEX ), sizeof ( DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DCOLORTEX_STORAGE ), v3dcolortex );
	classCode[ VertexexFVF3DNormal ] = CLASSCODE ( sizeof ( VERTEXPOINT3DNORMAL ), sizeof ( DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DNORMAL_STORAGE ), v3dnormal );
	classCode[ VertexexFVF3DNormalTex ] = CLASSCODE ( sizeof ( VERTEXPOINT3DNORMALTEX ), sizeof ( DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DNORMALTEX_STORAGE ), v3dnormaltex );
	classCode[ VertexexFVF3DTex ] = CLASSCODE ( sizeof ( VERTEXPOINT3DTEX ), sizeof ( DIRECTX9_GEOMETRY::DIRECTX9_VERTEXARRAY3DTEX_STORAGE ), v3dtex );
	};
DIRECTX9_GLOBALS::~DIRECTX9_GLOBALS ()
	{
	OBJRELEASE( d3d );
	OBJRELEASE( d3dDevice );
	OBJRELEASE( d3dSurface );
	};

LPDIRECT3D9&				DIRECTX9_GLOBALS::GetD3D() { return d3d; };
LPDIRECT3DDEVICE9&			DIRECTX9_GLOBALS::GetD3DDevice() { return d3dDevice; };
D3DPRESENT_PARAMETERS&		DIRECTX9_GLOBALS::GetD3DPresentParameters() { return d3dPresentParameters; };
D3DDISPLAYMODE&				DIRECTX9_GLOBALS::GetD3DDisplayMode() { return d3dDisplayMode; };
LPDIRECT3DSURFACE9&			DIRECTX9_GLOBALS::GetD3DSurface() { return d3dSurface; };

void						DIRECTX9_GLOBALS::SetD3D( LPDIRECT3D9 _d3d ) { d3d = _d3d; };
void						DIRECTX9_GLOBALS::SetD3DDevice()
	{}
void						DIRECTX9_GLOBALS::SetD3DPresentParameters ()
	{}
void						DIRECTX9_GLOBALS::SetD3DDisplayMode ()
	{}
void						DIRECTX9_GLOBALS::SetD3DSurface() {}

//-----------------------------------------------------CREATE-----------------------------------------------------//

int							DIRECTX9_GLOBALS::CreateGeometry ( _charP _name, GEOMETRY_TYPES _geometryType )
	{
	MAP_GEOMETRY[ geometryQuantity++ ] = new DIRECTX9_GEOMETRY( d3dDevice, _name, _geometryType );
	return geometryQuantity-1;
	};
int							DIRECTX9_GLOBALS::CreateGeometry( _charP _name,
															  VERTEX_TYPES _type,
															  VERTEXPOINTBASE * _verticesArray,
															  int _vertecesQuantity,
															  unsigned int * _indicesArray,
															  unsigned int _indecesQuantity,
															  int _bytesNumberPerVertex,
															  BUFFER_CONTENT_TYPES _bufferType,
															  unsigned int _elementsQuantity,
															  LPDIRECT3DVERTEXBUFFER9 _vBuffer,
															  LPDIRECT3DINDEXBUFFER9 _iBuffer,
															  D3DPRIMITIVETYPE _d3dPrimitiveType )
	{
	MAP_GEOMETRY[ geometryQuantity++ ] = new DIRECTX9_GEOMETRY (
		_name,
		_type,
		_verticesArray,
		_vertecesQuantity,
		_indicesArray,
		_indecesQuantity,
		_bytesNumberPerVertex,
		_bufferType,
		_elementsQuantity,
		_vBuffer,
		_iBuffer,
		_d3dPrimitiveType);
	return geometryQuantity - 1;
	};
int							DIRECTX9_GLOBALS::CreateTextString( const _charP _string, const _charP _appliedFont, const _charP _appliedColor, const RECT _position )
	{
	MAP_TEXTSTRINGS[ textstringsQuantity++ ] = new DIRECTX9_TEXTSTRINGS ( _string, _appliedFont, _appliedColor, _position );
	return textstringsQuantity - 1;
	};
int							DIRECTX9_GLOBALS::CreateLight( _charP _name )
	{
	MAP_LIGHTS[ lightsQuantity++ ] = new DIRECTX9_LIGHTS( 0 );
	return lightsQuantity - 1;
	};
int							DIRECTX9_GLOBALS::CreateMaterial( const MATERIAL_TYPES _materialType, const DEFAULT_COLORS _color )
	{
	//TODO Create material

	D3DMATERIAL9 * tempMaterial = NULL;
	float value1 = 0;

	switch ( _materialType )
		{
		case GRAPHCORE::Ambient:
			tempMaterial = new D3DMATERIAL9();
			ZeroMemory( tempMaterial, sizeof( D3DMATERIAL9 ) );
			switch ( _color )
				{
				case GRAPHCORE::White:
					value1 = 1.0f;
					break;
				case GRAPHCORE::Black:
					value1 = 0.0f;
					break;
				default:
					break;
				}
			tempMaterial->Diffuse.r = tempMaterial->Ambient.r = value1; // êðàñíûé
			tempMaterial->Diffuse.g = tempMaterial->Ambient.g = value1; // çåëåíûé
			tempMaterial->Diffuse.b = tempMaterial->Ambient.b = value1; // ñèíèé
			tempMaterial->Diffuse.a = tempMaterial->Ambient.a = 1.0f;	// àëüôà
			tempMaterial->Power = 1.0f;
			MAP_MATERIALS[ materialsQuantity ] = new DIRECTX9_MATERIALS( tempMaterial );
			break;
		case GRAPHCORE::AmbientDiffuse:
			break;
		case GRAPHCORE::AmbientDiffuseSpecular:
			break;
		case GRAPHCORE::AmbientDiffuseSpecularEmittive:
			break;
		default:
			break;
		}
	return materialsQuantity++;
	}
int							DIRECTX9_GLOBALS::CreateTexture( const TEXTURE_TYPES _texture_type, const DEFAULT_COLORS _color, const RECT _area )
	{
	MAP_TEXTURES[ texturesQuantity ] = new DIRECTX9_TEXTURES( d3dDevice, _texture_type, _color, _area );
	return texturesQuantity++;
	};
int							DIRECTX9_GLOBALS::CreateCameraFree ( WORLDPOSITION& _position, WORLDPOSITION& _look, WORLDPOSITION& _up, WORLDPOSITION * _positionBinded,
																 float _angle_Of_View, float _resolution_Of_Screen, float _starting_Point, float _ending_Point )
	{
	MAP_CAMERAS[ camerasQuantity++ ] = new DIRECTX9_CAMERAS_FREE ( d3dDevice, _position, _look, _up, _positionBinded,
																   _angle_Of_View, _resolution_Of_Screen, _starting_Point, _ending_Point );
	return camerasQuantity - 1;
	};
int							DIRECTX9_GLOBALS::CreateCameraTarget ( WORLDPOSITION& _position, WORLDPOSITION& _target, WORLDPOSITION& _up,
																   WORLDPOSITION * _positionBinded, WORLDPOSITION * _targetBinded, WORLDPOSITION * _upBinded,
																   float _angle_Of_View, float _resolution_Of_Screen, float _starting_Point, float _ending_Point )
	{
	MAP_CAMERAS[ camerasQuantity++ ] = new DIRECTX9_CAMERAS_TARGET ( d3dDevice, _position, _target, _up, _positionBinded, _targetBinded, _upBinded,
																	 _angle_Of_View, _resolution_Of_Screen, _starting_Point, _ending_Point );
	return camerasQuantity - 1;
	};
int							DIRECTX9_GLOBALS::CreateGrid()
	{
	MAP_SINGLETONS[ ID_GRID ] = DIRECTX9_GRID::Instance();
	( ( DIRECTX9_GRID * ) MAP_SINGLETONS[ ID_GRID ] )->Fill_Grid( this );
	return ID_GRID;
	};
int							DIRECTX9_GLOBALS::CreateUpScreen(const int _clientWidth, const int _clientHeight)
	{
	MAP_SINGLETONS[ ID_UPSCREEN ] = DIRECTX9_UPSCREEN::Instance();
	( ( DIRECTX9_UPSCREEN * ) MAP_SINGLETONS[ ID_UPSCREEN ] )->Fill_UpScreen( this, _clientWidth, _clientHeight, -1 );
	return ID_UPSCREEN;
	};
int							DIRECTX9_GLOBALS::CreateCursor()
	{
	MAP_SINGLETONS[ ID_CURSOR ] = DIRECTX9_CURSOR::Instance();
	return ID_CURSOR;
	};
int							DIRECTX9_GLOBALS::CreateSkyMap()
	{
	MAP_SINGLETONS[ ID_SKYBOX ] = DIRECTX9_SKYMAP::Instance();
	return ID_SKYBOX;
	};
int							DIRECTX9_GLOBALS::CreateObject( _charP _name )
	{
	MAP_OBJECTS[ objectsQuantity++ ] = new DIRECTX9_OBJECTS( _name );
	return objectsQuantity - 1;
	};
int							DIRECTX9_GLOBALS::CreateAnimation( const _charP _name, const void * _animationSequence )
	{
	MAP_ANIMATIONS[ animationsQuantity ] = new DIRECTX9_ANIMATION_X( d3dDevice, _name, COLLISION_TYPES::None );
	return animationsQuantity++;
	};

//----------------------------------------------------~CREATE-----------------------------------------------------//

//------------------------------------------------------LOAD------------------------------------------------------//

int							DIRECTX9_GLOBALS::LoadTexture( const _charP& _relativePath, const RECT& _area ) //Full path is required
	{
	map<int, TEXTURES *>::iterator MAP_TEXTURES_ITER = MAP_TEXTURES.begin();
	for ( ; MAP_TEXTURES_ITER != MAP_TEXTURES.end(); MAP_TEXTURES_ITER++ )
		{
		_charP temp = MAP_TEXTURES_ITER->second->GetName();
		if ( temp && !strcmp( temp, _relativePath ) )
			return MAP_TEXTURES_ITER->first;
		}
	DIRECTX9_TEXTURES * tempTex = new DIRECTX9_TEXTURES( d3dDevice, _relativePath, _area );
	
	if ( tempTex->GetTexture() )
		{
		MAP_TEXTURES[ texturesQuantity++ ] = tempTex;
		return texturesQuantity-1;
		}
	else
		{
		OBJDELETE( tempTex );
		return -1;
		}
	};
vector<int>					DIRECTX9_GLOBALS::LoadGeometry( const _charP& _relativeMeshPath, const _charP& _relativeResFolder, SUPPORTED_FILE_FORMATS _format )
	{
	switch ( _format )
		{
		case _x:
			return LoadGeometryX( _relativeMeshPath, _relativeResFolder );
			//case _obj:
			//	return 0;
			//case _g:
			//	return 0;
		default:
			return vector<int> ();
		};
	};
vector<int>					DIRECTX9_GLOBALS::LoadGeometryX( const _charP& _relativeMeshPath, const _charP& _relativeResFolder )
	{
	LPDIRECT3DDEVICE9 device = GetD3DDevice ();

	int f = 4 | 2;
	int g = f && 1;

	vector<int> outIDs;

	LPD3DXMESH Mesh = NULL;
	LPD3DXBUFFER buffer = NULL;

	D3DXMATERIAL * d3dxMaterials = NULL;
	D3DMATERIAL9 * meshMaterials = NULL;

	DWORD materialsQuantity = 0, size = 0;
	int fullPathLength = 0;
	string textureFileName;

#pragma region NEW_PARSER
	if ( SUCCEEDED ( D3DXLoadMeshFromX ( _relativeMeshPath, D3DXMESH_SYSTEMMEM, device, NULL, &buffer, NULL, &materialsQuantity, &Mesh ) ) )
		{
#pragma region INITIATION
		LPDIRECT3DVERTEXBUFFER9 meshVertexBuffer = NULL, *vBufferImpl = NULL;
		LPDIRECT3DINDEXBUFFER9 meshIndexBuffer = NULL, *iBufferImpl = NULL;
		void * meshVertexBufferData = NULL, *vBufferImplData = NULL, *meshIndexBufferData = NULL, *iBufferImplData = NULL;

		VERTEXPOINTBASE * VertexArray = NULL;
		UINT * IndexArray = NULL;
#pragma endregion
#pragma region OPTIMIZATION
		Mesh->OptimizeInplace ( D3DXMESHOPT_ATTRSORT, NULL, NULL, NULL, NULL );
#pragma endregion

		//////////////////////////////////////////////
		//Get main buffers and attribute table

		Mesh->GetVertexBuffer ( &meshVertexBuffer );
		Mesh->GetIndexBuffer ( &meshIndexBuffer );

		Mesh->GetAttributeTable ( NULL, &size );
		if ( !size ) size++; //TODO: take away this shit
		vector<D3DXATTRIBUTERANGE> table ( size );
		Mesh->GetAttributeTable ( &table[ 0 ], &size );

		//////////////////////////////////////////////
		//Lock main buffers
		DWORD VertexLocalQuantity = 0, memoryset = 0, FVF = 0;
		UINT IndexLocalQuantity = 0;

		meshVertexBuffer->Lock ( 0, 0, ( void** ) &meshVertexBufferData, 0 );
		meshIndexBuffer->Lock ( 0, 0, ( void** ) &meshIndexBufferData, 0 );

		d3dxMaterials = ( D3DXMATERIAL* ) buffer->GetBufferPointer ();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Go through submeshes and create geometry object for each one

		for ( UINT i = 0; i < size; ++i )
			{
			//UNIQUE INITIATION//
			FVF = Mesh->GetFVF ();
			DWORD indexSize = 2; //For 16 bit
			D3DFORMAT Format = ( (Mesh->GetOptions () | D3DXMESH_32BIT) == Mesh->GetOptions () ) ? indexSize = 4, D3DFMT_INDEX32 : D3DFMT_INDEX16;
			VertexLocalQuantity = table[ i ].VertexCount;
			IndexLocalQuantity = table[ i ].FaceCount * 3; //Fix this shit, indices quantity maybe different from this value
			memoryset = VertexLocalQuantity * classCode[ FVF ].sizeBuffer;

#pragma region BUFFERS_DATA_SETUP
			VertexArray = ( VERTEXPOINTBASE * ) operator new ( memoryset );
			CREATE_ARRAY ( IndexArray, UINT, IndexLocalQuantity / (4 / indexSize) + 1 ); //Full or half (plus one for odd numbers)
			
			LPDIRECT3DVERTEXBUFFER9 vBufferImpl = NULL;
			LPDIRECT3DINDEXBUFFER9 iBufferImpl = NULL;
			device->CreateVertexBuffer ( memoryset, 0, FVF, D3DPOOL_MANAGED, &vBufferImpl, NULL );
			device->CreateIndexBuffer ( indexSize * IndexLocalQuantity,
										D3DUSAGE_WRITEONLY,
										Format,
										D3DPOOL_MANAGED,
										&iBufferImpl,
										NULL );
				
#pragma endregion
#pragma region VERTEX_BUFFER_DATA_COPYING
			vBufferImpl->Lock ( 0, sizeof ( vBufferImplData ), ( void** ) &vBufferImplData, 0 );
			memcpy ( vBufferImplData,
					 (( char* ) meshVertexBufferData ) + table[ i ].VertexStart * classCode[ FVF ].sizeBuffer,
					 memoryset );
			memcpy ( VertexArray,
					 vBufferImplData,
					 memoryset );
			vBufferImpl->Unlock ();
#pragma endregion
#pragma region INDEX_BUFFER_DATA_COPYING
			iBufferImpl->Lock ( 0, sizeof ( iBufferImplData ), ( void** ) &iBufferImplData, 0 );	//lock buffer
			memcpy ( iBufferImplData,
					 (( byte * ) meshIndexBufferData ) + table[ i ].FaceStart * 3 * indexSize, //Fix this shit, indices quantity maybe different from this value
					 indexSize * IndexLocalQuantity );
			UINT iValue = 0, dValue = 0;

			if (i > 0)
				for ( UINT j = 0; j < IndexLocalQuantity; j++ )
					{
					memcpy (&iValue, ((byte *) iBufferImplData) + j * indexSize, indexSize );
					iValue -= table[ i ].VertexStart;
					memcpy ( ((byte *) iBufferImplData) + j * indexSize, &iValue, indexSize );
					}
			memcpy ( IndexArray,
					 iBufferImplData,
					 indexSize * IndexLocalQuantity );
			iBufferImpl->Unlock ();									//unlock buffer  
#pragma endregion
#pragma region MATERIALS_TEXTURES
			d3dxMaterials[ i ].pTextureFilename = ( !d3dxMaterials[ i ].pTextureFilename )
				? ( DEFAULT_PATH_TEXTURE )
				: (
					fullPathLength = strlen ( _relativeResFolder ) + strlen ( d3dxMaterials[ i ].pTextureFilename ) + 1,
					textureFileName.append ( _relativeResFolder ),
					textureFileName.append ( d3dxMaterials[ i ].pTextureFilename ),
					textureFileName.c_str ()
					);
#pragma endregion

			MAP_GEOMETRY[ geometryQuantity ] = new DIRECTX9_GEOMETRY (
				_relativeMeshPath,
				classCode[ FVF ].type,
				VertexArray,
				VertexLocalQuantity,
				IndexArray,
				IndexLocalQuantity,
				classCode[ FVF ].sizeBuffer,
				BUFFER_CONTENT_TYPES::index,
				table[ i ].FaceCount,
				vBufferImpl,
				iBufferImpl,
				D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST );
			CopyMaterial ( new D3DMATERIAL9 ( d3dxMaterials[ i ].MatD3D ) );
			LoadTexture ( d3dxMaterials[ i ].pTextureFilename, RECT () );
			textureFileName.clear ();
			outIDs.push_back ( geometryQuantity++ );
			}
		OBJRELEASE ( buffer );
		meshVertexBuffer->Unlock ();
		meshIndexBuffer->Unlock ();
		meshVertexBuffer->Release ();
		meshIndexBuffer->Release ();
		};
#pragma endregion

//	//MAP_GEOMETRY[ geometryQuantity ] = new DIRECTX9_GEOMETRY( this, _relativeMeshPath, _relativeResFolder, _x );
//	outIDs.push_back( geometryQuantity++ );
	return outIDs;
	};

//-----------------------------------------------------~LOAD------------------------------------------------------//

//------------------------------------------------------COPY------------------------------------------------------//

int							DIRECTX9_GLOBALS::CopyMaterial( const void * _material ) //TODO GET RID OF THIS HOOK!
	{
	MAP_MATERIALS[ materialsQuantity ] = new DIRECTX9_MATERIALS( ( D3DMATERIAL9 * ) _material );
	return materialsQuantity++;
	};

//-----------------------------------------------------~COPY------------------------------------------------------//

//--------------------------------------------------------------~DIRECTX9_GLOBALS---------------------------------------------------------------//
#pragma endregion