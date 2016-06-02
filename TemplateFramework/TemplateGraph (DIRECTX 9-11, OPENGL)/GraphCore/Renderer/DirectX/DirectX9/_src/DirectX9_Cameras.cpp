#include "../_inc/DirectX9_Cameras.h"

using namespace GRAPHCORE;

#pragma region DIRECTX9_CAMERAS
//------------------------------------DIRECTX9_CAMERAS------------------------------------//
DIRECTX9_CAMERAS::DIRECTX9_CAMERAS( LPDIRECT3DDEVICE9& _device, float _object_Rotate_Presentation, float _camera_Height_Presentation ) :
device( _device ), object_Rotate_Presentation( _object_Rotate_Presentation ), camera_Height_Presentation( _camera_Height_Presentation )
	{};
DIRECTX9_CAMERAS::~DIRECTX9_CAMERAS()
	{};
//-----------------------------------~DIRECTX9_CAMERAS------------------------------------//  
#pragma endregion
#pragma region DIRECTX9_CAMERAS_FREE
//------------------------------------DIRECTX9_CAMERAS_FREE------------------------------------//
DIRECTX9_CAMERAS_FREE::DIRECTX9_CAMERAS_FREE( LPDIRECT3DDEVICE9& _device, WORLDPOSITION& _position, WORLDPOSITION& _look, WORLDPOSITION& _up, WORLDPOSITION * _positionBinded,
											  float _angle_Of_View, float _resolution_Of_Screen, float _starting_Point, float _ending_Point ) :
											  DIRECTX9_CAMERAS( _device ),
											  DIRECTX_CAMERAS_FREE( _position, _look, _up, _positionBinded, _angle_Of_View, _resolution_Of_Screen, _starting_Point, _ending_Point )
	{};

TEMPLATEMATRIX DIRECTX9_CAMERAS_FREE::GetViewMatrix()
	{
	D3DXMATRIX CameraMatrix;
	D3DXMatrixLookAtLH( &CameraMatrix,
						&D3DXVECTOR3( positionStatic.GetXDefault(), positionStatic.GetYDefault(), positionStatic.GetZDefault() ),
						&D3DXVECTOR3( targetStatic.GetXDefault(), targetStatic.GetYDefault(), targetStatic.GetZDefault() ),
						&D3DXVECTOR3( upStatic.GetXDefault(), upStatic.GetYDefault(), upStatic.GetZDefault() ) );

	return DIRECTX9_TEMPLATEMATRIX( CameraMatrix );
	};
void DIRECTX9_CAMERAS_FREE::GetViewMatrix( D3DXMATRIX & _viewMatrix )
	{
	D3DXMatrixLookAtLH( &_viewMatrix,
						&D3DXVECTOR3( positionStatic.GetXDefault(), positionStatic.GetYDefault(), positionStatic.GetZDefault() ),
						&D3DXVECTOR3( targetStatic.GetXDefault(), targetStatic.GetYDefault(), targetStatic.GetZDefault() ),
						&D3DXVECTOR3( upStatic.GetXDefault(), upStatic.GetYDefault(), upStatic.GetZDefault() ) );
	};
void DIRECTX9_CAMERAS_FREE::GetProjectionMatrix( D3DXMATRIX & _projectionMatrix )
	{
	D3DXMatrixPerspectiveFovLH( &_projectionMatrix, angle_Of_View, resolution_Of_Screen, starting_Point, ending_Point );
	};
