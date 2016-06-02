#include "../_inc/DirectX9_Animations_X.h"

#pragma region DIRECTX9_ANIMATION_X
//-----------------------------------DIRECTX9_ANIMATION_X-----------------------------------//
using namespace GRAPHCORE;

DIRECTX9_ANIMATION_X::D3DXFRAME_EXTENDED			*	DIRECTX9_ANIMATION_X::frameDefault = NULL;
DIRECTX9_ANIMATION_X::D3DXMESHCONTAINER_EXTENDED	*	DIRECTX9_ANIMATION_X::boxDefault = NULL;
const float kMoveTransitionTime = 0.25f;

DIRECTX9_ANIMATION_X::DIRECTX9_ANIMATION_X( LPDIRECT3DDEVICE9 _device = NULL, LPCSTR _objectAnimatedName = "XAnimation Object", COLLISION_TYPES _collisionTypes = None ) : frameRoot( NULL ), animController( NULL ), m_currentTrack( 0 ), currentAnimationSet( 0 ), maxBones( 0 ), boneMatrices( 0 )
	{
	//if ( !frameDefault ) frameDefault = new D3DXFRAME_EXTENDED( boxDefault );
	//if ( SUCCEEDED( LoadMeshHierarchy( _objectAnimatedName, _device ) ) ) SetAnimationSet( currentAnimationSet ); else frameRoot = frameDefault;
	};
DIRECTX9_ANIMATION_X::~DIRECTX9_ANIMATION_X()
	{
	//TODO:
	//if ( animController )
	//	{
	//	animController->Release();
	//	animController = 0;
	//	}
	//if ( frameRoot )
	//	{
	//	LPD3DXALLOCATEHIERARCHY_EXTENDED memoryAllocator;
	//	D3DXFrameDestroy( frameRoot, &memoryAllocator );
	//	frameRoot = 0;
	//	}
	//if ( boneMatrices )
	//	{
	//	delete []boneMatrices;
	//	boneMatrices = 0;
	//	}
	};
//-------------Load frames-------------//
HRESULT DIRECTX9_ANIMATION_X::LoadMeshHierarchy( LPCSTR _name, LPDIRECT3DDEVICE9 _device )
	{
	if ( _name == "" || !_device ) return E_FAIL;
	LPD3DXALLOCATEHIERARCHY_EXTENDED * memoryAllocator = new LPD3DXALLOCATEHIERARCHY_EXTENDED;
	if ( FAILED( D3DXLoadMeshHierarchyFromX( _name, D3DXMESH_MANAGED, _device, memoryAllocator, NULL, ( LPD3DXFRAME * ) &frameRoot, &animController ) ) ) return E_FAIL;

	OBJDELETE( memoryAllocator );

	if ( frameRoot )
		{
		SetupBoneMatrices( frameRoot, _device );
		boneMatrices = new D3DXMATRIX[ maxBones ];
		ZeroMemory( boneMatrices, sizeof( D3DXMATRIX ) *maxBones );
		}

	if ( animController )
		{
		int m_numAnimationSets = animController->GetMaxNumAnimationSets();
		LPD3DXANIMATIONSET set;

		for ( int i = 0; i < m_numAnimationSets; i++ )
			{
			animController->GetAnimationSet( i, &set );
			currentAnimationSet = 0;
			Animations.push_back( new ANIMATION_SET( set->GetName(), set->GetPeriod(), 0, ANIMATION_SET::ANIMATION_TYPE::Loop ) );
			set->Release();
			};
		};

	return S_OK;
	};
