#include "../_inc/DirectX9.h"
#include "../_inc/DirectX9_Frustum.h"

#pragma region DIRECTX9
//-----------------------------------DIRECTX9_MESHESX-----------------------------------//
using namespace GRAPHCORE;

#define DEFAULT_BACKBUFFER_HEIGHT 640
#define DEFAULT_BACKBUFFER_WIDTH 800

DIRECTX9::DIRECTX9() : DIRECTX()
	{
	Frustum = new DIRECTX9_FRUSTUM();
	Global = new DIRECTX9_GLOBALS();
	SceneController = new DIRECTX9_SCENECONTROLLER();
	};
DIRECTX9::~DIRECTX9()
	{
	Destroy_Meshes();
	Destroy_Objects();
	Destroy_Texts();
	Destroy_Cameras();
	};

HRESULT DIRECTX9::Initiate_D3D( HWND _hWnd )
	{
	if ( !( ( ( DIRECTX9_GLOBALS * ) Global )->GetD3D() = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		{
		MessageBox( _hWnd, "Cannot create DirectX 9 Device", "Error creating device", 0 ); exit( 1 );
		};
	return S_OK;
	};
HRESULT DIRECTX9::Initiate_GraphDevice( HWND _hWnd, int _sizeX, int _sizeY )
	{
	for ( int i = 0; i < MAX_PIXEL_FORMATS; i++ )
		{
		( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDisplayMode().Format = PIXELFORMATS[ i ];
		if ( SUCCEEDED( ( ( DIRECTX9_GLOBALS * ) Global )->GetD3D()->CheckDeviceType( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, ( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDisplayMode().Format, ( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDisplayMode().Format, false ) ) ) break;
		};

	if ( ( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDisplayMode().Format == D3DFMT_UNKNOWN )
		{
		MessageBox( _hWnd, "Cannot get display mode format", "Error getting display mode", 0 ); PostQuitMessage( 0 );
		};

	( ( DIRECTX9_GLOBALS * ) Global )->GetD3D()->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDisplayMode() ); D3DCAPS9 caps; ( ( DIRECTX9_GLOBALS * ) Global )->GetD3D()->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps );

	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DPresentParameters().AutoDepthStencilFormat = D3DFMT_D16;
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DPresentParameters().BackBufferCount = 1;
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DPresentParameters().BackBufferFormat = ( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDisplayMode().Format;
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DPresentParameters().BackBufferHeight = _sizeY;
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DPresentParameters().BackBufferWidth = _sizeX;
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DPresentParameters().EnableAutoDepthStencil = TRUE;
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DPresentParameters().Flags = 0;
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DPresentParameters().hDeviceWindow = _hWnd;
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DPresentParameters().MultiSampleQuality = 0;
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DPresentParameters().MultiSampleType = D3DMULTISAMPLE_NONE;
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DPresentParameters().PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DPresentParameters().SwapEffect = D3DSWAPEFFECT_DISCARD;
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DPresentParameters().FullScreen_RefreshRateInHz = 0;
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DPresentParameters().Windowed = true;

	if ( FAILED( ( ( DIRECTX9_GLOBALS * ) Global )->GetD3D()->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &( ( DIRECTX9_GLOBALS * ) Global )->GetD3DPresentParameters(), &( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice() ) ) )
		{
		MessageBox( _hWnd, "Device ((DIRECTX9_GLOBALS *)Global)->GetD3D()->CreateDevice... couldn't be created", "Graphical device error in DirectX 9.0c", 0 ); exit( 1 );
		};

	return S_OK;
	};
int		DIRECTX9::Initiate_Camera_Free( WORLDPOSITION& _position, WORLDPOSITION& _look, WORLDPOSITION& _up, WORLDPOSITION * _positionBinded,
									float _angle_Of_View, float _resolution_Of_Screen, float _starting_Point, float _ending_Point )
	{
	int cameraID = ( ( DIRECTX9_GLOBALS * ) Global )->CreateCameraFree( _position, _look, _up, _positionBinded, _angle_Of_View, _resolution_Of_Screen, _starting_Point, _ending_Point );

	SetProjectionMatrix( ( ( DIRECTX9_GLOBALS * ) Global )->GetCamera( cameraID ) );

	return cameraID;
	};
int		DIRECTX9::Initiate_Camera_Target( WORLDPOSITION& _position, WORLDPOSITION& _target, WORLDPOSITION& _up,
									  WORLDPOSITION * _positionBinded, WORLDPOSITION * _targetBinded, WORLDPOSITION * _upBinded,
									  float _angle_Of_View, float _resolution_Of_Screen, float _starting_Point, float _ending_Point )
	{
	return ( ( DIRECTX9_GLOBALS * ) Global )->CreateCameraTarget( _position, _target, _up, _positionBinded, _targetBinded, _upBinded, _angle_Of_View, _resolution_Of_Screen, _starting_Point, _ending_Point );
	};

int		DIRECTX9::Initiate_Geometry( _charP _name, VERTEX_TYPES _formatType, GEOMETRY_TYPES _geometryType )
	{
	return 0;
	};
HRESULT DIRECTX9::Initiate_Light( _charP _name, LIGHT_TYPES _type )
	{
	//if (Search_Light(_name) == NULL) Light[_name] = new LIGHTS(Light.size());

	//ZeroMemory(&Light[_name]->Light, sizeof(Light[_name]->Light));

	//D3DCOLORVALUE f; f.a = 0.5f; f.b = 0.6f; f.g = 0.5f; f.r = 1.0f;

	//Light[_name]->Light.Position		= D3DXVECTOR3 (0,0,0);
	//Light[_name]->Light.Direction		= D3DXVECTOR3 (0,1,0);
	//Light[_name]->Light.Type			= D3DLIGHT_POINT; //D3DLIGHT_DIRECTIONAL;
	//Light[_name]->Light.Ambient		= f;
	//Light[_name]->Light.Diffuse		= f; //color;
	//Light[_name]->Light.Specular		= f;
	//Light[_name]->Light.Range			= 140.0f;
	//Light[_name]->Light.Theta			= 0.5f;
	//Light[_name]->Light.Phi			= 1.0f;
	//Light[_name]->Light.Falloff		= 1.0f;
	//Light[_name]->Light.Attenuation0	= 1.0f;

	return E_FAIL;
	};
vector<int>		DIRECTX9::Load_Geometry( const _charP& _relativeMeshPath, const _charP& _relativeResFolder, const SUPPORTED_FILE_FORMATS _format, const COLLISION_TYPES _collisionType )
	{
	//TODO: Add Collision
	return Global->LoadGeometry( _relativeMeshPath, _relativeResFolder, _format );
	};
HRESULT DIRECTX9::Initiate_MeshAnimation( _charP name, COLLISION_TYPES _collisionType )
	{
	/*if (!Search_MeshAnimated(_name)) Geometry[_name] = new XANIMATION(((DIRECTX9_GLOBALS *)Global)->GetD3DDevice(), _name, _collisionTypes);*/
	return S_OK;
	};
int		DIRECTX9::Initiate_Object( _charP _name )
	{
	return Global->CreateObject( _name );
	};
HRESULT DIRECTX9::Initiate_SpecialEffect( _charP _name )
	{
	//if (Search_SpecialEffect(_name) == NULL) SpecialEffect[_name] = new SPECIALEFFECTS(_device);
	return S_OK;
	};
HRESULT DIRECTX9::Initiate_Surface( int _height, int _width, _charP _name )
	{
	//TODO Implement
	//GraphicalCoreLocker.lock();
	//( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->CreateOffscreenPlainSurface( _width, _height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &( ( DIRECTX9_GLOBALS * ) Global )->GetD3DSurface(), NULL );
	//D3DXLoadSurfaceFromFile( ( ( DIRECTX9_GLOBALS * ) Global )->GetD3DSurface(), NULL, NULL, _name, NULL, D3DX_DEFAULT, 0, NULL );
	//( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &( ( DIRECTX9_GLOBALS * ) Global )->GetD3DBackBuffer() );
	//GraphicalCoreLocker.unlock();
	return S_OK;
	};
HRESULT	DIRECTX9::Initiate_Terrain( string _fileName )
	{
	//// Высота для каждой вершины
	//std::vector<BYTE> in(262144);

	//std::ifstream inFile(fileName.c_str(), std::ios_base::binary);

	////if(inFile == 0)
	////      return false;

	//inFile.read(
	//	( char* ) &in[ 0 ], // буффер
	//	in.size());    // количество читаемых в буфер байт

	//inFile.close();

	//// копируем вектор BYTE в вектор int
	//Heightmap.resize(262144);
	//for ( int i = 0; i < in.size(); i++ )
	//	Heightmap[ i ] = in[ i ];

	return E_FAIL;
	};
HRESULT DIRECTX9::Initiate_Text( _charP _name, _charP _string, _charP _font, _charP _color, RECT _position )
	{
	//MAP_TEXTSTRINGS[int(MAP_TEXTSTRINGS.size()) + 1] = new DIRECTX9_TEXTSTRINGS(_string, _font, _color, _position);
	return S_OK;
	};
HRESULT DIRECTX9::Initiate_Text_Font( _charP _facename, int _height, int _weight, bool _isItalic )
	{
	//GraphicalCoreLocker.lock();
	//DIRECTX9_TEXTSTRINGS::Initiate_Font(((DIRECTX9_GLOBALS *)Global)->GetD3DDevice(), _facename, _height, _weight, _isItalic);
	//GraphicalCoreLocker.unlock();
	return E_FAIL;
	};
HRESULT DIRECTX9::Initiate_Text_Color( _charP _colorName, DWORD _color )
	{
	//GraphicalCoreLocker.lock();
	//DIRECTX9_TEXTSTRINGS::Initiate_Color(_colorName, _color);
	//GraphicalCoreLocker.unlock();
	return S_OK;
	};
int		DIRECTX9::Initiate_Texture( const _charP _name )
	{
	return ( ( DIRECTX9_GLOBALS * ) Global )->LoadTexture( _name, RECT() ); //TODO RECT
	};
HRESULT DIRECTX9::Initiate_TextureScreen( float X1, float Y1, float X2, float Y2, float X3, float Y3, float X4, float Y4 )
	{
	//TODO Implement
	//if ( ( ( DIRECTX9_GLOBALS * ) Global )->GetD3DTexBuffer() != NULL ) ( ( DIRECTX9_GLOBALS * ) Global )->GetD3DTexBuffer()->Release();
	/*texScreen[0].X = X1; texScreen[0].Y = Y1; texScreen[0].Z = 0.45f; texScreen[0].RHW = 1.0f; texScreen[0].fU = 0.0f; texScreen[0].fV = 0.0f;
	texScreen[1].X = X2; texScreen[1].Y = Y2; texScreen[1].Z = 0.45f; texScreen[1].RHW = 1.0f; texScreen[1].fU = 1.0f; texScreen[1].fV = 0.0f;
	texScreen[2].X = X3; texScreen[2].Y = Y3; texScreen[2].Z = 0.45f; texScreen[2].RHW = 1.0f; texScreen[2].fU = 0.0f; texScreen[2].fV = 1.0f;
	texScreen[3].X = X4; texScreen[3].Y = Y4; texScreen[3].Z = 0.45f; texScreen[3].RHW = 1.0f; texScreen[3].fU = 1.0f; texScreen[3].fV = 1.0f;

	((DIRECTX9_GLOBALS *)Global)->GetD3DDevice()->CreateVertexBuffer(sizeof(texScreen), 0, VertexexFVF3DTex, D3DPOOL_MANAGED, &((DIRECTX9_GLOBALS *)Global)->GetD3DTexBuffer(), NULL);
	VOID* pData = NULL;
	((DIRECTX9_GLOBALS *)Global)->GetD3DTexBuffer()->Lock(0, sizeof(pData), (void**)&pData, 0);
	memcpy(pData, texScreen, sizeof(texScreen));
	((DIRECTX9_GLOBALS *)Global)->GetD3DTexBuffer()->Unlock();*/

	return E_FAIL;
	};

HRESULT DIRECTX9::Render_Singletons( vector<int> _IDs ) const
	{
	return E_NOTIMPL;
	}

////---------------RENDERING--------------//
//---------------SINGLETONS--------------//
HRESULT DIRECTX9::Render_Cursor() const
	{
	RENDERSINGLETON( ID_CURSOR );
	};
HRESULT DIRECTX9::Render_Grid() const
	{
	RENDERSINGLETON( ID_GRID );
	};
HRESULT DIRECTX9::Render_SkyBox() const
	{
	RENDERSINGLETON( ID_SKYBOX );
	};
HRESULT DIRECTX9::Render_UpScreen() const
	{
	RENDERSINGLETON( ID_UPSCREEN );
	};
//---------------~SINGLETONS--------------//

HRESULT DIRECTX9::Render_Effect()
	{
	return E_FAIL;
	};
HRESULT DIRECTX9::Render_Sprite( RECT _src, RECT _dest )
	{
	//TODO Implement sprites
	//const RECT* src = &_src;
	//const RECT* dest = &_dest;
	//( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->StretchRect( ( ( DIRECTX9_GLOBALS * ) Global )->GetD3DSurface(), src, ( ( DIRECTX9_GLOBALS * ) Global )->GetD3DBackBuffer(), dest, D3DTEXF_NONE );
	return S_OK;
	};
HRESULT DIRECTX9::Render_Text( int _textKey, RECT _rec )
	{
	//((DIRECTX9_TEXTSTRINGS *)MAP_TEXTSTRINGS[_textKey])->Render(_rec);
	return S_OK;
	};
HRESULT DIRECTX9::Render_Objects( const vector<OBJECTSREGISTRY>& IDList ) const
	{
	Frustum->ConstructFrustum( Global->GetCamera( SceneController->getCameraID() ) );

	int g = 0;

	for ( size_t i = 0; i < IDList.size(); i++ )
		{
		OBJECTS * const TempObject = Global->GetObjectI( IDList[ i ].ID );
		if ( TempObject && TempObject->GetMeshTree() )
			{
			bool renderModel = Frustum->CheckPoint( TempObject->GetMeshTree()->GetXt(),
													TempObject->GetMeshTree()->GetYt(),
													TempObject->GetMeshTree()->GetZt() );
			
			//if ( renderModel )
				//{
				//g++;
				TempObject->Render( Global, IDList[ i ] );
				//}
			}
		}
	if ( !g )
		{
		int b = 0;
		}

	return S_OK;
	};
////--------------~RENDERING--------------//

////--------------DESTRUCTION-------------//

HRESULT DIRECTX9::Destroy_D3D()
	{
	OBJRELEASE( ( ( DIRECTX9_GLOBALS * ) Global )->GetD3D() ); return E_FAIL;
	};
HRESULT DIRECTX9::Destroy_Device()
	{
	OBJRELEASE( ( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice() ); return E_FAIL;
	};
HRESULT DIRECTX9::Destroy_Font( LPD3DXFONT font )
	{
	OBJRELEASE( font ); return E_FAIL;
	};
HRESULT	DIRECTX9::Destroy_Mesh( _charP name, _charP _name )
	{
	//GraphicalCoreLocker.lock();
	//if ( !Mesh ) return E_FAIL;
	//if ( Mesh->Remove_Mesh(name) == E_FAIL ) return E_FAIL;
	//MAP_UI.erase(_name);
	//GraphicalCoreLocker.unlock();
	return S_OK;
	};
HRESULT DIRECTX9::Destroy_Surface( LPDIRECT3DSURFACE9 SURFACE )
	{
	OBJRELEASE( SURFACE ); return S_OK;
	};
HRESULT DIRECTX9::Destroy_UpScreen( LPDIRECT3DVERTEXBUFFER9 )
	{
	//OBJRELEASE(buffer);
	return E_FAIL;
	};
HRESULT DIRECTX9::Destroy_Texture( _charP name )
	{
	//GraphicalCoreLocker.lock();
	//if ( ( !Texture ) || ( !_name ) ) return E_FAIL;
	//Texture->Remove_Texture(_name);
	//GraphicalCoreLocker.unlock();
	return E_FAIL;
	};
HRESULT DIRECTX9::Destroy_Text( _charP name )
	{
	return E_FAIL;
	};
HRESULT DIRECTX9::Destroy_Texts()
	{
	//TEXTSTRINGS * Temp = Text->Root;
	//Text = Text->Root;
	//while ( Text )
	//	{
	//	Text = Text->textNext;
	//	delete Temp;
	//	Temp = Text;
	//	};
	//Temp = NULL;
	return E_FAIL;
	};
HRESULT DIRECTX9::Destroy_Meshes()
	{
	//GraphicalCoreLocker.lock();
	//if ( !Mesh ) return E_FAIL;
	//Mesh->Clean();
	//MAP_UI.clear();
	//GraphicalCoreLocker.unlock();
	return E_FAIL;
	};
HRESULT DIRECTX9::Destroy_Object( int _ID )
	{
	//GraphicalCoreLocker.lock();
	//if ( !Object ) return E_FAIL;
	//if ( MAP_OBJ.size() )
	//	{
	//	map<int, OBJECTS::MESHES_TREE>::iterator Map_Iter = MAP_OBJ.find(_ID);
	//	if ( Map_Iter != MAP_OBJ.end() )
	//		MAP_OBJ.erase(Map_Iter);
	//	}
	//GraphicalCoreLocker.unlock();
	return E_FAIL;
	};
HRESULT DIRECTX9::Destroy_Objects()
	{
	//GraphicalCoreLocker.lock();
	//if ( !Object ) return E_FAIL;
	//Object->Clean();
	//MAP_OBJ.clear();
	//GraphicalCoreLocker.unlock();
	return E_FAIL;
	};
HRESULT DIRECTX9::Destroy_Cameras()
	{
	//OBJDELETE(Camera); 
	return E_FAIL;
	};

////--------------ADDITIONAL-------------//
void	DIRECTX9::Set_Grid( int _width, float _cellSize, DWORD _newColor )
	{
	SINGLETONS * Grid = Global->GetSingleton( ID_GRID );
	if ( !Grid )
		Grid = Global->GetSingleton( Global->CreateGrid() );
	( ( DIRECTX9_GRID * ) Grid )->Fill_Grid( ( DIRECTX9_GLOBALS * ) Global, _width, _cellSize, _newColor );
	};
void	DIRECTX9::Set_UpScreen( const int _clientWidth, const int _clientHeight, const int _textureID )
	{
	SINGLETONS * UpScreen = Global->GetSingleton( ID_UPSCREEN );
	if ( !UpScreen )
		UpScreen = Global->GetSingleton( Global->CreateUpScreen(_clientWidth, _clientHeight) );
	( ( DIRECTX9_UPSCREEN * ) UpScreen )->Fill_UpScreen( ( DIRECTX9_GLOBALS * ) Global, _clientWidth, _clientHeight, _textureID );
	}

HRESULT DIRECTX9::Set_RenderOptions()
	{
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->SetRenderState( D3DRS_LIGHTING, false );
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->SetRenderState( D3DRS_DITHERENABLE, false);
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->SetRenderState( D3DRS_ZENABLE, TRUE );
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->SetRenderState( D3DRS_NORMALIZENORMALS, true);

	((DIRECTX9_GLOBALS *)Global)->GetD3DDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
	((DIRECTX9_GLOBALS *)Global)->GetD3DDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	((DIRECTX9_GLOBALS *)Global)->GetD3DDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	((DIRECTX9_GLOBALS *)Global)->GetD3DDevice()->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);
	((DIRECTX9_GLOBALS *)Global)->GetD3DDevice()->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, 7);
	((DIRECTX9_GLOBALS *)Global)->GetD3DDevice()->SetSamplerState(0, D3DSAMP_MAXMIPLEVEL, 0);
	((DIRECTX9_GLOBALS *)Global)->GetD3DDevice()->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, 7);

	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE );
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_BLENDTEXTUREALPHA );

	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR/*D3DTEXF_POINT*/ );

	return true;
	};
