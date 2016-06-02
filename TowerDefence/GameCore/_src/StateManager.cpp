#include "../_inc/StateManager.h"
#include "../../../TemplateFramework/TemplateCommon/CommonCore/Macroses.h"

using namespace APP;

#pragma region STATEMANAGER
//----------------------------------GRID----------------------------------//

vector<int> STATEMANAGER::DataBase = vector<int> ();

bool STATEMANAGER::Update ()
	{
	//StateManager should have at least 1 object to process
	//If no objects r available, exit this shit

	if ( !DataBase.size () ) return 0;

	//Gather objects' inner commands
	for ( size_t i = 0; i < DataBase.size (); i++ )
		{

		}
	
	//Process 'em


	//Send objects' outer commands
	for ( size_t i = 0; i < DataBase.size (); i++ )
		{
		//Dependin' on situation, either sends OnRespawn | OnDie | OnUpdate command
		}

	return 1;
	}
//---------------------------------~GRID----------------------------------//  
#pragma endregion
