#include "../_inc/Geometry.h"

#pragma region GEOMETRY
//----------------------------------GEOMETRY----------------------------------//
using namespace GRAPHCORE;

#pragma region VERTEXARRAYBASE
//----------------------------------VERTEXARRAYBASE----------------------------------//

GEOMETRY::VERTEXARRAYBASE::VERTEXARRAYBASE(BUFFER_CONTENT_TYPES _bufferType) : BufferType(_bufferType) {};
GEOMETRY::VERTEXARRAYBASE::~VERTEXARRAYBASE() {};

int	GEOMETRY::VERTEXARRAYBASE::GetTextureID()
	{
	return MAPNONEXISTANTID;
	}

//---------------------------------~VERTEXARRAYBASE----------------------------------//
#pragma endregion
#pragma region VERTEXARRAYNATIVE
//----------------------------------VERTEXARRAYNATIVE----------------------------------//

GEOMETRY::VERTEXARRAYNATIVE::VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES ) :
	VerticesArray(_verticesArray), 
	indicesArray(_indicesArray),
	verticesQuantity(_vertecesQuantity),
	indicesQuantity(_indecesQuantity),
	bytesNumberPerVertex(_bytesNumberPerVertex),
	elementsQuantity(_elementsQuantity),
	VERTEXARRAYBASE(_bufferType) {};

GEOMETRY::VERTEXARRAYNATIVE::~VERTEXARRAYNATIVE()
	{
	if (verticesQuantity == 1)
		{
		OBJDELETE(VerticesArray);
		}
	else
		{
		OBJSDELETE(VerticesArray);
		};
	if (indicesQuantity == 1)
		{
		OBJDELETE(indicesArray);
		}
	else
		{
		OBJSDELETE(indicesArray);
		};
	}

void *	GEOMETRY::VERTEXARRAYNATIVE::GetVerticesArray()
	{
	return VerticesArray;
	};
int		GEOMETRY::VERTEXARRAYNATIVE::GetVerticesQuantity ()
	{
	return verticesQuantity;
	};
unsigned int *	GEOMETRY::VERTEXARRAYNATIVE::GetIndicesArray()
	{
	return indicesArray;
	};
unsigned int		GEOMETRY::VERTEXARRAYNATIVE::GetIndicesQuantity()
	{
	return indicesQuantity;
	};
int		GEOMETRY::VERTEXARRAYNATIVE::GetBytesNumberPerVertex ()
	{
	return bytesNumberPerVertex;
	};
//---------------------------------~VERTEXARRAYNATIVE----------------------------------//
#pragma endregion
#pragma region VERTEXARRAY2DCOLOR_STORAGE
//----------------------------------VERTEXARRAY2DCOLOR_STORAGE----------------------------------//

GEOMETRY::VERTEXARRAY2DCOLOR_STORAGE::VERTEXARRAY2DCOLOR_STORAGE(VERTEX_ARRAY_NATIVE_ATTRIBUTES) :
	VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
	{};

VERTEX_TYPES	GEOMETRY::VERTEXARRAY2DCOLOR_STORAGE::Get_Vertices_Format()
	{
	return v2dcolor;
	};
//---------------------------------~VERTEXARRAY2DCOLOR_STORAGE----------------------------------//  
#pragma endregion
#pragma region VERTEXARRAY2DCOLORTEX_STORAGE
//----------------------------------VERTEXARRAY2DCOLORTEX_STORAGE----------------------------------//

GEOMETRY::VERTEXARRAY2DCOLORTEX_STORAGE::VERTEXARRAY2DCOLORTEX_STORAGE(VERTEX_ARRAY_NATIVE_ATTRIBUTES) : 
	VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
	{};

VERTEX_TYPES	GEOMETRY::VERTEXARRAY2DCOLORTEX_STORAGE::Get_Vertices_Format()
	{
	return v2dcolortex;
	};
//---------------------------------~VERTEXARRAY2DCOLORTEX_STORAGE----------------------------------//  
#pragma endregion
#pragma region VERTEXARRAY2DTEX_STORAGE
//----------------------------------VERTEXARRAY2DTEX_STORAGE----------------------------------//

GEOMETRY::VERTEXARRAY2DTEX_STORAGE::VERTEXARRAY2DTEX_STORAGE(VERTEX_ARRAY_NATIVE_ATTRIBUTES) : 
	VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT ) 
	{};

VERTEX_TYPES	GEOMETRY::VERTEXARRAY2DTEX_STORAGE::Get_Vertices_Format()
	{
	return v2dtex;
	};
//---------------------------------~VERTEXARRAY2DTEX_STORAGE----------------------------------//  
#pragma endregion
#pragma region VERTEXARRAY3DCOLOR_STORAGE
//----------------------------------VERTEXARRAY3DCOLOR_STORAGE----------------------------------//
GEOMETRY::VERTEXARRAY3DCOLOR_STORAGE::VERTEXARRAY3DCOLOR_STORAGE(VERTEX_ARRAY_NATIVE_ATTRIBUTES) : 
	VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
	{};

VERTEX_TYPES	GEOMETRY::VERTEXARRAY3DCOLOR_STORAGE::Get_Vertices_Format()
	{
	return v3dcolor;
	};
	//---------------------------------~VERTEXARRAY3DCOLOR_STORAGE----------------------------------//  
