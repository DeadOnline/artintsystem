#include "../_inc/DominoRainMesh.h"

#pragma region DOMINORAINMESH
//----------------------------------DOMINORAINMESH----------------------------------//
using namespace APP;

DOMINORAINMESH::DOMINORAINMESH ( int dominoRainMeshID, int dominoRainSpawnerID, float _rotationSpeed, float _fallingSpeed )
	{}

void DOMINORAINMESH::OnSpawn ()
	{
	//When created, it should know the ID of it's parent
	}

void DOMINORAINMESH::OnDie ()
	{
	
	}

void DOMINORAINMESH::OnClicked ()
	{}

void DOMINORAINMESH::OnCondition ()
	{}

void DOMINORAINMESH::OnDataRequest ()
	{
	
	//So it may request info 'bout it's local area bounds
	//And positionate itself on random point of top plane of its local area
	RequestData.push_back (REQUESTDATA(GET_PARAMETER, dominoRainSpawnerID, "areaHeight"));
	RequestData.push_back (REQUESTDATA(GET_PARAMETER, dominoRainSpawnerID, "Xp"));
	RequestData.push_back (REQUESTDATA(GET_PARAMETER, dominoRainSpawnerID, "Yp"));
	RequestData.push_back (REQUESTDATA(GET_PARAMETER, dominoRainSpawnerID, "Zp"));
	}

void DOMINORAINMESH::OnDataReceive ()
	{}

//---------------------------------~DOMINORAINMESH----------------------------------//  
#pragma endregion

