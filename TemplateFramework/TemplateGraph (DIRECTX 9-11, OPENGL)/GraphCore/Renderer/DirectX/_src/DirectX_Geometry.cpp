#include "../_inc/DirectX_Geometry.h"

#pragma region DIRECTX_GEOMETRY
//----------------------------------------DIRECTX_GEOMETRY----------------------------------------//
using namespace GRAPHCORE;

#pragma region DIRECTX_GEOMETRY:VERTEXDATAFRAGMENT
//----------------------------DIRECTX_GEOMETRY:VERTEXDATAFRAGMENT----------------------------//
DIRECTX_GEOMETRY::VERTEXDATAFRAGMENT::VERTEXDATAFRAGMENT(LPCSTR _name, vector<VERTEXPOINTBASE *> _vertices) :
name(_name), vertices(_vertices)
{ };
void	DIRECTX_GEOMETRY::Add_Fragment(LPCSTR _name, VERTEX_TYPES _type, vector<VERTEXPOINTBASE *> _verteces)
{
	if (!_name)
	{
		//AddLog("DIRECTX_GEOMETRY::Add_Fragment() - '_name' argument is empty!");
		return;
	}
	if (!VertexManager.empty())
	{
		Range = VertexManager.equal_range(_type);

		for (VertexManagerIter = Range.first; VertexManagerIter != Range.second; VertexManagerIter++)
		{
			if (VertexManagerIter->second.name == _name)
			{
				//AddLog("DIRECTX_GEOMETRY::Add_Fragment() - Fragment with current name and type already exists!");
				return;
			};
		};
	};
	VertexManager.insert(pair<VERTEX_TYPES, VERTEXDATAFRAGMENT>(_type, VERTEXDATAFRAGMENT(_name, _verteces)));
	return;
};
void	DIRECTX_GEOMETRY::Remove_Fragment(LPCSTR _name, VERTEX_TYPES _type)
{
	if (!_name)
	{
		//AddLog("DIRECTX_GEOMETRY::Remove_Fragment() - '_name' argument is empty!");
		return;
	}
	if (VertexManager.empty())
	{
		//AddLog("DIRECTX_GEOMETRY::Remove_Fragment() - VertexManager is empty!");
		return;
	};
	Range = VertexManager.equal_range(_type);
	for (VertexManagerIter = Range.first; VertexManagerIter != Range.second; VertexManagerIter++)
	{
		if (VertexManagerIter->second.name == _name)
		{
			VertexManager.erase(VertexManagerIter);
			break;
		};
	};
};
void	DIRECTX_GEOMETRY::Set_Fragment(LPCSTR _name, VERTEX_TYPES _type, vector<VERTEXPOINTBASE *> _verteces)
{
	if (!_name)
	{
		//AddLog("DIRECTX_GEOMETRY::Set_Fragment() - '_name' argument is empty!");
		return;
	}
	if (!VertexManager.empty())
	{
		Range = VertexManager.equal_range(_type);

		for (VertexManagerIter = Range.first; VertexManagerIter != Range.second; VertexManagerIter++)
		{
			if (VertexManagerIter->second.name == _name)
			{
				VertexManagerIter->second.vertices = _verteces;
				return;
			};
		};
	};
	//AddLog("DIRECTX_GEOMETRY::Set_Fragment() - Fragment with current name and type doesn't exist. Nothing to change.");
	return;
};
DIRECTX_GEOMETRY::VERTEXDATAFRAGMENT * DIRECTX_GEOMETRY::Get_Fragment(LPCSTR _name, VERTEX_TYPES _type)
{
	if (!_name)
	{
		//AddLog("DIRECTX_GEOMETRY::Get_Fragment() - '_name' argument is empty!");
		return NULL;
	}
	if (!VertexManager.empty())
	{
		Range = VertexManager.equal_range(_type);

		for (VertexManagerIter = Range.first; VertexManagerIter != Range.second; VertexManagerIter++)
		{
			if (VertexManagerIter->second.name == _name)
			{
				return &VertexManagerIter->second;
			};
		};
	};
	//AddLog("DIRECTX_GEOMETRY::Get_Fragment() - Fragment with current name and type doesn't exist. Nothing to return.");
	return NULL;
};
//---------------------------~DIRECTX_GEOMETRY:VERTEXDATAFRAGMENT----------------------------//  
#pragma endregion


DIRECTX_GEOMETRY::DIRECTX_GEOMETRY(_charP _name) : GEOMETRY(_name)  { };
DIRECTX_GEOMETRY::~DIRECTX_GEOMETRY() { };
//----------------------------------------DIRECTX_GEOMETRY----------------------------------------//
#pragma endregion