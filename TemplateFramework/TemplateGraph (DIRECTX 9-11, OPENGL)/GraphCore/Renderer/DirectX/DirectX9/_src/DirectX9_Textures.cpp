#include "../_inc/DirectX9_Textures.h"

using namespace GRAPHCORE;

#pragma region DIRECTX9_TEXTURES
//-----------------------------------DIRECTX9_TEXTURES-----------------------------------//
DIRECTX9_TEXTURES::DIRECTX9_TEXTURES( const LPDIRECT3DDEVICE9 _device, const _charP& _path, const RECT	_area ) : DIRECTX_TEXTURES( _path, _area )
	{
	if ( !SUCCEEDED( D3DXCreateTextureFromFileA( _device, _path, &texture ) ) ) //.bmp, .dds, .dib, .hdr, .jpg, .pfm, .png, .ppm, and .tga. formats supported
		{
		texture = NULL;
		}
	};
DIRECTX9_TEXTURES::DIRECTX9_TEXTURES( const LPDIRECT3DDEVICE9 _device, const TEXTURE_TYPES _textureType, const DEFAULT_COLORS _color, const RECT _area ) : DIRECTX_TEXTURES( DEFAULT, _area )
	{
	//TODO Generate texture usin' TEXTURE_TYPES 'n' DEFAULT_COLORS
	};
DIRECTX9_TEXTURES::~DIRECTX9_TEXTURES()
	{
	OBJRELEASE( texture );
	};

void DIRECTX9_TEXTURES::SetTexture( const void * _renderer ) const
	{
	( *( LPDIRECT3DDEVICE9 * ) &_renderer )->SetTexture( 0, texture );
	};
const LPDIRECT3DTEXTURE9 DIRECTX9_TEXTURES::GetTexture( ) const
	{
	return texture;
	};

HRESULT DIRECTX9_TEXTURES::Update_Texture( const void * _renderer, const _charP _path )
	{
	if ( !_renderer ) return E_FAIL;

	LPDIRECT3DDEVICE9 device = ( *( LPDIRECT3DDEVICE9 * ) &_renderer );

	LPDIRECT3DTEXTURE9	tempTex = NULL;
	
	if ( SUCCEEDED( D3DXCreateTextureFromFileA( device, _path, &tempTex ) ) ) //.bmp, .dds, .dib, .hdr, .jpg, .pfm, .png, .ppm, and .tga. formats supported
		{
		OBJRELEASE( texture );
		texture = tempTex;
		}
	};
//----------------------------------~DIRECTX9_TEXTURES-----------------------------------//  
#pragma endregion