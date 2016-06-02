#include "../_inc/DirectX9_Frustum.h"

using namespace GRAPHCORE;

#pragma region DIRECTX9_DIRECTX9_FRUSTUM
//-----------------------------------DIRECTX9_DIRECTX9_FRUSTUM-----------------------------------//

float&	  DIRECTX9_FRUSTUM::GetXn()
	{
	return rotationAngles[ 0 ][ 0 ];
	};
float&	  DIRECTX9_FRUSTUM::GetXf()
	{
	return rotationAngles[ 1 ][ 0 ];
	};
float&	  DIRECTX9_FRUSTUM::GetXl()
	{
	return rotationAngles[ 2 ][ 0 ];
	};
float&	  DIRECTX9_FRUSTUM::GetXr()
	{
	return rotationAngles[ 3 ][ 0 ];
	};
float&	  DIRECTX9_FRUSTUM::GetXt()
	{
	return rotationAngles[ 4 ][ 0 ];
	};
float&	  DIRECTX9_FRUSTUM::GetXb()
	{
	return rotationAngles[ 5 ][ 0 ];
	};
float&	  DIRECTX9_FRUSTUM::GetYn()
	{
	return rotationAngles[ 0 ][ 1 ];
	};
float&	  DIRECTX9_FRUSTUM::GetYf()
	{
	return rotationAngles[ 1 ][ 1 ];
	};
float&	  DIRECTX9_FRUSTUM::GetYl()
	{
	return rotationAngles[ 2 ][ 1 ];
	};
float&	  DIRECTX9_FRUSTUM::GetYr()
	{
	return rotationAngles[ 3 ][ 1 ];
	};
float&	  DIRECTX9_FRUSTUM::GetYt()
	{
	return rotationAngles[ 4 ][ 1 ];
	};
float&	  DIRECTX9_FRUSTUM::GetYb()
	{
	return rotationAngles[ 5 ][ 1 ];
	};
float&	  DIRECTX9_FRUSTUM::GetZn()
	{
	return rotationAngles[ 0 ][ 2 ];
	};
float&	  DIRECTX9_FRUSTUM::GetZf()
	{
	return rotationAngles[ 1 ][ 2 ];
	};
float&	  DIRECTX9_FRUSTUM::GetZl()
	{
	return rotationAngles[ 2 ][ 2 ];
	};
float&	  DIRECTX9_FRUSTUM::GetZr()
	{
	return rotationAngles[ 3 ][ 2 ];
	};
float&	  DIRECTX9_FRUSTUM::GetZt()
	{
	return rotationAngles[ 4 ][ 2 ];
	};
float&	  DIRECTX9_FRUSTUM::GetZb()
	{
	return rotationAngles[ 5 ][ 2 ];
	};

float&	  DIRECTX9_FRUSTUM::GetXna()
	{
	return planeVectors[ 0 ][ 0 ];
	};
float&	  DIRECTX9_FRUSTUM::GetYna()
	{
	return planeVectors[ 1 ][ 0 ];
	};
float&	  DIRECTX9_FRUSTUM::GetZna()
	{
	return planeVectors[ 2 ][ 0 ];
	};
float&	  DIRECTX9_FRUSTUM::GetXnb()
	{
	return planeVectors[ 0 ][ 1 ];
	};
float&	  DIRECTX9_FRUSTUM::GetYnb()
	{
	return planeVectors[ 1 ][ 1 ];
	};
float&	  DIRECTX9_FRUSTUM::GetZnb()
	{
	return planeVectors[ 2 ][ 1 ];
	};

