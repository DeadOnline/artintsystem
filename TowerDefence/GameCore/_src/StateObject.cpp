#include "../_inc/StateObject.h"

#pragma region STATEOBJECT
//----------------------------------STATEOBJECT----------------------------------//
using namespace APP;

STATEOBJECT::STATEOBJECT ()
	{}

STATEOBJECT::~STATEOBJECT ()
	{}

//---------------------------------~STATEOBJECT----------------------------------//  
#pragma endregion

REQUESTDATA::REQUESTDATA (REQUESTCOMMANDS _command, int _ID, string _parameter, int _value, int _argument): command(_command), ID(_ID), BASEDATA()
	{}

RECEIVEDDATA::RECEIVEDDATA (): BASEDATA()
	{}

BASEDATA::BASEDATA (string _parameter, int _value, int _argument): parameter(_parameter), value(_value), argument(_argument)
	{}
