#pragma once
#ifndef DirectX9AnimationXHeader
#define DirectX9AnimationXHeader

#include "../../_inc/DirectX_Animations.h"

#include "DirectX9_Globals.h"

#include <vector>
#include <assert.h>

namespace GRAPHCORE
	{
	class DIRECTX9_ANIMATION_X : public DIRECTX_ANIMATIONS
		{
	public:
		struct	D3DXMESHCONTAINER_EXTENDED : public D3DXMESHCONTAINER
			{
		public:
			LPDIRECT3DTEXTURE9	* pTextures;
			LPD3DXMESH			  SkinnedMesh;
			D3DXMATRIX			* BoneMatrices;
			D3DXMATRIX			* BoneOffsetMatrices;
			D3DXMATRIX		   ** ContainerSummaryMatrix;

			D3DXMESHCONTAINER_EXTENDED(LPDIRECT3DDEVICE9 _device);
			D3DXMESHCONTAINER_EXTENDED();

			static D3DXMESHCONTAINER_EXTENDED * GetDefaultMesh();
			static void SetDefaultMesh(D3DXMESHCONTAINER_EXTENDED * _mesh);
			} *xMeshContainer;
		struct	D3DXFRAME_EXTENDED : public D3DXFRAME
			{
		public:
			D3DXMATRIX ResultFrameMatrix;
			D3DXFRAME_EXTENDED(D3DXMESHCONTAINER_EXTENDED * _xMeshContainer);
			}	*frameRoot;
		struct ANIMATION_SET
			{
			LPCSTR name;
			enum ANIMATION_TYPE { Single, Loop } AnimationRecurrence;
			double length;
			double current_time;
			ANIMATION_SET(LPCSTR _name, double _length, double _current_time, ANIMATION_TYPE _animationType);
			void SetLength(double _length);
			};
		class	LPD3DXALLOCATEHIERARCHY_EXTENDED : public ID3DXAllocateHierarchy
			{
		public:
			STDMETHOD(CreateFrame)(LPCSTR, LPD3DXFRAME *);
			STDMETHOD(CreateMeshContainer)(LPCSTR, CONST D3DXMESHDATA *,
				CONST D3DXMATERIAL *, CONST D3DXEFFECTINSTANCE *,
				DWORD, CONST DWORD *, LPD3DXSKININFO,
				LPD3DXMESHCONTAINER *);
			STDMETHOD(DestroyFrame)(LPD3DXFRAME);
			STDMETHOD(DestroyMeshContainer)(LPD3DXMESHCONTAINER);
			char* DuplicateCharString(const char* charString);
			};

		//Animation controller
		LPD3DXANIMATIONCONTROLLER				animController;
		D3DXMATRIX *							boneMatrices;
		UINT									maxBones;
		int										currentAnimationSet;
		unsigned int							m_currentTrack;
		static	D3DXMESHCONTAINER_EXTENDED *	boxDefault;
		static	D3DXFRAME_EXTENDED *			frameDefault;
		std::vector<ANIMATION_SET *>			Animations;

		DIRECTX9_ANIMATION_X(LPDIRECT3DDEVICE9 _device, LPCSTR _objectAnimatedName, COLLISION_TYPES _collisionTypes);
		~DIRECTX9_ANIMATION_X();

		////----------------INITIATION--------------//
		HRESULT		LoadMeshHierarchy(LPCSTR _adress, LPDIRECT3DDEVICE9 _device);
		////---------------~INITIATION--------------//

		////----------------RENDERING---------------//
		void		SetWorldMatrix( const void * _renderer, const _charP &_bone, const TEMPLATEMATRIX& const _worldMatrix, const float _time ) const;
		////----------------~RENDERING--------------//
				
		void		DrawFrame(LPD3DXFRAME frame, LPDIRECT3DDEVICE9 _device) const;
		void		DrawMeshContainer(LPD3DXMESHCONTAINER meshContainerBase, LPD3DXFRAME frameBase, LPDIRECT3DDEVICE9 _device) const;
		HRESULT		Play(float elapsedTime);
		void		AnimateFrames(DOUBLE elapsedTime, D3DXMATRIX *matWorld);
		void		UpdateFrameMatrices(const D3DXFRAME *frameBase, const D3DXMATRIX *parentMatrix);
		void		UpdateSkinnedMesh(const D3DXFRAME *frameBase);
		HRESULT		SetAnimationSet(int);
		HRESULT		SetAnimationSetLength(int, double);
		void		NextAnimation();
		void		AnimateFaster();
		void		AnimateSlower();
		int			GetCurrentAnimationSet() const;
		string		GetAnimationSetName(unsigned int index);

		const		D3DXMATRIX GetBoneMatrix() const;
	private:
		HRESULT		SetupBoneMatrices( D3DXFRAME_EXTENDED *pFrame, LPDIRECT3DDEVICE9 _device );
		};
	};

#endif