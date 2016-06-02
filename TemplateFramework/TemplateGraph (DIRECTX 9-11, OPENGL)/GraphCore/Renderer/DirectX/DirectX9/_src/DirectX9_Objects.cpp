#include "../_inc/DirectX9_Objects.h"

using namespace GRAPHCORE;

#pragma region DIRECTX9_OBJECTS
//------------------------------------DIRECTX9_OBJECTS------------------------------------//
#pragma region DIRECTX9_OBJECTS::DIRECTX9_MESHES_TREE
//------------------------------------DIRECTX9_OBJECTS::DIRECTX9_MESHES_TREE------------------------------------//
#pragma region DIRECTX9_OBJECTS:DIRECTX9_MESHES_TREE:DIRECTX9_COLLISION
//------------------------------------DIRECTX9_OBJECTS:DIRECTX9_MESHES_TREE:DIRECTX9_COLLISION------------------------------------//
DIRECTX9_OBJECTS::DIRECTX9_MESHES_TREE::DIRECTX9_COLLISION::DIRECTX9_COLLISION():vCollisionBuffer( NULL ), iCollisionBuffer( NULL ), iCollisionQuantity( 0 ), vCollisionQuantity( 0 ), vCollisionFormat( 0 ), fCollisionQuantity( 0 )
	{};
HRESULT	DIRECTX9_OBJECTS::DIRECTX9_MESHES_TREE::DIRECTX9_COLLISION::Set_Collision( COLLISION_TYPES _CollisionType = None, LPD3DXMESH _mesh = NULL )
	{
	return E_FAIL;
	};