HRESULT DIRECTX9_ANIMATION_X::SetupBoneMatrices( D3DXFRAME_EXTENDED *pFrame, LPDIRECT3DDEVICE9 _device )
	{
	// Cast to our extended structure first
	D3DXMESHCONTAINER_EXTENDED* pMesh = ( D3DXMESHCONTAINER_EXTENDED* ) pFrame->pMeshContainer;

	while ( pMesh && pMesh->pSkinInfo )
		{
		D3DVERTEXELEMENT9 Declaration[ MAX_FVF_DECL_SIZE ];
		if ( FAILED( pMesh->MeshData.pMesh->GetDeclaration( Declaration ) ) )	return E_FAIL;

		pMesh->MeshData.pMesh->CloneMeshFVF( D3DXMESH_MANAGED, pMesh->MeshData.pMesh->GetFVF(), _device, &pMesh->SkinnedMesh );
		maxBones = max( maxBones, ( UINT ) pMesh->pSkinInfo->GetNumBones() );

		for ( unsigned int i = 0; i < pMesh->pSkinInfo->GetNumBones(); i++ )
			{
			D3DXFRAME_EXTENDED* pTempFrame = ( D3DXFRAME_EXTENDED* ) D3DXFrameFind( frameRoot, pMesh->pSkinInfo->GetBoneName( i ) );
			pMesh->ContainerSummaryMatrix[ i ] = &pTempFrame->ResultFrameMatrix;
			}

		pMesh = ( D3DXMESHCONTAINER_EXTENDED* ) pMesh->pNextMeshContainer;
		}

	if ( pFrame->pFrameSibling ) SetupBoneMatrices( ( D3DXFRAME_EXTENDED* ) pFrame->pFrameSibling, _device );
	if ( pFrame->pFrameFirstChild ) SetupBoneMatrices( ( D3DXFRAME_EXTENDED* ) pFrame->pFrameFirstChild, _device );
	return S_OK;
	}
//-----------Animate frames------------//
HRESULT DIRECTX9_ANIMATION_X::Play( float _elapsedTime )
	{
	if ( !this ) return E_FAIL; if ( !frameRoot || !animController || ( currentAnimationSet == -1 ) ) return E_FAIL; //If neither current object nor its frameroot nor its animationcontroller exists, exit function

	if ( Animations[ currentAnimationSet ]->current_time + _elapsedTime <= Animations[ currentAnimationSet ]->length ) //If current animation time increased by elapsed time left is less then max animation time, 
		{
		Animations[ currentAnimationSet ]->current_time += _elapsedTime; AnimateFrames( _elapsedTime, NULL );
		} //Update current timers
	else
		{
		if ( Animations[ currentAnimationSet ]->AnimationRecurrence == ANIMATION_SET::Loop ) //Otherwise, if current animation set is checked as LOOP, cycle timer
			{
			Animations[ currentAnimationSet ]->current_time += ( _elapsedTime - Animations[ currentAnimationSet ]->length );
			AnimateFrames( _elapsedTime, NULL );
			}
		else if ( Animations[ currentAnimationSet ]->current_time != Animations[ currentAnimationSet ]->length ) //If it is SINGLE, update timers on time left before max time and stuck current time to max value
			{
			AnimateFrames( Animations[ currentAnimationSet ]->length - Animations[ currentAnimationSet ]->current_time, NULL );
			Animations[ currentAnimationSet ]->current_time = Animations[ currentAnimationSet ]->length;
			};
		};
	return S_OK;
	};
void	DIRECTX9_ANIMATION_X::AnimateFrames( DOUBLE elapsedTime, D3DXMATRIX * matWorld = NULL )
	{
	animController->AdvanceTime( elapsedTime, NULL );

	UpdateFrameMatrices( frameRoot, matWorld );
	UpdateSkinnedMesh( frameRoot );
	};
void	DIRECTX9_ANIMATION_X::UpdateFrameMatrices( const D3DXFRAME *frameBase, const D3DXMATRIX *parentMatrix )
	{
	D3DXFRAME_EXTENDED *currentFrame = ( D3DXFRAME_EXTENDED* ) frameBase;

	if ( parentMatrix != NULL ) D3DXMatrixMultiply( &currentFrame->ResultFrameMatrix, &currentFrame->TransformationMatrix, parentMatrix ); else currentFrame->ResultFrameMatrix = currentFrame->TransformationMatrix;

	if ( currentFrame->pFrameSibling != NULL ) UpdateFrameMatrices( currentFrame->pFrameSibling, parentMatrix );
	if ( currentFrame->pFrameFirstChild != NULL ) UpdateFrameMatrices( currentFrame->pFrameFirstChild, &currentFrame->ResultFrameMatrix );
	};
