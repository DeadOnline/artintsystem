#pragma once
#ifndef DirectX9TexturesHeader
#define DirectX9TexturesHeader

#include "../../_inc/DirectX_Textures.h"

#include "DirectX9_Globals.h"

namespace GRAPHCORE
	{
	class DIRECTX9_TEXTURES : public DIRECTX_TEXTURES
		{
		protected:

			LPDIRECT3DTEXTURE9	texture;

		public:
			///////////
			DIRECTX9_TEXTURES( const LPDIRECT3DDEVICE9 _device, const _charP& _path, const RECT	_area );
			DIRECTX9_TEXTURES( const LPDIRECT3DDEVICE9 _device, const TEXTURE_TYPES _textureType, const DEFAULT_COLORS _color, const RECT	_area );
			~DIRECTX9_TEXTURES();

			void						SetTexture( const void * _renderer ) const;
			const LPDIRECT3DTEXTURE9	GetTexture() const;
			HRESULT						Update_Texture( const void * _renderer, const _charP _path );
		};
	};

#endif