//HRESULT	DIRECTX9_OBJECTS::DIRECTX9_MESHES_TREE::DIRECTX9_COLLISION::Set_Collision(LPDIRECT3DVERTEXBUFFER9 _vCollisionBuffer = NULL, LPDIRECT3DINDEXBUFFER9 _iCollisionBuffer = NULL,
//	int _iCollisionQuantity = 0, int _vCollisionQuantity = 0, BUFFER_CONTENT_TYPES _type = vertex, int _vCollisionFormat = 0, int _fCollisionFormat = 0)
//{
//	Collision = new DIRECTX9_BOUNDINGMAP(_vCollisionBuffer, _iCollisionBuffer, _iCollisionQuantity, _vCollisionQuantity, _vCollisionFormat, _fCollisionFormat);
//	Type = _type;
//	return S_OK;
//};
//
//void	DIRECTX9_OBJECTS::DIRECTX9_MESHES_TREE::DIRECTX9_COLLISION::Render()
//{
//	pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
//	pD3DDevice->SetFVF(vCollisionFormat);
//	pD3DDevice->SetStreamSource(0, vCollisionBuffer, 0, bytesNumberPerVertex);
//	pD3DDevice->SetIndices(iCollisionBuffer);
//	pD3DDevice->SetTexture(NULL, NULL);
//
//	if (CollisionType == index) pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vCollisionQuantity, 0, iCollisionQuantity);
//	else pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, fCollisionQuantity);
//
//	pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
//};
//-----------------------------------~DIRECTX9_OBJECTS:DIRECTX9_MESHES_TREE:DIRECTX9_COLLISION------------------------------------//  
#pragma endregion
#pragma region DIRECTX9_OBJECTS:COLLISIONS:DIRECTX9_BOUNDINGSPHERE
//------------------------------------DIRECTX9_OBJECTS:COLLISIONS:DIRECTX9_BOUNDINGSPHERE------------------------------------//
//DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGSPHERE::DIRECTX9_BOUNDINGSPHERE(LPDIRECT3DDEVICE9 _device = NULL, LPD3DXMESH _mesh = NULL, int * bytesNumberPerVertex = NULL) :
//DIRECTX9_COLLISION(), center(0, 0, 0), radius(1)
//{
//	CalculateBoundingFigure(_device, _mesh);
//	*bytesNumberPerVertex = 24;
//	fCollisionQuantity = _mesh->GetNumFaces();
//};
//void	DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGSPHERE::CalculateBoundingFigure(LPDIRECT3DDEVICE9 _device = NULL, LPD3DXMESH _mesh = NULL)
//{
//	if (!_mesh || !_device) return;
//	BYTE* v = 0;
//	_mesh->LockVertexBuffer(0, (void**)&v);
//	D3DXComputeBoundingSphere((D3DXVECTOR3*)v, _mesh->GetNumVertices(), D3DXGetFVFVertexSize(_mesh->GetFVF()), &center, &radius);
//	_mesh->UnlockVertexBuffer();
//
//	LPD3DXMESH mesh;
//	D3DXCreateSphere(_device, radius, 10, 10, &mesh, NULL);
//	mesh->GetVertexBuffer(&vCollisionBuffer);
//	mesh->GetIndexBuffer(&iCollisionBuffer);
//	vCollisionQuantity = mesh->GetNumVertices();
//	iCollisionQuantity = 0;
//	vCollisionFormat = VertexexFVF3DNormal;
//	mesh->Release();
//};
//DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGSPHERE::RAYINFO DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGSPHERE::ScanIntersection(CAMERAS_FREE * _camera)
//{
//	//D3DXVECTOR3 v = ( _camera->Camera_Vector_Pos + *_camera->Camera_Vector_Pivot ) - center;
//
//	//float b = 2.0f * D3DXVec3Dot(&_camera->Camera_Vector_Look, &v);
//	//float c = D3DXVec3Dot(&v, &v) - ( FLOAT ) ( radius * radius );
//
//	//// Находим дискриминант
//	//float discriminant = ( b * b ) - ( 4.0f * c );
//
//	//// Проверяем на мнимые числа
//	//if ( discriminant < 0.0f ) { Ray.pDist = -1; Ray.pHit = false; return Ray; };
//
//	//discriminant = sqrtf(discriminant);
//
//	//float s0 = ( -b + discriminant ) / 2.0f; //Points of
//	//float s1 = ( -b - discriminant ) / 2.0f; //intersection
//
//	//// Если есть решение >= 0, луч пересекает сферу
//	//if ( s0 >= 0.0f || s1 >= 0.0f ) { Ray.pHit = true; s0 <= s1 ? Ray.pDist = s0 : Ray.pDist = s1; };
//	return Ray;
//};
//-----------------------------------~DIRECTX9_OBJECTS:COLLISIONS:DIRECTX9_BOUNDINGSPHERE------------------------------------//  
#pragma endregion
#pragma region DIRECTX9_OBJECTS:COLLISIONS:DIRECTX9_BOUNDINGBOX
//------------------------------------DIRECTX9_OBJECTS:COLLISIONS:DIRECTX9_BOUNDINGBOX------------------------------------//
//DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGBOX::DIRECTX9_BOUNDINGBOX(LPDIRECT3DDEVICE9 _device, LPD3DXMESH _mesh = NULL, int * bytesNumberPerVertex = NULL) : DIRECTX9_COLLISION(), minimum(D3DXVECTOR3(0, 0, 0)), maximum(D3DXVECTOR3(0, 0, 0))
//{
//	CalculateBoundingFigure(_device, _mesh);
//	*bytesNumberPerVertex = 24;
//	fCollisionQuantity = _mesh->GetNumFaces();
//};
//void DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGBOX::CalculateBoundingFigure(LPDIRECT3DDEVICE9 _device = NULL, LPD3DXMESH _mesh = NULL)
//{
//	if (!_mesh || !_device) return;
//
//	//----------------------------------Get 2 collision points max and min----------------------------------//
//
//	BYTE* v = 0;
//	_mesh->LockVertexBuffer(0, (void**)&v);
//	D3DXComputeBoundingBox((D3DXVECTOR3*)v, _mesh->GetNumVertices(), D3DXGetFVFVertexSize(_mesh->GetFVF()), &minimum, &maximum);
//	_mesh->UnlockVertexBuffer();
//
//	//----------------------------------~Get 2 collision points max and min---------------------------------//
//
//	//----------------------------------Creating cube, index typed----------------------------------//
//	LPD3DXMESH mesh;
//	D3DXCreateBox(_device, (maximum - minimum).x, (maximum - minimum).y, (maximum - minimum).z, &mesh, NULL);
//	mesh->GetVertexBuffer(&vCollisionBuffer);
//	mesh->GetIndexBuffer(&iCollisionBuffer);
//	vCollisionQuantity = mesh->GetNumVertices();
//	iCollisionQuantity = 0;
//	int g = mesh->GetNumBytesPerVertex();
//	vCollisionFormat = mesh->GetFVF();
//	mesh->Release();
//};
//DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGBOX::RAYINFO DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGBOX::ScanIntersection(CAMERAS_FREE * _camera)
//{
//	//Ray.pHit = D3DXBoxBoundProbe(&minimum, &maximum, &( _camera->Camera_Vector_Pos + *_camera->Camera_Vector_Pivot ), &_camera->Camera_Vector_Look);
//	return Ray;
//};
//-----------------------------------~DIRECTX9_OBJECTS:COLLISIONS:DIRECTX9_BOUNDINGBOX------------------------------------//  
#pragma endregion
#pragma region DIRECTX9_OBJECTS:COLLISIONS:DIRECTX9_BOUNDINGMAP
//------------------------------------DIRECTX9_OBJECTS:COLLISIONS:DIRECTX9_BOUNDINGMAP------------------------------------//
//DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGMAP::DIRECTX9_BOUNDINGMAP(LPD3DXMESH _mesh, int * bytesNumberPerVertex = NULL)
//{
//	CalculateBoundingFigure(NULL, _mesh);
//	if (bytesNumberPerVertex) *bytesNumberPerVertex = _mesh->GetNumBytesPerVertex();
//	fCollisionQuantity = _mesh->GetNumFaces();
//};
//DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGMAP::DIRECTX9_BOUNDINGMAP(LPDIRECT3DVERTEXBUFFER9 _vCollisionBuffer = NULL, LPDIRECT3DINDEXBUFFER9 _iCollisionBuffer = NULL, int _iCollisionQuantity = 0, int _vCollisionQuantity = 0, int _vCollisionFormat = 0, int _fCollisionFormat = 0)
//{
//	vCollisionBuffer = _vCollisionBuffer;
//	iCollisionBuffer = _iCollisionBuffer;
//	iCollisionQuantity = _iCollisionQuantity;
//	vCollisionQuantity = _vCollisionQuantity;
//	vCollisionFormat = _vCollisionFormat;
//	fCollisionQuantity = _fCollisionFormat;
//};
//void	DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGMAP::CalculateBoundingFigure(LPDIRECT3DDEVICE9 _device = NULL, LPD3DXMESH _mesh = NULL)
//{
//	if (!_mesh) return;
//	_mesh->GetVertexBuffer(&vCollisionBuffer);
//	_mesh->GetIndexBuffer(&iCollisionBuffer);
//	vCollisionQuantity = _mesh->GetNumVertices();
//	iCollisionQuantity = 0;
//	vCollisionFormat = _mesh->GetFVF();
//};
//DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGMAP::RAYINFO DIRECTX9_OBJECTS::COLLISIONS::DIRECTX9_BOUNDINGMAP::ScanIntersection(CAMERAS_FREE * _camera)
//{
//	//if (!Map) { Ray.pDistX = -1; Ray.pHitX = false; return Ray; };
//	//BOOL HIT = true; Ray.pDistX = -6;
//	//D3DXIntersect(Map->xMeshContainer->MeshData.pMesh,&(_camera->Camera_Vector_Pos+*_camera->Camera_Vector_Pivot-D3DXVECTOR3(-155.934158,6.707680,-9.907097)),&_camera->Camera_Vector_Look,&HIT,NULL,NULL,NULL,&Ray.pDistX,NULL,NULL); //pDist - Distance to floor
//	//if (Ray.pDistX != -6)
//		//Ray.pDistX = Ray.pDistX;
//	return Ray;
//};
//-----------------------------------~DIRECTX9_OBJECTS:COLLISIONS:DIRECTX9_BOUNDINGMAP------------------------------------//  
#pragma endregion

