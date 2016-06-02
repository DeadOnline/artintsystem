#include "../_inc/SceneController.h"

#pragma region SCENECONTROLLER
//----------------------------------SCENECONTROLLER----------------------------------//
using namespace GRAPHCORE;

SCENECONTROLLER::SCENECONTROLLER() : camID( 0 ), cursor( false ), grid( false ), upScreen( false ), skyBox( false ) {}
SCENECONTROLLER::~SCENECONTROLLER() {}

void SCENECONTROLLER::Update( const SCENECONTROLLER& renderList )
	{
	grid = renderList.grid;
	upScreen = renderList.upScreen;
	cursor = renderList.cursor;
	skyBox = renderList.skyBox;
	camID = renderList.camID;
	objects = renderList.objects;
	}
void SCENECONTROLLER::SetCamera( int _camID )
	{
	camID = _camID;
	}
void SCENECONTROLLER::ShowCursor( const bool _show )
	{
	cursor = _show;
	}
void SCENECONTROLLER::ShowGrid( const bool _show )
	{
	grid = _show;
	}
void SCENECONTROLLER::ShowUpScreen( const bool _show )
	{
	upScreen = _show;
	}
void SCENECONTROLLER::ShowSkyBox( const bool _show )
	{
	skyBox = _show;
	}
void SCENECONTROLLER::AddObjectMatrix( const int _ID, const TEMPLATEMATRIX& const _matrix )
	{
	objects[ _ID ].rootWorldMatrix = _matrix;
	}
void SCENECONTROLLER::AddObjectAnimationTime( const int _ID, const int _animationID, const float _time )
	{
	objects[ _ID ].rootAnimationSet.animationID = _animationID;
	objects[ _ID ].rootAnimationSet.time = _time;
	}
void SCENECONTROLLER::AddObjectEntry( const int _ID, const TEMPLATEMATRIX& const _worldMatrix, ANIMATIONSET const _animationSet, const ATTRIBUTESMAP _meshEntry )
	{
	objects.push_back( OBJECTSREGISTRY( _ID, _worldMatrix, _animationSet, _meshEntry ) );
	}
void SCENECONTROLLER::AddObject( const int _ID )
	{
	objects.push_back( OBJECTSREGISTRY( _ID ) );
	};
int SCENECONTROLLER::getCameraID()
	{
	return camID;
	};
bool SCENECONTROLLER::getCursor()
	{
	return cursor;
	};
bool SCENECONTROLLER::getGrid()
	{
	return grid;
	};
bool SCENECONTROLLER::getUpScreen()
	{
	return upScreen;
	};
bool SCENECONTROLLER::getSkyBox()
	{
	return skyBox;
	};
const vector<OBJECTSREGISTRY>& SCENECONTROLLER::getObjects() const
	{
	return objects;
	};
//---------------------------------~SCENECONTROLLER----------------------------------//  
#pragma endregion