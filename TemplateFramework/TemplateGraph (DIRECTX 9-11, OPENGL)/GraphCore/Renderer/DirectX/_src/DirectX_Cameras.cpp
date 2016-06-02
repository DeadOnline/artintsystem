#include "../_inc/DirectX_Cameras.h"

using namespace GRAPHCORE;

#pragma region DIRECTX_CAMERAS
//-----------------------------------DIRECTX_CAMERAS-----------------------------------//
DIRECTX_CAMERAS::DIRECTX_CAMERAS()
{ };
//----------------------------------~DIRECTX_CAMERAS-----------------------------------//
#pragma endregion
#pragma region DIRECTX_CAMERAS_FREE
//-----------------------------------DIRECTX_CAMERAS_FREE-----------------------------------//
DIRECTX_CAMERAS_FREE::DIRECTX_CAMERAS_FREE(WORLDPOSITION& _position, WORLDPOSITION& _look, WORLDPOSITION& _up, WORLDPOSITION * _positionBind,
	float _angle_Of_View, float _resolution_Of_Screen, float _starting_Point, float _ending_Point) :
	CAMERAS_FREE(_position, _look, _up, _positionBind, _angle_Of_View, _resolution_Of_Screen, _starting_Point, _ending_Point)
{ };
void			DIRECTX_CAMERAS_FREE::setCameraStrafe(WORLDPOSITION& _direction, float _units)
{
	WORLDPOSITION rightStatic(
		targetStatic.GetYDefault()*upStatic.GetZDefault() - targetStatic.GetZDefault()*upStatic.GetYDefault(),
		targetStatic.GetZDefault()*upStatic.GetXDefault() - targetStatic.GetXDefault()*upStatic.GetZDefault(),
		targetStatic.GetXDefault()*upStatic.GetYDefault() - targetStatic.GetYDefault()*upStatic.GetXDefault());
	positionStatic += targetStatic * _direction.GetXDefault() * _units;
	positionStatic += rightStatic * _direction.GetZDefault() * _units;
};
void			DIRECTX_CAMERAS_FREE::setCameraWalk(WORLDPOSITION& _direction, float _units)
{
	WORLDPOSITION Temp(0.0f, 0.0f, 1.0f);
	//float dot = (Temp.x * targetStatic.x) + (Temp.z * targetStatic.z);
	//	targetStatic += _direction * _angle;
	//	
	//	}

	//	

	//

	//D3DXVec3Normalize(&Temp2, &Temp2);

	//positionStatic += targetStatic * _units;
};
void			DIRECTX_CAMERAS_FREE::setCameraElevate(WORLDPOSITION& _direction, float _units)
{
	//eyeY += direction * sin(anglePitch + PI/2) * MOVE_SPEED;
	// eyeZ += direction * -cos(angleYaw + PI/2) * MOVE_SPEED;
};

void			DIRECTX_CAMERAS_FREE::setCameraRoll(float angle)
{
	//Set function
};
void			DIRECTX_CAMERAS_FREE::setCameraYaw(float angle)
{

};
void			DIRECTX_CAMERAS_FREE::setCameraPitch(float angle)
{

};
void			DIRECTX_CAMERAS_FREE::setCameraYawPitchRoll(float _angleX, float _angleY, float _angleZ)
{

};

void			DIRECTX_CAMERAS_FREE::CameraMovesAround(float _speed)
{
	//float angle = float(D3DXToRadian(object_Rotate_Presentation));
	//float Radius = sqrt(positionStatic.x*positionStatic.x + positionStatic.z*positionStatic.z);

	//object_Rotate_Presentation -= Speed;
	//( !object_Rotate_Presentation ) ? object_Rotate_Presentation = 360 : 0;

	//positionStatic.x = Radius*sin(angle);
	//positionStatic.z = Radius*cos(angle);

	//SetCameraMatrix(_device, World);
};
void			DIRECTX_CAMERAS_FREE::CameraMovesUp(float _units)
{
	/*camera_Height_Presentation -= 0.7f;
	( camera_Height_Presentation <= 0 ) ? camera_Height_Presentation = 0.0f : 0;
	positionStatic.y += float(cos(D3DXToRadian(90.0f - camera_Height_Presentation))) * 3.0f;
	SetCameraMatrix(_device, World);*/
};
void			DIRECTX_CAMERAS_FREE::CameraMovesTo(float _x, float _x1, float _z, float _z1, float _y)
{
	//if ( !camera_Height_Presentation ) camera_Height_Presentation = 45;
	//positionStatic.x += ( X - positionStatic.x ) / camera_Height_Presentation;
	//positionStatic.y += ( Y - positionStatic.y ) / camera_Height_Presentation;
	//positionStatic.z += ( Z - positionStatic.z ) / camera_Height_Presentation;
	////targetStatic.x += ( X1 - targetStatic.x ) / camera_Height_Presentation;
	////targetStatic.z += ( Z1 - targetStatic.z ) / camera_Height_Presentation;
	//SetCameraMatrix(_device, World);
	//camera_Height_Presentation--
};
//----------------------------------~DIRECTX_CAMERAS_FREE-----------------------------------//
#pragma endregion
#pragma region DIRECTX_CAMERAS_TARGET
//-----------------------------------DIRECTX_CAMERAS_TARGET-----------------------------------//
DIRECTX_CAMERAS_TARGET::DIRECTX_CAMERAS_TARGET(WORLDPOSITION& _position, WORLDPOSITION& _target, WORLDPOSITION& _up,
	WORLDPOSITION  * _positionBinded, WORLDPOSITION * _targetBinded, WORLDPOSITION * _upBinded,
	float _angle_Of_View, float _resolution_Of_Screen, float _starting_Point, float _ending_Point) :
	CAMERAS_TARGET(_position, _target, _up, _positionBinded, _targetBinded, _upBinded, _angle_Of_View, _resolution_Of_Screen, _starting_Point, _ending_Point)
{ };

