#pragma once
#ifndef DirectXGeometryHeader
#define DirectXGeometryHeader

#include "../../_inc/Geometry.h"

#include <vector>
#include <unordered_map>

using namespace std;

namespace GRAPHCORE
{
	class DIRECTX_GEOMETRY : public GEOMETRY
	{
	public:

		struct VERTEXDATAFRAGMENT
		{
			LPCSTR name;
			vector<VERTEXPOINTBASE *> vertices;
			VERTEXDATAFRAGMENT(LPCSTR _name, vector<VERTEXPOINTBASE *> _vertices);
		};

		typedef unordered_multimap<VERTEX_TYPES, VERTEXDATAFRAGMENT> fragmentMap;

		fragmentMap											VertexManager;
		fragmentMap::iterator								VertexManagerIter;
		pair<fragmentMap::iterator, fragmentMap::iterator>	Range;

		DIRECTX_GEOMETRY(_charP _fullNameGeometry);
		~DIRECTX_GEOMETRY();

		void					Add_Fragment(LPCSTR _name, VERTEX_TYPES _type, vector<VERTEXPOINTBASE *> _verteces);
		void					Remove_Fragment(LPCSTR _name, VERTEX_TYPES _type);
		VERTEXDATAFRAGMENT *	Get_Fragment(LPCSTR _name, VERTEX_TYPES _type);
		void					Set_Fragment(LPCSTR _name, VERTEX_TYPES _type, vector<VERTEXPOINTBASE *> _verteces);
	};
};

#endif