void DIRECTX9_CAMERAS_FREE::GetWorldCameraMatrix( D3DXMATRIX & _worldMatrix)
	{
	D3DXMatrixIdentity( &_worldMatrix );

	D3DXVECTOR3 right, target, up;
	target.x = targetStatic.GetXDefault(); target.y = targetStatic.GetYDefault(); target.z = targetStatic.GetZDefault();
	up.x = upStatic.GetXDefault(); up.y = upStatic.GetYDefault(); up.z = upStatic.GetZDefault();
	D3DXVec3Cross( &right, &target, &up );

	_worldMatrix._11 = right.x; _worldMatrix._12 = up.x; _worldMatrix._13 = target.x;
	_worldMatrix._21 = right.y; _worldMatrix._22 = up.y; _worldMatrix._23 = target.y;
	_worldMatrix._31 = right.z; _worldMatrix._32 = up.z; _worldMatrix._33 = target.z;
	_worldMatrix._41 = positionStatic.GetXDefault(); _worldMatrix._42 = positionStatic.GetYDefault(); _worldMatrix._43 = positionStatic.GetZDefault();
	};

TEMPLATEMATRIX DIRECTX9_CAMERAS_FREE::GetProjectionMatrix()
	{
	D3DXMATRIX CameraMatrix;
	D3DXMatrixPerspectiveFovLH( &CameraMatrix, angle_Of_View, resolution_Of_Screen, starting_Point, ending_Point );
	return DIRECTX9_TEMPLATEMATRIX( CameraMatrix );
	};

void DIRECTX9_CAMERAS_FREE::setCameraRoll( float angle )
	{

	};
void DIRECTX9_CAMERAS_FREE::setCameraPitch( float _angle )
	{
	D3DXMATRIX CameraMatrix;
	D3DXMatrixIdentity( &CameraMatrix );
	D3DXVECTOR3 rightVector;
	D3DXVECTOR3 upVector = D3DXVECTOR3( upStatic.GetXDefault(), upStatic.GetYDefault(), upStatic.GetZDefault() ),
		lookVector = D3DXVECTOR3( targetStatic.GetXDefault(), targetStatic.GetYDefault(), targetStatic.GetZDefault() );
	D3DXVec3Cross( &rightVector, &upVector, &lookVector );

	D3DXMatrixRotationAxis( &CameraMatrix, &rightVector, -_angle );
	D3DXVec3TransformCoord( &upVector, &upVector, &CameraMatrix );
	D3DXVec3TransformCoord( &lookVector, &lookVector, &CameraMatrix );

	upStatic.SetXDefault( upVector.x ); upStatic.SetYDefault( upVector.y ); upStatic.SetZDefault( upVector.z );
	targetStatic.SetXDefault( lookVector.x ); targetStatic.SetYDefault( lookVector.y ); targetStatic.SetZDefault( lookVector.z );
	upStatic.UnbindCoords();
	targetStatic.UnbindCoords();
	};
void DIRECTX9_CAMERAS_FREE::setCameraYaw( float _angle )
	{
	D3DXMATRIX CameraMatrix;
	D3DXMatrixIdentity( &CameraMatrix );
	D3DXVECTOR3 rightVector;
	D3DXVECTOR3 upVector = D3DXVECTOR3( upStatic.GetXDefault(), upStatic.GetYDefault(), upStatic.GetZDefault() ),
		lookVector = D3DXVECTOR3( targetStatic.GetXDefault(), targetStatic.GetYDefault(), targetStatic.GetZDefault() );
	D3DXVec3Cross( &rightVector, &upVector, &lookVector );

	D3DXMatrixRotationY( &CameraMatrix, -_angle );
	D3DXVec3TransformCoord( &lookVector, &lookVector, &CameraMatrix );
	D3DXVec3TransformCoord( &upVector, &upVector, &CameraMatrix );

	upStatic.SetXDefault( upVector.x ); upStatic.SetYDefault( upVector.y ); upStatic.SetZDefault( upVector.z );
	targetStatic.SetXDefault( lookVector.x ); targetStatic.SetYDefault( lookVector.y ); targetStatic.SetZDefault( lookVector.z );
	upStatic.UnbindCoords();
	targetStatic.UnbindCoords();
	};