void			DIRECTX_CAMERAS_TARGET::setCameraStrafe(WORLDPOSITION& _direction, float _units)
{
	//D3DXVECTOR3 Temp(_direction.GetXDefault(), _direction.GetYDefault(), _direction.GetZDefault());
	//D3DXVec3Normalize(&Temp, &Temp);
	//positionStatic += WORLDPOSITION(Temp) * _units;
};
void			DIRECTX_CAMERAS_TARGET::setCameraWalk(WORLDPOSITION& _direction, float _units)
{
	//D3DXVECTOR3 Temp1(_direction.x, _direction.y, _direction.z);
	//D3DXVECTOR3 Temp2(targetStatic.x, targetStatic.y, targetStatic.z);
	//D3DXVec3Normalize(&Temp1, &Temp1);
	//D3DXVec3Normalize(&Temp2, &Temp2);
	//Temp2 += Temp1 * _angle;
	//D3DXVec3Normalize(&Temp2, &Temp2);
	//positionStatic += targetStatic * _units;
};
void			DIRECTX_CAMERAS_TARGET::setCameraElevate(WORLDPOSITION& _direction, float _units)
{
	//eyeY += direction * sin(anglePitch + PI/2) * MOVE_SPEED;
	// eyeZ += direction * -cos(angleYaw + PI/2) * MOVE_SPEED;
};

void			DIRECTX_CAMERAS_TARGET::setCameraRoll(float angle)
{

};
void			DIRECTX_CAMERAS_TARGET::setCameraPitch(float angle)
{
	//Camera_Vector_Pitch += angle*0.5f;
}; // вращение относительно правого вектора
void			DIRECTX_CAMERAS_TARGET::setCameraYaw(float angle)
{
	//Camera_Vector_Yaw += angle*0.5f;
};   // вращение относительно верхнего вектора

void			DIRECTX_CAMERAS_TARGET::CameraMovesAround(float _speed)
{
	//float angle = float(D3DXToRadian(object_Rotate_Presentation));
	//float Radius = sqrt(positionStatic.x*positionStatic.x + positionStatic.z*positionStatic.z);
	//object_Rotate_Presentation -= Speed;
	//( !object_Rotate_Presentation ) ? object_Rotate_Presentation = 360 : 0;
	//positionStatic.x = Radius*sin(angle);
	//positionStatic.z = Radius*cos(angle);
	//SetCameraMatrix(_device, World);
};
void			DIRECTX_CAMERAS_TARGET::CameraMovesUp(float _units)
{
	/*camera_Height_Presentation -= 0.7f;
	( camera_Height_Presentation <= 0 ) ? camera_Height_Presentation = 0.0f : 0;
	positionStatic.y += float(cos(D3DXToRadian(90.0f - camera_Height_Presentation))) * 3.0f;
	SetCameraMatrix(_device, World);*/
};
void			DIRECTX_CAMERAS_TARGET::CameraMovesTo(float _x, float _x1, float _z, float _z1, float _y)
{
	//if ( !camera_Height_Presentation ) camera_Height_Presentation = 45;
	//positionStatic.x += ( X - positionStatic.x ) / camera_Height_Presentation;
	//positionStatic.y += ( Y - positionStatic.y ) / camera_Height_Presentation;
	//positionStatic.z += ( Z - positionStatic.z ) / camera_Height_Presentation;
	////targetStatic.x += ( X1 - targetStatic.x ) / camera_Height_Presentation;
	////targetStatic.z += ( Z1 - targetStatic.z ) / camera_Height_Presentation;
	//SetCameraMatrix(_device, World);
	//camera_Height_Presentation--
};
//----------------------------------~DIRECTX_CAMERAS_TARGET-----------------------------------//  
#pragma endregion