#include "../_inc/Objects.h"

#pragma region OBJECTS
//----------------------------------OBJECTS----------------------------------//
using namespace GRAPHCORE;
using namespace std;

#pragma region OBJECTS:MESHES_TREE
//------------------------------------OBJECTS:MESHES_TREE------------------------------------//
int OBJECTS::MESHES_TREE::quantity = 0;

OBJECTS::MESHES_TREE::MESHES_TREE( MESHES_TREE * _parent, MESH_ARGUMENTS ) :
								   parent( _parent ), name( _nodeName ),
								   translation( _translation ), rotation( _rotation ), scaling( _scaling ),
								   geometryID( _geometryID ), materialID( _materialID ), textureID( _textureID ), animationSet( _animationID ),
								   Collision( NULL )
	{
	quantity++;
	//BYTE* v = 0;
	//( *Mesh->GetMesh(meshName)->mesh )->LockVertexBuffer(0, ( void** ) &v);
	//D3DXComputeBoundingSphere(( D3DXVECTOR3* ) v, ( *Mesh->GetMesh(meshName)->mesh )->GetNumVertices(), D3DXGetFVFVertexSize(( *Mesh->GetMesh(meshName)->mesh )->GetFVF()), &Sphere._center, &Sphere._radius);
	//D3DXComputeBoundingBox(( D3DXVECTOR3* ) v, ( *Mesh->GetMesh(meshName)->mesh )->GetNumVertices(), D3DXGetFVFVertexSize(( *Mesh->GetMesh(meshName)->mesh )->GetFVF()), &Box._min, &Box._max);
	//( *Mesh->GetMesh(meshName)->mesh )->UnlockVertexBuffer();
	};
OBJECTS::MESHES_TREE::~MESHES_TREE()
	{
	list<OBJECTS::MESHES_TREE *>::iterator ParentChildrenIter;

	for ( ParentChildrenIter = Children.begin(); ParentChildrenIter != Children.end(); ParentChildrenIter++ )
		{
		delete *ParentChildrenIter;
		}
	};

const	_charP	OBJECTS::MESHES_TREE::GetName() const
	{
	return name;
	};
void	OBJECTS::MESHES_TREE::SetName( _charP _name )
	{
	name = _name;
	};
void	OBJECTS::MESHES_TREE::SetXt( float& _Xt )
	{
	translation.SetXDefault( _Xt );
	}
void	OBJECTS::MESHES_TREE::SetYt( float& _Yt )
	{
	translation.SetYDefault( _Yt );
	}
void	OBJECTS::MESHES_TREE::SetZt( float& _Zt )
	{
	translation.SetZDefault( _Zt );
	}
void	OBJECTS::MESHES_TREE::SetXa( float& _Xt )
	{
	rotation.SetXDefault( _Xt );
	}
void	OBJECTS::MESHES_TREE::SetYa( float& _Yt )
	{
	rotation.SetYDefault( _Yt );
	}
void	OBJECTS::MESHES_TREE::SetZa( float& _Zt )
	{
	rotation.SetZDefault( _Zt );
	}
void	OBJECTS::MESHES_TREE::SetXs( float& _Xt )
	{
	scaling.SetXDefault( _Xt );
	}
void	OBJECTS::MESHES_TREE::SetYs( float& _Yt )
	{
	scaling.SetYDefault( _Yt );
	}
void	OBJECTS::MESHES_TREE::SetZs( float& _Zt )
	{
	scaling.SetZDefault( _Zt );
	}
void	OBJECTS::MESHES_TREE::SetXtBinded( float& _Xt )
	{
	translation.SetXBinded( _Xt );
	}
void	OBJECTS::MESHES_TREE::SetYtBinded( float& _Yt )
	{
	translation.SetYBinded( _Yt );
	}
void	OBJECTS::MESHES_TREE::SetZtBinded( float& _Zt )
	{
	translation.SetZBinded( _Zt );
	}
void	OBJECTS::MESHES_TREE::SetXaBinded( float& _Xt )
	{
	rotation.SetXBinded( _Xt );
	}
void	OBJECTS::MESHES_TREE::SetYaBinded( float& _Yt )
	{
	rotation.SetYBinded( _Yt );
	}
void	OBJECTS::MESHES_TREE::SetZaBinded( float& _Zt )
	{
	rotation.SetZBinded( _Zt );
	}
