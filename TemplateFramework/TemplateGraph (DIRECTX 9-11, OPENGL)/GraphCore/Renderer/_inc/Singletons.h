#pragma once
#ifndef SingletonHeader
#define SingletonHeader

namespace GRAPHCORE
	{
	#define RENDERSINGLETON(ID) const SINGLETONS * Singleton = Global->GetSingleton( ID ); \
	if ( Singleton ) { Singleton->Render( Global ); return S_OK; } else { return E_FAIL; } return E_FAIL;

	class SINGLETONS
		{
	protected:
		SINGLETONS();
		SINGLETONS(const SINGLETONS& root);
		virtual ~SINGLETONS();
		SINGLETONS& operator=(const SINGLETONS&);
	public:
		virtual		void deleteInstance() = 0;
		virtual		void Render( void * const _globals ) const = 0;
		};
	};
#endif