DIRECTX9_OBJECTS::DIRECTX9_MESHES_TREE::DIRECTX9_MESHES_TREE( MESHES_TREE * _parent, MESH_ARGUMENTS, COLLISION_TYPES _CollisionType ) :
MESHES_TREE( _parent, _nodeName, _geometryID, _materialID, _textureID, _animationID, _translation, _rotation, _scaling )
	{
	//BYTE* v = 0;
	//( *Mesh->GetMesh(meshName)->mesh )->LockVertexBuffer(0, ( void** ) &v);
	//D3DXComputeBoundingSphere(( D3DXVECTOR3* ) v, ( *Mesh->GetMesh(meshName)->mesh )->GetNumVertices(), D3DXGetFVFVertexSize(( *Mesh->GetMesh(meshName)->mesh )->GetFVF()), &Sphere._center, &Sphere._radius);
	//D3DXComputeBoundingBox(( D3DXVECTOR3* ) v, ( *Mesh->GetMesh(meshName)->mesh )->GetNumVertices(), D3DXGetFVFVertexSize(( *Mesh->GetMesh(meshName)->mesh )->GetFVF()), &Box._min, &Box._max);
	//( *Mesh->GetMesh(meshName)->mesh )->UnlockVertexBuffer();
	};

HRESULT		DIRECTX9_OBJECTS::DIRECTX9_MESHES_TREE::SetCollision( COLLISION_TYPES _CollisionType )
	{
	//switch (_CollisionType)
	//{
	//case Sphere:
	//	if (((DIRECTX9_GLOBALS *)GetGlobals())->GetMeshes(GetMeshID())->GetFormat() == _x)
	//	{
	//		DIRECTX9_MESHES_X::MESHES_DATA * Mesh =
	//			(DIRECTX9_MESHES_X::MESHES_DATA *)((DIRECTX9_GLOBALS *)GetGlobals())->GetMeshes(GetMeshID())->GetMesh();
	//		Collision = new DIRECTX9_BOUNDINGSPHERE(*Mesh->mesh, NULL);
	//	};
	//	break;
	//case Box:
	//	if (((DIRECTX9_GLOBALS *)GetGlobals())->GetMeshes(GetMeshID())->GetFormat() == _x)
	//	{
	//		DIRECTX9_MESHES_X::MESHES_DATA * Mesh =
	//			(DIRECTX9_MESHES_X::MESHES_DATA *)((DIRECTX9_GLOBALS *)GetGlobals())->GetMeshes(GetMeshID())->GetMesh();
	//		Collision = new DIRECTX9_BOUNDINGBOX(*Mesh->mesh, NULL);
	//	};
	//	break;
	//case Map:
	//	if (((DIRECTX9_GLOBALS *)GetGlobals())->GetMeshes(GetMeshID())->GetFormat() == _x)
	//	{
	//		DIRECTX9_MESHES_X::MESHES_DATA * Mesh =
	//			(DIRECTX9_MESHES_X::MESHES_DATA *)((DIRECTX9_GLOBALS *)GetGlobals())->GetMeshes(GetMeshID())->GetMesh();
	//		Collision = new DIRECTX9_BOUNDINGMAP(*Mesh->mesh, NULL);
	//	};
	//	break;
	//};
	return S_OK;
	};

