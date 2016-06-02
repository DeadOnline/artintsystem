#include "..\..\TemplateFramework\TemplateGraph (DIRECTX 9-11, OPENGL)\GraphCore\Renderer\_inc\UpScreen.h"
#include "..\..\TemplateFramework\TemplateGraph (DIRECTX 9-11, OPENGL)\GraphCore\Renderer\_inc\UpScreen.h"
#include "..\..\TemplateFramework\TemplateGraph (DIRECTX 9-11, OPENGL)\GraphCore\Renderer\_inc\UpScreen.h"
#pragma once

#include "ALL.h"

#define	CAMERA_STARTING_POS	100.0f

#define VertexesAFVF2D		(D3DFVF_XYZ    | D3DFVF_DIFFUSE)
#define VertexesFVF2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define VertexexFVF2DTex    (D3DFVF_XYZRHW | D3DFVF_TEX1)
#define VertexexFVF3DColTex (D3DFVF_XYZ	   | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define VertexexFVF3DTex	(D3DFVF_XYZ    | D3DFVF_NORMAL  | D3DFVF_TEX1)

#define MIN(A,B) (((A)<(B))?(A):(B))
#define MAX(A,B) (((A)>(B))?(A):(B))
#define VEC_SUB(R,A,B) {(R)[0]=(A)[0]-(B)[0];(R)[1]=(A)[1]-(B)[1]; \
                        (R)[2]=(A)[2]-(B)[2];}
#define VEC_ADD(R,A,B) {(R)[0]=(A)[0]+(B)[0];(R)[1]=(A)[1]+(B)[1]; \
                        (R)[2]=(A)[2]+(B)[2];}
#define VEC_MULN(A,N) { (A)[0]*=(N); (A)[1]*=(N); (A)[2]*=(N); }
#define VEC_DIVV(R,A,B) {(R)[0]=(A)[0]/(B)[0];(R)[1]=(A)[1]/(B)[1]; \
                         (R)[2]=(A)[2]/(B)[2];}
#define VEC_ASSIGN(A,B) {(A)[0]=(B)[0];(A)[1]=(B)[1];(A)[2]=(B)[2];}
#define VEC_MIN(R,A,B){(R)[0] = MIN((A)[0],(B)[0]); \
                       (R)[1] = MIN((A)[1],(B)[1]); \
                       (R)[2] = MIN((A)[2],(B)[2]);}
#define VEC_MAX(R,A,B){(R)[0] = MAX((A)[0],(B)[0]); \
                       (R)[1] = MAX((A)[1],(B)[1]); \
                       (R)[2] = MAX((A)[2],(B)[2]);}

#define OBJRELEASE(X) if (X) (X)->Release(); X = NULL;
#define OBJDELETE(X) if (X) delete X; X = NULL;
#define OBJSDELETE(X) if (X) delete [] X; X = NULL;

