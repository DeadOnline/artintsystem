#include "../_inc/Singletons.h"

#include "../../_inc/GraphCoreMacroses.h"

#pragma region SINGLETONS
//----------------------------------SINGLETONS----------------------------------//
using namespace GRAPHCORE;

SINGLETONS::SINGLETONS() { };
SINGLETONS::SINGLETONS(const SINGLETONS& root) { };
SINGLETONS::~SINGLETONS() { }
SINGLETONS & GRAPHCORE::SINGLETONS::operator=( const SINGLETONS & )
	{
	return *this;
	};
//---------------------------------~SINGLETONS----------------------------------//  
#pragma endregion