void DIRECTX9_FRUSTUM::ConstructFrustum( CAMERAS * _currentCamera )
	{
	D3DXMATRIX D3DviewMatrix; D3DXMatrixIdentity( &D3DviewMatrix );
	D3DXMATRIX D3DprojMatrix; D3DXMatrixIdentity( &D3DprojMatrix );
	
	( ( DIRECTX9_CAMERAS_FREE * ) _currentCamera )->GetWorldCameraMatrix( D3DviewMatrix );
	( ( DIRECTX9_CAMERAS_FREE * ) _currentCamera )->GetProjectionMatrix( D3DprojMatrix );

	D3DXPLANE  D3DXplanes[ 6 ];

	//screenDepth = _currentCamera->GetEndPoint();
	//float g = _currentCamera->GetStartPoint();
	//// Вычисление минимальной дистации по Z в фрустуме.
	//float zMinimum = -D3DprojMatrix._43 / D3DprojMatrix._33;
	//float r = screenDepth / ( screenDepth - zMinimum );
	//D3DprojMatrix._33 = r;
	//D3DprojMatrix._43 = -r * zMinimum;

	// Создание матрицы фрустума из видовой и обновленой проекционной матриц.
	D3DXMATRIX frustumMatrix; D3DXMatrixIdentity( &frustumMatrix );
	D3DXMatrixMultiply( &frustumMatrix, &D3DviewMatrix, &D3DprojMatrix );

	float a = 0.0f, b = 0.0f, c = 0.0f, d = 0.0f;

	// Вычисление близкой (near) плоскости.
	a = frustumMatrix._14 + frustumMatrix._13;
	b = frustumMatrix._24 + frustumMatrix._23;
	c = frustumMatrix._34 + frustumMatrix._33;
	d = frustumMatrix._44 + frustumMatrix._43;
	D3DXplanes[ 0 ] = D3DXPLANE( a, b, c, d ); //0,1,0,2000
 	D3DXPlaneNormalize( &D3DXplanes[ 0 ], &D3DXplanes[ 0 ] );

	// Вычисление дальней (far) плоскости.
	a = frustumMatrix._14 - frustumMatrix._13;
	b = frustumMatrix._24 - frustumMatrix._23;
	c = frustumMatrix._34 - frustumMatrix._33;
	d = frustumMatrix._44 - frustumMatrix._43;
	D3DXplanes[ 1 ] = D3DXPLANE( a, b, c, d );
	D3DXPlaneNormalize( &D3DXplanes[ 1 ], &D3DXplanes[ 1 ] );

	// Вычисление левой (left) плоскости.
	a = frustumMatrix._14 + frustumMatrix._11;
	b = frustumMatrix._24 + frustumMatrix._21;
	c = frustumMatrix._34 + frustumMatrix._31;
	d = frustumMatrix._44 + frustumMatrix._41;
	D3DXplanes[ 2 ] = D3DXPLANE( a, b, c, d );
	D3DXPlaneNormalize( &D3DXplanes[ 2 ], &D3DXplanes[ 2 ] );

	// Вычисление правой (right) плоскости.
	a = frustumMatrix._14 - frustumMatrix._11;
	b = frustumMatrix._24 - frustumMatrix._21;
	c = frustumMatrix._34 - frustumMatrix._31;
	d = frustumMatrix._44 - frustumMatrix._41;
	D3DXplanes[ 3 ] = D3DXPLANE( a, b, c, d );
	D3DXPlaneNormalize( &D3DXplanes[ 3 ], &D3DXplanes[ 3 ] );

	// Вычисление верхней (top) плоскости.
	a = frustumMatrix._14 - frustumMatrix._12;
	b = frustumMatrix._24 - frustumMatrix._22;
	c = frustumMatrix._34 - frustumMatrix._32;
	d = frustumMatrix._44 - frustumMatrix._42;
	D3DXplanes[ 4 ] = D3DXPLANE( a, b, c, d );
	D3DXPlaneNormalize( &D3DXplanes[ 4 ], &D3DXplanes[ 4 ] );

	// Вычисление нижней (bottom) плоскости.
	a = frustumMatrix._14 + frustumMatrix._12;
	b = frustumMatrix._24 + frustumMatrix._22;
	c = frustumMatrix._34 + frustumMatrix._32;
	d = frustumMatrix._44 + frustumMatrix._42;
	D3DXplanes[ 5 ] = D3DXPLANE( a, b, c, d );
	D3DXPlaneNormalize( &D3DXplanes[ 5 ], &D3DXplanes[ 5 ] );

	for ( size_t i = 0; i < 6; i++ )
		{
		m_planes[0][ i ] = ( D3DXplanes[ i ].a );
		m_planes[1][ i ] = ( D3DXplanes[ i ].b );
		m_planes[2][ i ] = ( D3DXplanes[ i ].c );
		m_planes[3][ i ] = ( D3DXplanes[ i ].d );

		//planeVectors[ 0 ][ i ] = m_planes[0][ i ] * m_planes[3][ i ]; //Binded to camera, X
		//planeVectors[ 1 ][ i ] = m_planes[1][ i ] * m_planes[3][ i ]; //PROBLEM HERE
		//planeVectors[ 2 ][ i ] = m_planes[2][ i ] * m_planes[3][ i ]; //Binded to camera, Z

		//rotationAngles[ 0 ][ i ] = sqrt(
		//	m_planes[0][ i ] * m_planes[0][ i ] +
		//	m_planes[1][ i ] * m_planes[1][ i ] +
		//	m_planes[2][ i ] * m_planes[2][ i ] );

		//rotationAngles[ 1 ][ i ] = ( m_planes[0][ i ] )?atan( m_planes[1][ i ] / m_planes[0][ i ] ):0;
		//rotationAngles[ 2 ][ i ] = ( rotationAngles[ 0 ][ i ] )?atan( m_planes[2][ i ] / rotationAngles[ 0 ][ i ] ):0;
		}
	}
