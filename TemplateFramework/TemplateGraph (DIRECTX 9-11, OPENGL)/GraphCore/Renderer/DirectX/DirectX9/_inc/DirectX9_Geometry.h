#pragma once
#ifndef DirectX9GeometryHeader
#define DirectX9GeometryHeader

#include "../../_inc/DirectX_Geometry.h"

#include "DirectX9_Globals.h"

#include <d3dx9.h>
#include <d3d9.h>

namespace GRAPHCORE
	{
	class DIRECTX9_GLOBALS;

	class DIRECTX9_GEOMETRY : public DIRECTX_GEOMETRY
		{
	public:
		///////////////////////////////NATIVE///////////////////////////////

		#define DIRECTX9_BUFFER_ATTRIBUTES \
			LPDIRECT3DVERTEXBUFFER9 _vBuffer, \
			LPDIRECT3DINDEXBUFFER9	_iBuffer, \
			D3DPRIMITIVETYPE		_d3dPrimitiveType

		#define DIRECTX9_BUFFER_ATTRIBUTES_INIT \
			_vBuffer, \
			_iBuffer, \
			_d3dPrimitiveType		

		struct DIRECTX9_BUFFER
			{
		protected:
			LPDIRECT3DVERTEXBUFFER9 vBuffer;
			LPDIRECT3DINDEXBUFFER9	iBuffer;

			D3DPRIMITIVETYPE		d3dPrimitiveType;

		public:
			DIRECTX9_BUFFER( DIRECTX9_BUFFER_ATTRIBUTES );
			~DIRECTX9_BUFFER();

			LPDIRECT3DVERTEXBUFFER9&	GetVertexBuffer();
			LPDIRECT3DINDEXBUFFER9&		GetIndexBuffer();
			};

		class DIRECTX9_VERTEXARRAYNATIVE : public virtual VERTEXARRAYNATIVE, public DIRECTX9_BUFFER
			{
			public:
				DIRECTX9_VERTEXARRAYNATIVE ( VERTEX_ARRAY_NATIVE_ATTRIBUTES, DIRECTX9_BUFFER_ATTRIBUTES );
				virtual ~DIRECTX9_VERTEXARRAYNATIVE ();
				void							Render ( void * _renderer );
			};

		//class DIRECTX9_VERTEXARRAY2DCOLOR_STORAGE : public VERTEXARRAY2DCOLOR_STORAGE, public DIRECTX9_BUFFER
		//	{
		//public:
		//	friend class DIRECTX9_GRID;
		//	DIRECTX9_VERTEXARRAY2DCOLOR_STORAGE(VERTEXPOINTBASE * _verticesArray, int _vertecesQuantity, int * _indicesArray, int _indecesQuantity, int _bytesNumberPerVertex, BUFFER_CONTENT_TYPES _bufferType, unsigned int _elementsQuantity, LPDIRECT3DVERTEXBUFFER9 _vBuffer, LPDIRECT3DINDEXBUFFER9 _iBuffer, D3DPRIMITIVETYPE _d3dPrimitiveType, int _textureID);
		//	void Render(void * _renderer);
		//	};
		//class DIRECTX9_VERTEXARRAY2DCOLORTEX_STORAGE : public VERTEXARRAY2DCOLORTEX_STORAGE, public DIRECTX9_BUFFER
		//	{
		//public:
		//	DIRECTX9_VERTEXARRAY2DCOLORTEX_STORAGE(VERTEXPOINTBASE * _verticesArray, int _vertecesQuantity, int * _indicesArray, int _indecesQuantity, int _bytesNumberPerVertex, BUFFER_CONTENT_TYPES _bufferType, unsigned int _elementsQuantity, LPDIRECT3DVERTEXBUFFER9 _vBuffer, LPDIRECT3DINDEXBUFFER9 _iBuffer, D3DPRIMITIVETYPE _d3dPrimitiveType, int _textureID);
		//	void Render(void * _renderer);
		//	};
		//class DIRECTX9_VERTEXARRAY2DTEX_STORAGE : public VERTEXARRAY2DTEX_STORAGE, public DIRECTX9_BUFFER
		//	{
		//public:
		//	DIRECTX9_VERTEXARRAY2DTEX_STORAGE(VERTEXPOINTBASE * _verticesArray, int _vertecesQuantity, int * _indicesArray, int _indecesQuantity, int _bytesNumberPerVertex, BUFFER_CONTENT_TYPES _bufferType, unsigned int _elementsQuantity, LPDIRECT3DVERTEXBUFFER9 _vBuffer, LPDIRECT3DINDEXBUFFER9 _iBuffer, D3DPRIMITIVETYPE _d3dPrimitiveType, int _textureID);
		//	void Render(void * _renderer);
		//	};
		//class DIRECTX9_VERTEXARRAY3DCOLOR_STORAGE : public VERTEXARRAY3DCOLOR_STORAGE, public DIRECTX9_BUFFER
		//	{
		//public:
		//	DIRECTX9_VERTEXARRAY3DCOLOR_STORAGE(VERTEXPOINTBASE * _verticesArray, int _vertecesQuantity, int * _indicesArray, int _indecesQuantity, int _bytesNumberPerVertex, BUFFER_CONTENT_TYPES _bufferType, unsigned int _elementsQuantity, LPDIRECT3DVERTEXBUFFER9 _vBuffer, LPDIRECT3DINDEXBUFFER9 _iBuffer, D3DPRIMITIVETYPE _d3dPrimitiveType, int _textureID);
		//	void Render(void * _renderer);
		//	};
		//class DIRECTX9_VERTEXARRAY3DCOLORNORMAL_STORAGE : public VERTEXARRAY3DCOLORNORMAL_STORAGE, public DIRECTX9_BUFFER
		//	{
		//public:
		//	DIRECTX9_VERTEXARRAY3DCOLORNORMAL_STORAGE( VERTEXPOINTBASE * _verticesArray, int _vertecesQuantity, int * _indicesArray, int _indecesQuantity, int _bytesNumberPerVertex, BUFFER_CONTENT_TYPES _bufferType, unsigned int _elementsQuantity, LPDIRECT3DVERTEXBUFFER9 _vBuffer, LPDIRECT3DINDEXBUFFER9 _iBuffer, D3DPRIMITIVETYPE _d3dPrimitiveType, int _textureID );
		//	void Render( void * _renderer );
		//	};
		//class DIRECTX9_VERTEXARRAY3DCOLORNORMALTEX_STORAGE : public VERTEXARRAY3DCOLORNORMALTEX_STORAGE, public DIRECTX9_BUFFER
		//	{
		//public:
		//	DIRECTX9_VERTEXARRAY3DCOLORNORMALTEX_STORAGE( VERTEXPOINTBASE * _verticesArray, int _vertecesQuantity, int * _indicesArray, int _indecesQuantity, int _bytesNumberPerVertex, BUFFER_CONTENT_TYPES _bufferType, unsigned int _elementsQuantity, LPDIRECT3DVERTEXBUFFER9 _vBuffer, LPDIRECT3DINDEXBUFFER9 _iBuffer, D3DPRIMITIVETYPE _d3dPrimitiveType, int _textureID );
		//	void Render( void * _renderer );
		//	};
		//class DIRECTX9_VERTEXARRAY3DCOLORTEX_STORAGE : public VERTEXARRAY3DCOLORTEX_STORAGE, public DIRECTX9_BUFFER
		//	{
		//public:
		//	DIRECTX9_VERTEXARRAY3DCOLORTEX_STORAGE( VERTEXPOINTBASE * _verticesArray, int _vertecesQuantity, int * _indicesArray, int _indecesQuantity, int _bytesNumberPerVertex, BUFFER_CONTENT_TYPES _bufferType, unsigned int _elementsQuantity, LPDIRECT3DVERTEXBUFFER9 _vBuffer, LPDIRECT3DINDEXBUFFER9 _iBuffer, D3DPRIMITIVETYPE _d3dPrimitiveType, int _textureID );
		//	void Render(void * _renderer);
		//	};
		//class DIRECTX9_VERTEXARRAY3DNORMAL_STORAGE : public VERTEXARRAY3DCOLORNORMAL_STORAGE, public DIRECTX9_BUFFER
		//	{
		//public:
		//	DIRECTX9_VERTEXARRAY3DNORMAL_STORAGE( VERTEXPOINTBASE * _verticesArray, int _vertecesQuantity, int * _indicesArray, int _indecesQuantity, int _bytesNumberPerVertex, BUFFER_CONTENT_TYPES _bufferType, unsigned int _elementsQuantity, LPDIRECT3DVERTEXBUFFER9 _vBuffer, LPDIRECT3DINDEXBUFFER9 _iBuffer, D3DPRIMITIVETYPE _d3dPrimitiveType, int _textureID );
		//	void Render(void * _renderer);
		//	};
		//class DIRECTX9_VERTEXARRAY3DNORMALTEX_STORAGE : public VERTEXARRAY3DNORMALTEX_STORAGE, public DIRECTX9_BUFFER
		//	{
		//public:
		//	DIRECTX9_VERTEXARRAY3DNORMALTEX_STORAGE( VERTEXPOINTBASE * _verticesArray, int _vertecesQuantity, int * _indicesArray, int _indecesQuantity, int _bytesNumberPerVertex, BUFFER_CONTENT_TYPES _bufferType, unsigned int _elementsQuantity, LPDIRECT3DVERTEXBUFFER9 _vBuffer, LPDIRECT3DINDEXBUFFER9 _iBuffer, D3DPRIMITIVETYPE _d3dPrimitiveType, int _textureID );
		//	void Render(void * _renderer);
		//	};
		//class DIRECTX9_VERTEXARRAY3DTEX_STORAGE : public VERTEXARRAY3DTEX_STORAGE, public DIRECTX9_BUFFER
		//	{
		//public:
		//	DIRECTX9_VERTEXARRAY3DTEX_STORAGE( VERTEXPOINTBASE * _verticesArray, int _vertecesQuantity, int * _indicesArray, int _indecesQuantity, int _bytesNumberPerVertex, BUFFER_CONTENT_TYPES _bufferType, unsigned int _elementsQuantity, LPDIRECT3DVERTEXBUFFER9 _vBuffer, LPDIRECT3DINDEXBUFFER9 _iBuffer, D3DPRIMITIVETYPE _d3dPrimitiveType, int _textureID );
		//	void Render( void * _renderer );
		//	};

		#define CREATE_DIRECTX9_VERTEX_CLASS(class_name, parent_class_name) class class_name : \
			public DIRECTX9_VERTEXARRAYNATIVE, public parent_class_name { \
			public: class_name( VERTEX_ARRAY_NATIVE_ATTRIBUTES, DIRECTX9_BUFFER_ATTRIBUTES ); void	Set_Vertices_Format( void * _renderer ); }

		CREATE_DIRECTX9_VERTEX_CLASS( DIRECTX9_VERTEXARRAY2DCOLOR_STORAGE, VERTEXARRAY2DCOLOR_STORAGE );
		CREATE_DIRECTX9_VERTEX_CLASS( DIRECTX9_VERTEXARRAY2DCOLORTEX_STORAGE, VERTEXARRAY2DCOLORTEX_STORAGE );
		CREATE_DIRECTX9_VERTEX_CLASS( DIRECTX9_VERTEXARRAY2DTEX_STORAGE, VERTEXARRAY2DTEX_STORAGE );
		CREATE_DIRECTX9_VERTEX_CLASS( DIRECTX9_VERTEXARRAY3DCOLOR_STORAGE, VERTEXARRAY3DCOLOR_STORAGE );
		CREATE_DIRECTX9_VERTEX_CLASS( DIRECTX9_VERTEXARRAY3DCOLORNORMAL_STORAGE, VERTEXARRAY3DCOLORNORMAL_STORAGE );
		CREATE_DIRECTX9_VERTEX_CLASS( DIRECTX9_VERTEXARRAY3DCOLORNORMALTEX_STORAGE, VERTEXARRAY3DCOLORNORMALTEX_STORAGE );
		CREATE_DIRECTX9_VERTEX_CLASS( DIRECTX9_VERTEXARRAY3DCOLORTEX_STORAGE, VERTEXARRAY3DCOLORTEX_STORAGE );
		CREATE_DIRECTX9_VERTEX_CLASS( DIRECTX9_VERTEXARRAY3DNORMAL_STORAGE, VERTEXARRAY3DNORMAL_STORAGE );
		CREATE_DIRECTX9_VERTEX_CLASS( DIRECTX9_VERTEXARRAY3DNORMALTEX_STORAGE, VERTEXARRAY3DNORMALTEX_STORAGE );
		CREATE_DIRECTX9_VERTEX_CLASS( DIRECTX9_VERTEXARRAY3DTEX_STORAGE, VERTEXARRAY3DTEX_STORAGE );

		//////////////////////////////~NATIVE///////////////////////////////

		//////////////////////////////IMPORTED//////////////////////////////

		class DIRECTX9_VERTEXARRAY_X : public VERTEXARRAYBASE
			{
		protected:
			LPD3DXMESH				mesh;
			//D3DMATERIAL9 *		meshMaterials;
			int						materialsQuantity;
			vector<int>				textureIDSArray;

		public:
			DIRECTX9_VERTEXARRAY_X( LPD3DXMESH _mesh, int _materialsQuantity, D3DMATERIAL9 * _meshMaterials, vector<int> _textureIDSArray );

			void					Render( void * _renderer );
			void					Set_Vertices_Format( void * _renderer );
			void *					GetVerticesArray();
			int						GetVerticesQuantity();
			unsigned int *			GetIndicesArray();
			unsigned int			GetIndicesQuantity();
			int						GetMaterialsQuantity();
			int						GetTextureID(int _num);
			VERTEX_TYPES			Get_Vertices_Format();

			int						GetElementsType();
			unsigned int			GetElementsQuantity();
			};

		/////////////////////////////~IMPORTED//////////////////////////////

	private:
		HRESULT Initiate_Cube3DColor_DX9(LPDIRECT3DDEVICE9 _device, int _side);
		HRESULT Initiate_Sphere_DX9(LPDIRECT3DDEVICE9 _device, float _radius, int _dimension);
		HRESULT Initiate_Plane(LPDIRECT3DDEVICE9 _device, float _sizeX, float _sizeY);
		HRESULT Initiate_Plane_UpScreen(LPDIRECT3DDEVICE9 _device, float _sizeX, float _sizeY);

	public:

		DIRECTX9_GEOMETRY( _charP _name, VERTEX_TYPES _type, VERTEX_ARRAY_NATIVE_ATTRIBUTES, DIRECTX9_BUFFER_ATTRIBUTES );
		DIRECTX9_GEOMETRY( LPDIRECT3DDEVICE9 _device, _charP _name, GEOMETRY_TYPES _geometryType );
		DIRECTX9_GEOMETRY( DIRECTX9_GLOBALS * _globals, _charP _absoluteMeshPath, _charP _resFolder, DIRECTX_SUPPORTED_FILE_FORMATS _type );
		~DIRECTX9_GEOMETRY();
		};
	};

#endif