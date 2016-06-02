#pragma once
#ifndef DirectX9Header
#define DirectX9Header

#include "../../_inc/DirectX.h"

#include "DirectX9_Globals.h"

//------------------------------------------DIRECTX 9.0-------------------------------------------//

const D3DCOLOR DEFAULTCOLOURS[] =
{
	D3DCOLOR_XRGB(0, 0, 0),       //Black
	D3DCOLOR_XRGB(0, 0, 255),     //Blue
	D3DCOLOR_XRGB(0, 127, 255),   //Cerulean
	D3DCOLOR_XRGB(0, 255, 0),     //Green
	D3DCOLOR_XRGB(255, 255, 0),   //Yellow
	D3DCOLOR_XRGB(255, 0, 0),     //Red
	D3DCOLOR_XRGB(255, 0, 255),   //Magenta
	D3DCOLOR_XRGB(255, 255, 255), //White
	D3DCOLOR_XRGB(127, 127, 127)  //Grey
};
#define MAX_DEFAULT_COLOURS 9

const D3DFORMAT PIXELFORMATS[] =
{
	D3DFMT_A8R8G8B8,
	D3DFMT_X8R8G8B8,
	D3DFMT_R5G6B5,
	D3DFMT_X1R5G5B5
};
#define MAX_PIXEL_FORMATS 4
#define BACK_BUFFER_MULTIPLIER 2.0

namespace GRAPHCORE
{
	class	DIRECTX9 : public DIRECTX
	{
	public:

		enum DIRECTX9_SUPPORTED_FILE_FORMATS { _x, _g };

		DIRECTX9();
		~DIRECTX9();

		////--------------INITIATION-------------//

		HRESULT Initiate_D3D(HWND hWnd);
		HRESULT Initiate_GraphDevice(HWND hWnd, int sizeX = 100, int sizeY = 100);

		int Initiate_Camera_Free(WORLDPOSITION& _position, WORLDPOSITION& _look, WORLDPOSITION& _up, WORLDPOSITION * _positionBinded = NULL,
			float _angle_Of_View = 75.0f, float _resolution_Of_Screen = 4.0f / 3.0f, float _starting_Point = 0.1f, float _ending_Point = 1000.0f);

		int Initiate_Camera_Target(WORLDPOSITION& _position, WORLDPOSITION& _target, WORLDPOSITION& _up,
			WORLDPOSITION * _positionBinded = NULL, WORLDPOSITION * _targetBinded = NULL, WORLDPOSITION * _upBinded = NULL,
			float _angle_Of_View = 75.0f, float _resolution_Of_Screen = 4.0f / 3.0f, float _starting_Point = 0.1f, float _ending_Point = 1000.0f);

		int		Initiate_Geometry(_charP _name, VERTEX_TYPES _formatType, GEOMETRY_TYPES _geometryType);
		HRESULT	Initiate_Light(_charP _name, LIGHT_TYPES _type);
		vector<int>	Load_Geometry( const _charP& _relativeMeshPath, const _charP& _relativeResFolder, const SUPPORTED_FILE_FORMATS _format, const COLLISION_TYPES _collisionType );
		HRESULT		Initiate_MeshAnimation(_charP name, COLLISION_TYPES _collisionType);
		int		Initiate_Object( _charP _name );
		HRESULT Initiate_SkyMap(_charP _name) { }; //http://netlib.narod.ru/library/book0051/ch08_06.htm
		HRESULT Initiate_SpecialEffect(_charP _name);
		HRESULT Initiate_Surface(int height, int width, _charP name);
		HRESULT Initiate_Terrain(string _fileName);
		HRESULT Initiate_Text(_charP _name, _charP _string, _charP _font, _charP _color, RECT _position = RECT());
		HRESULT Initiate_Text_Color(_charP _colorName, DWORD _color);
		HRESULT Initiate_Text_Font(_charP _faceName, int _Height = 10, int _Weight = 400, bool _IsItalic = false);
		int		Initiate_Texture( const _charP _name );
		HRESULT Initiate_TextureScreen(float X1, float Y1, float X2, float Y2, float X3, float Y3, float X4, float Y4);

		////---------------RENDERING--------------//
		//---------------SINGLETONS--------------//
		HRESULT Render_Singletons( vector<int> _IDs ) const ;
		HRESULT Render_Cursor() const;
		HRESULT Render_SkyBox() const;
		HRESULT Render_UpScreen() const;
		HRESULT Render_Grid() const;
		//---------------~SINGLETONS--------------//

		HRESULT Render_Sprite( RECT _src, RECT _dest );
		HRESULT Render_Text( int _textKey, RECT _rec );
		HRESULT Render_Objects( const vector<OBJECTSREGISTRY>& IDList ) const;
		HRESULT Render_Effect();
		////--------------~RENDERING--------------//

		////--------------DESTRUCTION-------------//

		HRESULT Destroy_D3D();
		HRESULT Destroy_Device();
		HRESULT Destroy_Font(LPD3DXFONT font);												// ”ничтожить шрифт
		HRESULT Destroy_Mesh(_charP name, _charP _name);
		HRESULT Destroy_Surface(LPDIRECT3DSURFACE9 SURFACE);
		HRESULT Destroy_UpScreen(LPDIRECT3DVERTEXBUFFER9);
		HRESULT Destroy_Texture(_charP name);
		HRESULT Destroy_Text(_charP name);
		HRESULT Destroy_Texts();
		HRESULT Destroy_Meshes();
		HRESULT Destroy_Object(int _ID);
		HRESULT Destroy_Objects();
		HRESULT Destroy_Cameras();

		////--------------ADDITIONAL-------------//

		HRESULT Set_RenderState( DWORD _type, DWORD _value );
		HRESULT Set_RenderOptions();
		HRESULT SetProjectionMatrix(CAMERAS * _camera);
		HRESULT SetViewMatrix(CAMERAS * _camera);
		void	Set_CameraPosition(int _ID, float _xPos, float _yPos, float _xAng, float _yAng);
		void	Change_CameraPosition(int _ID, float _xPos, float _yPos, float _xAng, float _yAng);

		void	Set_Grid ( int _width, float _cellSize, DWORD _newColor );
		void	Set_UpScreen ( const int _clientWidth, const int _clientHeight, const int _textureID );

		HRESULT	Add_Geometry_To_Object ( const int _objID, OBJECTS::MESHES_TREE * _parent, MESH_ARGUMENTS );

		HRESULT StartScene( );
		HRESULT EndScene();

		HRESULT Initiate(HWND hWnd, int sizeX, int sizeY);
		HRESULT Render();
		HRESULT Destroy();
	};
};

//-----------------------------------------~DIRECTX 9.0-------------------------------------------//

#endif