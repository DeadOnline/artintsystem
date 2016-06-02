#include "../_inc/DirectX.h"

#pragma region DIRECTX
//------------------------------------------------------------------------------DIRECTX-------------------------------------------------------------------------------//
using namespace GRAPHCORE;

DIRECTX::DIRECTX() 
{ };

DIRECTX::~DIRECTX()
{ };

HRESULT	 DIRECTX::AssignToCamera(CAMERAS * _targetCamera, CAMERAS * _sourceCamera)
{
	_targetCamera = _sourceCamera;
	return S_OK;
};
//-----------------------------------------------------------------------------~DIRECTX-------------------------------------------------------------------------------//  
#pragma endregion

HRESULT GRAPHCORE::DIRECTX::Render ()
	{
	return E_NOTIMPL;
	}
