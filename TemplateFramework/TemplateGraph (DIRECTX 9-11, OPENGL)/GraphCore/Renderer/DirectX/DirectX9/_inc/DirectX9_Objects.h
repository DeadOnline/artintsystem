#pragma once
#ifndef DirectX9ObjectsHeader
#define DirectX9ObjectsHeader

#include "../../_inc/DirectX_Objects.h"

#include "DirectX9_Globals.h"

namespace GRAPHCORE
	{
	class DIRECTX9_OBJECTS : public DIRECTX_OBJECTS
		{
	private:

		D3DMATERIAL9 	meshMaterial;		// Materials for our mesh

		class DIRECTX9_MESHES_TREE : public MESHES_TREE
			{
		private:
			struct	DIRECTX9_COLLISION : public COLLISION
			{
			private:
				LPDIRECT3DVERTEXBUFFER9 vCollisionBuffer;
				LPDIRECT3DINDEXBUFFER9	iCollisionBuffer;
				int iCollisionQuantity, vCollisionQuantity, fCollisionQuantity;
				int vCollisionFormat;

			public:
				DIRECTX9_COLLISION();

				virtual void		CalculateBoundingFigure(LPD3DXMESH _mesh) = 0;
				virtual RAYINFO		ScanIntersection(CAMERAS_FREE *) = 0;

				HRESULT				Set_Collision(COLLISION_TYPES _CollisionType, LPD3DXMESH _mesh);
				HRESULT				Set_Collision(LPDIRECT3DVERTEXBUFFER9 _vCollisionBuffer, LPDIRECT3DINDEXBUFFER9 _iCollisionBuffer,
					int _iCollisionQuantity, int _vCollisionQuantity, BUFFER_CONTENT_TYPES _type,
					int _vCollisionFormat, int _fCollisionFormat);

				virtual void		Render( void * _renderer ) = 0;
			};
			struct	DIRECTX9_BOUNDINGSPHERE : public DIRECTX9_COLLISION
			{
				D3DXVECTOR3	center;
				float		radius;

				DIRECTX9_BOUNDINGSPHERE(LPD3DXMESH _mesh, int * bytesNumberPerVertex);

				void		CalculateBoundingFigure(LPD3DXMESH _mesh);
				RAYINFO		ScanIntersection(CAMERAS_FREE * _camera);
				void		Render( void * _renderer );
			};
			struct	DIRECTX9_BOUNDINGBOX : public DIRECTX9_COLLISION
			{
				bool		isPointInside(D3DXVECTOR3& p);
				D3DXVECTOR3 minimum;
				D3DXVECTOR3 maximum;

				DIRECTX9_BOUNDINGBOX(LPD3DXMESH _mesh, int * bytesNumberPerVertex);

				void		CalculateBoundingFigure(LPD3DXMESH _mesh);
				RAYINFO		ScanIntersection(CAMERAS_FREE * _camera);
				void		Render( void * _renderer );
			};
			struct	DIRECTX9_BOUNDINGMAP : public DIRECTX9_COLLISION
			{
				DIRECTX9_BOUNDINGMAP(LPD3DXMESH _mesh, int * bytesNumberPerVertex);
				DIRECTX9_BOUNDINGMAP(LPDIRECT3DVERTEXBUFFER9 _vCollisionBuffer, LPDIRECT3DINDEXBUFFER9 _iCollisionBuffer,
					int _iCollisionQuantity, int _vCollisionQuantity, int _vCollisionFormat, int _fCollisionFormat);

				void		CalculateBoundingFigure(LPD3DXMESH _mesh);
				RAYINFO		ScanIntersection(CAMERAS_FREE * _camera);
				void		Render( void * _renderer );
			};
		
		public:
			DIRECTX9_MESHES_TREE( MESHES_TREE * _parent, MESH_ARGUMENTS_DEFAULT, COLLISION_TYPES _CollisionType = None );

			HRESULT SetCollision(COLLISION_TYPES _CollisionType = None);

			HRESULT	AddChildMesh( MESH_ARGUMENTS_DEFAULT, COLLISION_TYPES _CollisionType = None );
			void	ApplyObjectWorldMatrix();
			void	Render( const GLOBALS * _globals, TEMPLATEMATRIX const &_parentMatrix, ANIMATIONSET _parentAnimation, map<_charP, MESHESENTRIES> _meshEntries );
			};

	public:
		DIRECTX9_OBJECTS( _charP _name );
		~DIRECTX9_OBJECTS();

		HRESULT	 AddMesh( MESHES_TREE * _parent, MESH_ARGUMENTS_DEFAULT );
		void	Render( const GLOBALS * _globals, const OBJECTSREGISTRY& _structure ) const;
		};
	};

#endif