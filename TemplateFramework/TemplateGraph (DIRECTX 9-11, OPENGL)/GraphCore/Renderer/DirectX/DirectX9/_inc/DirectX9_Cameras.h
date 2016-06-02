#pragma once
#ifndef DirectX9CamerasHeader
#define DirectX9CamerasHeader

#include "../../_inc/DirectX_Cameras.h"

#include "DirectX9_Globals.h"

namespace GRAPHCORE
	{
	class DIRECTX9_CAMERAS
		{
		protected:
			LPDIRECT3DDEVICE9 device;
			///////////
			float		object_Rotate_Presentation;
			float		camera_Height_Presentation;
			///////////
		public:
			DIRECTX9_CAMERAS(
				LPDIRECT3DDEVICE9& _device, float _object_Rotate_Presentation = 1.0f, float _camera_Height_Presentation = 1.0f );
			~DIRECTX9_CAMERAS();
		};
	class DIRECTX9_CAMERAS_FREE : public DIRECTX9_CAMERAS, public DIRECTX_CAMERAS_FREE
		{
		public:
			DIRECTX9_CAMERAS_FREE(
				LPDIRECT3DDEVICE9& _device, WORLDPOSITION& _position, WORLDPOSITION& _look, WORLDPOSITION& _up, WORLDPOSITION * _positionBinded = NULL,
				float _angle_Of_View = 75.0f, float _resolution_Of_Screen = 4.0f / 3.0f, float _starting_Point = 0.1f, float _ending_Point = 1000.0f );

			TEMPLATEMATRIX GetViewMatrix();
			void GetViewMatrix( D3DXMATRIX& );
			TEMPLATEMATRIX GetProjectionMatrix();
			void GetProjectionMatrix( D3DXMATRIX & );
			void GetWorldCameraMatrix( D3DXMATRIX & );

			void setCameraMatrixView( void * _renderer, MATRIX_TYPES _matrixType );

			void setCameraRoll( float angle );
			void setCameraPitch( float angle );
			void setCameraYaw( float angle );

			void setCameraYawPitchRoll( float _angleX, float _angleY, float _angleZ );
		};
	class DIRECTX9_CAMERAS_TARGET : public DIRECTX9_CAMERAS, public DIRECTX_CAMERAS_TARGET
		{
		public:
			DIRECTX9_CAMERAS_TARGET(
				LPDIRECT3DDEVICE9& _device, WORLDPOSITION& _position, WORLDPOSITION& _target, WORLDPOSITION& _up,
				WORLDPOSITION * _positionBinded = NULL, WORLDPOSITION * _targetBinded = NULL, WORLDPOSITION * _upBinded = NULL,
				float _angle_Of_View = 75.0f, float _resolution_Of_Screen = 4.0f / 3.0f, float _starting_Point = 0.1f, float _ending_Point = 1000.0f );

			TEMPLATEMATRIX GetViewMatrix();
			TEMPLATEMATRIX GetProjectionMatrix();

			void setCameraYawPitchRoll( float _angleX, float _angleY, float _angleZ );

			void setCameraMatrixView( void * _renderer, MATRIX_TYPES _matrixType );
		};
	};

#endif