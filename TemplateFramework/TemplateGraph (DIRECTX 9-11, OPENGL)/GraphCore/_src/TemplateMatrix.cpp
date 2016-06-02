#include "../_inc/TemplateMatrix.h"

#pragma region TEMPLATEMATRIX
//----------------------------------TEMPLATEMATRIX----------------------------------//
using namespace GRAPHCORE;

TEMPLATEMATRIX::TEMPLATEMATRIX( float _m00, float _m01, float _m02, float _m03,
								float _m10, float _m11, float _m12, float _m13,
								float _m20, float _m21, float _m22, float _m23,
								float _m30, float _m31, float _m32, float _m33 ) : 
								m00( _m00 ), m01( _m01 ), m02( _m02 ), m03( _m03 ),
								m10( _m10 ), m11( _m11 ), m12( _m12 ), m13( _m13 ),
								m20( _m20 ), m21( _m21 ), m22( _m22 ), m23( _m23 ),
								m30( _m30 ), m31( _m31 ), m32( _m32 ), m33( _m33 ) {};



//---------------------------------~TEMPLATEMATRIX----------------------------------//  
#pragma endregion