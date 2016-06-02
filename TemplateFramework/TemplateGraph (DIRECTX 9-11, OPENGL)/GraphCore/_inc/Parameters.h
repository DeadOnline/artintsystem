#pragma once

#ifndef ParametersHeader
#define ParametersHeader

#include <vector>
#include <map>

#include "Enums.h"
#include "TemplateMatrix.h"
#include "../../../TemplateCommon/CommonCore/Macroses.h"

namespace GRAPHCORE
	{
	using namespace std;

	struct ANIMATIONSET
		{
		int animationID;
		float time;
		};

	union VALUE
		{
		int ID;
		ANIMATIONSET animationSet;
		};

	typedef map<ATTRIBUTES_TYPES, VALUE> ATTRIBUTES;

	class MESHESENTRIES
		{
		public:
			MESHESENTRIES();
			~MESHESENTRIES();

			ATTRIBUTES& 		getAttributes();

		private:
			ATTRIBUTES			attributes;
		};

	typedef map<_charP, MESHESENTRIES> ATTRIBUTESMAP;

	struct OBJECTSREGISTRY
		{
		int				ID;
		TEMPLATEMATRIX	rootWorldMatrix;
		ANIMATIONSET	rootAnimationSet;
		ATTRIBUTESMAP	entries;
		OBJECTSREGISTRY(
			const int _ID = 0,
			const TEMPLATEMATRIX& const _rootWorldMatrix = TEMPLATEMATRIX(),
			ANIMATIONSET const _rootAnimationSet = ANIMATIONSET(),
			const ATTRIBUTESMAP _entries = ATTRIBUTESMAP());
		~OBJECTSREGISTRY();
		};
	}

#endif