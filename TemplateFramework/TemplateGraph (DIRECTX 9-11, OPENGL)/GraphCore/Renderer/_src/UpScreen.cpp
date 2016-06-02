#include "../_inc/UpScreen.h"

#pragma region UPSCREEN
//----------------------------------UPSCREEN----------------------------------//
using namespace GRAPHCORE;

UPSCREEN * UPSCREEN::Object = NULL;

void UPSCREEN::ChangeUpScreenAlpha( const int _alpha ) { alpha = _alpha; };
void UPSCREEN::ChangeUpScreenColor( const DEFAULT_COLORS _colors ) { /*TODO*/ }
void UPSCREEN::ChangeUpScreenTexture ( const int _textureID )
	{
	textureID = _textureID;
	}
GRAPHCORE::UPSCREEN::UPSCREEN (): alpha( 0 ), geometryID( MAPNONEXISTANTID ), textureID( MAPNONEXISTANTID ) {}
GRAPHCORE::UPSCREEN::UPSCREEN ( const UPSCREEN & root )	{}
GRAPHCORE::UPSCREEN::~UPSCREEN () {}
UPSCREEN & UPSCREEN::operator=( const UPSCREEN & )
	{
	return *this;
	};

void UPSCREEN::deleteInstance ()
	{
	OBJDELETE (Object);
	};
//---------------------------------~UPSCREEN----------------------------------//  
#pragma endregion