#pragma once

#ifndef StateObjectsHeader
#define StateObjectsHeader

#include <list>
#include <string>

using namespace std;

namespace APP
	{
	enum RECEIVEDCOMMANDS
		{
		SET_PARAMETER_TYPE, //Forcefully sets parameter for current object followin' statemanager order | SET_PARAMETER PARAMETER_STR VALUE
		VALUE_BY_DEMAND //Receives particular value needed for current object to process if needed | VALUE_BY_DEMAND PARAMETER_STR VALUE
		};
	enum REQUESTCOMMANDS
		{
		SPAWN_TYPE_ID, //Request to spawn object with followin' ID from database' types (always returns spawned object ID later in correspondin' order) | SPAWN TYPE_ID
		KILL_OBJECT_ID, //Kill object in database with defined ID in database storage | KILL ID
		GET_PARAMETER, //Get particular parameter from particular object in database storage | GET_PARAMETER ID PARAMETER_STR VALUE
		SET_PARAMETER, //Set particular parameter for particular object in database storage | SET_PARAMETER ID PARAMETER_STR VALUE
		GET_TIME //Gets time tick from system | GET_TIME
		};

	struct BASEDATA
		{
		string parameter;
		int value, argument; //arguments should be reconsidered
		BASEDATA (string _parameter = "", int _value = 0, int _argument = 0);
		};
	struct REQUESTDATA: public BASEDATA
		{
		REQUESTCOMMANDS command;
		int ID;
		REQUESTDATA (REQUESTCOMMANDS _command, int _ID = -1, string _parameter = "", int _value = 0, int _argument = 0);
		};
	struct RECEIVEDDATA: public BASEDATA
		{
		RECEIVEDCOMMANDS command;
		RECEIVEDDATA ();
		};

	class STATEOBJECT
		{
		protected:

			list<REQUESTDATA> RequestData;
			list<RECEIVEDDATA> ReceivedData;

		protected:

			STATEOBJECT( );
			~STATEOBJECT( );

			virtual void	OnSpawn( ) = 0;
			virtual void	OnDie( ) = 0;

			virtual void	OnClicked () = 0;
			virtual void	OnCondition () = 0;

			virtual void	OnDataRequest () = 0;
			virtual void	OnDataReceive () = 0;
		};
	};

#endif