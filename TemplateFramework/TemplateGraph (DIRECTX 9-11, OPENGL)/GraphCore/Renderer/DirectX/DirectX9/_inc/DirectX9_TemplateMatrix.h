#pragma once
#ifndef DirectX9TemplateMatrixHeader
#define DirectX9TemplateMatrixHeader

#include <d3dx9.h>
#include "../../../../_inc/TemplateMatrix.h"
#include "../../../../_inc/WorldPosition.h"

namespace GRAPHCORE
	{
	class DIRECTX9_TEMPLATEMATRIX : public TEMPLATEMATRIX
		{
		public:
			DIRECTX9_TEMPLATEMATRIX( float m00 = 1.0f, float m01 = 0.0f, float m02 = 0.0f, float m03 = 0.0f,
									 float m10 = 0.0f, float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f,
									 float m20 = 0.0f, float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f,
									 float m30 = 0.0f, float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f );
			DIRECTX9_TEMPLATEMATRIX( const D3DXMATRIX const &_matrix );
			DIRECTX9_TEMPLATEMATRIX( const TEMPLATEMATRIX const &_matrix );
			~DIRECTX9_TEMPLATEMATRIX();

			void operator=( const TEMPLATEMATRIX const &_matrix );
			void operator*( const WORLDPOSITION const &_vector );
			void operator=( const D3DXMATRIX const &_matrix );
			D3DXMATRIX GetMatrix() const;
			static D3DXMATRIX GetMatrix( const TEMPLATEMATRIX const &_matrix );
		};
	};

#endif