void DIRECTX9_CAMERAS_FREE::setCameraYawPitchRoll( float _angleX, float _angleY, float _angleZ )
	{
	D3DXMATRIX FinalMatrix;
	D3DXVECTOR3 rightVector;
	D3DXVECTOR3 upVector = D3DXVECTOR3( upStatic.GetXDefault(), upStatic.GetYDefault(), upStatic.GetZDefault() ),
		lookVector = D3DXVECTOR3( targetStatic.GetXDefault(), targetStatic.GetYDefault(), targetStatic.GetZDefault() );
	D3DXVec3Cross( &rightVector, &upVector, &lookVector );

	/////////////////INTERMEDIATE MATRICES///////////////
	D3DXMatrixRotationAxis( &FinalMatrix, &rightVector, _angleY );

	D3DXVec3TransformCoord( &lookVector, &lookVector, &FinalMatrix );
	D3DXVec3TransformCoord( &upVector, &upVector, &FinalMatrix );

	D3DXMatrixRotationY( &FinalMatrix, -_angleX );

	D3DXVec3TransformCoord( &lookVector, &lookVector, &FinalMatrix );
	D3DXVec3TransformCoord( &upVector, &upVector, &FinalMatrix );
	////////////////~INTERMEDIATE MATRICES///////////////

	upStatic.SetXDefault( upVector.x ); upStatic.SetYDefault( upVector.y ); upStatic.SetZDefault( upVector.z );
	targetStatic.SetXDefault( lookVector.x ); targetStatic.SetYDefault( lookVector.y ); targetStatic.SetZDefault( lookVector.z );
	upStatic.UnbindCoords();
	targetStatic.UnbindCoords();
	};

void	DIRECTX9_CAMERAS_FREE::setCameraMatrixView( void * _renderer, MATRIX_TYPES _matrixType )
	{
	D3DXMATRIX CameraMatrix;
	D3DXMatrixIdentity( &CameraMatrix );
	LPDIRECT3DDEVICE9 device = *( LPDIRECT3DDEVICE9 * ) &_renderer;

	positionStatic.UnbindCoords();
	targetStatic.UnbindCoords();
	upStatic.UnbindCoords();

	if ( _matrixType == View )
		{
		D3DXMatrixLookAtLH( &CameraMatrix,
							&D3DXVECTOR3(
							positionStatic.GetXDefault(),
							positionStatic.GetYDefault(),
							positionStatic.GetZDefault() ),
							&D3DXVECTOR3(
							targetStatic.GetXDefault() + positionStatic.GetXDefault(),
							targetStatic.GetYDefault() + positionStatic.GetYDefault(),
							targetStatic.GetZDefault() + positionStatic.GetZDefault() ),
							&D3DXVECTOR3
							( upStatic.GetXDefault(),
							upStatic.GetYDefault(),
							upStatic.GetZDefault() ) );
		device->SetTransform( D3DTS_VIEW, &CameraMatrix );
		}
	else
		{
		D3DXMatrixPerspectiveFovLH( &CameraMatrix, angle_Of_View, resolution_Of_Screen, starting_Point, ending_Point );
		device->SetTransform( D3DTS_PROJECTION, &CameraMatrix );
		};

	//D3DXMatrixRotationYawPitchRoll(&Camera_Matrix_Rotation, Camera_Vector_Yaw, Camera_Vector_Pitch, 0);
	//D3DXVec3TransformCoord(&Camera_Vector_Pos, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Camera_Matrix_Rotation);
	//D3DXVec3Normalize(&Camera_Vector_Pos, &Camera_Vector_Pos);
	//Camera_Vector_Pos = ( Camera_Vector_Pos * Camera_Target_Distance ) + *Camera_Vector_Pivot;

	//D3DXVec3Normalize(&Camera_Vector_Look, &( *Camera_Vector_Pivot - Camera_Vector_Pos ));
	//D3DXVec3Normalize(&Camera_Vector_Look, &Camera_Vector_Look);
	//Camera_Vector_Right = D3DXVECTOR3(-Camera_Vector_Look.z, 0.0f, Camera_Vector_Look.x);
	//D3DXVECTOR3 Temp = Camera_Vector_Pos - *Camera_Vector_Pivot; D3DXVec3Normalize(&Temp, &Temp);
	//D3DXVec3Cross(&Temp, &Temp, &Camera_Vector_Right);
	//Camera_Vector_Right = -Camera_Vector_Right;
	//D3DXVec3Normalize(&Camera_Vector_Up, &Temp);
	//D3DXMatrixLookAtLH(&Camera_Matrix_View, &Camera_Vector_Pos, Camera_Vector_Pivot, &Camera_Vector_Up);
	return;
	};