void	DIRECTX9_ANIMATION_X::UpdateSkinnedMesh( const D3DXFRAME * frameBase )
	{
	D3DXFRAME_EXTENDED			* currentFrame = ( D3DXFRAME_EXTENDED* ) frameBase;
	D3DXMESHCONTAINER_EXTENDED	* pMesh = ( D3DXMESHCONTAINER_EXTENDED* ) currentFrame->pMeshContainer;

	while ( pMesh && pMesh->pSkinInfo )
		{
		for ( unsigned int i = 0; i < pMesh->pSkinInfo->GetNumBones(); i++ )
			{
			assert( i <= maxBones );
			D3DXMatrixMultiply( &boneMatrices[ i ], &pMesh->BoneOffsetMatrices[ i ], pMesh->ContainerSummaryMatrix[ i ] );
			};

		void *srcPtr = NULL; if ( FAILED( pMesh->MeshData.pMesh->LockVertexBuffer( D3DLOCK_READONLY, ( void** ) &srcPtr ) ) ) break;
		void *destPtr = NULL; if ( FAILED( pMesh->SkinnedMesh->LockVertexBuffer( 0, ( void** ) &destPtr ) ) ) break;

		if ( FAILED( pMesh->pSkinInfo->UpdateSkinnedMesh( boneMatrices, NULL, srcPtr, destPtr ) ) ) break;

		pMesh->SkinnedMesh->UnlockVertexBuffer();
		pMesh->MeshData.pMesh->UnlockVertexBuffer();

		pMesh = ( D3DXMESHCONTAINER_EXTENDED* ) pMesh->pNextMeshContainer;
		};

	if ( currentFrame->pFrameSibling != NULL ) UpdateSkinnedMesh( currentFrame->pFrameSibling );
	if ( currentFrame->pFrameFirstChild != NULL )	UpdateSkinnedMesh( currentFrame->pFrameFirstChild );
	};
