#pragma once
#ifndef DirectX9GridHeader
#define DirectX9GridHeader

#include "DirectX9_Globals.h"

namespace GRAPHCORE
	{
	class DIRECTX9_GLOBALS;

	class DIRECTX9_GRID : public GRID
		{
	public:
		static	DIRECTX9_GRID * Instance();
		virtual	void			deleteInstance();

				void Fill_Grid( GLOBALS * _globals, int _size = 100, float _cellSize = 100, DWORD _newColor = 0);
				void Render( void * const _globals ) const;

	protected:
		DIRECTX9_GRID();
		DIRECTX9_GRID(const DIRECTX9_GRID& root);
		~DIRECTX9_GRID();
		DIRECTX9_GRID& operator=(const DIRECTX9_GRID&);
		};
	};

#endif