#pragma endregion
#pragma region VERTEXARRAY3DCOLORNORMAL_STORAGE
//----------------------------------VERTEXARRAY3DCOLORNORMAL_STORAGE----------------------------------//

GEOMETRY::VERTEXARRAY3DCOLORNORMAL_STORAGE::VERTEXARRAY3DCOLORNORMAL_STORAGE(VERTEX_ARRAY_NATIVE_ATTRIBUTES) : 
	VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
	{};

VERTEX_TYPES	GEOMETRY::VERTEXARRAY3DCOLORNORMAL_STORAGE::Get_Vertices_Format()
	{
	return v3dcolornormal;
	};
//---------------------------------~VERTEXARRAY3DCOLORNORMAL_STORAGE----------------------------------//  
#pragma endregion
#pragma region VERTEXARRAY3DCOLORNORMALTEX_STORAGE
//----------------------------------VERTEXARRAY3DCOLORNORMALTEX_STORAGE----------------------------------//

GEOMETRY::VERTEXARRAY3DCOLORNORMALTEX_STORAGE::VERTEXARRAY3DCOLORNORMALTEX_STORAGE(VERTEX_ARRAY_NATIVE_ATTRIBUTES) : 
	VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
	{};

VERTEX_TYPES	GEOMETRY::VERTEXARRAY3DCOLORNORMALTEX_STORAGE::Get_Vertices_Format()
	{
	return v3dcolornormaltex;
	};
//---------------------------------~VERTEXARRAY3DCOLORNORMALTEX_STORAGE----------------------------------//  
#pragma endregion
#pragma region VERTEXARRAY3DCOLORTEX_STORAGE
//----------------------------------VERTEXARRAY3DCOLORTEX_STORAGE----------------------------------//

GEOMETRY::VERTEXARRAY3DCOLORTEX_STORAGE::VERTEXARRAY3DCOLORTEX_STORAGE(VERTEX_ARRAY_NATIVE_ATTRIBUTES) :
	VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
	{};

VERTEX_TYPES	GEOMETRY::VERTEXARRAY3DCOLORTEX_STORAGE::Get_Vertices_Format()
	{
	return v3dcolortex;
	};
//---------------------------------~VERTEXARRAY3DCOLORTEX_STORAGE----------------------------------//  
#pragma endregion
#pragma region VERTEXARRAY3DNORMAL_STORAGE
//----------------------------------VERTEXARRAY3DNORMAL_STORAGE----------------------------------//

GEOMETRY::VERTEXARRAY3DNORMAL_STORAGE::VERTEXARRAY3DNORMAL_STORAGE(VERTEX_ARRAY_NATIVE_ATTRIBUTES) : 
	VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
	{};

VERTEX_TYPES	GEOMETRY::VERTEXARRAY3DNORMAL_STORAGE::Get_Vertices_Format()
	{
	return v3dnormal;
	};
	//---------------------------------~VERTEXARRAY3DNORMAL_STORAGE----------------------------------//  
#pragma endregion
#pragma region VERTEXARRAY3DNORMALTEX_STORAGE
//----------------------------------VERTEXARRAY3DNORMALTEX_STORAGE----------------------------------//

GEOMETRY::VERTEXARRAY3DNORMALTEX_STORAGE::VERTEXARRAY3DNORMALTEX_STORAGE(VERTEX_ARRAY_NATIVE_ATTRIBUTES) :
	VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
	{};

VERTEX_TYPES	GEOMETRY::VERTEXARRAY3DNORMALTEX_STORAGE::Get_Vertices_Format()
	{
	return v3dnormaltex;
	};
//---------------------------------~VERTEXARRAY3DNORMALTEX_STORAGE----------------------------------//  
#pragma endregion
#pragma region VERTEXARRAY3DTEX_STORAGE
//----------------------------------VERTEXARRAY3DTEX_STORAGE----------------------------------//
GEOMETRY::VERTEXARRAY3DTEX_STORAGE::VERTEXARRAY3DTEX_STORAGE(VERTEX_ARRAY_NATIVE_ATTRIBUTES) : 
	VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT )
	{};

VERTEX_TYPES	GEOMETRY::VERTEXARRAY3DTEX_STORAGE::Get_Vertices_Format()
	{
	return v3dtex;
	};
//---------------------------------~VERTEXARRAY3DTEX_STORAGE----------------------------------//  
#pragma endregion

GEOMETRY::GEOMETRY ( _charP _name ) : name ( _name ), VerticesBatch ( NULL ) {};
GEOMETRY::~GEOMETRY ()
	{
	OBJDELETE ( VerticesBatch );
	};

GEOMETRY::VERTEXARRAYBASE *	GEOMETRY::GetVertexArray ()
	{
	return VerticesBatch;
	};
int							GEOMETRY::GetTextureID()
	{
	return VerticesBatch->GetTextureID();
	}
int		GEOMETRY::GetVertexQuantity()
	{
	return VerticesBatch->GetVerticesQuantity ();
	};
VERTEX_TYPES	GEOMETRY::GetFormat ()
	{
	return VerticesBatch->Get_Vertices_Format();
	}
_charP	GEOMETRY::GetName ()
	{
	return name;
	};
void	GEOMETRY::Render(void * _renderer)
	{
	VerticesBatch->Set_Vertices_Format( _renderer );
	VerticesBatch->Render( _renderer );
	};
//---------------------------------~GEOMETRY----------------------------------//  
#pragma endregion