//--------Change animation set---------//
HRESULT DIRECTX9_ANIMATION_X::SetAnimationSet( int _index )
	{
	if ( Animations[ currentAnimationSet ]->AnimationRecurrence == ANIMATION_SET::Loop )
		{
		if ( !this ) return E_FAIL;
		if ( !Animations.size() || _index > ( size_t ) ( Animations.size() - 1 ) ) return E_FAIL;

		// Remember current time
		animController->ResetTime();
		double currentTime = Animations[ currentAnimationSet ]->current_time;
		Animations[ currentAnimationSet ]->current_time = 0;

		// Remember current animation
		currentAnimationSet = _index;

		// Get the animation set from the controller
		LPD3DXANIMATIONSET set;
		animController->GetAnimationSet( currentAnimationSet, &set );

		// Note: for a smooth transition between animation sets we can use two tracks and assign the new set to the track
		// not currently playing then insert Keys into the KeyTrack to do the transition between the tracks
		// tracks can be mixed together so we can gradually change into the new animation

		// Alternate tracks
		DWORD newTrack = ( m_currentTrack == 0?1:0 );

		// Assign to our track
		animController->SetTrackAnimationSet( newTrack, set ); // set to 0 track
		set->Release();

		// Clear any track events currently assigned to our two tracks
		animController->UnkeyAllTrackEvents( m_currentTrack );
		animController->UnkeyAllTrackEvents( newTrack );

		// Add an event key to disable the currently playing track kMoveTransitionTime seconds in the future
		animController->KeyTrackEnable( m_currentTrack, FALSE, currentTime + kMoveTransitionTime );
		// Add an event key to change the speed right away so the animation completes in kMoveTransitionTime seconds
		animController->KeyTrackSpeed( m_currentTrack, 0.0f, currentTime, kMoveTransitionTime, D3DXTRANSITION_LINEAR );
		// Add an event to change the weighting of the current track (the effect it has blended with the secon track)
		animController->KeyTrackWeight( m_currentTrack, 0.0f, currentTime, kMoveTransitionTime, D3DXTRANSITION_LINEAR );

		// Enable the new track
		animController->SetTrackEnable( newTrack, TRUE );
		// Add an event key to set the speed of the track
		animController->KeyTrackSpeed( newTrack, 1.0f, currentTime, kMoveTransitionTime, D3DXTRANSITION_LINEAR );
		// Add an event to change the weighting of the current track (the effect it has blended with the first track)
		// As you can see this will go from 0 effect to total effect(1.0f) in kMoveTransitionTime seconds and the first track goes from 
		// total to 0.0f in the same time.
		animController->KeyTrackWeight( newTrack, 1.0f, currentTime, kMoveTransitionTime, D3DXTRANSITION_LINEAR );

		// Remember current track
		m_currentTrack = newTrack;
		}
	else
		{

		//Animations[_index]->current_time = Animations[_index]->length - Animations[currentAnimationSet]->current_time;
		Animations[ currentAnimationSet ]->current_time = 0;
		currentAnimationSet = _index;

		LPD3DXANIMATIONSET set;

		animController->ResetTime();
		animController->SetTrackPosition( 0, 0 );
		animController->GetAnimationSet( currentAnimationSet, &set );
		animController->SetTrackAnimationSet( 0, set );
		animController->AdvanceTime( Animations[ currentAnimationSet ]->current_time, NULL );


		set->Release();

		};

	return S_OK;
	};
HRESULT DIRECTX9_ANIMATION_X::SetAnimationSetLength( int _animationSetNumber, double _length )
	{
	if ( !this ) return E_FAIL; if ( !animController ) return E_FAIL; if ( _animationSetNumber > ( size_t ) Animations.size() ) return E_FAIL;
	Animations[ _animationSetNumber ]->SetLength( _length );
	return S_OK;
	};
void	DIRECTX9_ANIMATION_X::AnimateSlower()
	{
	//	m_speedAdjust+=0.1f;
	}
void	DIRECTX9_ANIMATION_X::AnimateFaster()
	{
	//if (m_speedAdjust>0.1f)	m_speedAdjust-=0.1f;
	}
int		DIRECTX9_ANIMATION_X::GetCurrentAnimationSet() const { return currentAnimationSet; }
//---------------Render---------------//
void	DIRECTX9_ANIMATION_X::SetWorldMatrix( const void * _renderer, const _charP &_bone, const TEMPLATEMATRIX& const _worldMatrix, const float _time ) const
	{
	if ( !_renderer || !_bone )	return;

	//DIRECTX9_TEMPLATEMATRIX worldMatrix( _worldMatrix );

	D3DXMATRIX finalMatrix;
	D3DXMatrixIdentity( &finalMatrix ); //Fill in usin' some of these pathetic functions

	/* Gotta fill appropriate shit in here */
	// Get bone matrix from somewhere and multiply it on world one to get proper final matrix

	D3DXMatrixMultiply( &finalMatrix, &finalMatrix, &DIRECTX9_TEMPLATEMATRIX::GetMatrix( _worldMatrix ) ); // TODO gotta carefully multiply this shit
	( *( LPDIRECT3DDEVICE9 * ) &_renderer )->SetTransform( D3DTS_WORLD, &finalMatrix );
	}
const	D3DXMATRIX DIRECTX9_ANIMATION_X::GetBoneMatrix() const
	{
	D3DXMATRIX temp;
	D3DXMatrixIdentity(&temp);
	return temp; // TODO return proper matrix
	};
