#pragma once
#ifndef MaterialsHeader
#define MaterialsHeader

#include "../../../../TemplateCommon/CommonCore/Macroses.h"

namespace GRAPHCORE
	{
	class MATERIALS
		{
		protected:
			_charP name;

		public:
			MATERIALS();
			virtual ~MATERIALS();
			virtual		void		SetMaterial( const void * _renderer ) const = 0;
			const _charP& GetName() const;
		};
	};

#endif