#pragma once
#ifndef DirectX9FrustumHeader
#define DirectX9FrustumHeader

#include "../../_inc/DirectX_Frustum.h"

#include "DirectX9_Globals.h"

namespace GRAPHCORE
	{
	class DIRECTX9_FRUSTUM : public DIRECTX_FRUSTUM
		{
		public:
			void ConstructFrustum( CAMERAS * _currentCamera );

			bool CheckPoint( float x, float y, float z );
			bool CheckCube( float xCenter, float yCenter, float zCenter, float size );
			bool CheckSphere( const float xCenter, const float yCenter, const float zCenter, const float radius );
			bool CheckRectangle( float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize );

			float&	  GetXna();
			float&	  GetYna();
			float&	  GetZna();
			float&	  GetXnb();
			float&	  GetYnb();
			float&	  GetZnb();

			float&	  GetXn();
			float&	  GetXf();
			float&	  GetXl();
			float&	  GetXr();
			float&	  GetXt();
			float&	  GetXb();

			float&	  GetYn();
			float&	  GetYf();
			float&	  GetYl();
			float&	  GetYr();
			float&	  GetYt();
			float&	  GetYb();

			float&	  GetZn();
			float&	  GetZf();
			float&	  GetZl();
			float&	  GetZr();
			float&	  GetZt();
			float&	  GetZb();
		};
	};

#endif