void	DIRECTX9_ANIMATION_X::DrawFrame( LPD3DXFRAME frame, LPDIRECT3DDEVICE9 _device ) const
	{
	LPD3DXMESHCONTAINER meshContainer = frame->pMeshContainer;

	while ( meshContainer )
		{
		DrawMeshContainer( meshContainer, frame, _device );
		meshContainer = meshContainer->pNextMeshContainer;
		}

	if ( frame->pFrameSibling ) DrawFrame( frame->pFrameSibling, _device );
	if ( frame->pFrameFirstChild ) DrawFrame( frame->pFrameFirstChild, _device );
	}
void	DIRECTX9_ANIMATION_X::DrawMeshContainer( LPD3DXMESHCONTAINER meshContainerBase, LPD3DXFRAME frameBase, LPDIRECT3DDEVICE9 _device ) const
	{
	D3DXFRAME_EXTENDED			* frame = ( D3DXFRAME_EXTENDED* ) frameBase;
	D3DXMESHCONTAINER_EXTENDED	* meshContainer = ( D3DXMESHCONTAINER_EXTENDED* ) meshContainerBase;

	if ( meshContainer->pSkinInfo )
		{
		D3DXMATRIX mat; D3DXMatrixIdentity( &mat );
		_device->SetTransform( D3DTS_WORLD, &mat );
		}
	else _device->SetTransform( D3DTS_WORLD, &frame->ResultFrameMatrix );

	for ( unsigned int iMaterial = 0; iMaterial < meshContainer->NumMaterials; iMaterial++ )
		{
		_device->SetMaterial( ( D3DMATERIAL9 * ) &meshContainer->pMaterials[ iMaterial ] );
		_device->SetTexture( 0, meshContainer->pTextures[ iMaterial ] );

		LPD3DXMESH pDrawMesh = ( meshContainer->pSkinInfo )?meshContainer->SkinnedMesh:meshContainer->MeshData.pMesh;
		pDrawMesh->DrawSubset( iMaterial );
		}
	}
//----------------------------------------------------------------------------------------//

#pragma region DIRECTX9_ANIMATION_X::D3DXMESHCONTAINER_EXTENDED
//----------------------------------DIRECTX9_ANIMATION_X::D3DXMESHCONTAINER_EXTENDED-----------------------------------// 
DIRECTX9_ANIMATION_X::D3DXMESHCONTAINER_EXTENDED::D3DXMESHCONTAINER_EXTENDED( LPDIRECT3DDEVICE9 _device ) :D3DXMESHCONTAINER(), pTextures( NULL ), SkinnedMesh( NULL ), BoneMatrices( NULL ), BoneOffsetMatrices( NULL ), ContainerSummaryMatrix( NULL )
	{
	//Creates default cube having normals
	D3DXCreateBox( _device, 20, 20, 20, &MeshData.pMesh, NULL );
	Name = "Default Box";
	NumMaterials = 1;
	pTextures = new LPDIRECT3DTEXTURE9();
	};
DIRECTX9_ANIMATION_X::D3DXMESHCONTAINER_EXTENDED::D3DXMESHCONTAINER_EXTENDED() :
D3DXMESHCONTAINER(), pTextures( NULL ), SkinnedMesh( NULL ), BoneMatrices( NULL ), BoneOffsetMatrices( NULL ), ContainerSummaryMatrix( NULL )
	{};
DIRECTX9_ANIMATION_X::D3DXMESHCONTAINER_EXTENDED * DIRECTX9_ANIMATION_X::D3DXMESHCONTAINER_EXTENDED::GetDefaultMesh()
	{
	return boxDefault;
	};
void DIRECTX9_ANIMATION_X::D3DXMESHCONTAINER_EXTENDED::SetDefaultMesh( D3DXMESHCONTAINER_EXTENDED * _mesh )
	{
	_mesh = boxDefault;
	};
