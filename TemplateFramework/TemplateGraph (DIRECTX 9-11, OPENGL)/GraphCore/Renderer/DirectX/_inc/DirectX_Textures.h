#pragma once
#ifndef DirectXTexturesHeader
#define DirectXTexturesHeader

#include "../../_inc/Textures.h"

namespace GRAPHCORE
	{
	class DIRECTX_TEXTURES : public TEXTURES
		{ 
	public:
		DIRECTX_TEXTURES( const _charP& _name, const RECT	_area );

		virtual		void		SetTexture( const void * _renderer ) const = 0;
		virtual		HRESULT		Update_Texture( const void * _renderer, const _charP _path ) = 0;
		};
};

#endif