void	OBJECTS::MESHES_TREE::SetXsBinded( float& _Xt )
	{
	scaling.SetXBinded( _Xt );
	}
void	OBJECTS::MESHES_TREE::SetYsBinded( float& _Yt )
	{
	scaling.SetYBinded( _Yt );
	}
void	OBJECTS::MESHES_TREE::SetZsBinded( float& _Zt )
	{
	scaling.SetZBinded( _Zt );
	}
const float	&OBJECTS::MESHES_TREE::GetXt()
	{
	return translation.GetXDefault();
	}
const float	&OBJECTS::MESHES_TREE::GetYt()
	{
	return translation.GetYDefault();
	};
const float	&OBJECTS::MESHES_TREE::GetZt()
	{
	return translation.GetZDefault();
	};
const float	&OBJECTS::MESHES_TREE::GetXa()
	{
	return rotation.GetXDefault();
	}
const float	&OBJECTS::MESHES_TREE::GetYa() 
	{
	return rotation.GetYDefault();
	};
const float	&OBJECTS::MESHES_TREE::GetZa()
	{
	return rotation.GetZDefault();
	};
const float	&OBJECTS::MESHES_TREE::GetXs()
	{
	return scaling.GetXDefault();
	}
const float	&OBJECTS::MESHES_TREE::GetYs()
	{
	return scaling.GetYDefault();
	};
const float	&OBJECTS::MESHES_TREE::GetZs()
	{
	return scaling.GetZDefault();
	};

HRESULT	OBJECTS::MESHES_TREE::AddChildMesh( MESH_ARGUMENTS )
	{
	return S_OK;
	};

OBJECTS::MESHES_TREE * OBJECTS::MESHES_TREE::GetParent()
	{
	return parent;
	};
OBJECTS::MESHES_TREE * OBJECTS::MESHES_TREE::GetChild( const _charP &_name )
	{
	list<OBJECTS::MESHES_TREE *>::iterator ChildrenIter;
	for ( ChildrenIter = Children.begin(); ChildrenIter != Children.end(); ChildrenIter++ )
		{
		if ( ( *ChildrenIter )->GetName() == _name )
			return *ChildrenIter;
		}
	return NULL;
	};
list<OBJECTS::MESHES_TREE *>& OBJECTS::MESHES_TREE::GetChildren()
	{
	return Children;
	};

HRESULT	OBJECTS::MESHES_TREE::AddMeshAsChild( MESHES_TREE * _newChildMesh )
	{
	if ( !_newChildMesh || (this == _newChildMesh) ) return E_FAIL;
	Children.push_back( _newChildMesh );
	_newChildMesh->parent = this;
	return S_OK;
	};

HRESULT	 OBJECTS::MESHES_TREE::RemoveChild( const _charP &_name )
	{
	list<OBJECTS::MESHES_TREE *>::iterator ChildrenIter;
	for ( ChildrenIter = Children.begin(); ChildrenIter != Children.end(); ChildrenIter++ )
		{
		if ( ( *ChildrenIter )->GetName() == _name )
			{
			delete *ChildrenIter;
			Children.erase( ChildrenIter );
			return S_OK;
			};
		}
	return E_FAIL;
	};
HRESULT	 OBJECTS::MESHES_TREE::RemoveChildren()
	{
	list<OBJECTS::MESHES_TREE *>::iterator ChildrenIter;
	for ( ChildrenIter = Children.begin(); ChildrenIter != Children.end(); ChildrenIter++ )
		{
		delete *ChildrenIter;
		};
	Children.clear();
	return S_OK;
	};

void OBJECTS::MESHES_TREE::ApplyTexture( int& _ID )
	{
	textureID = _ID;
	};
void OBJECTS::MESHES_TREE::ApplyMesh( int& _ID )
	{
	geometryID = _ID;
	};

int& OBJECTS::MESHES_TREE::GetTextureID()
	{
	return textureID;
	};
//-----------------------------------~OBJECTS:MESHES_TREE------------------------------------//  
#pragma endregion
#pragma region OBJECTS:MESHES_TREE:COLLISION
//------------------------------------OBJECTS:MESHES_TREE:COLLISION------------------------------------//
#pragma region OBJECTS:MESHES_TREE:COLLISIONS:RAYINFO
//--------------------------------OBJECTS:MESHES_TREE:COLLISIONS:RAYINFO--------------------------------//
OBJECTS::MESHES_TREE::COLLISION::RAYINFO::RAYINFO( BOOL _pHit = false, float _pDist = -2 )
	{
	pHit = pHitX = pHitY = pHitZ = _pHit, pDist = pDistX = pDistY = pDistZ = _pDist;
	};