//----------------------------------~DIRECTX9_ANIMATION_X::D3DXMESHCONTAINER_EXTENDED-----------------------------------//   
#pragma endregion
#pragma region DIRECTX9_ANIMATION_X::D3DXFRAME_EXTENDED
//-----------------------------------DIRECTX9_ANIMATION_X::D3DXFRAME_EXTENDED-----------------------------------// 
DIRECTX9_ANIMATION_X::D3DXFRAME_EXTENDED::D3DXFRAME_EXTENDED( D3DXMESHCONTAINER_EXTENDED * _xMeshContainer = boxDefault ) : D3DXFRAME()
	{
	D3DXMatrixIdentity( &ResultFrameMatrix );
	D3DXMatrixIdentity( &TransformationMatrix );
	Name = "Default Frame";
	pFrameFirstChild = pFrameSibling = NULL;
	pMeshContainer = ( LPD3DXMESHCONTAINER ) _xMeshContainer;
	};
//----------------------------------~DIRECTX9_ANIMATION_X::D3DXFRAME_EXTENDED-----------------------------------//   
#pragma endregion
#pragma region DIRECTX9_ANIMATION_X::ANIMATION_SET
//-----------------------------------DIRECTX9_ANIMATION_X::ANIMATION_SET-----------------------------------// 
DIRECTX9_ANIMATION_X::ANIMATION_SET::ANIMATION_SET( LPCSTR _name, double _length = 0, double _current_time = 0, ANIMATION_TYPE _animationType = Single ) : name( _name ), length( _length ), current_time( _current_time ), AnimationRecurrence( _animationType ) {};
void DIRECTX9_ANIMATION_X::ANIMATION_SET::SetLength( double _length ) { length = _length; };
//----------------------------------~DIRECTX9_ANIMATION_X::ANIMATION_SET-----------------------------------//   
#pragma endregion
#pragma region DIRECTX9_ANIMATION_X::LPD3DXALLOCATEHIERARCHY_EXTENDED
//-----------------------------------DIRECTX9_ANIMATION_X::LPD3DXALLOCATEHIERARCHY_EXTENDED-----------------------------------// 
HRESULT DIRECTX9_ANIMATION_X::LPD3DXALLOCATEHIERARCHY_EXTENDED::CreateFrame( LPCSTR Name, LPD3DXFRAME *retNewFrame )
	{
	*retNewFrame = 0;
	D3DXFRAME_EXTENDED *newFrame = new D3DXFRAME_EXTENDED;
	ZeroMemory( newFrame, sizeof( D3DXFRAME_EXTENDED ) );

	// Now fill in the data members in the frame structure

	// Now initialize other data members of the frame to defaults
	D3DXMatrixIdentity( &newFrame->TransformationMatrix );
	D3DXMatrixIdentity( &newFrame->ResultFrameMatrix );

	newFrame->pMeshContainer = 0;
	newFrame->pFrameSibling = 0;
	newFrame->pFrameFirstChild = 0;

	// Assign the return pointer to our newly created frame
	*retNewFrame = newFrame;

	// The frame name (note: may be 0 or zero length)
	if ( Name && strlen( Name ) )
		{
		//MessageBox(NULL, "New Frame", "Success", MB_OK);
		newFrame->Name = DuplicateCharString( Name );
		}
	else
		{
		//MessageBox(NULL, "No frame acceptable...", "Error", MB_OK);
		}
	return S_OK;
	}
