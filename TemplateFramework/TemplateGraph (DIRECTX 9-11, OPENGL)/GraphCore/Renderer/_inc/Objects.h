#pragma once
#ifndef ObjectsHeader
#define ObjectsHeader

#include "../../_inc/WorldPosition.h"

#include "../../_inc/GraphCoreMacroses.h"

#include "../../_inc/Enums.h"

#include "../../_inc/Parameters.h"

#include <list>

using namespace std;

namespace GRAPHCORE
	{
	class GLOBALS;

#define MESH_ARGUMENTS_DEFAULT  _charP _nodeName = "DEFAULT", int _geometryID = -1, int _materialID = -1, int _textureID = -1, bool _animationID = false, \
								WORLDPOSITION _translation = WORLDPOSITION(), WORLDPOSITION &_rotation = WORLDPOSITION(), WORLDPOSITION &_scaling = WORLDPOSITION( 1.0f, 1.0f, 1.0f )
#define MESH_ARGUMENTS  _charP _nodeName, int _geometryID, int _materialID, int _textureID, bool _animationID, \
						WORLDPOSITION _translation, WORLDPOSITION &_rotation, WORLDPOSITION &_scaling

#define MESH_ARGUMENTS_INIT _nodeName, _geometryID, _materialID, _textureID, _animationID, _translation, _rotation, _scaling

	class OBJECTS
		{
	public:
		struct MESHES_TREE
			{
		protected:
			_charP					name;

			int						geometryID; //If -1 use entry, else use by ID. If not found, use default.
			int						materialID; //If -1 use entry, else use by ID. If not found, use default.
			int						textureID; //If -1 use entry, else use by ID. If not found, use default.
			int						animationSet;  //If -1 use entry, else use by ID. If not found, use default.
						
			static int				quantity;
			MESHES_TREE *			parent;

		public:
			list<MESHES_TREE *>		Children;

		protected:			

			WORLDPOSITION			translation;
			WORLDPOSITION			rotation;
			WORLDPOSITION			scaling;

		public:
			struct COLLISION
			{
				int					bytesNumberPerVertex;

				struct RAYINFO
				{
					BOOL	pHit, pHitX, pHitY, pHitZ;
					float	pDist, pDistX, pDistY, pDistZ;
					RAYINFO(BOOL _pHit, float _pDist);
					BOOL Get_HIT();
					float Get_Dist();
				} Ray;

				COLLISION(int _bytesNumberPerVertex = 0);

				BOOL				Get_HIT();
				float 				Get_Dist();

				virtual void		Render( void * _renderer ) = 0;
			} * Collision;

		public:
			MESHES_TREE( MESHES_TREE * _parent, MESH_ARGUMENTS_DEFAULT );
			~MESHES_TREE();

			const _charP	GetName() const;
			void			SetName( _charP _name );

			void SetXt(float& _Xt);
			void SetYt(float& _Yt);
			void SetZt(float& _Zt);
			void SetXa(float& _Xa);
			void SetYa(float& _Ya);
			void SetZa(float& _Za);
			void SetXs(float& _Xs);
			void SetYs(float& _Ys);
			void SetZs(float& _Zs);
			void SetXtBinded(float& _Xt);
			void SetYtBinded(float& _Yt);
			void SetZtBinded(float& _Zt);
			void SetXaBinded(float& _Xa);
			void SetYaBinded(float& _Ya);
			void SetZaBinded(float& _Za);
			void SetXsBinded(float& _Xs);
			void SetYsBinded(float& _Ys);
			void SetZsBinded(float& _Zs);
			const float &GetXt();
			const float &GetYt();
			const float &GetZt();
			const float &GetXa();
			const float &GetYa();
			const float &GetZa();
			const float &GetXs();
			const float &GetYs();
			const float &GetZs();

			virtual HRESULT			AddChildMesh( MESH_ARGUMENTS_DEFAULT );
			MESHES_TREE *			GetParent();
			MESHES_TREE *			GetChild(const _charP &_ID);
			list<MESHES_TREE *>&	GetChildren();

			/*
			* Moves _node branch under _newParentNode branch as a child.
			* If no _node, exit
			* If no _newParentNode, make _node branch a new root
			* If _newParentNode, proceed with reattachment
			*/
			HRESULT					AddMeshAsChild( MESHES_TREE * _newChildMesh );

			HRESULT					RemoveChild(const _charP &_ID);
			HRESULT					RemoveChildren();

			void					ApplyMesh(int& _ID);
			void					ApplyTexture(int& _ID);

			int&					GetTextureID();

			virtual void			ApplyObjectWorldMatrix() = 0;
			virtual void			Render( const GLOBALS * _globals, const TEMPLATEMATRIX& const _parentMatrix, ANIMATIONSET _parentAnimation, map<_charP, MESHESENTRIES> _meshEntries ) = 0;
			};

	protected:
		LPCSTR	name;
		MESHES_TREE * MeshesTree;

	public:

		enum MATERIAL_TYPES	{ Dummy, Static, Active } Type;

		OBJECTS( LPCSTR	_name, MATERIAL_TYPES _type = Dummy );
		~OBJECTS();

		virtual HRESULT	AddMesh( MESHES_TREE * _parent, MESH_ARGUMENTS_DEFAULT ) = 0;
		HRESULT			ReAttachMesh( MESHES_TREE * _node, MESHES_TREE * _newParentNode );
		MESHES_TREE *	GetMesh(const _charP &_name);
		MESHES_TREE *	GetMeshTree();
		MESHES_TREE *	SearchMesh(const _charP &_name, MESHES_TREE * _startNode);
		HRESULT			Remove_Mesh(const _charP &_name);
		HRESULT			Remove_MeshTree( MESHES_TREE * _node );

		virtual void	Render( const GLOBALS * _globals, const OBJECTSREGISTRY& _structure ) const = 0;
		};
	};

#endif