#include "../../_inc/DirectX.h"

//---------------------------------------DIRECTX 10.0-11.0----------------------------------------//
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>

static DXGI_MODE_DESC			BackBufferDescription = { 0, 0, 60, 1, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED, DXGI_MODE_SCALING_STRETCHED };
static DXGI_SWAP_CHAIN_DESC    SwapChainDescription = { BackBufferDescription, 1, 0, DXGI_USAGE_RENDER_TARGET_OUTPUT, 2, NULL, TRUE, DXGI_SWAP_EFFECT_DISCARD };
static D3D11_TEXTURE2D_DESC		DepthStencilDescription = { 0, 0, 1, 1, DXGI_FORMAT_D24_UNORM_S8_UINT, 1, 0, D3D11_USAGE_DEFAULT, D3D11_BIND_DEPTH_STENCIL, 0, 0 };
//--------------------------------------~DIRECTX 10.0-11.0----------------------------------------//

//class	DIRECTX11 : public DIRECTX
//{
//
//public:
//
//	//----------------------ARGUMENTS-----------------------//
//
//	ID3D11Texture2D*							d3d11BackBuffer;							//d3d11BackBuffer... 2D Texture to paint on screen
//	IDXGISwapChain*								d3d11SwapChain;
//	ID3D11Device*								d3d11Device;						//Interface we will use to represent our hardware device (GPU)
//	ID3D11DeviceContext*						d3d11DevCon;
//	ID3D11RenderTargetView*						d3d11RenderTargetView;
//	D3D11_VIEWPORT								d3d11Viewport;
//
//	//--------DirectX 11.0 Z Buffer----------//
//	ID3D11DepthStencilView*						d3d11DepthStencilView;
//	ID3D11Texture2D*							d3d11DepthStencilBuffer;
//	D3D11_DEPTH_STENCIL_DESC					d3d11DepthStencilDescription;
//	//-------~DirectX 11.0 Z Buffer----------//
//
//	//--------DirectX 11.0 Blending----------//
//	D3D11_BLEND_DESC							d3d11BlendDescription;
//	D3D11_RENDER_TARGET_BLEND_DESC				d3d11RenderTargetBlendDescription;
//	ID3D11BlendState							* Transparency;
//	//-------~DirectX 11.0 Blending----------//
//
//	//---------------Picking----------------//
//	std::vector<D3DXVECTOR3> groundVertPosArray;
//	std::vector<D3DXVECTOR3> bottleVertPosArray;
//	std::vector<DWORD> groundVertIndexArray;
//	std::vector<DWORD> bottleVertIndexArray;
//	std::vector<int> bottleSubsetIndexStart;
//	std::vector<int> bottleSubsetTexture;
//	ID3D11Buffer* bottleVertBuff;
//	ID3D11Buffer* bottleIndexBuff;
//	D3DXMATRIX bottleWorld[20];
//	D3DXMATRIX Rotation;
//	D3DXMATRIX Scale;
//	D3DXMATRIX Translation;
//	int* bottleHit;
//	int bottleSubsets;
//	int numBottles;
//	int ClientWidth;
//	int ClientHeight;
//	int score;
//	bool isShoot;
//	float pickedDist;
//	//--------------~Picking----------------//
//
//	class SHADERS;
//
//	struct FVF_BASE
//	{
//	public:
//
//		static ID3D11Device*						d3d11Device;
//		static ID3D11DeviceContext*					d3d11DevCon;
//		static IDXGISwapChain*						d3d11SwapChain;
//
//		static D3D11_DEPTH_STENCIL_DESC				DepthStencilDescriptionOn, DepthStencilDescriptionOff;
//		static ID3D11DepthStencilState				* DepthStencilStateLessEqual, *DepthStencilStateNone;
//		static D3D11_RASTERIZER_DESC				d3d11RasterizerDescription;
//		static ID3D11RasterizerState				* WireFrame, *CCWcullMode, *CWcullMode, *RSCullNone;
//		static D3D11_BUFFER_DESC					BufferDesc;
//		static D3D11_SUBRESOURCE_DATA				BufferData;
//		static D3D11_SAMPLER_DESC					samplerDescription;
//
//		std::map<LPCSTR, std::pair<SHADERS*, ID3D11InputLayout *>> ShaderLayout;
//		LPCSTR										currentShader;
//
//		UINT										stride, offset;
//		ID3D11Buffer								* vertBuffer, *indexBuffer, *ClipBoardShaderBuffer;
//
//		FVF_BASE(UINT _stride) : stride(_stride), offset(0), vertBuffer(NULL), indexBuffer(NULL), ClipBoardShaderBuffer(NULL), currentShader(NULL)
//		{
//			//-----------------------------Rasterizers----------------------------//
//			d3d11RasterizerDescription.FillMode = D3D11_FILL_WIREFRAME;
//			d3d11RasterizerDescription.CullMode = D3D11_CULL_NONE;
//			d3d11Device->CreateRasterizerState(&d3d11RasterizerDescription, &WireFrame);
//
//			d3d11RasterizerDescription.FillMode = D3D11_FILL_SOLID;
//			d3d11RasterizerDescription.CullMode = D3D11_CULL_BACK;
//			d3d11RasterizerDescription.FrontCounterClockwise = true;
//			d3d11Device->CreateRasterizerState(&d3d11RasterizerDescription, &CCWcullMode);
//
//			d3d11RasterizerDescription.FrontCounterClockwise = false;
//			d3d11Device->CreateRasterizerState(&d3d11RasterizerDescription, &CWcullMode);
//
//			d3d11RasterizerDescription.CullMode = D3D11_CULL_NONE;
//			d3d11Device->CreateRasterizerState(&d3d11RasterizerDescription, &RSCullNone);
//			//----------------------------~Rasterizers----------------------------//
//		};
//		~FVF_BASE() { };
//
//		virtual void Render(ID3D11DeviceContext * d3d11DevCon) = 0;
//		virtual void AddShader(LPCSTR _name, SHADERS * _shader) = 0;
//	};
//	struct FVF_POS_COLOR : public FVF_BASE
//	{
//		struct VERTEX	//Overloaded Vertex Structure
//		{
//			VERTEX() { }
//			VERTEX(float x, float y, float z, float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _a = 1.0f) : pos(x, y, z), color(D3DXVECTOR4(_r, _g, _b, _a)) { };
//
//			D3DXVECTOR3	pos;
//			D3DXVECTOR4	color;
//		};
//		D3D11_INPUT_ELEMENT_DESC	PosColorLayout[2];
//
//		FVF_POS_COLOR() : FVF_BASE(sizeof(VERTEX))
//		{
//			D3D11_INPUT_ELEMENT_DESC PosTexNormalLayoutTemp[] =
//			{
//				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			};
//			for (int i = 0; i < 2; i++) PosColorLayout[i] = PosTexNormalLayoutTemp[i];
//		};
//
//		virtual void Render(ID3D11DeviceContext * d3d11DevCon) { };
//		void AddShader(LPCSTR _name, SHADERS * _shader)
//		{
//			std::pair <SHADERS *, ID3D11InputLayout *> Temp; Temp.first = _shader;
//			d3d11Device->CreateInputLayout(PosColorLayout, 2, Temp.first->VS_Buffer->GetBufferPointer(), Temp.first->VS_Buffer->GetBufferSize(), &Temp.second); //Create the Input Layout
//			if (ShaderLayout.find(_name) == ShaderLayout.end()) { ShaderLayout[_name] = Temp; currentShader = _name; };
//		}
//	};
//	struct FVF_POS_TEX : public FVF_BASE
//	{
//		ID3D11ShaderResourceView* Texture;
//		ID3D11SamplerState* TextureSamplerState;
//		struct VERTEX	//Overloaded Vertex Structure
//		{
//			VERTEX() { }
//			VERTEX(float _x, float _y, float _z, float _u = 0.0f, float _v = 0.0f) : pos(_x, _y, _z), texCoord(_u, _v) { };
//			D3DXVECTOR3	pos;
//			D3DXVECTOR2	texCoord;
//		};
//		D3D11_INPUT_ELEMENT_DESC	PosTexLayout[2];
//
//
//		FVF_POS_TEX() : FVF_BASE(sizeof(VERTEX)), Texture(NULL), TextureSamplerState(NULL)
//		{
//
//			D3D11_INPUT_ELEMENT_DESC PosTexNormalLayoutTemp[] =
//			{
//				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			};
//
//			for (int i = 0; i < 2; i++) PosTexLayout[i] = PosTexNormalLayoutTemp[i];
//
//			//Create the Sample State
//			d3d11Device->CreateSamplerState(&samplerDescription, &TextureSamplerState);
//
//		};
//
//		virtual void Render(ID3D11DeviceContext * d3d11DevCon)
//		{
//
//		};
//		void AddShader(LPCSTR _name, SHADERS * _shader)
//		{
//			std::pair <SHADERS *, ID3D11InputLayout *> Temp; Temp.first = _shader;
//			d3d11Device->CreateInputLayout(PosTexLayout, 2, Temp.first->VS_Buffer->GetBufferPointer(), Temp.first->VS_Buffer->GetBufferSize(), &Temp.second); //Create the Input Layout
//			if (ShaderLayout.find(_name) == ShaderLayout.end()) { ShaderLayout[_name] = Temp; currentShader = _name; };
//		}
//	};
//	struct FVF_POS_TEX_NORMAL : public FVF_BASE
//	{
//		ID3D11ShaderResourceView* Texture;
//		ID3D11SamplerState* TextureSamplerState;
//		struct VERTEX	//Overloaded Vertex Structure
//		{
//			VERTEX() { }
//			VERTEX(float _x, float _y, float _z, float _u = 0.0f, float _v = 0.0f, float _n1 = 0.0f, float _n2 = 0.0f, float _n3 = 0.0f) : pos(_x, _y, _z), texCoord(_u, _v), normal(_n1, _n2, _n3) { };
//			D3DXVECTOR3	pos;
//			D3DXVECTOR2	texCoord;
//			D3DXVECTOR3	normal;
//		};
//		D3D11_INPUT_ELEMENT_DESC PosTexNormalLayout[3];
//
//		FVF_POS_TEX_NORMAL() : FVF_BASE(sizeof(VERTEX)), TextureSamplerState(NULL), Texture(NULL)
//		{
//			D3D11_INPUT_ELEMENT_DESC PosTexNormalLayoutTemp[] =
//			{
//				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
//			};
//			for (int i = 0; i < 3; i++) PosTexNormalLayout[i] = PosTexNormalLayoutTemp[i];
//
//			//Create the Sample State
//			d3d11Device->CreateSamplerState(&samplerDescription, &TextureSamplerState);
//		};
//		virtual void Render(ID3D11DeviceContext * d3d11DevCon) { };
//		void AddShader(LPCSTR _name, SHADERS * _shader)
//		{
//			std::pair <SHADERS *, ID3D11InputLayout *> Temp; Temp.first = _shader;
//			d3d11Device->CreateInputLayout(PosTexNormalLayout, 3, Temp.first->VS_Buffer->GetBufferPointer(), Temp.first->VS_Buffer->GetBufferSize(), &Temp.second); //Create the Input Layout
//			if (ShaderLayout.find(_name) == ShaderLayout.end()) { ShaderLayout[_name] = Temp; currentShader = _name; };
//		}
//	};
//
//	class LIGHTS /*: public LIGHT_OBJECT*/
//	{
//	public:
//
//		enum TYPES { point, spot } Type;
//
//		static D3D11_BUFFER_DESC BufferDesc;
//		static ID3D11Buffer * constantBuffer;
//
//		LIGHTS(ID3D11Device * d3d11Device, TYPES _type) : Type(_type) { if (!constantBuffer) d3d11Device->CreateBuffer(&BufferDesc, NULL, &constantBuffer); };
//		~LIGHTS() { };
//
//		//virtual void Apply_Light(ID3D11DeviceContext * d3d11DevCon, CAMERAS_FREE * SceneCamera) = 0;
//	};
//	class LIGHTS_POINT : public LIGHTS
//	{
//	public:
//		struct POINTLIGHT
//		{
//			D3DXVECTOR3 pos;
//			float range;
//			D3DXVECTOR3 att;
//			float emptyslot1;
//			D3DXVECTOR4 ambient;
//			D3DXVECTOR4 diffuse;
//			POINTLIGHT(D3DXVECTOR3 _pos = D3DXVECTOR3(0, 0, 0), float _range = 50, float _pad1 = 0, float _pad2 = 0,
//				D3DXVECTOR3 _att = D3DXVECTOR3(0.0f, 0.1f, 0.01f), D3DXVECTOR4 _ambient = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4 _diffuse = D3DXVECTOR4(1, 1, 1, 1)) : pos(_pos),
//				range(_range), att(_att), ambient(_ambient), diffuse(_diffuse), emptyslot1(_pad1)
//			{ };
//		} Light;
//
//		LIGHTS_POINT(ID3D11Device * d3d11Device) : LIGHTS(d3d11Device, TYPES::point) { };
//		~LIGHTS_POINT() { };
//		//void Apply_Light(ID3D11DeviceContext * d3d11DevCon, CAMERAS_FREE * SceneCamera);
//	};
//	class LIGHTS_SPOT : public LIGHTS
//	{
//	public:
//		struct SPOTLIGHT
//		{
//			D3DXVECTOR3 pos;
//			float cone;
//			D3DXVECTOR3 dir;
//			float range;
//			D3DXVECTOR3 att;
//			float pad1;
//			D3DXVECTOR4 ambient;
//			D3DXVECTOR4 diffuse;
//			SPOTLIGHT(D3DXVECTOR3 _pos = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 _dir = D3DXVECTOR3(0, -1, 0), float _range = 50, float _cone = 20, D3DXVECTOR3 _att = D3DXVECTOR3(0.0f, 0.1f, 0.003f), D3DXVECTOR4 _ambient = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4 _diffuse = D3DXVECTOR4(1.0f, 1.0f, 1, 1)) : pos(_pos), dir(_dir), range(_range), cone(_cone), att(_att), ambient(_ambient), diffuse(_diffuse), pad1(0) { };
//		} Light;
//		LIGHTS_SPOT(ID3D11Device * d3d11Device) : LIGHTS(d3d11Device, TYPES::spot) { };
//		~LIGHTS_SPOT() { };
//		//void Apply_Light(ID3D11DeviceContext * d3d11DevCon, CAMERAS_FREE * SceneCamera);
//	};
//
//	class OBJGEOMETRY : /*public GEOMETRY_OBJECT,*/ public FVF_POS_TEX_NORMAL
//	{
//	public:
//		struct MATERIALS
//		{
//			std::wstring matName;
//			XMFLOAT4 ambColor;
//			XMFLOAT4 difColor; ID3D11ShaderResourceView* Texture_Diffuse;
//			XMFLOAT4 specColor;
//			int texArrayIndex;
//			MATERIALS() : ambColor(XMFLOAT4(0, 0, 0, 0)), difColor(XMFLOAT4(0, 0, 0, 0)), specColor(XMFLOAT4(0, 0, 0, 0)), texArrayIndex(0), Texture_Diffuse(NULL) { };
//		} Material;
//		struct SUBMESHES
//		{
//
//			int vertexQuantity;
//			LPCSTR name;
//			SUBMESHES() : vertexQuantity(0), name(NULL) { };
//		};
//		std::vector<SUBMESHES> SubMesh;
//		int VertQuantity, IndexQuantity;
//
//		//------------------------------Buffer desc-------------------------------//
//
//		struct CONSTANTBUFFERPEROBJECT
//		{
//			D3DXMATRIX  WVP;
//			D3DXMATRIX  World;
//			CONSTANTBUFFERPEROBJECT()
//			{
//				D3DXMatrixIdentity(&WVP);
//				D3DXMatrixIdentity(&World);
//			};
//		} constantBufferPerObject;
//
//		OBJGEOMETRY() : VertQuantity(0), IndexQuantity(0)
//		{
//			BufferDesc.ByteWidth = sizeof(CONSTANTBUFFERPEROBJECT);
//			BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//			d3d11Device->CreateBuffer(&BufferDesc, NULL, &ClipBoardShaderBuffer);
//		};
//		~OBJGEOMETRY() { };
//
//		void Initiate_ObjGeometry(LPCSTR filename, bool isRHCoordSys, bool computeNormals/*, std::vector<XMFLOAT3>& vertPosArray,	std::vector<DWORD>& vertIndexArray*/);
//		//void Render(CAMERAS_FREE * _camera);
//		void Add_Shader(int _meshNumber, LPCSTR _name, SHADERS* _shader);
//	};
//	class SHADERS
//	{
//	public:
//		ID3D11VertexShader * VS;
//		ID3D11PixelShader * PS;
//		ID3D10Blob* VS_Buffer;
//		ID3D10Blob* PS_Buffer;
//		SHADERS() : VS(NULL), PS(NULL) { };
//		~SHADERS() { };
//		void LoadShader(LPCSTR _adress, ID3D11Device * d3d11Device)
//		{
//			//Compile Shaders from shader file
//			//D3DX11CompileFromFile(_adress, 0, 0, "VS", "vs_4_0", 0, 0, 0, &VS_Buffer, 0, 0);
//			//D3DX11CompileFromFile(_adress, 0, 0, "PS", "ps_4_0", 0, 0, 0, &PS_Buffer, 0, 0);
//
//			//Create the Shader Objects
//			d3d11Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
//			d3d11Device->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);
//		};
//	};
//	class SKYMAP : public FVF_POS_TEX_NORMAL
//	{
//	public:
//
//		D3DXMATRIX  WVP;
//		ID3D11ShaderResourceView* smrv;
//
//		int NumSphereVertices;
//		int NumSphereFaces;
//
//		D3DXMATRIX Rotationx;
//		D3DXMATRIX Rotationy;
//		D3DXMATRIX Rotationz;
//
//		struct CONSTANTBUFFERPEROBJECT
//		{
//			D3DXMATRIX  WVP;
//			CONSTANTBUFFERPEROBJECT() { D3DXMatrixIdentity(&WVP); };
//		} constantBufferPerObject;
//
//		SKYMAP()
//		{
//			BufferDesc.ByteWidth = sizeof(CONSTANTBUFFERPEROBJECT);
//			BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//			d3d11Device->CreateBuffer(&BufferDesc, NULL, &ClipBoardShaderBuffer);
//		};
//		~SKYMAP() { };
//
//		void CreateSphere(int LatLines, int LongLines);
//		void Initiate_SkyMap(ID3D11Device * d3d11Device);
//		//void Render(ID3D11DeviceContext * d3d11DevCon, CAMERAS_FREE * SceneCamera);
//
//	};
//	class TEMPORARYMESH : /*public GEOMETRY_OBJECT,*/ public FVF_POS_TEX
//	{
//	public:
//
//		D3DXMATRIX  WVP;
//
//		struct CONSTANTBUFFERPEROBJECT
//		{
//			D3DXMATRIX  WVP;
//			CONSTANTBUFFERPEROBJECT() { D3DXMatrixIdentity(&WVP); };
//		} constantBufferPerObject;
//
//		TEMPORARYMESH()
//		{
//			BufferDesc.ByteWidth = sizeof(CONSTANTBUFFERPEROBJECT);
//			BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//			d3d11Device->CreateBuffer(&BufferDesc, NULL, &ClipBoardShaderBuffer);
//		};
//		~TEMPORARYMESH() { };
//
//		void Load_Geometry(ID3D11Device * d3d11Device);
//		//void Render(ID3D11DeviceContext * d3d11DevCon, CAMERAS_FREE * SceneCamera);
//
//	};
//	class UPSCREEN : public FVF_POS_COLOR
//	{
//	public:
//
//		float opacity;
//
//		UPSCREEN() : opacity(0)
//		{
//			BufferDesc.ByteWidth = sizeof(opacity) * 4;
//			BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//			d3d11Device->CreateBuffer(&BufferDesc, NULL, &ClipBoardShaderBuffer);
//		};
//		~UPSCREEN() { };
//
//		void Initiate_UpScreen(ID3D11Device * d3d11Device);
//		void Render(ID3D11DeviceContext * d3d11DevCon);
//
//	};
//
//	std::map<LPCSTR, FVF_POS_COLOR>			D3D11PosColorFVF;
//	std::map<LPCSTR, FVF_POS_TEX>			D3D11PosTexFVF;
//	std::map<LPCSTR, FVF_POS_TEX_NORMAL>	D3D11PosTexNormalFVF;
//	std::map<LPCSTR, LIGHTS *>				Light;
//	std::map<LPCSTR, TEMPORARYMESH>			MeshGeometry;
//	std::map<LPCSTR, OBJGEOMETRY>			ObjGeometry;
//	std::map<LPCSTR, SHADERS>				Shader;
//	std::map<LPCSTR, SKYMAP>				SkyMap;
//	std::map<LPCSTR, UPSCREEN>				UpScreen;
//
//	//---------------------~ARGUMENTS-----------------------//
//
//	//---------------------FUNCTIONS---------------------//
//
//	HRESULT Initiate_D3D(HWND hWnd);
//	HRESULT Initiate_GraphDevice(HWND hWnd, DWORD style, int sizeX, int sizeY);
//
//	HRESULT Initiate_Camera(CAMERA_TYPES _cameraType);
//	int Load_Geometry(LPCSTR _name, DIRECTX_SUPPORTED_FILE_FORMATS _fileFormat, char _geometryType, COLLISION_TYPES _collisionType);
//	HRESULT Initiate_MeshAnimation(LPCSTR name, DIRECTX_SUPPORTED_FILE_FORMATS _fileFormat, COLLISION_TYPES _collisionType);
//	HRESULT Initiate_Light(LPCSTR _name, LIGHT_TYPES _type);
//	HRESULT Initiate_Shader(LPCSTR _name, LPCSTR _adress);
//	HRESULT Initiate_SkyMap(LPCSTR _name);
//	HRESULT Initiate_SpecialEffect(LPCSTR _name);
//	HRESULT Initiate_Surface(int height, int width, LPCSTR name);
//	HRESULT Initiate_Text(LPCSTR _name, LPCSTR _string, int _fontNumber, int _color);
//	HRESULT Initiate_Text_Font(LPCSTR facename, int Height, int Weight, bool IsItalic);
//	HRESULT Initiate_Text_Color(D3DCOLOR _color, int _position);
//	HRESULT Initiate_Texture(LPCSTR _name);
//	HRESULT Initiate_TextureScreen(float X1, float Y1, float X2, float Y2, float X3, float Y3, float X4, float Y4);
//	HRESULT Initiate_UpScreen();
//
//	HRESULT Render_AnimatedMesh(LPCSTR _meshAnimKey);
//	HRESULT Render_Cursor(LPCSTR _textureKey, int m_fCursorX, int m_fCursorY, int m_iHotSpotX, int m_iHotSpotY);
//	HRESULT Render_Mesh(LPCSTR _meshKey);
//	HRESULT Render_ObjGeometry_DirectX11(LPCSTR _name);
//	HRESULT Render_Scene();
//	//HRESULT Render_SkyMap(LPCSTR _name, CAMERAS_FREE * _camera);
//	HRESULT Render_Sprite(RECT src1, RECT dest1);
//	HRESULT Render_Text(LPCSTR _textKey, RECT _rec);
//	HRESULT Render_Texture(LPCSTR _textureKey);
//	HRESULT Render_UpScreen();
//
//	HRESULT Change_TextureMap(LPDIRECT3DTEXTURE9 texture);
//	HRESULT Change_UpScreenAlpha(int alpha);
//
//	HRESULT Set_RenderOptions();
//
//	HRESULT SetProjectionMatrix(CAMERAS * _camera)
//	{
//		/*D3DXMatrixPerspectiveFovLH(&_camera->Camera_Matrix_Projection, 45, 1.77f, 1, 2000);*/
//		return S_OK;
//	};
//	HRESULT SetViewMatrix(CAMERAS * _camera)
//	{
//		return S_OK;
//	};
//	HRESULT SetWorldMatrix(D3DXMATRIX * _matrix)
//	{
//		return S_OK;
//	};
//
//	HRESULT StartScene()
//	{
//		return S_OK;
//	};
//	HRESULT EndScene()
//	{
//		return S_OK;
//	};
//
//	GLOBALS * GetGlobals();
//
//	//--------------------~FUNCTIONS---------------------//
//
//	///////////////**************picking**************////////////////////
//	//void pickRayVector(float mouseX, float mouseY, D3DXVECTOR3& pickRayInWorldSpacePos, D3DXVECTOR3& pickRayInWorldSpaceDir, CAMERAS_FREE * _camera, int _sizeX, int _sizeY);
//	bool PointInTriangle(D3DXVECTOR3& triV1, D3DXVECTOR3& triV2, D3DXVECTOR3& triV3, D3DXVECTOR3& point);
//	float pick(D3DXVECTOR3 pickRayInWorldSpacePos, D3DXVECTOR3 pickRayInWorldSpaceDir, std::vector<D3DXVECTOR3>& vertPosArray, std::vector<DWORD>& indexPosArray, D3DXMATRIX& worldSpace);
//	///////////////*************~picking**************////////////////////
//
//	DIRECTX11() : DIRECTX(), d3d11BackBuffer(NULL), d3d11SwapChain(NULL), d3d11Device(NULL), d3d11DevCon(NULL), d3d11RenderTargetView(NULL), d3d11DepthStencilBuffer(NULL), d3d11DepthStencilView(NULL), Transparency(NULL)
//	{
//		ZeroMemory(&d3d11Viewport, sizeof(D3D11_VIEWPORT));
//		ZeroMemory(&d3d11DepthStencilDescription, sizeof(D3D11_DEPTH_STENCIL_DESC));
//		ZeroMemory(&d3d11BlendDescription, sizeof(D3D11_BLEND_DESC));
//		ZeroMemory(&d3d11RenderTargetBlendDescription, sizeof(D3D11_RENDER_TARGET_BLEND_DESC));
//
//		bottleVertBuff = NULL;
//		bottleIndexBuff = NULL;
//		ZeroMemory(&bottleWorld, sizeof(D3DXMATRIX) * 20);
//		D3DXMatrixIdentity(&Rotation);
//		D3DXMatrixIdentity(&Scale);
//		D3DXMatrixIdentity(&Translation);
//		bottleHit = NULL;
//		bottleSubsets = 0;
//		numBottles = 0;
//		ClientWidth = 0;
//		ClientHeight = 0;
//		score = 0;
//		isShoot = false;
//		pickedDist = 0;
//	};
//
//};