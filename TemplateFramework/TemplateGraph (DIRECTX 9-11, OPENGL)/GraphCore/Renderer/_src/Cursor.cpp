#include "../_inc/Cursor.h"

#pragma region CURSORS
//----------------------------------UPSCREEN----------------------------------//
using namespace GRAPHCORE;

int CURSOR::textureID = -1;
CURSOR * CURSOR::Object = NULL;

void GRAPHCORE::CURSOR::deleteInstance ()
	{
	OBJDELETE (Object);
	}

void CURSOR::ChangeCursorTexture( const int _ID ) { textureID = _ID; };
void CURSOR::ChangeCursorCoords( const int _x, const int _y ) { /*TODO*/ }
GRAPHCORE::CURSOR::CURSOR ()
	{}
GRAPHCORE::CURSOR::CURSOR ( const CURSOR & root )
	{}
GRAPHCORE::CURSOR::~CURSOR ()
	{}
CURSOR & GRAPHCORE::CURSOR::operator=( const CURSOR & )
	{
	return *this;
	}
//---------------------------------~UPSCREEN----------------------------------//  
#pragma endregion