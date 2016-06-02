#include "../_inc/DirectX9_Materials.h"

using namespace GRAPHCORE;

#pragma region DIRECTX9_MATERIALS
//-----------------------------------DIRECTX9_MATERIALS-----------------------------------//
DIRECTX9_MATERIALS::DIRECTX9_MATERIALS(D3DMATERIAL9	* _material) : DIRECTX_MATERIALS(), material(_material)
	{
	};
DIRECTX9_MATERIALS::~DIRECTX9_MATERIALS()
	{
	OBJDELETE(material);
	};

void DIRECTX9_MATERIALS::SetMaterial( const void * _renderer ) const
	{
	( *( LPDIRECT3DDEVICE9 * ) &_renderer )->SetMaterial( material );
	};
//----------------------------------~DIRECTX9_MATERIALS-----------------------------------//  
#pragma endregion