class GRAPHCORE
	{
public:
	LPDIRECT3D9				D3D;        // Used to create the D3DDevice
	LPDIRECT3DDEVICE9		DEVICE;     // Our rendering device
	D3DPRESENT_PARAMETERS	D3DPP;
	D3DFORMAT				D3DF;
	D3DDISPLAYMODE			D3DM;

	LPDIRECT3DSURFACE9		SURFACE;
	LPDIRECT3DSURFACE9		BACKBUFFER;
	LPDIRECT3DVERTEXBUFFER9 VERTEXBUFFER, UPSCREENBUFFER, TEXBUFFER;
	LPDIRECT3DINDEXBUFFER9	INDEXBUFFER;

	//D3DFVF_DIFFUSE - формат вершин включающий компонент диффузного цвета.
	//D3DFVF_NORMAL - формат вершин включающий вектор нормали. Этот флажок не может использоваться совместно с флажком D3DFVF_XYZRHW.
	//D3DFVF_PSIZE - формат вершин указывающий только размер точки.
	//D3DFVF_SPECULAR - формат вершин включающий зеркальный цвет.
	//D3DFVF_XYZ - формат вершин включающий положение непреобразованных вершин. Этот флажок не может использоваться совместно с флажком D3DFVF_XYZRHW.
	//D3DFVF_XYZRHW - формат вершин включающий положение преобразованных вершин. Этот флажок не может использоваться совместно с флажком D3DFVF_XYZ или D3DFVF_NORMAL.
	//D3DFVF_XYZB1 по D3DFVF_XYZB5 - формат вершин включающий положение и соответствующее число надбавки. Используют для мультиматрицы вершин определяющие несколько действий. В настоящее время, Direct3D может смешивать до трех значений надбавок и четырех смешиваний матриц. Для более подробной информации об использовании смешиваемых матриц, см. Смешанные индексированные вершины.

	struct VERTEX_BASE { };
	struct VERTEX: public VERTEX_BASE { FLOAT _x, _y, _z; } *vert3D; int vert3DQuantity;													// Точки
	struct NORMAL: public VERTEX_BASE { FLOAT nx, ny, nz; } *normal3D;																		// Нормали
	struct VERTEXNORMAL: public VERTEX_BASE { FLOAT _x, _y, _z, nx, ny, nz; } *vertnormal3D;												// Точки с нормалями
	struct VERTEXCOLOR: public VERTEX_BASE { FLOAT _x, _y, _z; DWORD COLOR; } *vertcolor3D; int vertcolor3DQuantity;						// Точки с цветом
	struct VERTEXCOLORSPECULAR: public VERTEX_BASE { FLOAT _x, _y, _z; DWORD COLOR, SPECULAR; } *vertcolorspec3D;							// Точки с цветом и отражениями
	struct VERTEXNORMALCOLORSPECULAR: public VERTEX_BASE { FLOAT _x, _y, _z, nx, ny, nz; DWORD COLOR, SPECULAR; } *vertnormalcolorspec3D;	// Точки с нормалями, цветом и отражениями
	struct VERTEXDEFINITECOLOR: public VERTEX_BASE { FLOAT X, Y, Z, RHW; DWORD COLOR; } *vertdefcolor3D, upScreen[4];						// Точки с направлением и цветом
	struct VERTEXDEFINITETEXTURE: public VERTEX_BASE { FLOAT X, Y, Z, RHW, fU, fV; } *vertdeftex3D, texScreen[4];							// Точки с направлением и текстурой
	struct VERTEXTEXTURE: public VERTEX_BASE { FLOAT X, Y, Z; DWORD COLOR; FLOAT fU, fV; } *verttex3D;										// Точки с цветом и текстурой
	struct VERTEXNORMALTEXTURE: public VERTEX_BASE { FLOAT X, Y, Z, nx, ny, nz, fU, fV; } *vertnormaltex3D;									// Точки с нормалями и текстурой

	struct WORLDPOSITION 
		{
		float X;
		float Y;
		float Z;
	WORLDPOSITION(float _x, float _y, float _z): X(_x), Y(_y), Z(_z) {};
		};
	struct BOUNDINGSPHERE
		{
		D3DXVECTOR3 _center;
		float _radius;
		};
	struct BOUNDINGBOX
		{
		bool isPointInside(D3DXVECTOR3& p);
		D3DXVECTOR3 _min;
		D3DXVECTOR3 _max;
		};

	////////////// BASE \\\\\\\\\\\\\\\

	class TEXTSTRINGS
		{
	public:
		///////////
		static LPD3DXFONT font[10];
		static D3DCOLOR color[10];
		static D3DXFONT_DESC fontDesc;
		///////////
		int Applied_Font;
		int Applied_Color;
		LPCSTR string;
		RECT rec;
		///////////
		TEXTSTRINGS* textNext;
		static TEXTSTRINGS* Root;
		static int Quantity;
		///////////
	public:
		TEXTSTRINGS();
		~TEXTSTRINGS();
		HRESULT Initiate_Font(LPDIRECT3DDEVICE9 _Device, int _Height, int _Weight, bool _Italic, LPCSTR _Name, int _FontNumber);
		HRESULT Initiate_Color(D3DCOLOR &_color, int &_position);
		HRESULT Set_Font(int fontNumber);
		HRESULT Set_Color(int _colorNumber);
		HRESULT Destroy_Font();
		HRESULT Destroy_Fonts();
		HRESULT Reset_Colors();
		HRESULT ChangeRec(int Coordinate, int Value);
		HRESULT Initiate_TextString(LPCSTR _string, int fontnumber, RECT _rec);
		HRESULT Change_TextString(LPCSTR _string);
		};
	class TEXTURES
		{
	public:
		///////////
		struct TEXTURE_DATA
			{
			LPDIRECT3DTEXTURE9	*	texture;
			RECT					area;
			TEXTURE_DATA(LPDIRECT3DTEXTURE9 * _texture, RECT _area);
			TEXTURE_DATA();
			~TEXTURE_DATA();
			};
		static	LPDIRECT3DTEXTURE9	DefaultTexture;
		///////////
	private:
		///////////
		//path - data
		map<string, TEXTURE_DATA>	Textures;
		///////////
	public:
		///////////
	TEXTURES(LPDIRECT3DDEVICE9 _device);
	~TEXTURES();
		HRESULT Add_Texture(string _path, LPDIRECT3DTEXTURE9 * _texture);
		HRESULT Add_Texture(string _path, LPDIRECT3DDEVICE9 _device);
		HRESULT Remove_Texture(string _path);
		LPDIRECT3DTEXTURE9 Get_Texture(string _path);
		HRESULT Set_Texture(string _path, LPDIRECT3DTEXTURE9 * _texture);
		HRESULT Update_Default(LPDIRECT3DDEVICE9 _device);
	private:
		HRESULT Load_Texture(string _path, LPDIRECT3DDEVICE9 _device);
		};
	class GEOMETRY
		{
	public:
		map<LPCSTR, VERTEX_BASE *> Verteces;
	GEOMETRY() {};
	~GEOMETRY() {};
		void Add_Verteces(LPCSTR _name, VERTEX_BASE * _verteces)
			{
			if ((!_name) || (!_verteces)) return;
			if (Verteces.size())
				{
				if (Verteces.find(_name) != Verteces.end())
					AfxMessageBox("Geometry with current name already exists.");
				} else 
			Verteces[_name] = _verteces;
			if (Verteces.size() > 65500) AfxMessageBox("More than 65500 geometrical models were downloaded.");
			};
		void Remove_Verteces(LPCSTR _name)
			{
			if ((!_name) || (!Verteces.size())) return;
			if (Verteces.find(_name) != Verteces.end()) { Verteces.erase(_name); } else AfxMessageBox("Geometry with current name doesn't exist.");
			};
		VERTEX_BASE * Get_Verteces(LPCSTR _name)
			{
			if ((!_name) || (!Verteces.size())) return NULL;
			if (Verteces.find(_name) != Verteces.end()) return Verteces[_name]; else AfxMessageBox("Geometry with current name doesn't exist. Nothing to return.");
			return NULL;
			};
		void Set_Verteces(LPCSTR _name, VERTEX_BASE * _verteces)
			{
			if ((!_name) || (!_verteces) || (!Verteces.size())) return;
			if (Verteces.find(_name) != Verteces.end())
				Verteces[_name] = _verteces; 
			else 
				AfxMessageBox("Geometry with current name doesn't exist. Nothing to apply to.");
			};
		};

	//////////// SINGLETONS \\\\\\\\\\\\

	class UPSCREEN
		{
	public:
		static UPSCREEN& Instance()
			{
			static UPSCREEN theSingleInstance;
			return theSingleInstance;
			}
		LPDIRECT3DVERTEXBUFFER9 UPSCREENBUFFER;
		void Render_UpScreen(LPDIRECT3DDEVICE9 _device) 
			{
			if ((!_device) || (!UPSCREENBUFFER)) return;
			_device->SetFVF(VertexesFVF2D);
			_device->SetStreamSource(0,UPSCREENBUFFER,0,sizeof(VERTEXDEFINITECOLOR));
			_device->DrawPrimitive (D3DPT_TRIANGLESTRIP, 0, 2);
			};
		void Fill_UpScreen(LPDIRECT3DDEVICE9 _device, D3DDISPLAYMODE _D3DM, DWORD _newColor)
			{
			if ((!_device) || (!Geometry)) return;
			VERTEX_BASE * UpScreenBase = Geometry->Get_Verteces("UPSCREEN");

			if (!UpScreenBase)
				{
				VERTEXDEFINITECOLOR UpScreen[4];

				UpScreen[0].X = 0; UpScreen[0].Y = 0; UpScreen[0].Z = 0.5; UpScreen[0].RHW = 1; UpScreen[0].COLOR = _newColor;
				UpScreen[1].X = _D3DM.Width; UpScreen[1].Y = 0; UpScreen[1].Z = 0.5; UpScreen[1].RHW = 1; UpScreen[1].COLOR = _newColor;
				UpScreen[2].X = 0; UpScreen[2].Y = _D3DM.Height; UpScreen[2].Z = 0.5; UpScreen[2].RHW = 1; UpScreen[2].COLOR = _newColor;
				UpScreen[3].X = _D3DM.Width; UpScreen[3].Y = _D3DM.Height; UpScreen[3].Z = 0.5; UpScreen[3].RHW = 1; UpScreen[3].COLOR = _newColor;

				Geometry->Add_Verteces("UPSCREEN", UpScreen);
				} else {
				VERTEXDEFINITECOLOR * UpScreen = (VERTEXDEFINITECOLOR *) UpScreenBase;

				UpScreen[0].COLOR = UpScreen[1].COLOR = UpScreen[2].COLOR = UpScreen[3].COLOR = _newColor;

				Geometry->Set_Verteces("UPSCREEN", UpScreen);
				}
			
			VERTEXDEFINITECOLOR * UpScreen = (VERTEXDEFINITECOLOR *) Geometry->Get_Verteces("UPSCREEN");
			if (!UPSCREENBUFFER) 
				_device->CreateVertexBuffer(sizeof(VERTEXDEFINITECOLOR)*4,0,VertexesFVF2D,D3DPOOL_MANAGED,&UPSCREENBUFFER,NULL);
			VOID* pData = NULL;
			UPSCREENBUFFER->Lock(0,sizeof(pData),(void**)&pData,0);
			memcpy(pData,UpScreen,sizeof(VERTEXDEFINITECOLOR)*4);
			UPSCREENBUFFER->Unlock();
			}

	private:        
	
		UPSCREEN(){}
		inline GRAPHCORE::UPSCREEN::UPSCREEN ( const UPSCREEN & root )
			{}
		;
		UPSCREEN(const UPSCREEN& root);
		~UPSCREEN()
			{
			OBJRELEASE(UPSCREENBUFFER);
			Geometry->Remove_Verteces("UPSCREEN");
			}
		inline UPSCREEN & GRAPHCORE::UPSCREEN::operator=( const UPSCREEN & )
			{
			// TODO: insert return statement here
			}
		inline void GRAPHCORE::UPSCREEN::deleteInstance ()
			{
			OBJDELETE ( Object );
			};
		UPSCREEN& operator=(const UPSCREEN&);
		};
	class GRID
		{
	public:
		static GRID& Instance();
		LPDIRECT3DVERTEXBUFFER9 VERTEXBUFFER;
		long vertcolor3DQuantity;
		const LPCSTR name;
		void Render_Grid(LPDIRECT3DDEVICE9 _device);
		void Fill_Grid(LPDIRECT3DDEVICE9 _device, D3DDISPLAYMODE _D3DM, float _a, int _size, DWORD _newColor);

	private:        
	
		GRID();
		GRID(const GRID& root);
		~GRID();
		GRID& operator=(const GRID&);
		};
	
	//////////////// 1+ \\\\\\\\\\\\\\\\

	class CAMERAS
		{
	public:
		D3DXVECTOR3 position, target, up;
		D3DXMATRIX	current_Camera;
		D3DXMATRIX	current_Camera_Projection;
		///////////
		float		angle_Of_View;
		float		resolution_Of_Screen;
		float		starting_Point;
		float		ending_Point;
		///////////
		static int	camera_Count;
		///////////
		double		object_Rotate_Presentation;
		double		camera_Height_Presentation;
		///////////

	CAMERAS(float _param_X, float _param_Y, float _startPosX = CAMERA_STARTING_POS, float _startPosY = CAMERA_STARTING_POS, float _startPosZ = CAMERA_STARTING_POS, float _endPosX = 0, float _endPosY = 0, float _endPosZ = 0):
		position(_startPosX, _startPosY, _startPosZ), target(_endPosX, _endPosY, _endPosZ), up(0, 1, 0),
		angle_Of_View(45), resolution_Of_Screen(_param_X/_param_Y), starting_Point(1), ending_Point(2000),
		object_Rotate_Presentation(316), camera_Height_Presentation(90)
		{
		camera_Count++;
		D3DXMatrixIdentity(&current_Camera);
		D3DXMatrixIdentity(&current_Camera_Projection); 
		};
	~CAMERAS()
		{
		camera_Count--;
		};
		void Fill_Position(float _x, float _y, float _z) { position.x = _x; position.y = _y; position.z = _z; return; };
		void Fill_Target(float _x, float _y, float _z) { target.x = _x; target.y = _y; target.z = _z; return; };
		void Fill_Matrix_Camera (LPDIRECT3DDEVICE9 DEVICE) { D3DXMatrixLookAtLH(&current_Camera, &position, &target, &up); DEVICE->SetTransform(D3DTS_VIEW, &current_Camera); };
		void Fill_Matrix_Projection (LPDIRECT3DDEVICE9 DEVICE) { D3DXMatrixPerspectiveFovLH(&current_Camera_Projection, angle_Of_View, resolution_Of_Screen, starting_Point, ending_Point); DEVICE->SetTransform(D3DTS_PROJECTION, &current_Camera_Projection); };

		const float& AngleOfView () const { return angle_Of_View; };
		float& AngleOfViewChange () { return angle_Of_View; };

		const float& Resolution () const { return resolution_Of_Screen; };
		float& ResolutionChange () { return resolution_Of_Screen; };

		static int& CameraCount () {return camera_Count; };

		const float& StartPoint () const { return starting_Point; };
		float& StartPoint () { return starting_Point; };

		const float& EndPoint () const { return ending_Point; };
		float& EndPoint () { return ending_Point; };

		void SetPresentation (LPDIRECT3DDEVICE9 DEVICE, double Speed) {
			object_Rotate_Presentation-=Speed; if (object_Rotate_Presentation <= -361) object_Rotate_Presentation = 360;
			double Radius = sqrt(position.x*position.x + position.z*position.z);
			Fill_Position(Radius*sin(D3DXToRadian(object_Rotate_Presentation)), position.y, Radius*cos(D3DXToRadian(object_Rotate_Presentation)));
			Fill_Matrix_Camera(DEVICE);};
		void CameraMovesUp(LPDIRECT3DDEVICE9 DEVICE) {
			camera_Height_Presentation -= 0.7;
			if (camera_Height_Presentation <= 0) camera_Height_Presentation = 0;

			Fill_Position(position.x, position.y + cos(D3DXToRadian(90-camera_Height_Presentation))*3, position.z);
			Fill_Matrix_Camera(DEVICE);};
		void CameraMovesTo(LPDIRECT3DDEVICE9 DEVICE, int X, int X1, int Z, int Z1, int Y) {
			if (camera_Height_Presentation == 0) SetDefault_Camera_Height_Presentation();
			Fill_Position(position.x + (X-position.x)/camera_Height_Presentation, position.y + (Y-position.y)/camera_Height_Presentation, position.z + (Z - position.z)/camera_Height_Presentation);
			Fill_Target(target.x + (X1-target.x)/camera_Height_Presentation, target.y, target.z + (Z1 - target.z)/camera_Height_Presentation);
			Fill_Matrix_Camera(DEVICE);
			camera_Height_Presentation--;
		};
		void SetDefault_Camera_Height_Presentation() { camera_Height_Presentation = 45; };
		};

	//////////////// ANY \\\\\\\\\\\\\\\\

	class MESHES_X
		{
	public:
		struct MESHES_DATA
			{
			LPD3DXMESH *						mesh;				// Our mesh object in sysmem
			D3DMATERIAL9 *						meshMaterials;		// Materials for our mesh
			std::vector<string>	meshTextures;	// Textures for our mesh
			DWORD								materialsQuantity;	// Number of mesh materials
		MESHES_DATA();
		~MESHES_DATA();
			};
	
		static	 	LPD3DXMESH					defaultMesh;
		static		D3DMATERIAL9 *				defaultMeshMaterial;		// Materials for our mesh
	private:
		LPD3DXBUFFER							buffer;				// Buffer of meshes
		map<string, MESHES_DATA>				Meshes;
		///////////
	public:

	MESHES_X(LPDIRECT3DDEVICE9 _device);
	~MESHES_X();

		HRESULT Add_Mesh(string _path, LPDIRECT3DDEVICE9 _device);
		HRESULT Remove_Mesh(string _path);
		HRESULT Clean();
		MESHES_DATA * Get_Mesh(string _path);
		HRESULT Set_Mesh(string _path, MESHES_DATA * _mesh);
		HRESULT Update_Default(LPDIRECT3DDEVICE9 _device);
		long Get_Meshes_Quantity();
	private:
		HRESULT Load_Mesh(string _path, LPDIRECT3DDEVICE9 _device);
		};
	class MAPS
		{
	public:
		CString Name;
		const int ID;
	
		struct MAPMESH
			{
			MESHES_X* Mesh;
			///////////
			float Xt, Yt, Zt;
			float Xa, Ya, Za;
			float Xs, Ys, Zs;
		MAPMESH(MESHES_X * _mesh, float _Xt, float _Yt, float _Zt, float _Xa, float _Ya, float _Za, float _Xs, float _Ys, float _Zs):
				Mesh (_mesh), Xt(_Xt), Yt(_Yt), Zt(_Zt), Xa(_Xa), Ya(_Ya), Za(_Za), Xs(_Xs), Ys(_Ys), Zs(_Zs) { };
		~MAPMESH()
			{
			OBJDELETE(Mesh);
			}
			};
		std::vector<MAPMESH>LIST_MESH;

		struct COLLISIONS
			{
			VERTEXTEXTURE					texPointer[4];
			COLLISIONS	*					NextCollision;
			static LPDIRECT3DTEXTURE9 		texture;
			static LPDIRECT3DVERTEXBUFFER9	CollisionBuffer;
			static COLLISIONS  *			Root;
			static int						Quantity;
			COLLISIONS(): NextCollision(NULL) {};
			~COLLISIONS() { delete texture; };
			} * Collision;

		MAPS(): ID(0)
			{ };
		~MAPS()
			{ };

		};
	class OBJECTS
		{
	public:
		struct OBJECT_DATA
			{
			string name;
			const int ID;
			static int quantity;
			enum MATERIAL_TYPES
				{
				Dummy,
				Static,
				Active
				} Type;
			D3DXVECTOR3 translation;
			D3DXVECTOR3 rotation;
			D3DXVECTOR3 scaling;
			struct OBJECTMESH
				{
				OBJECT_DATA&	Parent;
				string			meshName;
				//////////////////////
				D3DXVECTOR3		rotation;		//Angle Matrix in Radians 
				D3DXVECTOR3		scaling;		//Scale Matrix
				D3DXVECTOR3		translation;	//Translation Matrix
				BOUNDINGSPHERE  Sphere;
				BOUNDINGBOX		Box;
				//////////////////////
			OBJECTMESH(OBJECT_DATA& _parent, LPCSTR _meshName, D3DXVECTOR3 _translation, D3DXVECTOR3 _rotation, D3DXVECTOR3 _scaling);
			~OBJECTMESH();

				void SetXt(float _Xt);
				void SetYt(float _Yt);
				void SetZt(float _Zt);
				void SetXa(float _Xa);
				void SetYa(float _Ya);
				void SetZa(float _Za);
				void SetXs(float _Xs);
				void SetYs(float _Ys);
				void SetZs(float _Zs);

				const float &GetXt() const;
				const float &GetYt() const;
				const float &GetZt() const;
				const float &GetXa() const;
				const float &GetYa() const;
				const float &GetZa() const;
				const float &GetXs() const;
				const float &GetYs() const;
				const float &GetZs() const;

				void ApplyMeshWorldMatrix(LPDIRECT3DDEVICE9 _device);
				};
			list<OBJECTMESH> LIST_MESH;
		public:
			OBJECT_DATA() : ID(quantity++) { };
			OBJECT_DATA(string _name, MATERIAL_TYPES _type, D3DXVECTOR3 _translation, D3DXVECTOR3 _rotation, D3DXVECTOR3 _scaling);
			~OBJECT_DATA();
			
			const string	ObjectName () const;
			string			ObjectNameChange ();

			void			SetXt(float _Xt);
			void			SetYt(float _Yt);
			void			SetZt(float _Zt);

			const float	&GetXt() const;
			const float	&GetYt() const;
			const float	&GetZt() const;

			HRESULT Apply_Texture(LPDIRECT3DTEXTURE9 * _texture, MESHES_X * Model);
			HRESULT Add_Mesh(LPDIRECT3DDEVICE9 _device, LPCSTR _meshName, WORLDPOSITION _pos);
			HRESULT Add_Mesh(LPCSTR _name, D3DXVECTOR3 _translation, D3DXVECTOR3 _angle, D3DXVECTOR3 _scaling);
			void	ApplyObjectWorldMatrix(LPDIRECT3DDEVICE9 DEVICE);
			HRESULT Clean();
			};
		list<OBJECT_DATA>			Objects;
		list<OBJECT_DATA>::iterator	Objects_Iter;

	public:

	OBJECTS();
	~OBJECTS();

		list<OBJECT_DATA>::iterator Add_Object(string _name, OBJECT_DATA::MATERIAL_TYPES _type, D3DXVECTOR3 _position);
		HRESULT						Remove_Object(list<OBJECT_DATA>::iterator _member);
		HRESULT						Clean();
		OBJECT_DATA *				Get_Object(list<OBJECT_DATA>::iterator _member);
		int							Object_Quantity();
		static OBJECTS *			Set_Current_Object(int _ID, LPCSTR _name);
		};

	static CAMERAS *				Camera;
	static GEOMETRY *				Geometry;
	static MAPS *					Map;
	static MESHES_X *				Mesh;
	static OBJECTS *				Object;
	static TEXTSTRINGS *			Text;
	static TEXTURES	*				Texture;
	
	map<CString, MESHES_X *>							MAP_UI;		//Models
	//map<int, list<OBJECTS::OBJECT_DATA>::iterator>	MAP_OBJ;	//Objects
	map<int, OBJECTS::OBJECT_DATA>						MAP_OBJ;	//Objects
	map<CString, TEXTURES *>							MAP_TEX;	//Textures
	map<CString, BOUNDINGSPHERE *>						MAP_COL;	//CollisionsSpherical
	vector<int>											Heightmap;

GRAPHCORE();
~GRAPHCORE();

//--------------INITIATION-------------//

	HRESULT			Initiate_D3D(HWND _hWnd);													// Инициировать Директ Х
	HRESULT			Initiate_Device(HWND _hWnd, bool _IsFullScreen, int _sizeX, int _sizeY);	// Инициировать Устройство (видуху)
	HRESULT			Initiate_MaterialsAndTextures();											// Инициировать все настройки текстур
	HRESULT			Initiate_IndexGrid();
	HRESULT			Initiate_IndexBuffer();														// Инициировать все настройки текстур
	HRESULT			Initiate_Font(char* _facename, int _Height, int _Weight, bool _IsItalic);	// Инициировать шрифт
	HRESULT			Initiate_Color(D3DCOLOR _color, int _position);								// Инициировать цвет

	TEXTSTRINGS *	Initiate_Text(LPCSTR _name, int _fontNumber, RECT _rec);			// Инициировать текст

	HRESULT			Initiate_Surface(int _height, int _width, LPCSTR _name);			// Инициировать поверхность
	HRESULT			Initiate_TextureScreen(float X1, float Y1, float X2, 
										   float Y2, float X3, float Y3, 
										   float X4, float Y4);							// Экран из текстур
	HRESULT			Initiate_TexturePointer(float X1, float Z1, float X2,
											float Z2, float X3, float Z3,
											float X4, float Z4);

	HRESULT			Initiate_Object(LPCSTR _name, int type, OBJECTS::OBJECT_DATA::MATERIAL_TYPES _type, D3DXVECTOR3 _pos);			// Инициировать объект .x
	MESHES_X *		Load_Geometry(LPCSTR _name);										// Инициировать меш .x
	CAMERAS *		Initiate_Camera(float _param_X, float _param_Y,
								float _startPosX = 300.0f, float _startPosY = 300.0f, float _startPosZ = 300.0f,
								float _endPosX = 0, float _endPosY = 0, float _endPosZ = 0); // Инициировать камеру
	HRESULT			Initiate_Terrain(std::string fileName);

	//---------------RENDERING--------------//

	HRESULT Render_Verteces();															// Вывести на экран точку
	HRESULT Render_Grid();																// Вывести на экран сетку (ландшафт)
	HRESULT Render_Text(TEXTSTRINGS* _text);											// Вывести на экран текст
	HRESULT Render_Sprite(RECT src1, RECT dest1);										// Вывести на экран спрайт
	HRESULT Render_UpScreen();															// Вывести на экран перекрывающий экран
	HRESULT Render_Texture(LPCSTR _name);															// Вывести на экран текстуру
	HRESULT Render_Meshes();															// Вывести на экран меш
	HRESULT Render_Objects();															// Вывести на экран объект
	HRESULT Render_Effect();															// Вывести на экран спец-эффект

	//--------------DESTRUCTION-------------//

	HRESULT Destroy_D3D();
	HRESULT Destroy_Device();
	HRESULT Destroy_Font(LPD3DXFONT font);												// Уничтожить шрифт
	HRESULT Destroy_Surface(LPDIRECT3DSURFACE9 SURFACE);
	HRESULT Destroy_UpScreen(LPDIRECT3DVERTEXBUFFER9);
	HRESULT Destroy_Texture(LPCSTR name);
	HRESULT Destroy_Text(LPCSTR name);
	HRESULT Destroy_Texts();
	HRESULT Destroy_Mesh(LPCSTR name, CString _name);
	HRESULT Destroy_Meshes();
	HRESULT Destroy_Object(int _ID);
	HRESULT Destroy_Objects();
	HRESULT Destroy_Cameras();

	HRESULT Fill_VertexBuffer();														// Инициировать все настройки текстур
	HRESULT Fill_UpScreen(DWORD);														// Инициировать все настройки текстур
	HRESULT Fill_Grid(float _a, int _size, DWORD _newColor);										// Инициировать все настройки текстур
	HRESULT ChangeTextureMap(LPDIRECT3DTEXTURE9 texture);
	HRESULT ChangeUpScreenAlpha(int alpha);
	void	SetRenderState(_D3DRENDERSTATETYPE _type, DWORD _value);
	};
