#pragma once
#ifndef DirectXCamerasHeader
#define DirectXCamerasHeader

#include "../../_inc/Cameras.h"

#include "../../../_inc/WorldPosition.h"

#include "../../../_inc/GraphCoreMacroses.h"

namespace GRAPHCORE
{
	class DIRECTX_CAMERAS
	{
	public:
		DIRECTX_CAMERAS();

		virtual TEMPLATEMATRIX GetViewMatrix() = 0;
		virtual TEMPLATEMATRIX GetProjectionMatrix() = 0;
	};
	class DIRECTX_CAMERAS_FREE : public CAMERAS_FREE, public DIRECTX_CAMERAS
	{
	public:
		DIRECTX_CAMERAS_FREE(WORLDPOSITION& _position, WORLDPOSITION& _look, WORLDPOSITION& _up, WORLDPOSITION * _positionBind = NULL,
			float _angle_Of_View = 75.0f, float _resolution_Of_Screen = 4.0f / 3.0f, float _starting_Point = 0.1f, float _ending_Point = 1000.0f);

		void setCameraStrafe(WORLDPOSITION& _direction, float _units);
		void setCameraWalk(WORLDPOSITION& _direction, float _units);
		void setCameraElevate(WORLDPOSITION& _direction, float _units);

		virtual void setCameraRoll(float angle);
		virtual void setCameraPitch(float angle);
		virtual void setCameraYaw(float angle);

		virtual void setCameraYawPitchRoll(float _angleX, float _angleY, float _angleZ);

		void CameraMovesAround(float _speed);
		void CameraMovesUp(float _units);
		void CameraMovesTo(float _x, float _x1, float _z, float _z1, float _y);
	};
	class DIRECTX_CAMERAS_TARGET : public CAMERAS_TARGET, public DIRECTX_CAMERAS
	{
	public:
		DIRECTX_CAMERAS_TARGET(WORLDPOSITION& _position, WORLDPOSITION& _target, WORLDPOSITION& _up,
			WORLDPOSITION  * _positionBinded = NULL, WORLDPOSITION * _targetBinded = NULL, WORLDPOSITION * _upBinded = NULL,
			float _angle_Of_View = 75.0f, float _resolution_Of_Screen = 4.0f / 3.0f, float _starting_Point = 0.1f, float _ending_Point = 1000.0f);

		void setCameraStrafe(WORLDPOSITION& _direction, float _units);
		void setCameraWalk(WORLDPOSITION& _direction, float _units);
		void setCameraElevate(WORLDPOSITION& _direction, float _units);

		void setCameraRoll(float angle);
		void setCameraPitch(float angle);
		void setCameraYaw(float angle);

		void CameraMovesAround(float _speed);
		void CameraMovesUp(float _units);
		void CameraMovesTo(float _x, float _x1, float _z, float _z1, float _y);
	};
}

#endif