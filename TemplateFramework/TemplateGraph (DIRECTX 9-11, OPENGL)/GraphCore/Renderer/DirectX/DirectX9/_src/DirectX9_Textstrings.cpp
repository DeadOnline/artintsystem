#include "../_inc/DirectX9_Textstrings.h"

using namespace GRAPHCORE;

#pragma region DIRECTX9_TEXTSTRINGS
//-----------------------------------DIRECTX9_TEXTSTRINGS-----------------------------------//
map<LPCSTR, D3DCOLOR>	DIRECTX9_TEXTSTRINGS::color = map<LPCSTR, D3DCOLOR>();
map<LPCSTR, LPD3DXFONT>	DIRECTX9_TEXTSTRINGS::font = map<LPCSTR, LPD3DXFONT>();
D3DXFONT_DESC	DIRECTX9_TEXTSTRINGS::fontDesc = { 24, 0, 400, 0, false, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_PITCH, "Arial" };

DIRECTX9_TEXTSTRINGS::DIRECTX9_TEXTSTRINGS( _charP _name, LPCSTR _appliedFont, LPCSTR _appliedColor, RECT _position ) : DIRECTX_TEXTSTRINGS( _name )
	{
	Apply_Rec( _position );
	Apply_Font( _appliedFont );
	Apply_Color( _appliedColor );
	Apply_String( _name );
	};
DIRECTX9_TEXTSTRINGS::~DIRECTX9_TEXTSTRINGS()
	{
	Reset_All();
	};
HRESULT DIRECTX9_TEXTSTRINGS::Initiate_Font( LPDIRECT3DDEVICE9 _g_dDevice, LPCSTR _name, int _height, int _weight, bool _italic )
	{
	strcpy_s( fontDesc.FaceName, _name );
	fontDesc.Height = _height;
	fontDesc.Italic = _italic;
	fontDesc.Weight = _weight;
	D3DXCreateFontIndirect( _g_dDevice, &fontDesc, &font[ _name ] );
	return S_OK;
	};
HRESULT DIRECTX9_TEXTSTRINGS::Initiate_Color( LPCSTR _name, D3DCOLOR _color ) { color[ _name ] = _color; return S_OK; };
HRESULT DIRECTX9_TEXTSTRINGS::Set_Font( LPCSTR _fontNumber, LPD3DXFONT _font ) { font[ _fontNumber ] = _font; return S_OK; };
HRESULT DIRECTX9_TEXTSTRINGS::Set_Color( LPCSTR _colorNumber, D3DCOLOR _color ) { color[ _colorNumber ] = _color; return S_OK; };
HRESULT DIRECTX9_TEXTSTRINGS::Apply_Font( LPCSTR _fontNumber ) { appliedFont = _fontNumber; return S_OK; };
HRESULT DIRECTX9_TEXTSTRINGS::Apply_Color( LPCSTR _colorNumber ) { appliedColor = _colorNumber; return S_OK; };
HRESULT DIRECTX9_TEXTSTRINGS::Apply_String( LPCSTR _string ) { string = _string; return S_OK; };
HRESULT DIRECTX9_TEXTSTRINGS::Apply_Rec( RECT _position ) { rec = _position; return S_OK; };
HRESULT DIRECTX9_TEXTSTRINGS::Reset_Colors()
	{
	for ( map<LPCSTR, D3DCOLOR>::iterator colorIter = color.begin(); colorIter != color.end(); ++colorIter )
		{
		colorIter->second = 0;
		}
	return S_OK;
	};
HRESULT DIRECTX9_TEXTSTRINGS::Reset_Fonts()
	{
	for ( map<LPCSTR, LPD3DXFONT>::iterator fontIter = font.begin(); fontIter != font.end(); ++fontIter )
		{
		OBJRELEASE( fontIter->second );
		}
	ZeroMemory( &fontDesc, sizeof( D3DXFONT_DESC ) );
	return S_OK;
	}
HRESULT DIRECTX9_TEXTSTRINGS::Reset_All()
	{
	for ( map<LPCSTR, LPD3DXFONT>::iterator fontIter = font.begin(); fontIter != font.end(); ++fontIter )
		{
		OBJRELEASE( fontIter->second );
		}
	for ( map<LPCSTR, D3DCOLOR>::iterator colorIter = color.begin(); colorIter != color.end(); ++colorIter )
		{
		colorIter->second = 0;
		}
	ZeroMemory( &fontDesc, sizeof( D3DXFONT_DESC ) );
	return S_OK;
	}
HRESULT DIRECTX9_TEXTSTRINGS::Render( RECT _rec )
	{
	font[ appliedFont ]->DrawText( NULL, string, -1, &_rec, DT_CENTER, color[ appliedColor ] ); return S_OK;
	};
//-----------------------------------DIRECTX9_TEXTSTRINGS-----------------------------------//  
#pragma endregion