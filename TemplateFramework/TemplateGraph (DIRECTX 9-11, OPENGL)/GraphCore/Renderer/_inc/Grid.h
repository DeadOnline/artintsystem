#pragma once
#ifndef GridHeader
#define GridHeader

#include "Globals.h"

namespace GRAPHCORE
	{
	class GLOBALS;

	class GRID : public SINGLETONS
		{
		public:
			virtual	void	deleteInstance();

			virtual void Fill_Grid( GLOBALS * _globals, int _size = 100, float _cellSize = 100, DWORD _newColor = 0 ) = 0;
			void setID( int _geometryID );
			const int& getID() const;
			virtual void Render( void * const _globals ) const = 0;

		protected:
			int geometryID;
			static GRID * Object;

			GRID();
			GRID( const GRID& root );
			~GRID();
			GRID& operator=( const GRID& );			
		};
	};

#endif