//-----------------------------------~DIRECTX9_CAMERAS_FREE------------------------------------//  
#pragma endregion
#pragma region DIRECTX9_CAMERAS_TARGET
//------------------------------------DIRECTX9_CAMERAS_TARGET------------------------------------//
DIRECTX9_CAMERAS_TARGET::DIRECTX9_CAMERAS_TARGET( LPDIRECT3DDEVICE9& _device, WORLDPOSITION& _position, WORLDPOSITION& _target, WORLDPOSITION& _up,
												  WORLDPOSITION * _positionBinded, WORLDPOSITION * _targetBinded, WORLDPOSITION * _upBinded,
												  float _angle_Of_View, float _resolution_Of_Screen, float _starting_Point, float _ending_Point ) :
												  DIRECTX9_CAMERAS( _device ),
												  DIRECTX_CAMERAS_TARGET( _position, _target, _up, _positionBinded, _targetBinded, _upBinded, _angle_Of_View, _resolution_Of_Screen, _starting_Point, _ending_Point )
	{};

TEMPLATEMATRIX DIRECTX9_CAMERAS_TARGET::GetViewMatrix()
	{
	return TEMPLATEMATRIX();
	};
TEMPLATEMATRIX DIRECTX9_CAMERAS_TARGET::GetProjectionMatrix()
	{
	return TEMPLATEMATRIX();
	};

void DIRECTX9_CAMERAS_TARGET::setCameraYawPitchRoll( float _angleX, float _angleY, float _angleZ )
	{
	//D3DXMATRIX CameraMatrix;
	//D3DXMatrixIdentity(&CameraMatrix);
	//D3DXVECTOR3 rightVector;
	//D3DXVECTOR3 upVector = D3DXVECTOR3(upStatic.GetXDefault(), upStatic.GetYDefault(), upStatic.GetZDefault()),
	//	lookVector = D3DXVECTOR3(targetStatic.GetXDefault(), targetStatic.GetYDefault(), targetStatic.GetZDefault());
	//D3DXVec3Cross(&rightVector, &upVector, &lookVector);

	//D3DXMatrixRotationYawPitchRoll(&CameraMatrix, _angleX, _angleY, _angleZ);
	};

void	DIRECTX9_CAMERAS_TARGET::setCameraMatrixView( void * _renderer, MATRIX_TYPES _matrixType )
	{
	D3DXMATRIX CameraMatrix;
	LPDIRECT3DDEVICE9 device = *( LPDIRECT3DDEVICE9 * ) _renderer;

	if ( _matrixType == View )
		{
		D3DXMatrixLookAtLH( &CameraMatrix, &D3DXVECTOR3( positionStatic.GetXDefault(), positionStatic.GetYDefault(), positionStatic.GetZDefault() ), &D3DXVECTOR3( targetStatic.GetXDefault(), targetStatic.GetYDefault(), targetStatic.GetZDefault() ), &D3DXVECTOR3( upStatic.GetXDefault(), upStatic.GetYDefault(), upStatic.GetZDefault() ) );
		device->SetTransform( D3DTS_VIEW, &CameraMatrix );
		}
	else
		{
		D3DXMatrixPerspectiveFovLH( &CameraMatrix, angle_Of_View, resolution_Of_Screen, starting_Point, ending_Point );
		device->SetTransform( D3DTS_PROJECTION, &CameraMatrix );
		};
	return;
	};
//-----------------------------------~DIRECTX9_CAMERAS_TARGET------------------------------------//  
#pragma endregion