#include "../_inc/DirectX9_TemplateMatrix.h"

using namespace GRAPHCORE;

#pragma region DIRECTX9_TEMPLATEMATRIX
//-----------------------------------DIRECTX9_TEMPLATEMATRIX-----------------------------------//
DIRECTX9_TEMPLATEMATRIX::DIRECTX9_TEMPLATEMATRIX( float _m00, float _m01, float _m02, float _m03,
												  float _m10, float _m11, float _m12, float _m13,
												  float _m20, float _m21, float _m22, float _m23,
												  float _m30, float _m31, float _m32, float _m33 ) :
												  TEMPLATEMATRIX(
												  _m00, _m01, _m02, _m03,
												  _m10, _m11, _m12, _m13,
												  _m20, _m21, _m22, _m23,
												  _m30, _m31, _m32, _m33 )
	{};
DIRECTX9_TEMPLATEMATRIX::DIRECTX9_TEMPLATEMATRIX( const D3DXMATRIX const &_matrix ) :
TEMPLATEMATRIX(
_matrix._11, _matrix._12, _matrix._13, _matrix._14,
_matrix._21, _matrix._22, _matrix._23, _matrix._24,
_matrix._31, _matrix._32, _matrix._33, _matrix._34,
_matrix._41, _matrix._42, _matrix._43, _matrix._44 )
	{};
DIRECTX9_TEMPLATEMATRIX::DIRECTX9_TEMPLATEMATRIX( const TEMPLATEMATRIX const &_matrix ) :
TEMPLATEMATRIX( _matrix )
	{};
DIRECTX9_TEMPLATEMATRIX::~DIRECTX9_TEMPLATEMATRIX() {};

void DIRECTX9_TEMPLATEMATRIX::operator=( const TEMPLATEMATRIX const &_matrix )
	{
	*( ( TEMPLATEMATRIX * ) this ) = _matrix;
	/*m00 = _matrix.m00; m01 = _matrix.m01; m02 = _matrix.m02; m03 = _matrix.m03;
	m10 = _matrix.m10; m11 = _matrix.m11; m12 = _matrix.m12; m13 = _matrix.m13;
	m20 = _matrix.m20; m21 = _matrix.m21; m22 = _matrix.m22; m23 = _matrix.m23;
	m30 = _matrix.m30; m31 = _matrix.m31; m32 = _matrix.m32; m33 = _matrix.m33;*/
	};
void DIRECTX9_TEMPLATEMATRIX::operator=( const D3DXMATRIX const &_matrix )
	{
	m00 = _matrix._11; m01 = _matrix._12; m02 = _matrix._13; m03 = _matrix._14;
	m10 = _matrix._21; m11 = _matrix._22; m12 = _matrix._23; m13 = _matrix._24;
	m20 = _matrix._31; m21 = _matrix._32; m22 = _matrix._33; m23 = _matrix._34;
	m30 = _matrix._41; m31 = _matrix._42; m32 = _matrix._43; m33 = _matrix._44;
	};

D3DXMATRIX DIRECTX9_TEMPLATEMATRIX::GetMatrix() const
	{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity( &matrix );

	matrix._11 = m00; matrix._12 = m01; matrix._13 = m02; matrix._14 = m03;
	matrix._21 = m10; matrix._22 = m11; matrix._23 = m12; matrix._24 = m13;
	matrix._31 = m20; matrix._32 = m21; matrix._33 = m22; matrix._34 = m23;
	matrix._41 = m30; matrix._42 = m31; matrix._43 = m32; matrix._44 = m33;

	return matrix;
	}
D3DXMATRIX DIRECTX9_TEMPLATEMATRIX::GetMatrix( const TEMPLATEMATRIX const &_matrix )
	{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity( &matrix );

	matrix._11 = _matrix.m00; matrix._12 = _matrix.m01; matrix._13 = _matrix.m02; matrix._14 = _matrix.m03;
	matrix._21 = _matrix.m10; matrix._22 = _matrix.m11; matrix._23 = _matrix.m12; matrix._24 = _matrix.m13;
	matrix._31 = _matrix.m20; matrix._32 = _matrix.m21; matrix._33 = _matrix.m22; matrix._34 = _matrix.m23;
	matrix._41 = _matrix.m30; matrix._42 = _matrix.m31; matrix._43 = _matrix.m32; matrix._44 = _matrix.m33;

	return matrix;
	}
//----------------------------------~DIRECTX9_TEMPLATEMATRIX-----------------------------------//  
#pragma endregion