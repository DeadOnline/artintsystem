#pragma once
#ifndef DirectX9CursorHeader
#define DirectX9CursorHeader

#include "../../_inc/DirectX_Cursor.h"

#include "DirectX9_Globals.h"

namespace GRAPHCORE
	{
	class DIRECTX9_GLOBALS;

	class DIRECTX9_CURSOR : public DIRECTX_CURSOR
		{
		protected:
			LPDIRECT3DVERTEXBUFFER9 CURSORBUFFER;

			DIRECTX9_CURSOR();
			DIRECTX9_CURSOR( const DIRECTX9_CURSOR& root );
			~DIRECTX9_CURSOR();
			DIRECTX9_CURSOR& operator=( const DIRECTX9_CURSOR& );

		public:
			static	DIRECTX9_CURSOR * Instance();
			virtual	void deleteInstance ();

			void	Render( void * _globals ) const;
			void	Set_Cursor( LPDIRECT3DDEVICE9 _devices, const int &_ID );
		};
	};

#endif