HRESULT DIRECTX9_ANIMATION_X::LPD3DXALLOCATEHIERARCHY_EXTENDED::CreateMeshContainer( LPCSTR Name, CONST D3DXMESHDATA * meshData, CONST D3DXMATERIAL* materials, CONST D3DXEFFECTINSTANCE *effectInstances, DWORD numMaterials, CONST DWORD *adjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER* retNewMeshContainer )
	{
	if ( !meshData ) { retNewMeshContainer = ( LPD3DXMESHCONTAINER * ) &boxDefault; return S_OK; };
	D3DXMESHCONTAINER_EXTENDED *newMeshContainer = new D3DXMESHCONTAINER_EXTENDED();
	ZeroMemory( newMeshContainer, sizeof( D3DXMESHCONTAINER_EXTENDED ) );

	if ( Name && strlen( Name ) ) newMeshContainer->Name = DuplicateCharString( Name ); else newMeshContainer->Name = DuplicateCharString( "Unnamed Container" );
	if ( meshData->Type != D3DXMESHTYPE_MESH ) { DestroyMeshContainer( newMeshContainer ); return E_FAIL; };
	newMeshContainer->MeshData.Type = meshData->Type;

	//DWORD dwFaces = meshData->pMesh->GetNumFaces();
	//newMeshContainer->pAdjacency = new DWORD[dwFaces*3];
	//if (adjacency) memcpy(newMeshContainer->pAdjacency, adjacency, sizeof(DWORD) * dwFaces*3);
	//else if(FAILED( newMeshContainer->MeshData.pMesh->GenerateAdjacency( 1e-6f, (DWORD*)(void*)newMeshContainer->pAdjacency ) ) ) FillMemory((void*)newMeshContainer->pAdjacency, dwFaces*3, 0xFF );
	//
	newMeshContainer->pAdjacency = NULL;
	LPDIRECT3DDEVICE9 pd3dDevice = NULL;
	meshData->pMesh->GetDevice( &pd3dDevice );

	newMeshContainer->MeshData.pMesh = meshData->pMesh;
	newMeshContainer->MeshData.pMesh->AddRef();

	newMeshContainer->NumMaterials = max( numMaterials, 1 );
	newMeshContainer->pMaterials = new D3DXMATERIAL[ newMeshContainer->NumMaterials ];
	newMeshContainer->pTextures = new LPDIRECT3DTEXTURE9[ newMeshContainer->NumMaterials ];

	ZeroMemory( newMeshContainer->pMaterials, sizeof( D3DXMATERIAL ) * newMeshContainer->NumMaterials );
	ZeroMemory( newMeshContainer->pTextures, sizeof( LPDIRECT3DTEXTURE9 ) * newMeshContainer->NumMaterials );

	if ( numMaterials > 0 )
		{
		for ( DWORD i = 0; i < numMaterials; i++ )
			{
			newMeshContainer->pMaterials[ i ] = materials[ i ];
			if ( materials[ i ].pTextureFilename && lstrlenA( materials[ i ].pTextureFilename ) > 0 )
				{
				D3DXCreateTextureFromFile( pd3dDevice, materials[ i ].pTextureFilename, &newMeshContainer->pTextures[ i ] );
				};
			if ( !newMeshContainer->pTextures[ i ] ) newMeshContainer->pTextures[ i ] = boxDefault->pTextures[ 0 ];
			};
		}
	else
		{
		ZeroMemory( &newMeshContainer->pMaterials[ 0 ], sizeof( D3DMATERIAL9 ) );
		newMeshContainer->pMaterials = boxDefault->pMaterials;
		newMeshContainer->pTextures = boxDefault->pTextures;
		}

	// If there is skin data associated with the mesh copy it over
	if ( pSkinInfo )
		{
		newMeshContainer->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();

		UINT numBones = pSkinInfo->GetNumBones();
		newMeshContainer->BoneOffsetMatrices = new D3DXMATRIX[ numBones ];
		ZeroMemory( newMeshContainer->BoneOffsetMatrices, sizeof( D3DXMATRIX ) *numBones );
		newMeshContainer->ContainerSummaryMatrix = new D3DXMATRIX*[ numBones ];
		ZeroMemory( newMeshContainer->ContainerSummaryMatrix, sizeof( D3DXMATRIX* ) *numBones );
		for ( UINT i = 0; i < numBones; i++ )
			newMeshContainer->BoneOffsetMatrices[ i ] = *( newMeshContainer->pSkinInfo->GetBoneOffsetMatrix( i ) );
		}
	else
		{
		newMeshContainer->pSkinInfo = 0;
		newMeshContainer->BoneOffsetMatrices = 0;
		newMeshContainer->SkinnedMesh = 0;
		newMeshContainer->ContainerSummaryMatrix = 0;
		};
	pd3dDevice->Release();

	*retNewMeshContainer = newMeshContainer;

	return S_OK;
	}
