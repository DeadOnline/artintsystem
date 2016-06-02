#pragma once
#ifndef DirectX9GlobalsHeader
#define DirectX9GlobalsHeader

#include "../../../_inc/Globals.h"

#include "../../../../_inc/GraphCoreMacroses.h"

#include <d3dx9.h>
#include <d3d9.h>
#include <D3dx9tex.h>
#include <D3DX9Mesh.h>

#include <vector>

#include "DirectX9_Cameras.h"
#include "DirectX9_Effects.h"
#include "DirectX9_Geometry.h"
#include "DirectX9_Lights.h"
#include "DirectX9_Cursor.h"
#include "DirectX9_Materials.h"
#include "DirectX9_Objects.h"
#include "DirectX9_Textstrings.h"
#include "DirectX9_Textures.h"
#include "DirectX9_Animations_X.h"
#include "DirectX9_SkyMap.h"
#include "DirectX9_Grid.h"
#include "DirectX9_Upscreen.h"
#include "DirectX9_SceneController.h"
#include "DirectX9_TemplateMatrix.h"

namespace GRAPHCORE
	{
	class DIRECTX9_GLOBALS : public GLOBALS
		{
		LPDIRECT3D9					d3d;						// Used to create the D3DDevice
		LPDIRECT3DDEVICE9			d3dDevice;					// Our rendering device
		D3DPRESENT_PARAMETERS		d3dPresentParameters;
		D3DDISPLAYMODE				d3dDisplayMode;
		LPDIRECT3DSURFACE9			d3dSurface;

		struct CLASSCODE
			{
			int				sizeBuffer, sizeClass;
			VERTEX_TYPES	type;
			CLASSCODE(int _sizeBuffer = 0, int _sizeClass = 0, VERTEX_TYPES _type = v2dcolor) : sizeBuffer(_sizeBuffer), sizeClass(_sizeClass), type(_type) {};
			};

		map<int, CLASSCODE>			classCode;

		mutex						DirectX9GlobalsMutex;

	public:
		DIRECTX9_GLOBALS();
		~DIRECTX9_GLOBALS();

		LPDIRECT3D9&				GetD3D();
		LPDIRECT3DDEVICE9&			GetD3DDevice();
		D3DPRESENT_PARAMETERS&		GetD3DPresentParameters();
		D3DDISPLAYMODE&				GetD3DDisplayMode();
		LPDIRECT3DSURFACE9&			GetD3DSurface();

		void						SetD3D(LPDIRECT3D9	d3d);
		void						SetD3DDevice();
		void						SetD3DPresentParameters();
		void						SetD3DDisplayMode();
		void						SetD3DSurface();

		//-----------------------------------------------------CREATE-----------------------------------------------------//

		int							CreateGeometry(_charP _name, GEOMETRY_TYPES _geometryType);
		int							CreateGeometry(_charP _name,
										VERTEX_TYPES _type,
										VERTEXPOINTBASE * _verticesArray,
										int _vertecesQuantity,
										unsigned int * _indicesArray,
										unsigned int _indecesQuantity,
										int _bytesNumberPerVertex,
										BUFFER_CONTENT_TYPES _bufferType,
										unsigned int _elementsQuantity,
										LPDIRECT3DVERTEXBUFFER9 _vBuffer,
										LPDIRECT3DINDEXBUFFER9 _iBuffer,
										D3DPRIMITIVETYPE _d3dPrimitiveType);
		int							CreateTextString( const _charP _string, const _charP _appliedFont = 0, const _charP _appliedColor = 0, const RECT _position = RECT() );
		int							CreateTexture( const TEXTURE_TYPES _texture_type = Chess, const DEFAULT_COLORS _color = Black, const RECT _area = RECT() );
		int							CreateMaterial( const MATERIAL_TYPES _materialType = Ambient, const DEFAULT_COLORS _color = Black );
		int							CreateCameraFree(WORLDPOSITION& _position, WORLDPOSITION& _look, WORLDPOSITION& _up, WORLDPOSITION * _positionBinded,
													float _angle_Of_View, float _resolution_Of_Screen, float _starting_Point, float _ending_Point);
		int							CreateCameraTarget(WORLDPOSITION& _position, WORLDPOSITION& _target, WORLDPOSITION& _up,
													WORLDPOSITION * _positionBinded, WORLDPOSITION * _targetBinded, WORLDPOSITION * _upBinded,
													float _angle_Of_View, float _resolution_Of_Screen, float _starting_Point, float _ending_Point);
		int							CreateObject(_charP _name);
		int							CreateLight(_charP _name);
		int							CreateGrid();
		int							CreateUpScreen(const int _clientWidth, const int _clientHeight);
		int							CreateCursor();
		int							CreateSkyMap();
		int							CreateAnimation( const _charP _name, const void * _animationSequence );

		//----------------------------------------------------~CREATE-----------------------------------------------------//

		//------------------------------------------------------LOAD------------------------------------------------------//

		/* @define Loads texture from the filesystem
		*  @params [in] _path Full path
		*  @params [in] _area Size for texture to be transformed to
		*  @return ID
		*/
		int							LoadTexture( const _charP& _path, const RECT& _area = RECT() );
		vector<int>					LoadGeometry( const _charP& _relativeMeshPath, const _charP& _relativeResFolder, SUPPORTED_FILE_FORMATS _format );

		//-----------------------------------------------------~LOAD------------------------------------------------------//

		//------------------------------------------------------COPY------------------------------------------------------//

		int							CopyMaterial( const void * _material );

		//-----------------------------------------------------~COPY------------------------------------------------------//

	private:

		vector<int>					LoadGeometryX( const _charP& _relativeMeshPath, const _charP& _relativeResFolder );
		};
	};

#endif