#pragma once
#ifndef TexturesHeader
#define TexturesHeader

#include "../../_inc/GraphCoreMacroses.h"
#include "../../_inc/Enums.h"
#include "../../../../TemplateCommon/CommonCore/Macroses.h"

namespace GRAPHCORE
{
	class TEXTURES
	{
	private:
		_charP	name;
		RECT	area;

	public:
		TEXTURES( const _charP& _path, const RECT	_area );
		~TEXTURES();
				
		const		_charP		GetName() const;
		const		RECT&		GetRect() const;
		virtual		void		SetTexture( const void * _renderer ) const = 0;
		virtual		HRESULT		Update_Texture( const void * _renderer, const _charP _path ) = 0;
	};
};

#endif