BOOL OBJECTS::MESHES_TREE::COLLISION::RAYINFO::Get_HIT()
	{
	return pHit;
	};
float OBJECTS::MESHES_TREE::COLLISION::RAYINFO::Get_Dist()
	{
	return pDist;
	};
//-------------------------------~OBJECTS:MESHES_TREE:COLLISIONS:RAYINFO--------------------------------//
#pragma endregion

OBJECTS::MESHES_TREE::COLLISION::COLLISION( int _bytesNumberPerVertex ) : bytesNumberPerVertex( _bytesNumberPerVertex ) {};

BOOL	OBJECTS::MESHES_TREE::COLLISION::Get_HIT() { return Ray.pHit; };
float	OBJECTS::MESHES_TREE::COLLISION::Get_Dist() { return Ray.pDist; };
//-----------------------------------~OBJECTS:MESHES_TREE:COLLISION------------------------------------//  
#pragma endregion

OBJECTS::OBJECTS(LPCSTR	_name, MATERIAL_TYPES _type) : name(_name), Type(_type), MeshesTree(NULL)
	{};
OBJECTS::~OBJECTS()
	{
	Remove_MeshTree( MeshesTree );
	};

HRESULT	OBJECTS::ReAttachMesh( MESHES_TREE * _node, MESHES_TREE * _newParentNode )
	{
	if ( !_node || _node == MeshesTree ) return E_FAIL;

	MESHES_TREE * Parent = _node->GetParent();

	if ( !Parent ) //New mesh
		{
		if ( !_newParentNode ) //If no place to attach to, make _node root
			{
			_node->AddMeshAsChild( MeshesTree );
			MeshesTree = _node;
			}
		else
			{
			_newParentNode->AddMeshAsChild( _node );
			}
		}
	else //Particular mesh in hierarchy
		{
		list<OBJECTS::MESHES_TREE *>::iterator ParentChildrenIter;

		for ( ParentChildrenIter = Parent->Children.begin(); ParentChildrenIter != Parent->Children.end(); ParentChildrenIter++ )
			{
			if ( ( *ParentChildrenIter )->GetName() == _node->GetName() )
				{
				if ( !_newParentNode )
					{
					_node->AddMeshAsChild( MeshesTree );
					MeshesTree = _node;
					}
				else
					{
					_newParentNode->AddMeshAsChild( _node );
					}
				Parent->Children.erase( ParentChildrenIter );
				};
			}
		}

	return S_OK;
	};
OBJECTS::MESHES_TREE *	OBJECTS::GetMesh( const _charP &_name )
	{
	return SearchMesh( _name, MeshesTree );
	};
OBJECTS::MESHES_TREE *	OBJECTS::GetMeshTree()
	{
	return MeshesTree;
	};
OBJECTS::MESHES_TREE *	OBJECTS::SearchMesh( const _charP &_name, OBJECTS::MESHES_TREE * _startNode )
	{
	if ( _startNode->GetName() == _name ) return _startNode;
	OBJECTS::MESHES_TREE * Temp = NULL;

	list<OBJECTS::MESHES_TREE *>::iterator ChildrenIter;
	for ( ChildrenIter = _startNode->GetChildren().begin(); ChildrenIter != _startNode->GetChildren().end(); ChildrenIter++ )
		{
		Temp = SearchMesh( _name, *ChildrenIter );
		if ( Temp ) return Temp;
		};
	return NULL;
	};
HRESULT	OBJECTS::Remove_Mesh( const _charP &_name )
	{
	OBJECTS::MESHES_TREE * Temp = SearchMesh( _name, MeshesTree );
	if ( Temp )
		{
		Temp->GetParent()->RemoveChild( _name );
		return S_OK;
		}
	else
		{
		return E_FAIL;
		};
	};
HRESULT	OBJECTS::Remove_MeshTree( MESHES_TREE * _node )
	{
	if ( _node )
		{
		MESHES_TREE * Parent = _node->GetParent();
		if ( Parent )
			{
			Parent->RemoveChild( _node->GetName() );
			}
		else
			{
			OBJDELETE( MeshesTree );
			}
		}
	return S_OK;
	};
//---------------------------------~OBJECTS----------------------------------//  
#pragma endregion
