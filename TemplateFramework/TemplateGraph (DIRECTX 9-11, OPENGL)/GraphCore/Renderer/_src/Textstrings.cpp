#include "../_inc/Textstrings.h"

#pragma region TEXTSTRINGS
//----------------------------------TEXTSTRINGS----------------------------------//
using namespace GRAPHCORE;

TEXTSTRINGS::TEXTSTRINGS( const _charP _name ) : name( _name ) {};

const _charP TEXTSTRINGS::GetName() const { return name; };
//---------------------------------~TEXTSTRINGS----------------------------------//  
#pragma endregion