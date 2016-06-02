#pragma once
#ifndef DirectX9UpscreenHeader
#define DirectX9UpscreenHeader

#include "DirectX9_Globals.h"

namespace GRAPHCORE
{
	class DIRECTX9_GLOBALS;

	class DIRECTX9_UPSCREEN : public UPSCREEN
	{
	public:
		virtual	void				deleteInstance ();
		static	DIRECTX9_UPSCREEN * Instance();

			void	Fill_UpScreen(GLOBALS * _globals, const int _clientHeight, const int _clientWidth, const int _textureID);
			void	Change_UpScreenAlpha( int alpha );
			void	Render( void * const _globals ) const;
		
	protected:
		
		DIRECTX9_UPSCREEN();
		DIRECTX9_UPSCREEN(const DIRECTX9_UPSCREEN& root);
		~DIRECTX9_UPSCREEN();
		DIRECTX9_UPSCREEN& operator=(const DIRECTX9_UPSCREEN&);
	};
};

#endif