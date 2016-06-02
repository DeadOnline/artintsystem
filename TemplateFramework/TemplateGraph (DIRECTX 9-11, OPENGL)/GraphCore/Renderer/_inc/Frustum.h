#pragma once
#ifndef FrustumHeader
#define FrustumHeader

#include "Cameras.h"
#include "../../_inc/WorldPosition.h"

namespace GRAPHCORE
	{
	class FRUSTUM
		{
		public:
			virtual void ConstructFrustum( CAMERAS * _currentCamera ) = 0;

			virtual bool CheckPoint( float x, float y, float z ) = 0;
			virtual bool CheckCube( float xCenter, float yCenter, float zCenter, float size ) = 0;
			virtual bool CheckSphere( const float xCenter, const float yCenter, const float zCenter, const float radius ) = 0;
			virtual bool CheckRectangle( float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize ) = 0;

			virtual float&	  GetXna() = 0;
			virtual float&	  GetYna() = 0;
			virtual float&	  GetZna() = 0;
			virtual float&	  GetXnb() = 0;
			virtual float&	  GetYnb() = 0;
			virtual float&	  GetZnb() = 0;

			virtual float&	  GetXn() = 0;
			virtual float&	  GetXf() = 0;
			virtual float&	  GetXl() = 0;
			virtual float&	  GetXr() = 0;
			virtual float&	  GetXt() = 0;
			virtual float&	  GetXb() = 0;

			virtual float&	  GetYn() = 0;
			virtual float&	  GetYf() = 0;
			virtual float&	  GetYl() = 0;
			virtual float&	  GetYr() = 0;
			virtual float&	  GetYt() = 0;
			virtual float&	  GetYb() = 0;

			virtual float&	  GetZn() = 0;
			virtual float&	  GetZf() = 0;
			virtual float&	  GetZl() = 0;
			virtual float&	  GetZr() = 0;
			virtual float&	  GetZt() = 0;
			virtual float&	  GetZb() = 0;

		protected: //TODO change back
		public:
			float m_planes[ 4 ][ 6 ];
			float rotationAngles[ 3 ][ 6 ];
			float planeVectors[ 3 ][ 6 ];
		};
	};

#endif