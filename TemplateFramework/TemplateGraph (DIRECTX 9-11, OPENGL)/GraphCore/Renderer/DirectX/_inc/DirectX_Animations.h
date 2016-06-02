#pragma once
#ifndef DirectXAnimationsXHeader
#define DirectXAnimationsXHeader

#include "../../_inc/Animations.h"

namespace GRAPHCORE
{
	class DIRECTX_ANIMATIONS : public ANIMATIONS
		{
		virtual		void		SetWorldMatrix( const void * _renderer, const _charP &_bone, const TEMPLATEMATRIX& const _worldMatrix, const float _time ) const = 0;
		};
}

#endif