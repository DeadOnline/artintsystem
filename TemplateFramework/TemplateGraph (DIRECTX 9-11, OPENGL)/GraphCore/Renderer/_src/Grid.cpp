#include "../_inc/Grid.h"

#pragma region GRID
//----------------------------------GRID----------------------------------//
using namespace GRAPHCORE;

GRID * GRID::Object = NULL;

const int &GRID::getID() const { return geometryID; };
void GRID::setID( const int _geometryID ) { geometryID = _geometryID; };

GRID::GRID () : geometryID( MAPNONEXISTANTID ) {}
GRID::GRID ( const GRID & root ) {};
GRID::~GRID () {}
GRID & GRID::operator=( const GRID & Grid )
	{
	return *this;
	}
void GRID::deleteInstance ()
	{
	OBJDELETE (Object);
	};
//---------------------------------~GRID----------------------------------//  
#pragma endregion