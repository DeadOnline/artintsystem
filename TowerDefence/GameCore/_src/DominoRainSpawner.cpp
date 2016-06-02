#include "../_inc/DominoRainSpawner.h"

#pragma region DOMINORAINSPAWNER
//----------------------------------DOMINORAINSPAWNER----------------------------------//
using namespace APP;

DOMINORAINSPAWNER::DOMINORAINSPAWNER (int _dominoRainObjectTypeID, int _areaLength, int _areaWidth, int _areaHeight, float _spawnRate, float _rotationSpeed, float _fallingSpeed): 
	areaLength (_areaLength), areaWidth(_areaLength), areaHeight(_areaLength),
	spawnRate(_spawnRate), lastSpawnTime(_spawnRate), rotationSpeed(_rotationSpeed), fallingSpeed(_fallingSpeed),
	IsWorking(true), dominoRainObjectTypeID(_dominoRainObjectTypeID)
		{
	//Load domino geometry mesh
	//Load domino texture
		}

	DOMINORAINSPAWNER::~DOMINORAINSPAWNER ()
		{
		//Send a sygnal for sub objects to die
		}

	/*
	* Is called once right after creation
	* One may request some info from here
	*/
	void DOMINORAINSPAWNER::OnSpawn ()
		{
		//Fill Data object:
		//Request current time from system in ticks
		//
		}
	
	/*
	* Is called once right before bein' completely destroyed
	* One may send some last orders from here
	*/
	void DOMINORAINSPAWNER::OnDie ()
		{
		//Send immediate order to destroy every last domino object in dominoRain, which is still present on scene
		unordered_set<int>::iterator DominoIter = dominoRainIDs.begin();
		for ( ; DominoIter != dominoRainIDs.end(); ++DominoIter )
			{
			RequestData.push_back (REQUESTDATA(KILL_OBJECT_ID, *DominoIter));
			}
		}

	void DOMINORAINSPAWNER::OnClicked ()
		{}
	void DOMINORAINSPAWNER::OnCondition ()
		{}

	/*
	* Is called after StateManager starts gatherin' info at the start of each iteration
	* Dependin' on what state dominoRain is currently in, it will behave differently:
	* If it's set to true, on new iteration it will request either new domino object spawn, or update positions of already existing
	* Otherwise, it will request domino meshes killing as soon as they reach area bottom, and commit suicide after no dominoes left
	*/
	void DOMINORAINSPAWNER::OnDataRequest ()
		{
		//Determine if DominoRain spawner is workin' in ordinary mode or is stoppin'
		//Current scheme is designed for workin' mode only
		
		if (IsWorking)
			{ 		
			//Determine if new object should be spawned
			if ( dominoRainIDs.size () < MAXINSTANCES )
				{
				if ( lastSpawnTime >= spawnRate )
					{
					RequestData.push_back (REQUESTDATA(SPAWN_TYPE_ID, dominoRainObjectTypeID));
					lastSpawnTime = 0;
					}
				}
		
			for ( size_t i = 0; i < dominoRainIDs.size(); i++ )
				{
				//For each existin' object send request to rotate it in 3 dimensions and apply descendin' value
				//If object is below local areaHeight, move it onto random local upper plane position
				}	
			}	
		}

	/*
	* Is called after StateManager finishes procession of game condition each iteration
	* In our case DominoRain listens to outer orders of swapping it's state;
	* value_by_demand gets time_delta for determination if new mesh should be created (when registered bones quantity is not MAX)
	* and height positions for each bones it already has in list, so it could process 'em on new iteration
	*/
	void DOMINORAINSPAWNER::OnDataReceive ()
		{
		//ReceivedData should be already sorted in order to process SET_PARAMETER first, cuz it's necessary
		while ( ReceivedData.size() )
			{
			switch ( ReceivedData.front().command )
				{
				case APP::SET_PARAMETER_TYPE:
					//Here maybe simple if's just for checkin' up if necessary attributes are available
					//We need only stage for the current moment
					if ( ReceivedData.front ().parameter == "State" )
						IsWorking = ReceivedData.front ().value;
					break;
				case APP::VALUE_BY_DEMAND:
					if ( ReceivedData.front ().parameter == "TimeDelta" )
						lastSpawnTime = ReceivedData.front ().value;
					if ( ReceivedData.front ().parameter == "NewChildObjectID" )
						dominoRainIDs.insert(ReceivedData.front ().value);
					break;
				default:
					break;
				}
			ReceivedData.pop_front ();
			}
		}
//---------------------------------~DOMINORAINSPAWNER----------------------------------//  
#pragma endregion