HRESULT		DIRECTX9_OBJECTS::DIRECTX9_MESHES_TREE::AddChildMesh( MESH_ARGUMENTS, COLLISION_TYPES _CollisionType )
	{
	//TODO
	return S_OK;
	};
void		DIRECTX9_OBJECTS::DIRECTX9_MESHES_TREE::ApplyObjectWorldMatrix()
	{
	//INPUT CODE
	};
void		DIRECTX9_OBJECTS::DIRECTX9_MESHES_TREE::Render(
	const GLOBALS * _globals,
	TEMPLATEMATRIX const &_parentMatrix, //Must NOT be NULL
	ANIMATIONSET _parentAnimation,
	ATTRIBUTESMAP _meshEntries )
	{
	LPDIRECT3DDEVICE9 device = ( ( DIRECTX9_GLOBALS * ) _globals )->GetD3DDevice();
	DIRECTX9_GEOMETRY * Geometry = NULL, *tempGeometry = NULL;
	DIRECTX9_TEXTURES * Texture = NULL, *tempTexture = NULL;
	DIRECTX9_MATERIALS * Material = NULL, *tempMaterial = NULL;
	DIRECTX9_ANIMATION_X * AnimationSet = NULL, *tempAnimationSet = NULL;

	ATTRIBUTESMAP::iterator meshEntry = _meshEntries.end();

	ATTRIBUTES * attribute = NULL;

	if ( _meshEntries.size() )
		{
		meshEntry = _meshEntries.find( GetName() );
		if ( meshEntry != _meshEntries.end() )
			{
			attribute = &meshEntry->second.getAttributes(); //DON'T DELETE. Attribute contains entry info
			}
		}

	( geometryID != -1 )? //If geometryID is defined, we get Geometry object using this ID. Still, it may be invalid.
		(
		tempGeometry = ( DIRECTX9_GEOMETRY * ) _globals->GetGeometry( geometryID ),
		( tempGeometry )? //If it's null, we should apply default geometry to it.
		Geometry = tempGeometry:
		Geometry = ( DIRECTX9_GEOMETRY * ) _globals->GetGeometry( MAPDEFAULT )
		)
		:
		(
		( attribute )?
		Geometry = ( DIRECTX9_GEOMETRY * ) _globals->GetGeometry( ( *attribute )[ ATTRIBUTES_TYPES::Geometry ].ID ):
		Geometry = ( DIRECTX9_GEOMETRY * ) _globals->GetGeometry( MAPDEFAULT )
		);

	( materialID != -1 )? //If materialID is defined, we get Material object using this ID. Still, it may be invalid.
		tempMaterial = ( DIRECTX9_MATERIALS * ) _globals->GetMaterial( materialID ),
		( tempMaterial )? //If it's null, we should apply default material to it.
		Material = tempMaterial:
		Material = ( DIRECTX9_MATERIALS * ) _globals->GetMaterial( materialID )
		:
		(
		( attribute )?
		Material = ( DIRECTX9_MATERIALS * ) _globals->GetMaterial( ( *attribute )[ ATTRIBUTES_TYPES::Material ].ID ):
		Material = ( DIRECTX9_MATERIALS * ) _globals->GetMaterial( MAPDEFAULT )
		);

	( textureID != -1 )? //If textureID is defined, we get Texture object using this ID. Still, it may be invalid.
		tempTexture = ( DIRECTX9_TEXTURES * ) _globals->GetTexture( textureID ),
		( tempTexture )? //If it's null, we should apply default texture to it.
		Texture = tempTexture:
		Texture = ( DIRECTX9_TEXTURES * ) _globals->GetTexture( textureID )
		:
		(
		( attribute )?
		Texture = ( DIRECTX9_TEXTURES * ) _globals->GetTexture( ( *attribute )[ ATTRIBUTES_TYPES::Texture ].ID ):
		Texture = ( DIRECTX9_TEXTURES * ) _globals->GetTexture( MAPDEFAULT )
		);

	( animationSet )? //If textureID is defined, we get Texture object using this ID. Still, it may be invalid.
		tempAnimationSet = ( DIRECTX9_ANIMATION_X * ) _globals->GetAnimation( _parentAnimation.animationID ),
		( tempAnimationSet )? //If it's null, we should apply default animation to it.
		AnimationSet = tempAnimationSet:
		AnimationSet = ( DIRECTX9_ANIMATION_X * ) _globals->GetAnimation( MAPDEFAULT ), _parentAnimation.time
		:
		(
		( attribute )?
		AnimationSet = ( DIRECTX9_ANIMATION_X * ) _globals->GetAnimation( ( *attribute )[ ATTRIBUTES_TYPES::Animation ].animationSet.animationID ):
		AnimationSet = ( DIRECTX9_ANIMATION_X * ) _globals->GetAnimation( MAPDEFAULT )
		,
		( attribute )?
		_parentAnimation.time = ( *attribute )[ ATTRIBUTES_TYPES::Animation ].animationSet.time:
		_parentAnimation.time = 0
		);

	DIRECTX9_TEMPLATEMATRIX parentMatrix( _parentMatrix );
	D3DXMATRIX D3DXCurrentMatrix( parentMatrix.GetMatrix() ), D3DXTranslation, D3DXRotation, D3DXScaling; //Get parent matrix in order to get full current, depending on parent
	D3DXMatrixScaling( &D3DXScaling, scaling.GetXDefault(), scaling.GetYDefault(), scaling.GetZDefault() );
	D3DXMatrixRotationYawPitchRoll( &D3DXRotation, rotation.GetXDefault(), rotation.GetYDefault(), rotation.GetZDefault() );
	D3DXMatrixTranslation( &D3DXTranslation, translation.GetXDefault(), translation.GetYDefault(), translation.GetZDefault() );
	D3DXMatrixMultiply( &D3DXCurrentMatrix, &D3DXScaling, &D3DXRotation );
	D3DXMatrixMultiply( &D3DXCurrentMatrix, &D3DXCurrentMatrix, &D3DXTranslation );
	parentMatrix = D3DXCurrentMatrix;

	Material->SetMaterial( device );
	Texture->SetTexture( device ); //TODO: generate procedurial texture
	AnimationSet->SetWorldMatrix( device, "smth", parentMatrix, _parentAnimation.time );
	Geometry->Render( device );

	//TODO: Implement matrix MVP for each sub mesh, as well as setting up drawing shaders
	list<MESHES_TREE *>::iterator ChildrenIter = Children.begin();

	for ( ; ChildrenIter != Children.end(); ChildrenIter++ )
		{
		parentMatrix = parentMatrix.GetMatrix() * AnimationSet->GetBoneMatrix();
		( *ChildrenIter )->Render( _globals, parentMatrix, _parentAnimation, _meshEntries );
		}
	};
