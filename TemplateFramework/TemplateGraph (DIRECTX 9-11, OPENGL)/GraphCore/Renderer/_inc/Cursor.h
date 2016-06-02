#pragma once
#ifndef CursorHeader
#define CursorHeader

#include "Globals.h"

namespace GRAPHCORE
	{
	class GLOBALS;

	class CURSOR : public SINGLETONS
		{
		public:
			virtual		void deleteInstance ();
			virtual		void Render(  void * const _globals ) const = 0;
						void ChangeCursorTexture (const int _textureID);
						void ChangeCursorCoords( const int _x, const int _y );
						
		protected:
			static		CURSOR * Object;
			static		int textureID;

			CURSOR();
			CURSOR( const CURSOR& root );
			~CURSOR();
			CURSOR& operator=( const CURSOR& );
		};
	};

#endif