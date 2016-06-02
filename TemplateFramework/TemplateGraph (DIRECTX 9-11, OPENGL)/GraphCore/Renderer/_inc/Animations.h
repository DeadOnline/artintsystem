#pragma once
#ifndef AnimationsHeader
#define AnimationsHeader

#include "../../../../TemplateCommon/CommonCore/Macroses.h"
#include "../../_inc/TemplateMatrix.h"

namespace GRAPHCORE
	{
	class ANIMATIONS 
		{
	public:
		ANIMATIONS();
		virtual ~ANIMATIONS();
		virtual		void		SetWorldMatrix( const void * _renderer, const _charP &_bone, const TEMPLATEMATRIX& const _worldMatrix, const float _time ) const = 0;
		};
	};

#endif