#pragma once
#ifndef TextstringsHeader
#define TextstringsHeader

#include "../../../../TemplateCommon/CommonCore/Macroses.h"

namespace GRAPHCORE
	{
	class TEXTSTRINGS
		{
		protected:
			_charP	name;

		//public:
			TEXTSTRINGS( const _charP _name);

			const		_charP		GetName() const;
		};
	};

#endif