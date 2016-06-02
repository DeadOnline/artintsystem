#include "../_inc/Parameters.h"
#include "../_inc/GraphCoreMacroses.h"

using namespace GRAPHCORE;

#pragma region MESHESENTRIES
//----------------------------------MESHESENTRIES----------------------------------//
MESHESENTRIES::MESHESENTRIES() {};
MESHESENTRIES::~MESHESENTRIES() {}
ATTRIBUTES & MESHESENTRIES::getAttributes ()
	{
	return attributes;
	};
//---------------------------------~MESHESENTRIES----------------------------------//  
#pragma endregion

OBJECTSREGISTRY::OBJECTSREGISTRY( const int _ID,
								  const TEMPLATEMATRIX& const _rootWorldMatrix,
								  ANIMATIONSET const _rootAnimationSet,
								  const ATTRIBUTESMAP _entries ) : 
									ID(_ID),
									rootWorldMatrix(_rootWorldMatrix),
									rootAnimationSet( _rootAnimationSet ),
									entries( _entries) { }

OBJECTSREGISTRY::~OBJECTSREGISTRY() {}