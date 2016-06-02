#pragma once
#ifndef DirectX9TextstringsHeader
#define DirectX9TextstringsHeader

#include "../../_inc/DirectX_Textstrings.h"

#include "DirectX9_Globals.h"

namespace GRAPHCORE
{
	class DIRECTX9_TEXTSTRINGS : public DIRECTX_TEXTSTRINGS
	{
	public:
		///////////
		static map<LPCSTR, LPD3DXFONT> font;
		static map<LPCSTR, D3DCOLOR> color;
		static D3DXFONT_DESC fontDesc;
		///////////
		LPCSTR appliedFont;
		LPCSTR appliedColor;
		LPCSTR string;
		RECT rec;
		///////////

	public:

		DIRECTX9_TEXTSTRINGS( _charP _string, LPCSTR _appliedFont, LPCSTR _appliedColor, RECT _position );
		~DIRECTX9_TEXTSTRINGS();

		////--------------INITIATION-------------//

		static HRESULT Initiate_Font(LPDIRECT3DDEVICE9 _Device, LPCSTR _name, int _height, int _weight, bool _italic);
		static HRESULT Initiate_Color(LPCSTR _name, D3DCOLOR _color);

		////---------------SETTERS---------------//

		static HRESULT Set_Font(LPCSTR _fontNumber, LPD3DXFONT _font);
		static HRESULT Set_Color(LPCSTR _colorNumber, D3DCOLOR _color);

		HRESULT Apply_Font(LPCSTR _fontNumber);
		HRESULT Apply_Color(LPCSTR _colorNumber);
		HRESULT Apply_String(LPCSTR _string);
		HRESULT Apply_Rec(RECT _position);

		////--------------RENDERING--------------//

		HRESULT Render(RECT _rec);

		////--------------ADDITIONAL-------------//

		static HRESULT Reset_Colors();
		static HRESULT Reset_Fonts();
		static HRESULT Reset_All();
	};
};

#endif