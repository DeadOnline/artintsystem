#pragma once

#ifndef DominoRainSpawnerHeader
#define DominoRainSpawnerHeader

#include "../_inc/StateObject.h"

#include <unordered_set>

#define AREALENGTH 100
#define AREAWIDTH 100
#define AREAHEIGHT 100
#define SPAWNRATE 100
#define ROTATIONSPEED 100
#define FALLINGSPEED 100

#define MAXINSTANCES 15

using namespace std;

namespace APP
	{
	class DOMINORAINSPAWNER: public STATEOBJECT
		{
		private:
			int areaLength, areaWidth, areaHeight;
			float spawnRate, lastSpawnTime, rotationSpeed, fallingSpeed;
			bool IsWorking;

			int dominoRainObjectSpawnerID, dominoRainObjectTypeID;

			unordered_set<int> dominoRainIDs;

		protected:

			DOMINORAINSPAWNER( int _dominoRainObjectTypeID, int _areaLength = AREALENGTH, int _areaWidth = AREAWIDTH, int _areaHeight = AREAHEIGHT, float _spawnRate = SPAWNRATE, float _rotationSpeed = ROTATIONSPEED, float _fallingSpeed = FALLINGSPEED );
			~DOMINORAINSPAWNER( );

			void	OnSpawn( );
			void	OnDie( );

			void	OnClicked ();
			void	OnCondition ();

			void	OnDataRequest ();
			void	OnDataReceive ();
		};
	};

#endif