bool DIRECTX9_FRUSTUM::CheckPoint( float x, float y, float z )
	{
	D3DXVECTOR3 Set;
	D3DXPLANE Plane;
	for ( int i = 0; i < 6; i++ )
		{
		Set.x = x; Set.y = y; Set.z = z;
		Plane.a = m_planes[0][ i ];
		Plane.b = m_planes[1][ i ];
		Plane.c = m_planes[2][ i ];
		Plane.d = m_planes[3][ i ];

		float ret = D3DXPlaneDotCoord( &Plane, &Set );
		if ( ret < 0.0f )
			return false;
		}

	return true;
	}
bool DIRECTX9_FRUSTUM::CheckCube( float xCenter, float yCenter, float zCenter, float size )
	{
	D3DXPLANE Plane;
	for ( int i = 0; i < 6; i++ )
		{
		Plane.a = m_planes[0][ i ];
		Plane.b = m_planes[1][ i ];
		Plane.c = m_planes[2][ i ];
		Plane.d = m_planes[3][ i ];

		float ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter - size ), ( yCenter - size ), ( zCenter - size ) ) );
		if ( ret >= 0.0f )
			continue;

		ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter + size ), ( yCenter - size ), ( zCenter - size ) ) );
		if ( ret >= 0.0f )
			continue;

		ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter - size ), ( yCenter + size ), ( zCenter - size ) ) );
		if ( ret >= 0.0f )
			continue;

		ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter + size ), ( yCenter + size ), ( zCenter - size ) ) );
		if ( ret >= 0.0f )
			continue;

		ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter - size ), ( yCenter - size ), ( zCenter + size ) ) );
		if ( ret >= 0.0f )
			continue;

		ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter + size ), ( yCenter - size ), ( zCenter + size ) ) );
		if ( ret >= 0.0f )
			continue;

		ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter - size ), ( yCenter + size ), ( zCenter + size ) ) );
		if ( ret >= 0.0f )
			continue;

		ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter + size ), ( yCenter + size ), ( zCenter + size ) ) );
		if ( ret >= 0.0f )
			continue;

		return false;
		}

	return true;
	}
bool DIRECTX9_FRUSTUM::CheckSphere( const float xCenter, const float yCenter, const float zCenter, const float radius )
	{
	D3DXVECTOR3 Set;
	D3DXPLANE Plane;
	for ( int i = 0; i < 6; i++ )
		{
		Set.x = xCenter; Set.y = yCenter; Set.z = zCenter;

		Plane.a = m_planes[0][ i ];
		Plane.b = m_planes[1][ i ];
		Plane.c = m_planes[2][ i ];
		Plane.d = m_planes[3][ i ];

		float ret = D3DXPlaneDotCoord( &Plane, &Set );
		if ( ret < -radius )
			return false;
		}

	return true;
	}
bool DIRECTX9_FRUSTUM::CheckRectangle( float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize )
	{
	D3DXPLANE Plane;
	for ( int i = 0; i < 6; i++ )
		{
		Plane.a = m_planes[0][ i ];
		Plane.b = m_planes[1][ i ];
		Plane.c = m_planes[2][ i ];
		Plane.d = m_planes[3][ i ];

		float ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter - xSize ), ( yCenter - ySize ), ( zCenter - zSize ) ) );
		if ( ret >= 0.0f )
			continue;

		ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter + xSize ), ( yCenter - ySize ), ( zCenter - zSize ) ) );
		if ( ret >= 0.0f )
			continue;

		ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter - xSize ), ( yCenter + ySize ), ( zCenter - zSize ) ) );
		if ( ret >= 0.0f )
			continue;

		ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter - xSize ), ( yCenter - ySize ), ( zCenter + zSize ) ) );
		if ( ret >= 0.0f )
			continue;

		ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter + xSize ), ( yCenter + ySize ), ( zCenter - zSize ) ) );
		if ( ret >= 0.0f )
			continue;

		ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter + xSize ), ( yCenter - ySize ), ( zCenter + zSize ) ) );
		if ( ret >= 0.0f )
			continue;

		ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter - xSize ), ( yCenter + ySize ), ( zCenter + zSize ) ) );
		if ( ret >= 0.0f )
			continue;

		ret = D3DXPlaneDotCoord( &Plane, &D3DXVECTOR3( ( xCenter + xSize ), ( yCenter + ySize ), ( zCenter + zSize ) ) );
		if ( ret >= 0.0f )
			continue;

		return false;
		}

	return true;
	}
//-----------------------------------DIRECTX9_DIRECTX9_FRUSTUM-----------------------------------//  
#pragma endregion