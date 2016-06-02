#include "../_inc/WorldPosition.h"

#pragma region WORLDPOSITION
//----------------------------------WORLDPOSITION----------------------------------//
using namespace GRAPHCORE;

WORLDPOSITION::WORLDPOSITION( float _x, float _y, float _z, float _w) : x( _x ), y( _y ), z( _z ), w( _w )
	{
	x_binded = &x;
	y_binded = &y;
	z_binded = &z;
	w_binded = &w;
	};
WORLDPOSITION::WORLDPOSITION( const WORLDPOSITION &_worldPosition )
	{
	InternalCopy( _worldPosition );
	}
void WORLDPOSITION::operator=( const WORLDPOSITION &_worldPosition )
	{
	InternalCopy( _worldPosition );
	}
void WORLDPOSITION::InternalCopy( const WORLDPOSITION &_worldPosition )
	{
	x = _worldPosition.x;
	y = _worldPosition.y;
	z = _worldPosition.z;
	w = _worldPosition.w;
	x_binded = &x;
	y_binded = &y;
	z_binded = &z;
	w_binded = &w;
	}
void	WORLDPOSITION::operator+=( const WORLDPOSITION &a )
	{
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;
	};
void	WORLDPOSITION::operator/=( const float _value )
	{
	x /= _value;
	y /= _value;
	z /= _value;
	w /= _value;
	};
WORLDPOSITION	WORLDPOSITION::operator*( const float _value )
	{
	return WORLDPOSITION( *x_binded * _value, *y_binded * _value, *z_binded * _value, *w_binded * _value );
	}
float& WORLDPOSITION::GetXBinded()
	{
	return *x_binded;
	};
float& WORLDPOSITION::GetYBinded()
	{
	return *y_binded;
	};
float& WORLDPOSITION::GetZBinded()
	{
	return *z_binded;
	};
float& WORLDPOSITION::GetWBinded()
	{
	return *w_binded;
	};
float WORLDPOSITION::GetXDefault()
	{
	return *x_binded;
	};
float WORLDPOSITION::GetYDefault()
	{
	return *y_binded;
	};
float WORLDPOSITION::GetZDefault()
	{
	return *z_binded;
	};
float WORLDPOSITION::GetWDefault()
	{
	return *w_binded;
	};
void	WORLDPOSITION::SetXDefault( float _x )
	{
	x = _x;
	};
void	WORLDPOSITION::SetYDefault( float _y )
	{
	y = _y;
	};
void	WORLDPOSITION::SetZDefault( float _z )
	{
	z = _z;
	};
void	WORLDPOSITION::SetWDefault( float _w )
	{
	w = _w;
	};
void	WORLDPOSITION::SetXBinded( float &_x )
	{
	x_binded = &_x;
	};
void	WORLDPOSITION::SetYBinded( float &_y )
	{
	y_binded = &_y;
	};
void	WORLDPOSITION::SetZBinded( float &_z )
	{
	z_binded = &_z;
	};
void	WORLDPOSITION::SetWBinded( float &_w )
	{
	w_binded = &_w;
	};
void	WORLDPOSITION::UnbindCoords()
	{
	x_binded = &x;
	y_binded = &y;
	z_binded = &z;
	w_binded = &w;
	};
//---------------------------------~WORLDPOSITION----------------------------------//  
#pragma endregion