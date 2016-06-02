#pragma once
#ifndef DirectX9MaterialsHeader
#define DirectX9MaterialsHeader

#include "../../_inc/DirectX_Materials.h"

#include "DirectX9_Globals.h"

namespace GRAPHCORE
	{
	class DIRECTX9_MATERIALS : public DIRECTX_MATERIALS
		{
		protected:

			D3DMATERIAL9 *	material;

		public:
			///////////
			DIRECTX9_MATERIALS( D3DMATERIAL9 * _material );
			~DIRECTX9_MATERIALS();

			D3DMATERIAL9 *	Get_Material( string _path );
			HRESULT			Set_Material( string _path, D3DMATERIAL9 * _material );
			void			SetMaterial( const void * _renderer ) const;

		private:
			HRESULT			Load_Material( string _path, D3DMATERIAL9 _device );
		};
	};

#endif