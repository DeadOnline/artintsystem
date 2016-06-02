#pragma once
#ifndef DirectX9SkyMapHeader
#define DirectX9SkyMapHeader

#include "DirectX9_Globals.h"

namespace GRAPHCORE
	{
	class DIRECTX9_GLOBALS;

	class DIRECTX9_SKYMAP : public SINGLETONS
		{
		public:
			static	DIRECTX9_SKYMAP *	Instance();
			virtual	void				deleteInstance ();

			void Set_SkyMap( LPDIRECT3DDEVICE9 _device );

		protected:
			static int geometryID;

			LPDIRECT3DVERTEXBUFFER9 SKYMAPBUFFER;

			DIRECTX9_SKYMAP();
			DIRECTX9_SKYMAP( const DIRECTX9_SKYMAP& root );
			~DIRECTX9_SKYMAP();
			DIRECTX9_SKYMAP& operator=( const DIRECTX9_SKYMAP& );

		private:
			void Render( void * const _globals ) const;
		};
	};

#endif