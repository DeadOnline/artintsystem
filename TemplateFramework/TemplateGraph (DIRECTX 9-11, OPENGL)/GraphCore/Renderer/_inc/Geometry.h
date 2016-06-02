#pragma once
#ifndef GeometryHeader
#define GeometryHeader

#include "../../_inc/GraphCoreMacroses.h"

#include "../../_inc/Enums.h"

#include "../../_inc/Parameters.h"

namespace GRAPHCORE
	{
	#pragma region VERTEX STRUCTURE
	///////////////////////////////////////////////////////////////////////////VERTEX FORMATS///////////////////////////////////////////////////////////////////////////
	#define VertexesFVF2DColor			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
	#define VertexexFVF2DColorTex		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	#define VertexexFVF2DTex			(D3DFVF_XYZRHW | D3DFVF_TEX1)
	#define VertexesFVF3DColor			(D3DFVF_XYZ | D3DFVF_DIFFUSE)
	#define VertexesFVF3DColorNormal	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL)
	#define VertexexFVF3DColorNormalTex	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL | D3DFVF_TEX1)
	#define VertexexFVF3DColorTex		(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	#define VertexexFVF3DNormal			(D3DFVF_XYZ | D3DFVF_NORMAL)
	#define VertexexFVF3DNormalTex		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)
	#define VertexexFVF3DTex			(D3DFVF_XYZ | D3DFVF_TEX1)

	#define GENERATED_GEOMETRY_SIZE 50
	
	struct VERTEXPOINTBASE {};
	struct VERTEXPOINT2DCOLOR : public VERTEXPOINTBASE { FLOAT X, Y, Z, RHW; DWORD COLOR; VERTEXPOINT2DCOLOR ( FLOAT _x = 0.0f, FLOAT _y = 0.0f, FLOAT _z = 0.5, FLOAT _rhw = 1, DWORD _color = 10000 ) : X ( _x ), Y ( _y ), Z ( _z ), RHW ( _rhw ), COLOR ( _color ) {}; };
	struct VERTEXPOINT2DCOLORTEX : public VERTEXPOINTBASE { FLOAT X, Y, Z, RHW; DWORD COLOR; FLOAT fU, fV; VERTEXPOINT2DCOLORTEX ( FLOAT _x = 0, FLOAT _y = 0, FLOAT _z = 0.5, FLOAT _rhw = 1, DWORD _color = 10000, FLOAT _fU = 0.0f, FLOAT _fV = 0.0f ) : X ( _x ), Y ( _y ), Z ( _z ), RHW ( _rhw ), COLOR ( _color ), fU ( _fU ), fV ( _fV ) {}; };
	struct VERTEXPOINT2DTEX : public VERTEXPOINTBASE { FLOAT X, Y, Z, RHW; FLOAT fU, fV; VERTEXPOINT2DTEX ( FLOAT _x = 0.0f, FLOAT _y = 0.0f, FLOAT _z = 0.5, FLOAT _rhw = 1, FLOAT _fU = 0.0f, FLOAT _fV = 0.0f ) : X ( _x ), Y ( _y ), Z ( _z ), RHW ( _rhw ), fU ( _fU ), fV ( _fV ) {}; };
	struct VERTEXPOINT3DCOLOR : public VERTEXPOINTBASE { FLOAT X, Y, Z; DWORD COLOR; VERTEXPOINT3DCOLOR ( FLOAT _x = 0.0f, FLOAT _y = 0.0f, FLOAT _z = 0.0, DWORD _color = 10000 ) : X ( _x ), Y ( _y ), Z ( _z ), COLOR ( _color ) {}; };
	struct VERTEXPOINT3DCOLORNORMAL : public VERTEXPOINTBASE { FLOAT X, Y, Z; DWORD COLOR; FLOAT nx, ny, nz; VERTEXPOINT3DCOLORNORMAL ( FLOAT _x = 0.0f, FLOAT _y = 0.0f, FLOAT _z = 0.0, DWORD _color = 10000, FLOAT _nx = 0.0f, FLOAT _ny = 0.0f, FLOAT _nz = 0.0f ) : X ( _x ), Y ( _y ), Z ( _z ), COLOR ( _color ), nx ( _nx ), ny ( _ny ), nz ( _nz ) {}; };
	struct VERTEXPOINT3DCOLORNORMALTEX : public VERTEXPOINTBASE { FLOAT X, Y, Z; DWORD COLOR; FLOAT nx, ny, nz, fU, fV;  VERTEXPOINT3DCOLORNORMALTEX ( FLOAT _x = 0.0f, FLOAT _y = 0.0f, FLOAT _z = 0.0, DWORD _color = 10000, FLOAT _nx = 0.0f, FLOAT _ny = 0.0f, FLOAT _nz = 0.0f, FLOAT _fU = 0.0f, FLOAT _fV = 0.0f ) : X ( _x ), Y ( _y ), Z ( _z ), COLOR ( _color ), nx ( _nx ), ny ( _ny ), nz ( _nz ), fU ( _fU ), fV ( _fV ) {}; };
	struct VERTEXPOINT3DCOLORTEX : public VERTEXPOINTBASE { FLOAT X, Y, Z; DWORD COLOR; FLOAT fU, fV; VERTEXPOINT3DCOLORTEX ( FLOAT _x = 0.0f, FLOAT _y = 0.0f, FLOAT _z = 0.0, DWORD _color = 10000, FLOAT _fU = 0.0f, FLOAT _fV = 0.0f ) : X ( _x ), Y ( _y ), Z ( _z ), COLOR ( _color ), fU ( _fU ), fV ( _fV ) {}; };
	struct VERTEXPOINT3DNORMAL : public VERTEXPOINTBASE { FLOAT X, Y, Z, nx, ny, nz; VERTEXPOINT3DNORMAL ( FLOAT _x = 0.0f, FLOAT _y = 0.0f, FLOAT _z = 0.0, FLOAT _nx = 0.0f, FLOAT _ny = 0.0f, FLOAT _nz = 0.0f ) : X ( _x ), Y ( _y ), Z ( _z ), nx ( _nx ), ny ( _ny ), nz ( _nz ) {}; };
	struct VERTEXPOINT3DNORMALTEX : public VERTEXPOINTBASE { FLOAT X, Y, Z, nx, ny, nz, fU, fV; VERTEXPOINT3DNORMALTEX ( FLOAT _x = 0.0f, FLOAT _y = 0.0f, FLOAT _z = 0.0, FLOAT _nx = 0.0f, FLOAT _ny = 0.0f, FLOAT _nz = 0.0f, FLOAT _fU = 0.0f, FLOAT _fV = 0.0f ) : X ( _x ), Y ( _y ), Z ( _z ), nx ( _nx ), ny ( _ny ), nz ( _nz ), fU ( _fU ), fV ( _fV ) {}; };
	struct VERTEXPOINT3DTEX : public VERTEXPOINTBASE { FLOAT X, Y, Z, fU, fV; VERTEXPOINT3DTEX ( FLOAT _x = 0, FLOAT _y = 0, FLOAT _z = 0, FLOAT _fU = 0, FLOAT _fV = 0 ) : X ( _x ), Y ( _y ), Z ( _z ), fU ( _fU ), fV ( _fV ) {}; };
	//////////////////////////////////////////////////////////////////////////~VERTEX FORMATS///////////////////////////////////////////////////////////////////////////  
	#pragma endregion

	#define VERTEX_ARRAY_NATIVE_ATTRIBUTES \
			VERTEXPOINTBASE *	_verticesArray, \
			int _vertecesQuantity, \
			unsigned int * _indicesArray, \
			unsigned int _indecesQuantity, \
			int _bytesNumberPerVertex, \
			BUFFER_CONTENT_TYPES _bufferType, \
			unsigned int	_elementsQuantity

	#define VERTEX_ARRAY_NATIVE_ATTRIBUTES_INIT \
			_verticesArray, \
			_vertecesQuantity, \
			_indicesArray, \
			_indecesQuantity, \
			_bytesNumberPerVertex, \
			_bufferType, \
			_elementsQuantity

	class GEOMETRY
		{
	protected:

			_charP name;

	public:

		class VERTEXARRAYBASE
			{
		protected:
			BUFFER_CONTENT_TYPES			BufferType;
		public:
			virtual void					Render( void * _renderer ) = 0;
			virtual void					Set_Vertices_Format( void * _renderer ) = 0;
			virtual void *					GetVerticesArray() = 0;
			virtual int						GetVerticesQuantity() = 0;
			virtual unsigned int *			GetIndicesArray() = 0;
			virtual unsigned int			GetIndicesQuantity() = 0;
			virtual VERTEX_TYPES			Get_Vertices_Format() = 0;
			virtual int						GetTextureID();

			VERTEXARRAYBASE(BUFFER_CONTENT_TYPES _bufferType);
			virtual ~VERTEXARRAYBASE();
			} * VerticesBatch;

		class VERTEXARRAYNATIVE : public VERTEXARRAYBASE
			{
		protected:
			VERTEXPOINTBASE *				VerticesArray;
			unsigned int *					indicesArray;

			int								verticesQuantity;
			unsigned int					indicesQuantity;

			int								bytesNumberPerVertex;

			unsigned int					elementsQuantity;

		public:
			VERTEXARRAYNATIVE( VERTEX_ARRAY_NATIVE_ATTRIBUTES );

			virtual ~VERTEXARRAYNATIVE();
			virtual void					Render( void * _renderer ) = 0;
			virtual void					Set_Vertices_Format( void * _renderer ) = 0;
			virtual VERTEX_TYPES			Get_Vertices_Format() = 0;

			void *							GetVerticesArray();
			int								GetVerticesQuantity();
			unsigned int *					GetIndicesArray();
			unsigned int					GetIndicesQuantity();
			int								GetBytesNumberPerVertex();
			};

		#define CREATE_VERTEX_CLASS(class_name) class class_name : public virtual VERTEXARRAYNATIVE { \
			public: class_name( VERTEX_ARRAY_NATIVE_ATTRIBUTES ); VERTEX_TYPES	Get_Vertices_Format(); }

		CREATE_VERTEX_CLASS( VERTEXARRAY2DCOLOR_STORAGE );
		CREATE_VERTEX_CLASS( VERTEXARRAY2DCOLORTEX_STORAGE );
		CREATE_VERTEX_CLASS( VERTEXARRAY2DTEX_STORAGE );
		CREATE_VERTEX_CLASS( VERTEXARRAY3DCOLOR_STORAGE );
		CREATE_VERTEX_CLASS( VERTEXARRAY3DCOLORNORMAL_STORAGE );
		CREATE_VERTEX_CLASS( VERTEXARRAY3DCOLORNORMALTEX_STORAGE );
		CREATE_VERTEX_CLASS( VERTEXARRAY3DCOLORTEX_STORAGE );
		CREATE_VERTEX_CLASS( VERTEXARRAY3DNORMAL_STORAGE );
		CREATE_VERTEX_CLASS( VERTEXARRAY3DNORMALTEX_STORAGE );
		CREATE_VERTEX_CLASS( VERTEXARRAY3DTEX_STORAGE );

	public:

		GEOMETRY( _charP _fullNameGeometry );
		virtual ~GEOMETRY();

		int								GetTextureID();
		VERTEXARRAYBASE *				GetVertexArray();
		int								GetVertexQuantity();
		VERTEX_TYPES					GetFormat();
		_charP							GetName();

		void							Render( void * _renderer );
		};
	};

#endif