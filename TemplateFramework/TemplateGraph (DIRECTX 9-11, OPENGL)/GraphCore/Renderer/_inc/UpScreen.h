#pragma once
#ifndef UpScreenHeader
#define UpScreenHeader

#include "Globals.h"

namespace GRAPHCORE
	{
	class GLOBALS;

	class UPSCREEN : public SINGLETONS
		{
		public:
			virtual		void deleteInstance();

			void ChangeUpScreenAlpha( const int _alpha );
			void ChangeUpScreenColor( const DEFAULT_COLORS _colors );
			void ChangeUpScreenTexture( const int _textureID );
			virtual void Render( void * const _globals ) const = 0;

		protected:
			int alpha, geometryID, textureID;
			static UPSCREEN * Object;

			UPSCREEN();
			UPSCREEN( const UPSCREEN& root );
			~UPSCREEN();
			UPSCREEN& operator=( const UPSCREEN& );			
		};
	};

#endif