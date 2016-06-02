#pragma once
#ifndef DirectXMaterialsHeader
#define DirectXMaterialsHeader

#include "../../_inc/Materials.h"

namespace GRAPHCORE
	{
	class DIRECTX_MATERIALS : public MATERIALS
		{
		public:
			DIRECTX_MATERIALS();
			virtual ~DIRECTX_MATERIALS();
			virtual		void		SetMaterial( const void * _renderer ) const = 0;
		};
	};

#endif