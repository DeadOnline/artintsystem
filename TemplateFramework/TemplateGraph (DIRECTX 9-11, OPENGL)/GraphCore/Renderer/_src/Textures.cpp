#include "../_inc/Textures.h"

#pragma region TEXTURES
//----------------------------------TEXTURES----------------------------------//
using namespace GRAPHCORE;

TEXTURES::TEXTURES( const _charP& _name, const RECT	_area ) : name( _strdup( _name ) ), area( _area ) {};
TEXTURES::~TEXTURES()
	{
	OBJFREE( name );
	}

const _charP TEXTURES::GetName() const { return name; };
const RECT&	TEXTURES::GetRect() const { return area; };
//---------------------------------~TEXTURES----------------------------------//  
#pragma endregion