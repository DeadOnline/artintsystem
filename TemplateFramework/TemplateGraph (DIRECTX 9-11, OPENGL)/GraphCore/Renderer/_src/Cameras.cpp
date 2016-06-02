#include "../_inc/Cameras.h"

#include "../../_inc/WorldPosition.h"

#pragma region CAMERAS
//-----------------------------------CAMERAS-----------------------------------//
using namespace GRAPHCORE;

CAMERAS::CAMERAS(WORLDPOSITION& _positionStatic, WORLDPOSITION& _targetStatic, WORLDPOSITION& _upStatic, WORLDPOSITION * _positionBinded,
	float _angle_Of_View, float _resolution_Of_Screen, float _starting_Point, float _ending_Point) :
	positionStatic(_positionStatic), targetStatic(_targetStatic), upStatic(_upStatic), positionBinded(_positionBinded),
	angle_Of_View(_angle_Of_View), resolution_Of_Screen(_resolution_Of_Screen), starting_Point(_starting_Point), ending_Point(_ending_Point)
{ };
CAMERAS::~CAMERAS() { };

WORLDPOSITION& CAMERAS::GetStaticPosition() { return positionStatic; };
const WORLDPOSITION& CAMERAS::GetStaticTarget() const { return targetStatic; };
const WORLDPOSITION& CAMERAS::GetStaticUp() const { return upStatic; };
const WORLDPOSITION * CAMERAS::GetBindedPosition() const { return positionBinded; };

void CAMERAS::SetStaticPosition(WORLDPOSITION& _position) { positionStatic = _position; };
void CAMERAS::SetStaticTarget(WORLDPOSITION& _target) { targetStatic = _target; };
void CAMERAS::SetStaticUp(WORLDPOSITION& _up) { upStatic = _up; };
void CAMERAS::SetBindedPosition(WORLDPOSITION * _positionBinded) { positionBinded = _positionBinded; };

const float& CAMERAS::GetAngleOfView() const { return angle_Of_View; };
void CAMERAS::SetAngleOfView(const float& _angleOfView) { angle_Of_View = _angleOfView; };
const float& CAMERAS::GetResolution() const { return resolution_Of_Screen; };
void CAMERAS::SetResolution(const float& _resolution) { resolution_Of_Screen = _resolution; };
const float& CAMERAS::GetStartPoint() const { return starting_Point; };
void CAMERAS::SetStartPoint(const float& _startPoint) { starting_Point = _startPoint; };
const float& CAMERAS::GetEndPoint() const { return ending_Point; };
void CAMERAS::SetEndPoint(const float& _endPoint) { ending_Point = _endPoint; };
//----------------------------------~CAMERAS-----------------------------------//  
#pragma endregion
#pragma region CAMERAS_FREE
//------------------------------------CAMERAS_FREE------------------------------------//
CAMERAS_FREE::CAMERAS_FREE(WORLDPOSITION& _position, WORLDPOSITION& _look, WORLDPOSITION& _up, WORLDPOSITION * _positionBinded,
	float _angle_Of_View, float _resolution_Of_Screen, float _starting_Point, float _ending_Point) :
	CAMERAS(_position, _look, _up, _positionBinded, _angle_Of_View, _resolution_Of_Screen, _starting_Point, _ending_Point)
{
	//Calculate Look, Right
};
void CAMERAS_FREE::SetBindedTarget(WORLDPOSITION * _target) { };
void CAMERAS_FREE::SetBindedUp(WORLDPOSITION * _up) { };

const WORLDPOSITION * CAMERAS_FREE::GetBindedTarget() const { return NULL; };
const WORLDPOSITION * CAMERAS_FREE::GetBindedUp() const { return NULL; };

WORLDPOSITION CAMERAS_FREE::getCameraVectorRight()
{
	return WORLDPOSITION();
};
//-----------------------------------~CAMERAS_FREE------------------------------------//  
#pragma endregion
#pragma region CAMERAS_TARGET
//-----------------------------------CAMERAS_TARGET-----------------------------------//
CAMERAS_TARGET::CAMERAS_TARGET(
	WORLDPOSITION& _position,
	WORLDPOSITION& _target,
	WORLDPOSITION& _up,
	WORLDPOSITION * _positionBinded,
	WORLDPOSITION * _targetBinded,
	WORLDPOSITION * _upBinded,
	float _angle_Of_View,
	float _resolution_Of_Screen,
	float _starting_Point,
	float _ending_Point) :
	CAMERAS(_position, _target, _up, _positionBinded, _angle_Of_View, _resolution_Of_Screen, _starting_Point, _ending_Point), targetBinded(_targetBinded), upBinded(_upBinded)
{

};

void CAMERAS_TARGET::SetBindedTarget(WORLDPOSITION * _target) { targetBinded = _target; };
void CAMERAS_TARGET::SetBindedUp(WORLDPOSITION * _up) { upBinded = _up; };

const WORLDPOSITION * CAMERAS_TARGET::GetBindedTarget() const { return targetBinded; };
const WORLDPOSITION * CAMERAS_TARGET::GetBindedUp() const { return upBinded; };

WORLDPOSITION CAMERAS_TARGET::getCameraVectorRight()
{
	return WORLDPOSITION();
};
//----------------------------------~CAMERAS_TARGET-----------------------------------//
#pragma endregion