#pragma once
#ifndef TemplateMatrixHeader
#define TemplateMatrixHeader

namespace GRAPHCORE
	{
	struct	TEMPLATEMATRIX
		{
		public:
			float	m00, m01, m02, m03,
					m10, m11, m12, m13,
					m20, m21, m22, m23,
					m30, m31, m32, m33;

			TEMPLATEMATRIX( float m00 = 1.0f, float m01 = 0.0f, float m02 = 0.0f, float m03 = 0.0f,
							float m10 = 0.0f, float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f,
							float m20 = 0.0f, float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f,
							float m30 = 0.0f, float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f );

			void operator+=( TEMPLATEMATRIX &a );
			void operator/=( float _value );

			TEMPLATEMATRIX operator*( float _value );

		};
	}

#endif