//-----------------------------------~DIRECTX9_OBJECTS::DIRECTX9_MESHES_TREE------------------------------------//  
#pragma endregion

DIRECTX9_OBJECTS::DIRECTX9_OBJECTS( _charP _name ) : DIRECTX_OBJECTS( _name ) {};
DIRECTX9_OBJECTS::~DIRECTX9_OBJECTS() {};

HRESULT	DIRECTX9_OBJECTS::AddMesh( OBJECTS::MESHES_TREE * _parent, MESH_ARGUMENTS )
	{
	if ( !MeshesTree )
		MeshesTree = new DIRECTX9_MESHES_TREE( NULL, MESH_ARGUMENTS_INIT );
	else
		{
		if ( _parent )
			{
			return _parent->AddChildMesh( MESH_ARGUMENTS_INIT );
			}
		else
			{
			ReAttachMesh( new DIRECTX9_MESHES_TREE( NULL, MESH_ARGUMENTS_INIT ), NULL );
			//MESHES_TREE::rootMesh = MESHES_TREE::rootMesh->SetParent(new MESHES_TREE(NULL, _meshName, _meshID, _textureID, _animationID, _position, _rotation, _scaling));
			};
		}
	return S_OK;
	};

void	DIRECTX9_OBJECTS::Render( const GLOBALS * _globals, const OBJECTSREGISTRY& _structure ) const
	{
	if ( !MeshesTree ) return;
	MeshesTree->Render( _globals, _structure.rootWorldMatrix, _structure.rootAnimationSet, _structure.entries );
	};
//-----------------------------------~DIRECTX9_OBJECTS------------------------------------//  
#pragma endregion