HRESULT DIRECTX9_ANIMATION_X::LPD3DXALLOCATEHIERARCHY_EXTENDED::DestroyFrame( LPD3DXFRAME frameToFree )
	{
	// Convert to our extended type. OK to do this as we know for sure it is:
	D3DXFRAME_EXTENDED *frame = ( D3DXFRAME_EXTENDED* ) frameToFree;

	delete [] frame->Name;
	delete frame;

	return S_OK;
	}
HRESULT DIRECTX9_ANIMATION_X::LPD3DXALLOCATEHIERARCHY_EXTENDED::DestroyMeshContainer( LPD3DXMESHCONTAINER meshContainerBase )
	{
	// Convert to our extended type. OK as we know for sure it is:
	D3DXMESHCONTAINER_EXTENDED* meshContainer = ( D3DXMESHCONTAINER_EXTENDED* ) meshContainerBase;
	if ( !meshContainer )	return S_OK;

	// name
	delete [] meshContainer->Name;
	meshContainer->Name = NULL;

	// material array
	delete [] meshContainer->pMaterials;
	meshContainer->pMaterials = NULL;

	// release the textures before deleting the array
	if ( meshContainer->pTextures )
		{
		for ( UINT i = 0; i < meshContainer->NumMaterials; ++i )
			{
			if ( meshContainer->pTextures[ i ] )
				meshContainer->pTextures[ i ]->Release();
			}
		}

	// texture array
	delete [] meshContainer->pTextures;

	// adjacency data
	delete [] meshContainer->pAdjacency;

	// bone parts
	delete [] meshContainer->BoneOffsetMatrices;

	// frame matrices
	delete [] meshContainer->ContainerSummaryMatrix;

	// release skin mesh
	if ( meshContainer->SkinnedMesh )
		meshContainer->SkinnedMesh->Release();

	// release the main mesh
	if ( meshContainer->MeshData.pMesh )
		meshContainer->MeshData.pMesh->Release();

	// release skin information
	if ( meshContainer->pSkinInfo )
		meshContainer->pSkinInfo->Release();

	// finally delete the mesh container itself
	delete meshContainer;
	meshContainer = NULL;

	return S_OK;
	}
char * DIRECTX9_ANIMATION_X::LPD3DXALLOCATEHIERARCHY_EXTENDED::DuplicateCharString( const char* charString )
	{
	if ( !charString ) return 0;
	size_t len = strlen( charString ) + 1;
	char *newString = new char[ len ];
	memcpy( newString, charString, len*sizeof( char ) );
	return newString;
	};
//----------------------------------~DIRECTX9_ANIMATION_X::LPD3DXALLOCATEHIERARCHY_EXTENDED-----------------------------------//   
#pragma endregion
//----------------------------------~DIRECTX9_ANIMATION_X-----------------------------------//  
#pragma endregion

/*

////Будет рисовать меш в том положении во времени, в котором он находится сейчас
//if (!XAnimation[_meshAnimKey]) return E_FAIL;
//
//D3DXMATRIX matRot, matTrans,matScale;

//D3DXMatrixIdentity( &matRot );
//D3DXMatrixIdentity( &matTrans );
//D3DXMatrixIdentity( &matScale );
//
//D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 0.3f);

//D3DXMATRIX matWorld=matRot*matTrans*matScale;

////_MeshAnim->AnimateFrames(0,&matWorld);
//XAnimation[_meshAnimKey]->Render_Geometry(this);

*/