class ENGINE
	{
public:

	struct RAY
		{
		D3DXVECTOR3 _origin;
		D3DXVECTOR3 _direction;
		} PickingRay;

	struct FPS
		{
		float FrameCnt;    // Количество выведенных кадров
		float TimeElapsed /* Прошедшее время */, fps /* Частота визуализации кадров */, Time_Start, Time_End;
		FPS() { FrameCnt = TimeElapsed = fps = Time_Start = Time_End = 0;};
		} FPS;

	struct POINTER
		{
		D3DXVECTOR3 Angles;
		D3DXMATRIX	TRANSLATION, ROTATION, SCALING, Current_Model;
		GRAPHCORE::VERTEXTEXTURE texPointer[4];
		GRAPHCORE::VERTEX defCoords[4];
		LPDIRECT3DTEXTURE9 texture;
		static LPDIRECT3DVERTEXBUFFER9 POINTERBUFFER;
	POINTER(): texture(NULL), Angles(0,0,0) 
		{
		defCoords[0]._x = texPointer[0].X = 20; defCoords[0]._y = texPointer[0].Y = 0; defCoords[0]._z = texPointer[0].Z = 20; texPointer[0].fU = 0; texPointer[0].fV = 0; texPointer[0].COLOR = D3DCOLOR_RGBA(255, 255, 255, 0);
		defCoords[1]._x = texPointer[1].X = 20; defCoords[1]._y = texPointer[1].Y = 0; defCoords[1]._z = texPointer[1].Z = -20; texPointer[1].fU = 1; texPointer[1].fV = 0; texPointer[1].COLOR = D3DCOLOR_RGBA(255, 255, 255, 0);
		defCoords[2]._x = texPointer[2].X = -20; defCoords[2]._y = texPointer[2].Y = 0; defCoords[2]._z = texPointer[2].Z = 20; texPointer[2].fU = 0; texPointer[2].fV = 1; texPointer[2].COLOR = D3DCOLOR_RGBA(255, 255, 255, 0);
		defCoords[3]._x = texPointer[3].X = -20; defCoords[3]._y = texPointer[3].Y = 0; defCoords[3]._z = texPointer[3].Z = -20; texPointer[3].fU = 1; texPointer[3].fV = 1; texPointer[3].COLOR = D3DCOLOR_RGBA(255, 255, 255, 0);
		D3DXMatrixIdentity(&ROTATION);
		D3DXMatrixIdentity(&SCALING);
		D3DXMatrixIdentity(&TRANSLATION);
		};
		} Pointer; //Current Pointer Tex

	ENGINE() {};
	~ENGINE() {};

	HRESULT Initiate_Engine(LPDIRECT3DDEVICE9 _device, GRAPHCORE::TEXTURES * _tex)
		{
		_device->CreateVertexBuffer(sizeof(Pointer.texPointer[0])*4,0,VertexexFVF3DColTex,D3DPOOL_MANAGED,&Pointer.POINTERBUFFER,NULL);
		VOID* pData = NULL;
		Pointer.POINTERBUFFER->Lock(0,0,(void**)&pData,0);
		memcpy(pData,Pointer.texPointer,sizeof(Pointer.texPointer[0])*4);
		Pointer.POINTERBUFFER->Unlock();
		Pointer.texture = _tex->Get_Texture("DEFAULT");
		return S_OK;
		};
	HRESULT Change_Pointer_Coords(LPDIRECT3DDEVICE9 _device, int Direction)
	{
		switch (Direction)
		{
		case 1: D3DXMatrixTranslation(&Pointer.TRANSLATION, Pointer.TRANSLATION._41, Pointer.TRANSLATION._42, Pointer.TRANSLATION._43+40); break;
		case 2: D3DXMatrixTranslation(&Pointer.TRANSLATION, Pointer.TRANSLATION._41+40, Pointer.TRANSLATION._42, Pointer.TRANSLATION._43); break;
		case 3: D3DXMatrixTranslation(&Pointer.TRANSLATION, Pointer.TRANSLATION._41, Pointer.TRANSLATION._42, Pointer.TRANSLATION._43-40); break;
		case 4: D3DXMatrixTranslation(&Pointer.TRANSLATION, Pointer.TRANSLATION._41-40, Pointer.TRANSLATION._42, Pointer.TRANSLATION._43); break;
		case 5: D3DXMatrixTranslation(&Pointer.TRANSLATION, Pointer.TRANSLATION._41, Pointer.TRANSLATION._42+40, Pointer.TRANSLATION._43); break;
		case 6: D3DXMatrixTranslation(&Pointer.TRANSLATION, Pointer.TRANSLATION._41, Pointer.TRANSLATION._42-40, Pointer.TRANSLATION._43); break;
		case 7: D3DXMatrixRotationYawPitchRoll(&Pointer.ROTATION, D3DXToRadian(Pointer.Angles.x-3), D3DXToRadian(Pointer.Angles.y), D3DXToRadian(Pointer.Angles.z)); Pointer.Angles.x-=3; break;
		case 8: D3DXMatrixRotationYawPitchRoll(&Pointer.ROTATION, D3DXToRadian(Pointer.Angles.x+3), D3DXToRadian(Pointer.Angles.y), D3DXToRadian(Pointer.Angles.z)); Pointer.Angles.x+=3; break;
		case 9: D3DXMatrixRotationYawPitchRoll(&Pointer.ROTATION, D3DXToRadian(Pointer.Angles.x), D3DXToRadian(Pointer.Angles.y-3), D3DXToRadian(Pointer.Angles.z)); Pointer.Angles.y-=3; break;
		case 10: D3DXMatrixRotationYawPitchRoll(&Pointer.ROTATION, D3DXToRadian(Pointer.Angles.x), D3DXToRadian(Pointer.Angles.y+3), D3DXToRadian(Pointer.Angles.z)); Pointer.Angles.y+=3; break;
		case 11: D3DXMatrixRotationYawPitchRoll(&Pointer.ROTATION, D3DXToRadian(Pointer.Angles.x), D3DXToRadian(Pointer.Angles.y), D3DXToRadian(Pointer.Angles.z-3)); Pointer.Angles.z-=3; break;
		case 12: D3DXMatrixRotationYawPitchRoll(&Pointer.ROTATION, D3DXToRadian(Pointer.Angles.x), D3DXToRadian(Pointer.Angles.y), D3DXToRadian(Pointer.Angles.z+3)); Pointer.Angles.z+=3; break;
		case 13: D3DXMatrixScaling(&Pointer.SCALING, Pointer.SCALING._11-0.2f, Pointer.SCALING._22, Pointer.SCALING._33); break;
		case 14: D3DXMatrixScaling(&Pointer.SCALING, Pointer.SCALING._11+0.2f, Pointer.SCALING._22, Pointer.SCALING._33); break;
		case 15: D3DXMatrixScaling(&Pointer.SCALING, Pointer.SCALING._11, Pointer.SCALING._22, Pointer.SCALING._33-0.2f); break;
		case 16: D3DXMatrixScaling(&Pointer.SCALING, Pointer.SCALING._11, Pointer.SCALING._22, Pointer.SCALING._33+0.2f); break;
		};

		Pointer.Current_Model = Pointer.ROTATION * Pointer.SCALING * Pointer.TRANSLATION;
		for (int i = 0; i <=3 ; i++)
		{
		Pointer.texPointer[i].X = Pointer.defCoords[i]._x*Pointer.Current_Model._11 + Pointer.defCoords[i]._y*Pointer.Current_Model._21 + Pointer.defCoords[i]._z*Pointer.Current_Model._31 + Pointer.Current_Model._41;
		Pointer.texPointer[i].Y = Pointer.defCoords[i]._x*Pointer.Current_Model._12 + Pointer.defCoords[i]._y*Pointer.Current_Model._22 + Pointer.defCoords[i]._z*Pointer.Current_Model._32 + Pointer.Current_Model._42;
		Pointer.texPointer[i].Z = Pointer.defCoords[i]._x*Pointer.Current_Model._13 + Pointer.defCoords[i]._y*Pointer.Current_Model._23 + Pointer.defCoords[i]._z*Pointer.Current_Model._33 + Pointer.Current_Model._43;
		}
	Pointer.POINTERBUFFER->Release();
	_device->CreateVertexBuffer(sizeof(Pointer.texPointer[0])*4,0,VertexexFVF3DColTex,D3DPOOL_MANAGED,&Pointer.POINTERBUFFER,NULL);
	VOID* pData = NULL;
	Pointer.POINTERBUFFER->Lock(0,0,(void**)&pData,0);
	memcpy(pData,Pointer.texPointer,sizeof(Pointer.texPointer[0])*4);
	Pointer.POINTERBUFFER->Unlock();
	return S_OK;
	};
	HRESULT Change_Pointer_Texture(GRAPHCORE::TEXTURES * _tex) { Pointer.texture = _tex->Get_Texture("DEFAULT"); };
	HRESULT Add_Wall (LPDIRECT3DDEVICE9 _device, GRAPHCORE::MAPS * map) 
	{
		if (map->Collision == NULL) { 
			map->Collision = new GRAPHCORE::MAPS::COLLISIONS; map->Collision->Root = map->Collision; map->Collision->Quantity++; 
		} else {
			map->Collision->NextCollision = new GRAPHCORE::MAPS::COLLISIONS; map->Collision->Quantity++; map->Collision = map->Collision->NextCollision;
		};
		map->Collision->texPointer[0] = Pointer.texPointer[0];
		map->Collision->texPointer[1] = Pointer.texPointer[1];
		map->Collision->texPointer[2] = Pointer.texPointer[2];
		map->Collision->texPointer[3] = Pointer.texPointer[3];

		map->Collision->texture = Pointer.texture;

		GRAPHCORE::MAPS::COLLISIONS * Temp = map->Collision->Root; GRAPHCORE::VERTEXTEXTURE * TempVert = new GRAPHCORE::VERTEXTEXTURE[4*map->Collision->Quantity]; int TempNumb = 0;

		if (map->Collision->CollisionBuffer!=NULL) map->Collision->CollisionBuffer->Release();
		_device->CreateVertexBuffer(sizeof(map->Collision->texPointer[0])*4*map->Collision->Quantity,0,VertexexFVF3DColTex,D3DPOOL_MANAGED,&map->Collision->CollisionBuffer,NULL);
		map->Collision->CollisionBuffer->Lock(0,0,(void**)&TempVert,0);

		while (Temp!=NULL)
		{
			TempVert[0+4*TempNumb] = Temp->texPointer[0];
			TempVert[1+4*TempNumb] = Temp->texPointer[1];
			TempVert[2+4*TempNumb] = Temp->texPointer[2];
			TempVert[3+4*TempNumb] = Temp->texPointer[3];
		Temp = Temp->NextCollision;
		TempNumb++;
		}

		map->Collision->CollisionBuffer->Unlock();
	return S_OK;
	};
	HRESULT Render_Pointer(LPDIRECT3DDEVICE9 _device)
	{
		//Draw Pointer
	_device->SetStreamSource(0,Pointer.POINTERBUFFER,0,sizeof(GRAPHCORE::VERTEXTEXTURE));
	_device->SetTexture(0,Pointer.texture);
	_device->DrawPrimitive (D3DPT_TRIANGLESTRIP, 0, 2);

	_device->SetTexture(0,NULL);
	return S_OK;
	};

	CString DoRayProcedure(int x, int y, LPDIRECT3DDEVICE9 device, GRAPHCORE::OBJECTS * Object);

	HRESULT CalculatePickingRay(int x, int y, LPDIRECT3DDEVICE9 device);
	HRESULT TransformPickingRay(LPDIRECT3DDEVICE9 device);

	bool RaySphereIntersectionTest(GRAPHCORE::BOUNDINGSPHERE * sphere);
	float * RayCubeIntersectionTest(GRAPHCORE::BOUNDINGBOX * box);
	};