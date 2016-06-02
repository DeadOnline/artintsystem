#pragma once

#ifndef DominoRainMeshHeader
#define DominoRainMeshHeader

#include "../_inc/StateObject.h"

#define ROTATIONSPEED 100
#define FALLINGSPEED 100

using namespace std;

namespace APP
	{
	class DOMINORAINMESH: public STATEOBJECT
		{
		private:
			float rotationSpeed, fallingSpeed, heightPosition, localTop, localBottom;
			bool IsWorking;

			int dominoRainMeshID, dominoRainSpawnerID;

		protected:

			DOMINORAINMESH( int dominoRainMeshID, int dominoRainSpawnerID, float _rotationSpeed = ROTATIONSPEED, float _fallingSpeed = FALLINGSPEED );
			~DOMINORAINMESH( );

			void	OnSpawn( );
			void	OnDie( );

			void	OnClicked ();
			void	OnCondition ();

			void	OnDataRequest ();
			void	OnDataReceive ();
		};
	};

#endif