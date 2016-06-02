#pragma once
#ifndef CamerasHeader
#define CamerasHeader

#include "../../_inc/GraphCoreMacroses.h"
#include "../../_inc/WorldPosition.h"
#include "../../_inc/TemplateMatrix.h"

#define ANGLE_OF_VIEW 120.0f
#define SCREEN_DIMENSION 1.666667f
#define NEAR_DISTANCE 1.0f
#define FAR_DISTANCE 5000000.0f 

namespace GRAPHCORE
{
	class CAMERAS
	{
	public:
		enum CAMERAGUIDES
		{
			Vec_Position,
			Vec_Target,
			Vec_Look,
			Vec_Right,
			Vec_Up
		};
		enum MATRIX_TYPES
		{
			View,
			Projection
		};
	protected:

		///////////
		float		angle_Of_View;
		float		resolution_Of_Screen;
		float		starting_Point;
		float		ending_Point;
		///////////
		WORLDPOSITION positionStatic, targetStatic, upStatic;
		WORLDPOSITION * positionBinded;
		///////////

	protected:
		CAMERAS(WORLDPOSITION& _position, WORLDPOSITION& _targetStatic, WORLDPOSITION& _up, WORLDPOSITION * _positionBinded = NULL,
			float _angle_Of_View = 75.0f, float _resolution_Of_Screen = 4.0f / 3.0f, float _starting_Point = 0.1f, float _ending_Point = 1000.0f);
	public:
		~CAMERAS();

	public:

		WORLDPOSITION& GetStaticPosition();
		const WORLDPOSITION& GetStaticTarget() const;
		const WORLDPOSITION& GetStaticUp() const;
		const WORLDPOSITION * GetBindedPosition() const;
		virtual const WORLDPOSITION * GetBindedTarget() const = 0;
		virtual const WORLDPOSITION * GetBindedUp() const = 0;
		virtual TEMPLATEMATRIX GetViewMatrix() = 0;
		virtual TEMPLATEMATRIX GetProjectionMatrix() = 0;
		
		void SetStaticPosition(WORLDPOSITION& _position);
		void SetStaticTarget(WORLDPOSITION& _target);
		void SetStaticUp(WORLDPOSITION& _up);
		void SetBindedPosition(WORLDPOSITION * _position);
		virtual void SetBindedTarget(WORLDPOSITION * _target) = 0;
		virtual void SetBindedUp(WORLDPOSITION * _up) = 0;

		const float& GetAngleOfView() const;
		const float& GetResolution() const;
		const float& GetStartPoint() const;
		const float& GetEndPoint() const;

		void SetAngleOfView(const float& _angleOfView);
		void SetResolution(const float& _resolution);
		void SetStartPoint(const float& _startPoint);
		void SetEndPoint(const float& _endPoint);

		virtual void setCameraStrafe(WORLDPOSITION& _direction, float _units) = 0;
		virtual void setCameraWalk(WORLDPOSITION& _direction, float _units) = 0;
		virtual void setCameraElevate(WORLDPOSITION& _direction, float _units) = 0;

		virtual void setCameraRoll(float _angle) = 0;
		virtual void setCameraPitch(float _angle) = 0;
		virtual void setCameraYaw(float _angle) = 0;

		virtual void setCameraYawPitchRoll(float _angleX, float _angleY, float _angleZ) = 0;

		virtual void CameraMovesAround(float _speed) = 0;
		virtual void CameraMovesUp(float _units) = 0;
		virtual void CameraMovesTo(float _x, float _x1, float _z, float _z1, float _y) = 0;

		virtual WORLDPOSITION getCameraVectorRight() = 0;

		virtual void setCameraMatrixView( void * _renderer, MATRIX_TYPES _matrixType ) = 0;
	};
	class CAMERAS_FREE : public CAMERAS
	{
	protected:
		CAMERAS_FREE(WORLDPOSITION& _position,
			WORLDPOSITION& _look,
			WORLDPOSITION& _up,
			WORLDPOSITION * _positionBinded = NULL,
			float _angle_Of_View = 75.0f,
			float _resolution_Of_Screen = 4.0f / 3.0f,
			float _starting_Point = 0.1f,
			float _ending_Point = 1000.0f);

		virtual const WORLDPOSITION * GetBindedTarget() const;
		virtual const WORLDPOSITION * GetBindedUp() const;

		virtual void SetBindedTarget(WORLDPOSITION * _target);
		virtual void SetBindedUp(WORLDPOSITION * _up);

		WORLDPOSITION getCameraVectorRight();
	};
	class CAMERAS_TARGET : public CAMERAS
	{
	protected:

		WORLDPOSITION * targetBinded, *upBinded;
		CAMERAS_TARGET(
			WORLDPOSITION& _position,
			WORLDPOSITION& _target,
			WORLDPOSITION& _up,
			WORLDPOSITION * _positionBinded = NULL,
			WORLDPOSITION * _targetBinded = NULL,
			WORLDPOSITION * _upBinded = NULL,
			float _angle_Of_View = 75.0f,
			float _resolution_Of_Screen = 4.0f / 3.0f,
			float _starting_Point = 0.1f,
			float _ending_Point = 1000.0f);

	public:

		virtual const WORLDPOSITION * GetBindedTarget() const;
		virtual const WORLDPOSITION * GetBindedUp() const;

		virtual void SetBindedTarget(WORLDPOSITION * _target);
		virtual void SetBindedUp(WORLDPOSITION * _up);

		virtual WORLDPOSITION getCameraVectorRight();
	};
};

#endif