HRESULT DIRECTX9::Set_RenderState( DWORD _type, DWORD _value )
	{
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->SetRenderState( ( D3DRENDERSTATETYPE ) _type, _value );
	return E_FAIL;
	};
HRESULT DIRECTX9::SetProjectionMatrix( CAMERAS * _camera )
	{
	if ( !_camera ) return E_FAIL;
	LPDIRECT3DDEVICE9 device = ( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice();
	_camera->setCameraMatrixView( device, CAMERAS::MATRIX_TYPES::Projection );
	return S_OK;
	};
HRESULT DIRECTX9::SetViewMatrix( CAMERAS * _camera )
	{
	if ( !_camera ) return E_FAIL;
	LPDIRECT3DDEVICE9 device = ( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice();
	_camera->setCameraMatrixView( device, CAMERAS::MATRIX_TYPES::View );
	return S_OK;
	};

void	DIRECTX9::Set_CameraPosition( int _ID, float _xPos, float _yPos, float _xAng, float _yAng )
	{

	};
void	DIRECTX9::Change_CameraPosition( int _ID, float _xPos, float _yPos, float _xAng, float _yAng )
	{
	Global->GetCamera( _ID )->setCameraYawPitchRoll( _xAng, _yAng, 0 );
	Global->GetCamera( _ID )->setCameraStrafe( WORLDPOSITION( _xPos, 0, _yPos ), 8. );
	};

HRESULT	DIRECTX9::Add_Geometry_To_Object ( const int _objID, OBJECTS::MESHES_TREE * _parent, MESH_ARGUMENTS )
	{
	//Object existance check
	OBJECTS * obj = Global->GetObjectI ( _objID );
	if ( !obj ) return E_FAIL;

	//Call object's method
	obj->AddMesh (_parent, MESH_ARGUMENTS_INIT);
	};

HRESULT DIRECTX9::StartScene()
	{
	LPDIRECT3DDEVICE9 device = ( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice();

	device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA( 170, 170, 170, 0 ), 1.0f, 0 );
	device->BeginScene();

	//TODO: Camera index should be taken from engine
	//Until then, get default camera

	CAMERAS * TempCamera = ( ( DIRECTX9_GLOBALS * ) Global )->GetCamera( SceneController->getCameraID() );
	if ( TempCamera ) TempCamera->setCameraMatrixView( device, CAMERAS::MATRIX_TYPES::View );

	return S_OK;
	};
HRESULT DIRECTX9::EndScene()
	{
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->EndScene();
	( ( DIRECTX9_GLOBALS * ) Global )->GetD3DDevice()->Present( NULL, NULL, NULL, NULL );
	return S_OK;
	};

HRESULT DIRECTX9::Initiate( HWND _hWnd, int _sizeX, int _sizeY )
	{
	Initiate_D3D( _hWnd );
	Initiate_GraphDevice( _hWnd, _sizeX, _sizeY );

	//------------------------------------------DEFAULTS------------------------------------------//
	( ( DIRECTX9_GLOBALS * ) Global )->CreateGeometry( DEFAULT, GEOMETRY_TYPES::Cube );
	( ( DIRECTX9_GLOBALS * ) Global )->CreateMaterial();
	( ( DIRECTX9_GLOBALS * ) Global )->CreateTexture();
	( ( DIRECTX9_GLOBALS * ) Global )->CreateTextString( DEFAULT );
	( ( DIRECTX9_GLOBALS * ) Global )->CreateAnimation( DEFAULT, NULL );
	//-----------------------------------------~DEFAULTS------------------------------------------//
	Initiate_Camera_Free(
		WORLDPOSITION( 0, 1000, 0 ), //TODO MAGIC NUMBER
		WORLDPOSITION( 0, 1, 0 ),
		WORLDPOSITION( 1, 0, 0 ),
		NULL, ANGLE_OF_VIEW, SCREEN_DIMENSION, NEAR_DISTANCE, FAR_DISTANCE );

	return S_OK;
	}
HRESULT DIRECTX9::Render()
	{
	return E_NOTIMPL;
	};
HRESULT DIRECTX9::Destroy()
	{
	return E_FAIL;
	};

//----------------------------------~DIRECTX9_MESHESX-----------------------------------//
#pragma endregion