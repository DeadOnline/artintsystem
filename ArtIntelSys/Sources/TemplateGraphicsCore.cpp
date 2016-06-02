#include "stdafx.h"
#include "ALL.h"

GRAPHCORE::CAMERAS *				GRAPHCORE::Camera	= NULL;
GRAPHCORE::MESHES_X *				GRAPHCORE::Mesh		= NULL;
GRAPHCORE::MAPS *					GRAPHCORE::Map		= NULL;
GRAPHCORE::OBJECTS *				GRAPHCORE::Object	= NULL;
GRAPHCORE::TEXTSTRINGS *			GRAPHCORE::Text		= NULL;
GRAPHCORE::TEXTURES *				GRAPHCORE::Texture	= NULL;
GRAPHCORE::GEOMETRY *				GRAPHCORE::Geometry = NULL;

int									GRAPHCORE::CAMERAS::camera_Count	= 0;

LPDIRECT3DTEXTURE9					GRAPHCORE::MAPS::COLLISIONS::texture = NULL;
GRAPHCORE::MAPS::COLLISIONS *		GRAPHCORE::MAPS::COLLISIONS::Root = NULL;
LPDIRECT3DVERTEXBUFFER9				GRAPHCORE::MAPS::COLLISIONS::CollisionBuffer = NULL;
int									GRAPHCORE::MAPS::COLLISIONS::Quantity = 0;

int									GRAPHCORE::TEXTSTRINGS::Quantity = 0;
D3DCOLOR							GRAPHCORE::TEXTSTRINGS::color[] = { 0xffffffff };
LPD3DXFONT							GRAPHCORE::TEXTSTRINGS::font[10] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };
D3DXFONT_DESC						GRAPHCORE::TEXTSTRINGS::fontDesc = {24,0,400,0,false,DEFAULT_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_PITCH,"Arial"};
GRAPHCORE::TEXTSTRINGS *			GRAPHCORE::TEXTSTRINGS::Root = NULL;

LPD3DXMESH						 	GRAPHCORE::MESHES_X::defaultMesh			= NULL;
LPDIRECT3DTEXTURE9					GRAPHCORE::TEXTURES::DefaultTexture			= NULL;
D3DMATERIAL9 *						GRAPHCORE::MESHES_X::defaultMeshMaterial	= NULL;

int									GRAPHCORE::OBJECTS::OBJECT_DATA::quantity = 0;

static								mutex GraphicalCoreLocker, GraphicalCoreLocker1;
CRITICAL_SECTION					GraphicalCoreZone;

#pragma region GRAPHCORE
						GRAPHCORE::GRAPHCORE() : D3D(NULL), DEVICE(NULL), D3DF(D3DFMT_X8R8G8B8), BACKBUFFER(NULL), SURFACE(NULL), UPSCREENBUFFER(NULL), TEXBUFFER(NULL), INDEXBUFFER(NULL), VERTEXBUFFER(NULL),
						vert3D(NULL), normal3D(NULL), vertnormal3D(NULL), vertcolor3D(NULL), vertcolorspec3D(NULL), vertnormalcolorspec3D(NULL), vertdefcolor3D(NULL), vertdeftex3D(NULL), verttex3D(NULL), vertnormaltex3D(NULL),
						vertcolor3DQuantity(0), vert3DQuantity(0)
							{
							ZeroMemory(&upScreen, sizeof(VERTEXCOLOR));
							ZeroMemory(&D3DM, sizeof(D3DDISPLAYMODE));
							ZeroMemory(&D3DPP, sizeof(D3DPP));
							D3DM.Format = D3DF;
							D3DM.Height = GetSystemMetrics(SM_CYSCREEN);
							D3DM.Width = GetSystemMetrics(SM_CXSCREEN);
							D3DM.RefreshRate = 0;

							InitializeCriticalSection(&GraphicalCoreZone);
							};
						GRAPHCORE::~GRAPHCORE()
							{
							OBJRELEASE(D3D);
							OBJRELEASE(DEVICE);
							OBJRELEASE(SURFACE);
							OBJRELEASE(BACKBUFFER);
							OBJRELEASE(VERTEXBUFFER);
							OBJRELEASE(UPSCREENBUFFER);
							OBJRELEASE(TEXBUFFER);
							OBJRELEASE(INDEXBUFFER);

							OBJSDELETE(vert3D);
							OBJSDELETE(normal3D);
							OBJSDELETE(vertnormal3D);
							OBJSDELETE(vertcolor3D);
							OBJSDELETE(vertcolorspec3D);
							OBJSDELETE(vertnormalcolorspec3D);
							OBJSDELETE(vertdefcolor3D);
							OBJSDELETE(vertdeftex3D);
							OBJSDELETE(verttex3D);
							OBJSDELETE(vertnormaltex3D);

							OBJDELETE(Camera);
							OBJDELETE(Mesh);
							OBJDELETE(Texture);
							OBJDELETE(Object);
							Destroy_Meshes();
							Destroy_Objects();
							Destroy_Texts();
							Destroy_Cameras(); //Destroys only 1 camera
							};
HRESULT					GRAPHCORE::Initiate_D3D(HWND hWnd)
	{
	if (NULL == (D3D = Direct3DCreate9(D3D_SDK_VERSION))) { MessageBox(hWnd, "Íå óäàëîñü ñîçäàòü D3D...", "Âûõîä èç ïðîãðàììû", 0); exit(1); };
	};
HRESULT					GRAPHCORE::Initiate_Device(HWND hWnd, bool IsFullScreen, int sizeX, int sizeY)
	{
	D3D->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DF, D3DF, FALSE);
	D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &D3DM);

	D3DPP.AutoDepthStencilFormat = D3DFMT_D16;
	D3DPP.BackBufferFormat = D3DM.Format;
	if (IsFullScreen)
		{
		D3DPP.BackBufferHeight = sizeY; D3DPP.BackBufferWidth = sizeX;
		}
	else
		{
		D3DPP.BackBufferHeight = D3DM.Height; D3DPP.BackBufferWidth = D3DM.Width;
		}
	D3DPP.BackBufferCount = 1;
	D3DPP.EnableAutoDepthStencil = TRUE;
	D3DPP.Flags = 0;
	if (IsFullScreen) D3DPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	D3DPP.hDeviceWindow = hWnd;
	D3DPP.MultiSampleType = D3DMULTISAMPLE_NONE;
	D3DPP.MultiSampleQuality = 0;
	D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3DPP.Windowed = !IsFullScreen;

	if (FAILED(D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &D3DPP, &DEVICE))) { MessageBox(hWnd, "Íå óäàëîñü ñîçäàòü D3D->CreateDevice...", "Âûõîä èç ïðîãðàììû", 0); exit(1); }
	return S_OK;
	};
HRESULT					GRAPHCORE::Initiate_MaterialsAndTextures()
	{
	D3DMATERIAL9 d3ddm;
	ZeroMemory(&d3ddm, sizeof(D3DMATERIAL9));

	d3ddm.Diffuse.r = d3ddm.Ambient.r = 1.0f; // êðàñíûé
	d3ddm.Diffuse.g = d3ddm.Ambient.g = 1.0f; // çåëåíûé
	d3ddm.Diffuse.b = d3ddm.Ambient.b = 1.0f; // ñèíèé
	d3ddm.Diffuse.a = d3ddm.Ambient.a = 1.0f; // àëüôà
	d3ddm.Power = 1.0f;

	DEVICE->SetMaterial(&d3ddm);

	// Ðàáîòà ñ âåðøèíàìè
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//DEVICE->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	//DEVICE->SetRenderState( D3DRS_SRCBLENDALPHA, D3DBLEND_SRCALPHA );
	//DEVICE->SetRenderState( D3DRS_DESTBLENDALPHA, D3DBLEND_INVSRCALPHA );
	//DEVICE->SetRenderState( D3DRS_AMBIENT, RGB(255,255,255));
	//DEVICE->SetRenderState( D3DRS_ZENABLE, 0);   // D3DZB_FALSE | D3DZB_TRUE | D3DZB_USEW
	//DEVICE->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID);	 // D3DFILL_POINT | D3DFILL_WIREFRAME | D3DFILL_SOLID
	//DEVICE->SetRenderState( D3DRS_SHADEMODE, 0); // D3DSHADE_FLAT | D3DSHADE_GOURAUD | D3DSHADE_PHONG
	//DEVICE->SetRenderState( D3DRS_ZWRITEENABLE, 0);
	//DEVICE->SetRenderState( D3DRS_ALPHATESTENABLE, 0);
	//DEVICE->SetRenderState( D3DRS_LASTPIXEL, 0);
	// DEVICE->SetRenderState( D3DRS_SRCBLEND, 0);
	// DEVICE->SetRenderState( D3DRS_DESTBLEND, 0);
	// DEVICE->SetRenderState( D3DRS_CULLMODE, 0);
	// DEVICE->SetRenderState( D3DRS_ZFUNC, 0);
	// DEVICE->SetRenderState( D3DRS_ALPHAREF, 0);
	// DEVICE->SetRenderState( D3DRS_ALPHAFUNC, 0);
	// DEVICE->SetRenderState( D3DRS_DITHERENABLE, 0);
	// DEVICE->SetRenderState( D3DRS_ALPHABLENDENABLE, 0);
	// DEVICE->SetRenderState( D3DRS_FOGENABLE, 0);
	// DEVICE->SetRenderState( D3DRS_SPECULARENABLE, 0);
	// DEVICE->SetRenderState( D3DRS_FOGCOLOR, 0);
	// DEVICE->SetRenderState( D3DRS_FOGTABLEMODE, 0);
	// DEVICE->SetRenderState( D3DRS_FOGSTART, 0);
	// DEVICE->SetRenderState( D3DRS_FOGEND, 0);
	// //DEVICE->SetRenderState( D3DRS_FOGDENSITY                  = 38,
	// //DEVICE->SetRenderState( D3DRS_RANGEFOGENABLE              = 48,
	// //DEVICE->SetRenderState( D3DRS_STENCILENABLE               = 52,
	// //DEVICE->SetRenderState( D3DRS_STENCILFAIL                 = 53,
	// //DEVICE->SetRenderState( D3DRS_STENCILZFAIL                = 54,
	// //DEVICE->SetRenderState( D3DRS_STENCILPASS                 = 55,
	// //DEVICE->SetRenderState( D3DRS_STENCILFUNC                 = 56,
	// //DEVICE->SetRenderState( D3DRS_STENCILREF                  = 57,
	// //DEVICE->SetRenderState( D3DRS_STENCILMASK                 = 58,
	// //DEVICE->SetRenderState( D3DRS_STENCILWRITEMASK            = 59,
	// //DEVICE->SetRenderState( D3DRS_TEXTUREFACTOR               = 60,
	// //DEVICE->SetRenderState( D3DRS_WRAP0                       = 128,
	// //DEVICE->SetRenderState( D3DRS_WRAP1                       = 129,
	// //DEVICE->SetRenderState( D3DRS_WRAP2                       = 130,
	// //DEVICE->SetRenderState( D3DRS_WRAP3                       = 131,
	// //DEVICE->SetRenderState( D3DRS_WRAP4                       = 132,
	// //DEVICE->SetRenderState( D3DRS_WRAP5                       = 133,
	// //DEVICE->SetRenderState( D3DRS_WRAP6                       = 134,
	// //DEVICE->SetRenderState( D3DRS_WRAP7                       = 135,
	// //DEVICE->SetRenderState( D3DRS_CLIPPING                    = 136,
	// //DEVICE->SetRenderState( D3DRS_LIGHTING                    = 137,
	// //DEVICE->SetRenderState( D3DRS_AMBIENT                     = 139,
	// //DEVICE->SetRenderState( D3DRS_FOGVERTEXMODE               = 140,
	// //DEVICE->SetRenderState( D3DRS_COLORVERTEX                 = 141,
	// //DEVICE->SetRenderState( D3DRS_LOCALVIEWER                 = 142,
	// //DEVICE->SetRenderState( D3DRS_NORMALIZENORMALS            = 143,
	// //DEVICE->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE       = 145,
	// //DEVICE->SetRenderState( D3DRS_SPECULARMATERIALSOURCE      = 146,
	// //DEVICE->SetRenderState( D3DRS_AMBIENTMATERIALSOURCE       = 147,
	// //DEVICE->SetRenderState( D3DRS_EMISSIVEMATERIALSOURCE      = 148,
	// //DEVICE->SetRenderState( D3DRS_VERTEXBLEND                 = 151,
	// //DEVICE->SetRenderState( D3DRS_CLIPPLANEENABLE             = 152,
	// //DEVICE->SetRenderState( D3DRS_POINTSIZE                   = 154,
	// //DEVICE->SetRenderState( D3DRS_POINTSIZE_MIN               = 155,
	// //DEVICE->SetRenderState( D3DRS_POINTSPRITEENABLE           = 156,
	// //DEVICE->SetRenderState( D3DRS_POINTSCALEENABLE            = 157,
	// //DEVICE->SetRenderState( D3DRS_POINTSCALE_A                = 158,
	// //DEVICE->SetRenderState( D3DRS_POINTSCALE_B                = 159,
	// //DEVICE->SetRenderState( D3DRS_POINTSCALE_C                = 160,
	// //DEVICE->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS        = 161,
	// //DEVICE->SetRenderState( D3DRS_MULTISAMPLEMASK             = 162,
	// //DEVICE->SetRenderState( D3DRS_PATCHEDGESTYLE              = 163,
	// //DEVICE->SetRenderState( D3DRS_DEBUGMONITORTOKEN           = 165,
	// //DEVICE->SetRenderState( D3DRS_POINTSIZE_MAX               = 166,
	// //DEVICE->SetRenderState( D3DRS_INDEXEDVERTEXBLENDENABLE    = 167,
	// //DEVICE->SetRenderState( D3DRS_COLORWRITEENABLE            = 168,
	// //DEVICE->SetRenderState( D3DRS_TWEENFACTOR                 = 170,
	// //DEVICE->SetRenderState( D3DRS_BLENDOP                     = 171,
	// //DEVICE->SetRenderState( D3DRS_POSITIONDEGREE              = 172,
	// //DEVICE->SetRenderState( D3DRS_NORMALDEGREE                = 173,
	// //DEVICE->SetRenderState( D3DRS_SCISSORTESTENABLE           = 174,
	// //DEVICE->SetRenderState( D3DRS_SLOPESCALEDEPTHBIAS         = 175,
	// //DEVICE->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE       = 176,
	// //DEVICE->SetRenderState( D3DRS_MINTESSELLATIONLEVEL        = 178,
	// //DEVICE->SetRenderState( D3DRS_MAXTESSELLATIONLEVEL        = 179,
	// //DEVICE->SetRenderState( D3DRS_ADAPTIVETESS_X              = 180,
	// //DEVICE->SetRenderState( D3DRS_ADAPTIVETESS_Y              = 181,
	// //DEVICE->SetRenderState( D3DRS_ADAPTIVETESS_Z              = 182,
	// //DEVICE->SetRenderState( D3DRS_ADAPTIVETESS_W              = 183,
	// //DEVICE->SetRenderState( D3DRS_ENABLEADAPTIVETESSELLATION  = 184,
	// //DEVICE->SetRenderState( D3DRS_TWOSIDEDSTENCILMODE         = 185,
	// //DEVICE->SetRenderState( D3DRS_CCW_STENCILFAIL             = 186,
	// //DEVICE->SetRenderState( D3DRS_CCW_STENCILZFAIL            = 187,
	// //DEVICE->SetRenderState( D3DRS_CCW_STENCILPASS             = 188,
	// //DEVICE->SetRenderState( D3DRS_CCW_STENCILFUNC             = 189,
	// //DEVICE->SetRenderState( D3DRS_COLORWRITEENABLE1           = 190,
	// //DEVICE->SetRenderState( D3DRS_COLORWRITEENABLE2           = 191,
	// //DEVICE->SetRenderState( D3DRS_COLORWRITEENABLE3           = 192,
	// //DEVICE->SetRenderState( D3DRS_BLENDFACTOR                 = 193,
	// //DEVICE->SetRenderState( D3DRS_SRGBWRITEENABLE             = 194,
	// //DEVICE->SetRenderState( D3DRS_DEPTHBIAS                   = 195,
	// //DEVICE->SetRenderState( D3DRS_WRAP8                       = 198,
	// //DEVICE->SetRenderState( D3DRS_WRAP9                       = 199,
	// //DEVICE->SetRenderState( D3DRS_WRAP10                      = 200,
	// //DEVICE->SetRenderState( D3DRS_WRAP11                      = 201,
	// //DEVICE->SetRenderState( D3DRS_WRAP12                      = 202,
	// //DEVICE->SetRenderState( D3DRS_WRAP13                      = 203,
	// //DEVICE->SetRenderState( D3DRS_WRAP14                      = 204,
	// //DEVICE->SetRenderState( D3DRS_WRAP15                      = 205,
	// //DEVICE->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE    = 206,
	// //DEVICE->SetRenderState( D3DRS_SRCBLENDALPHA               = 207,
	// //DEVICE->SetRenderState( D3DRS_DESTBLENDALPHA              = 208,
	// //DEVICE->SetRenderState( D3DRS_BLENDOPALPHA                = 209,
	// //DEVICE->SetRenderState( D3DRS_FORCE_DWORD                 = 0x7fffffff

	//// Установка типа альфа-смешивания
	//DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//DEVICE->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	//DEVICE->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	//DEVICE->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	//DEVICE->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
	//DEVICE->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE );
	//DEVICE->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_BLENDTEXTUREALPHA);


	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	return S_OK;
	};
HRESULT					GRAPHCORE::Initiate_IndexBuffer()
	{
	DEVICE->CreateIndexBuffer(sizeof(WORD), D3DUSAGE_DYNAMIC | D3DUSAGE_SOFTWAREPROCESSING, D3DFMT_INDEX32, D3DPOOL_MANAGED, &INDEXBUFFER, NULL);
	return S_OK;
	};
HRESULT					GRAPHCORE::Initiate_Font(char* facename, int Height, int Weight, bool IsItalic)
	{
	int i = 0;
	while (Text->font[i] != NULL && i < 10 && Text != NULL) i++;
	GraphicalCoreLocker.lock();
	Text->Initiate_Font(DEVICE, Height, Weight, IsItalic, facename, i);
	GraphicalCoreLocker.unlock();

	return S_OK;
	};
HRESULT					GRAPHCORE::Initiate_Color(D3DCOLOR _color, int _position)
{
	if (_position >= 0 && _position <= 9)
	{
		GraphicalCoreLocker.lock();
		Text->Initiate_Color(_color, _position);
		GraphicalCoreLocker.unlock();
	}
	return S_OK;
};
GRAPHCORE::TEXTSTRINGS* GRAPHCORE::Initiate_Text(LPCSTR _string, int fontNumber, RECT _rec)
{
	if (!Text) {
		Text = new TEXTSTRINGS;
	}
	else {
		Text->textNext = new TEXTSTRINGS; Text = Text->textNext;
	};
	if (Text->font[0] == NULL) Initiate_Font("Arial", 24, 400, false);
	if (fontNumber >= 10 || Text->font[fontNumber] == NULL) fontNumber = 0;
	GraphicalCoreLocker.lock();
	Text->Initiate_TextString(_string, fontNumber, _rec);
	GraphicalCoreLocker.unlock();
	return S_OK;
};
HRESULT					GRAPHCORE::Initiate_Surface(int height, int width, LPCSTR name)
{
	GraphicalCoreLocker.lock();
	DEVICE->CreateOffscreenPlainSurface(width, height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &SURFACE, NULL);
	D3DXLoadSurfaceFromFile(SURFACE, NULL, NULL, name, NULL, D3DX_DEFAULT, 0, NULL);
	DEVICE->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &BACKBUFFER);
	GraphicalCoreLocker.unlock();
	return S_OK;
};
HRESULT					GRAPHCORE::Initiate_TextureScreen(float X1, float Y1, float X2, float Y2, float X3, float Y3, float X4, float Y4)
{
	if (TEXBUFFER != NULL) TEXBUFFER->Release();
	texScreen[0].X = X1; texScreen[0].Z = 0; texScreen[0].Y = Y1; texScreen[0].RHW = 1; texScreen[0].fU = 0; texScreen[0].fV = 0;
	texScreen[1].X = X2; texScreen[1].Z = 0; texScreen[1].Y = Y2; texScreen[1].RHW = 1; texScreen[1].fU = 1; texScreen[1].fV = 0;
	texScreen[2].X = X3; texScreen[2].Z = 0; texScreen[2].Y = Y3; texScreen[2].RHW = 1; texScreen[2].fU = 0; texScreen[2].fV = 1;
	texScreen[3].X = X4; texScreen[3].Z = 0; texScreen[3].Y = Y4; texScreen[3].RHW = 1; texScreen[3].fU = 1; texScreen[3].fV = 1;

	DEVICE->CreateVertexBuffer(sizeof(texScreen), 0, VertexexFVF2DTex, D3DPOOL_MANAGED, &TEXBUFFER, NULL);
	VOID* pData = NULL;
	TEXBUFFER->Lock(0, sizeof(pData), (void**)&pData, 0);
	memcpy(pData, texScreen, sizeof(texScreen));
	TEXBUFFER->Unlock();

	return S_OK;
};
HRESULT					GRAPHCORE::Initiate_TexturePointer(float X1, float Z1, float X2, float Z2, float X3, float Z3, float X4, float Z4)
{
	//if (TEXBUFFER!=NULL) TEXBUFFER->Release();
	//VERTEXTEXTURE * Temp = Pointer.texPointer;
	//Temp[0].X = X1; Temp[0].Y = 0; Temp[0].Z = Z1; Temp[0].fU = 0; Temp[0].fV = 0; Temp[0].COLOR = D3DCOLOR_RGBA(70, 70, 70, 0);
	//Temp[1].X = X2; Temp[1].Y = 0; Temp[1].Z = Z2; Temp[1].fU = 1; Temp[1].fV = 0; Temp[1].COLOR = D3DCOLOR_RGBA(70, 70, 70, 0);
	//Temp[2].X = X3; Temp[2].Y = 0; Temp[2].Z = Z3; Temp[2].fU = 0; Temp[2].fV = 1; Temp[2].COLOR = D3DCOLOR_RGBA(70, 70, 70, 0);
	//Temp[3].X = X4; Temp[3].Y = 0; Temp[3].Z = Z4; Temp[3].fU = 1; Temp[3].fV = 1; Temp[3].COLOR = D3DCOLOR_RGBA(70, 70, 70, 0);

	//DEVICE->CreateVertexBuffer(sizeof(Temp[0])*4,0,VertexexFVF3DColTex,D3DPOOL_MANAGED,&TEXBUFFER,NULL);
	//VOID* pData = NULL;
	//TEXBUFFER->Lock(0,0,(void**)&pData,0);
	//memcpy(pData,Temp,sizeof(Temp[0])*4);
	//TEXBUFFER->Unlock();

	//Pointer.texPointer[0] = Temp[0];
	//Pointer.texPointer[1] = Temp[1];
	//Pointer.texPointer[2] = Temp[2];
	//Pointer.texPointer[3] = Temp[3];

	return S_OK;
};
GRAPHCORE::CAMERAS *	GRAPHCORE::Initiate_Camera(float _param_X, float _param_Y,
	float _startPosX, float _startPosY, float _startPosZ,
	float _endPosX, float _endPosY, float _endPosZ)
{
	Camera = new CAMERAS(_param_X, _param_Y, _startPosX, _startPosY, _startPosZ, _endPosX, _endPosY, _endPosZ); return S_OK;
};
GRAPHCORE::MESHES_X *	GRAPHCORE::Load_Geometry(LPCSTR _name)
{
	GraphicalCoreLocker.lock();
	if (!Mesh)
		Mesh = new MESHES_X(DEVICE);
	if (Mesh->Add_Mesh(GET_PATH_MODEL(_name), DEVICE) == E_FAIL)
	{
		if (!Mesh->Get_Meshes_Quantity())
			OBJDELETE(Mesh);
		return NULL;
	}
	else
		MAP_UI[_name] = Mesh;
	MAP_UI[_name] = Mesh;
	GraphicalCoreLocker.unlock();
	return Mesh;
};
HRESULT					GRAPHCORE::Initiate_Object(LPCSTR _name, int _ID, OBJECTS::OBJECT_DATA::MATERIAL_TYPES _type, D3DXVECTOR3 _pos)
	{
	//GraphicalCoreLocker.lock();
	if (!Object)
			Object = new OBJECTS();
	MAP_OBJ.insert(std::make_pair(_ID, OBJECTS::OBJECT_DATA(_name, _type, _pos, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1))));
	//GraphicalCoreLocker.unlock();
	return S_OK;
	};
HRESULT					GRAPHCORE::Initiate_Terrain(std::string fileName)
{
	// Âûñîòà äëÿ êàæäîé âåðøèíû
	std::vector<BYTE> in(262144);

	std::ifstream inFile(fileName.c_str(), std::ios_base::binary);

	//if(inFile == 0)
	//      return false;

	inFile.read(
		(char*)&in[0], // áóôôåð
		in.size());    // êîëè÷åñòâî ÷èòàåìûõ â áóôåð áàéò

	inFile.close();

	// êîïèðóåì âåêòîð BYTE â âåêòîð int
	Heightmap.resize(262144);
	for (int i = 0; i < in.size(); i++)
		Heightmap[i] = in[i];

	return S_OK;

};
HRESULT					GRAPHCORE::Destroy_D3D() { OBJRELEASE(D3D); return S_OK; };
HRESULT					GRAPHCORE::Destroy_Device() { OBJRELEASE(DEVICE); return S_OK; };
HRESULT					GRAPHCORE::Destroy_Surface(LPDIRECT3DSURFACE9 SURFACE) { OBJRELEASE(SURFACE); return S_OK; };
HRESULT					GRAPHCORE::Destroy_Font(LPD3DXFONT font) { OBJRELEASE(font); return S_OK; };
HRESULT					GRAPHCORE::Destroy_UpScreen(LPDIRECT3DVERTEXBUFFER9 buffer)
{
	OBJRELEASE(buffer);
	return S_OK;
};
HRESULT					GRAPHCORE::Destroy_Text(LPCSTR name)
{
	return S_OK;
};
HRESULT					GRAPHCORE::Destroy_Texts()
{
	TEXTSTRINGS * Temp = Text->Root;
	Text = Text->Root;
	while (Text)
	{
		Text = Text->textNext;
		delete Temp;
		Temp = Text;
	};
	Temp = NULL;
	return S_OK;
};
HRESULT					GRAPHCORE::Destroy_Texture(LPCSTR _name)
{
	//GraphicalCoreLocker.lock();
	if ((!Texture) || (!_name)) return E_FAIL;
	Texture->Remove_Texture(_name);
	//GraphicalCoreLocker.unlock();
	return S_OK;
};
HRESULT					GRAPHCORE::Destroy_Mesh(LPCSTR name, CString _name)
{
	//GraphicalCoreLocker.lock();
	if (!Mesh) return E_FAIL;
	if (Mesh->Remove_Mesh(name) == E_FAIL) return E_FAIL;
	MAP_UI.erase(_name);
	//GraphicalCoreLocker.unlock();
	return S_OK;
};
HRESULT					GRAPHCORE::Destroy_Meshes()
{
	//GraphicalCoreLocker.lock();
	if (!Mesh) return E_FAIL;
	Mesh->Clean();
	MAP_UI.clear();
	//GraphicalCoreLocker.unlock();
	return S_OK;
};
HRESULT					GRAPHCORE::Destroy_Object(int _ID)
	{
	GraphicalCoreLocker.lock();
	if (!Object) return E_FAIL;
	if (MAP_OBJ.size())
		{
		map<int, OBJECTS::OBJECT_DATA>::iterator Map_Iter = MAP_OBJ.find(_ID);
		if (Map_Iter != MAP_OBJ.end())
			MAP_OBJ.erase(Map_Iter);
		}
	GraphicalCoreLocker.unlock();
	return S_OK;
	};
HRESULT					GRAPHCORE::Destroy_Objects()
{
	//GraphicalCoreLocker.lock();
	if (!Object) return E_FAIL;
	Object->Clean();
	MAP_OBJ.clear();
	//GraphicalCoreLocker.unlock();
	return S_OK;
};
HRESULT					GRAPHCORE::Destroy_Cameras()
{
	OBJDELETE(Camera);
	return S_OK;
};
HRESULT					GRAPHCORE::Fill_VertexBuffer()
{
	DEVICE->CreateVertexBuffer(sizeof(vertcolor3D[0])*vertcolor3DQuantity, 0, VertexesAFVF2D, D3DPOOL_MANAGED, &VERTEXBUFFER, NULL);
	VOID* pData = NULL;
	VERTEXBUFFER->Lock(0, 0, (void**)&pData, 0);
	memcpy(pData, vertcolor3D, sizeof(vertcolor3D[0])*vertcolor3DQuantity);
	VERTEXBUFFER->Unlock();
	return S_OK;
};
HRESULT					GRAPHCORE::Fill_UpScreen(DWORD _color)
{
	UPSCREEN::Instance().Fill_UpScreen(DEVICE, D3DM, _color);
	return S_OK;
};
HRESULT					GRAPHCORE::Fill_Grid(float _a = 10.0f, int _size = 16, DWORD _newColor = 0)
{
	GRID::Instance().Fill_Grid(DEVICE, D3DM, _a, _size, _newColor);
	return S_OK;
};
HRESULT					GRAPHCORE::Render_Verteces()
{
	//Old Version
	//if (!DEVICE || !VERTEXBUFFER || !vertcolor3D) return E_FAIL;
	//DEVICE->SetStreamSource(0, VERTEXBUFFER, 0, sizeof(vertcolor3D[0]));
	//DEVICE->SetFVF(VertexesAFVF2D);
	//DEVICE->DrawPrimitive(D3DPT_LINELIST, 0, vertcolor3DQuantity/2);
	return S_OK;
};
HRESULT					GRAPHCORE::Render_Grid()
	{
	GRID::Instance().Render_Grid(DEVICE);
	return S_OK;
	};
HRESULT					GRAPHCORE::Render_Text(TEXTSTRINGS* _text)
{
	if (_text)
		_text->font[0]->DrawText(NULL, _text->string, -1, &_text->rec, DT_LEFT, _text->color[_text->Applied_Color]);
	return S_OK;
};
HRESULT					GRAPHCORE::Render_Sprite(RECT src, RECT dest)
{
	const RECT* src1 = &src;
	const RECT* dest1 = &dest;
	DEVICE->StretchRect(SURFACE, src1, BACKBUFFER, dest1, D3DTEXF_NONE);
	return S_OK;
};
HRESULT					GRAPHCORE::Render_UpScreen()
{
	UPSCREEN::Instance().Render_UpScreen(DEVICE);
	return S_OK;
};
HRESULT					GRAPHCORE::Render_Texture(LPCSTR _name)
{
	//Old Version of Render Textures

	//DEVICE->SetFVF(VertexexFVF3DColTex);	

	//Draw Walls
	//DEVICE->SetStreamSource(0,Map->Collision->CollisionBuffer,0,sizeof(VERTEXTEXTURE));

	//int TempQ = Map->Collision->Quantity;
	//MAPS::COLLISIONS * TempW = Map->Collision->Root;
	//if (Map->Collision->CollisionBuffer!=NULL)
	//	while (TempQ)
	//		{
	//		DEVICE->SetTexture(0,*TempW->texture);
	//		DEVICE->DrawPrimitive (D3DPT_TRIANGLESTRIP, 4*(Map->Collision->Quantity-TempQ), 2);
	//		TempQ--; TempW = TempW->NextCollision;
	//		};
	return S_OK;
};
HRESULT					GRAPHCORE::Render_Meshes()
	{
	if (GraphicalCoreLocker.try_lock())
		{
		DEVICE->SetFVF(VertexexFVF3DTex);
		map<int, OBJECTS::OBJECT_DATA>::iterator			Objects_Iter;
		list<OBJECTS::OBJECT_DATA::OBJECTMESH>::iterator	VEC_MESH_Iter;
		for (Objects_Iter = MAP_OBJ.begin(); Objects_Iter != MAP_OBJ.end(); Objects_Iter++)
			{
			if (Objects_Iter->second.LIST_MESH.size())
			for (VEC_MESH_Iter = Objects_Iter->second.LIST_MESH.begin(); VEC_MESH_Iter != Objects_Iter->second.LIST_MESH.end(); ++VEC_MESH_Iter)
				{
				VEC_MESH_Iter->ApplyMeshWorldMatrix(DEVICE);
				for (DWORD j = 0; j < Mesh->Get_Mesh(VEC_MESH_Iter->meshName)->materialsQuantity; j++)
					{
					DEVICE->SetMaterial(&Mesh->Get_Mesh(VEC_MESH_Iter->meshName)->meshMaterials[j]);
					DEVICE->SetTexture(0, Texture->Get_Texture(Mesh->Get_Mesh(VEC_MESH_Iter->meshName)->meshTextures[j].c_str()));
					(*Mesh->Get_Mesh(VEC_MESH_Iter->meshName)->mesh)->DrawSubset(j);
					};
				};
			};
		DEVICE->SetTexture(0, NULL);
		GraphicalCoreLocker.unlock();
		}
	return S_OK;
	};
HRESULT					GRAPHCORE::ChangeUpScreenAlpha(int alpha)
	{
	for ( int i = 0; i<4; i++ ) upScreen[ i ].COLOR = D3DCOLOR_RGBA(0, 0, 0, alpha);
	OBJRELEASE(UPSCREENBUFFER);
	DEVICE->CreateVertexBuffer(sizeof( upScreen ), 0, VertexesFVF2D, D3DPOOL_MANAGED, &UPSCREENBUFFER, NULL);
	VOID* pData = NULL;
	UPSCREENBUFFER->Lock(0, sizeof( pData ), ( void** ) &pData, 0);
	memcpy(pData, upScreen, sizeof( upScreen ));
	UPSCREENBUFFER->Unlock();
	return S_OK;
	};
void					GRAPHCORE::SetRenderState(_D3DRENDERSTATETYPE _type, DWORD _value)
	{ 
	DEVICE->SetRenderState(_type, _value);
	};
#pragma endregion
#pragma region GRAPHCORE_GRID
		GRAPHCORE::GRID& GRAPHCORE::GRID::Instance()
			{
			static GRID theSingleInstance;
			return theSingleInstance;
			}
		GRAPHCORE::GRID::GRID() : vertcolor3DQuantity(0), name("GRID")
			{
			if ( !Geometry ) Geometry = new GEOMETRY();
			};
		GRAPHCORE::GRID::~GRID()
			{
			OBJRELEASE(VERTEXBUFFER);
			Geometry->Remove_Verteces(name);
			OBJDELETE(Geometry);
			};
void	GRAPHCORE::GRID::Render_Grid(LPDIRECT3DDEVICE9 _device)
	{
	if ( ( !_device ) || ( !VERTEXBUFFER ) ) return;
	D3DXMATRIX Translation;
	D3DXMatrixIdentity(&Translation);
	_device->SetTransform(D3DTS_WORLD, &Translation);
	_device->SetStreamSource(0, VERTEXBUFFER, 0, sizeof( VERTEXCOLOR ));
	_device->SetFVF(VertexesAFVF2D);
	_device->SetTexture(0, NULL);
	_device->DrawPrimitive(D3DPT_LINELIST, 0, vertcolor3DQuantity*0.5f);
	};
void	GRAPHCORE::GRID::Fill_Grid(LPDIRECT3DDEVICE9 _device, D3DDISPLAYMODE _D3DM, float _a = 10.0f, int _size = 16, DWORD _newColor = 0)
	{
	if ( ( !_device ) || ( !Geometry ) || ( _size > 100 ) ) return;
	VERTEX_BASE * GridBase = Geometry->Get_Verteces(name);
	int shiftF = ( _size * 2 + 1 ) * 2, shiftS = ( _size * 2 + 1 ) * 2 + 1;
	vertcolor3DQuantity = 0;

	if ( !GridBase )
		{
		VERTEXCOLOR Grid[ 804 ];
		GridBase = Grid;
		};

	VERTEXCOLOR * Grid = ( VERTEXCOLOR * ) GridBase;

	for ( float i = -_size; i <= _size; i++ )
		{
		Grid[ vertcolor3DQuantity * 2 ]._x = i*_a; Grid[ vertcolor3DQuantity * 2 ]._y = 0; Grid[ vertcolor3DQuantity * 2 ]._z = -_size * 10;
		Grid[ vertcolor3DQuantity * 2 + 1 ]._x = i*_a; Grid[ vertcolor3DQuantity * 2 + 1 ]._y = 0; Grid[ vertcolor3DQuantity * 2 + 1 ]._z = _size * 10;
		Grid[ vertcolor3DQuantity * 2 + shiftF ]._x = _size * 10; Grid[ vertcolor3DQuantity * 2 + shiftF ]._y = 0; Grid[ vertcolor3DQuantity * 2 + shiftF ]._z = i*_a;
		Grid[ vertcolor3DQuantity * 2 + shiftS ]._x = -_size * 10; Grid[ vertcolor3DQuantity * 2 + shiftS ]._y = 0; Grid[ vertcolor3DQuantity * 2 + shiftS ]._z = i*_a;
		Grid[ vertcolor3DQuantity * 2 ].COLOR = Grid[ vertcolor3DQuantity * 2 + 1 ].COLOR = Grid[ vertcolor3DQuantity * 2 + shiftF ].COLOR = Grid[ vertcolor3DQuantity * 2 + shiftS ].COLOR = _newColor;
		vertcolor3DQuantity++;
		}

	vertcolor3DQuantity *= 4;
	Geometry->Set_Verteces(name, Grid);

	if ( !VERTEXBUFFER )
		_device->CreateVertexBuffer(sizeof( VERTEXDEFINITECOLOR ) *vertcolor3DQuantity, 0, VertexesFVF2D, D3DPOOL_MANAGED, &VERTEXBUFFER, NULL);
	VOID* pData = NULL;
	VERTEXBUFFER->Lock(0, sizeof( pData ), ( void** ) &pData, 0);
	memcpy(pData, Grid, sizeof( VERTEXDEFINITECOLOR ) *vertcolor3DQuantity);
	VERTEXBUFFER->Unlock();
	};
#pragma endregion
#pragma region GRAPHCORE_TEXTSTRING
		GRAPHCORE::TEXTSTRINGS::TEXTSTRINGS() : Applied_Font(0), Applied_Color(0), string(""), textNext(NULL)
			{
			rec.left = 200;
			rec.top = 420;
			rec.bottom = 460;
			rec.right = 400;
			fontDesc.CharSet = DEFAULT_CHARSET;
			fontDesc.OutputPrecision = OUT_TT_PRECIS;
			fontDesc.PitchAndFamily = DEFAULT_PITCH;
			fontDesc.Quality = CLIP_DEFAULT_PRECIS;
			fontDesc.MipLevels = D3DX_DEFAULT;
			fontDesc.Width = 0;
			if (Quantity == 0) Root = this;
			Quantity++;
			};
		GRAPHCORE::TEXTSTRINGS::~TEXTSTRINGS()
			{
			Quantity--;
			if (!Quantity)
				{
				Destroy_Fonts();
				Reset_Colors();
				Root = NULL;
				}
			textNext = NULL;
			};
HRESULT GRAPHCORE::TEXTSTRINGS::Initiate_Font(LPDIRECT3DDEVICE9 _Device, int _Height, int _Weight, bool _Italic, LPCSTR _Name, int _FontNumber)
{
	strcpy_s(fontDesc.FaceName, _Name);
	fontDesc.Height = _Height;
	fontDesc.Italic = _Italic;
	fontDesc.Weight = _Weight;
	HRESULT r;
	if (_FontNumber < 10) r = D3DXCreateFontIndirect(_Device, &fontDesc, &font[_FontNumber]); else return E_FAIL;
	return S_OK;
};
HRESULT GRAPHCORE::TEXTSTRINGS::Initiate_Color(D3DCOLOR &_color, int &_position) { color[_position] = _color; return S_OK; };
HRESULT GRAPHCORE::TEXTSTRINGS::Set_Font(int fontNumber) { Applied_Font = fontNumber; return S_OK; };
HRESULT GRAPHCORE::TEXTSTRINGS::Set_Color(int _colorNumber) { Applied_Color = _colorNumber; return S_OK; };
HRESULT GRAPHCORE::TEXTSTRINGS::Destroy_Font()
{
	return S_OK;
};
HRESULT GRAPHCORE::TEXTSTRINGS::Destroy_Fonts()
{
	for (int i = 0; i < 10; i++)
	{
		OBJRELEASE(font[i]);
	}
	ZeroMemory(&fontDesc, sizeof(D3DXFONT_DESC));
	return S_OK;
};
HRESULT GRAPHCORE::TEXTSTRINGS::Reset_Colors()
{
	for (int i = 0; i < 10; i++)
	{
		color[i] = 0;
	};
	return S_OK;
};
HRESULT GRAPHCORE::TEXTSTRINGS::Initiate_TextString(LPCSTR _string, int fontnumber, RECT _rec)
	{
	string = _string; Applied_Color = 0; Applied_Font = fontnumber; rec = _rec; return S_OK;
	};
HRESULT GRAPHCORE::TEXTSTRINGS::ChangeRec(int Coordinate, int Value)
	{
	if ( Coordinate == 0 ) rec.left = Value; if ( Coordinate == 1 ) rec.top = Value; if ( Coordinate == 2 ) rec.right = Value; if ( Coordinate == 3 ) rec.bottom = Value; return S_OK;
	};
HRESULT GRAPHCORE::TEXTSTRINGS::Change_TextString(LPCSTR _string)
	{
	this->string = _string; return S_OK;
	};
#pragma endregion
#pragma region GRAPHCORE_TEXTURES
					GRAPHCORE::TEXTURES::TEXTURES(LPDIRECT3DDEVICE9 _device)
						{
						Update_Default(_device);
						};
					GRAPHCORE::TEXTURES::~TEXTURES()
						{
						if (DefaultTexture)
							{
							OBJRELEASE(DefaultTexture);
							};
						};
HRESULT				GRAPHCORE::TEXTURES::Add_Texture(string _path, LPDIRECT3DTEXTURE9 * _texture)
	{
	if ((!_path.length()) || (!_texture) || (!DefaultTexture))
		{
		AfxMessageBox("In TEXTURES: Add_Texture: Either empty name or missing texture (default texture). Cannot proceed with operation.");
		return E_FAIL;
		};

	if (Textures.find(_path) != Textures.end())
		{
		AfxMessageBox("In TEXTURES: Add_Texture: Texture with this name already exists.");
		return E_FAIL;
		} else {
		Textures[_path].texture = _texture;
		};

	if (Textures.size() > 1000) AfxMessageBox("In TEXTURES: Add_Texture: More than 1000 textures were downloaded.");
	return S_OK;
	};
HRESULT				GRAPHCORE::TEXTURES::Add_Texture(string _path, LPDIRECT3DDEVICE9 _device)
	{
	//S_OK - new or existing texture were applied.
	//E_FAIL - no texture was loaded. using default.
	CHECK_FOR_EXISTENCE_NAME_DEVICE("TEXTURES: Add_Texture", _path.c_str(), _device);
	if (Update_Default(_device) == E_FAIL) return E_FAIL;

	if (Textures.size())
		{
		if (Textures.find(_path) != Textures.end())
			{
			return S_OK;
			} else {
			if (Load_Texture(_path, _device) == E_FAIL) return E_FAIL;
			};
		} else {
		if (Load_Texture(_path, _device) == E_FAIL) return E_FAIL;
		};

	if (Textures.size() > 1000) AfxMessageBox("In TEXTURES: Add_Texture: More than 1000 textures were downloaded.");
	return S_OK;
	};
HRESULT				GRAPHCORE::TEXTURES::Remove_Texture(string _path)
	{
	if ((!_path.length()) || (!Textures.size()))
		{
		AfxMessageBox("In TEXTURES: Remove_Texture: Either name or textures pool is empty. Cannot proceed with operation.");
		return E_FAIL;
		};

	if (Textures.find(_path) == Textures.end())
		{
		AfxMessageBox("In TEXTURES: Remove_Texture: Texture with this name doesn't exist. Cannot proceed with operation.");
		return E_FAIL;
		} else
		Textures.erase(_path);
	return S_OK;
	};
LPDIRECT3DTEXTURE9	GRAPHCORE::TEXTURES::Get_Texture(string _path)
	{
	if ((!_path.length()) || (!Textures.size()))
		{
		string g("In TEXTURES: Get_Texture: "); g.append(_path); g.append(" resource wasn't found or textures pool is empty.");
		AfxMessageBox(g.c_str());
		return NULL;
		};
	if (Textures.find(_path) == Textures.end())
		{
		string g("In TEXTURES: Get_Texture: "); g.append(_path); g.append(" resource wasn't found in textures pool.");
		AfxMessageBox(g.c_str());
		return NULL;
		};
	return *Textures[_path].texture;
	};
HRESULT				GRAPHCORE::TEXTURES::Set_Texture(string _path, LPDIRECT3DTEXTURE9 * _texture)
	{
	if ((!_path.length()) || (!_texture) || (!Textures.size())) return E_FAIL;
		{
		AfxMessageBox("In TEXTURES: Set_Texture: Either empty name, missing 'Texture' object or textures pool is empty. Cannot proceed with operation.");
		return E_FAIL;
		};
	if (Textures.find(_path) == Textures.end())
		{
		string g("In TEXTURES: Set_Texture: "); g.append(_path); g.append(" texture wasn't found in loaded reqistry.");
		AfxMessageBox(g.c_str());
		return E_FAIL;
		};
	Textures[_path].texture = _texture;
	return S_OK;
	};
HRESULT				GRAPHCORE::TEXTURES::Load_Texture(string _path, LPDIRECT3DDEVICE9 _device)
	{
	//S_OK - new texture was loaded.
	//E_FAIL - no texture was loaded. using default.

	Textures[_path].texture = new LPDIRECT3DTEXTURE9();
	if (!SUCCEEDED(D3DXCreateTextureFromFileA(_device, _path.c_str(), Textures[_path].texture)))
		{
		string g("In TEXTURES: Load_Texture: "); g.append(_path); g.append(" texture resource wasn't found. Using default.");
		AfxMessageBox(g.c_str());
		delete Textures[_path].texture;
		Textures[_path].texture = &DefaultTexture;
		return E_FAIL;
		};
	return S_OK;
	};
HRESULT				GRAPHCORE::TEXTURES::Update_Default(LPDIRECT3DDEVICE9 _device)
	{
	if (!DefaultTexture)
		{
		if (!SUCCEEDED(D3DXCreateTextureFromFileA(_device, GET_PATH_MATERIAL("DefaultTexture.png"), &DefaultTexture)))
			{
			AfxMessageBox("In TEXTURES: Update_Default: Default texture cannot be loaded. Cannot create Texture object.");
			OBJDELETE(DefaultTexture);
			return E_FAIL;
			};
		};
	return S_OK;
	};
#pragma endregion
#pragma region GRAPHCORE_TEXTURES_TEXTUREDATA
GRAPHCORE::TEXTURES::TEXTURE_DATA::TEXTURE_DATA(LPDIRECT3DTEXTURE9 * _texture, RECT _area = RECT()) : texture(_texture), area(_area) {};
GRAPHCORE::TEXTURES::TEXTURE_DATA::TEXTURE_DATA() : texture(NULL), area(RECT()) {};
GRAPHCORE::TEXTURES::TEXTURE_DATA::~TEXTURE_DATA()
{
	if (texture)
	{
		if (*texture)
		{
			OBJRELEASE(*texture);
			OBJDELETE(texture);
		};
	};
};
#pragma endregion
#pragma region GRAPHCORE_MESHESX
		GRAPHCORE::MESHES_X::MESHES_X(LPDIRECT3DDEVICE9 _device)
			{
			Update_Default(_device);
			};
		GRAPHCORE::MESHES_X::~MESHES_X()
			{
			OBJDELETE(Texture);
			if (defaultMesh)
				{
				OBJRELEASE(defaultMesh);
				};
			OBJDELETE(defaultMeshMaterial);
			};
HRESULT GRAPHCORE::MESHES_X::Add_Mesh(string _path, LPDIRECT3DDEVICE9 _device)
	{
	CHECK_FOR_EXISTENCE_NAME_DEVICE("Mesh", _path.c_str(), _device);
	if (Update_Default(_device) == E_FAIL) return E_FAIL;

	if (!Meshes.size())
		Load_Mesh(_path, _device);
	else
		{
		if (Meshes.find(_path) != Meshes.end())
			{
			string g("In MESHES_X: Add_Mesh: "); g.append(_path); g.append(" model already exists.");
			AfxMessageBox(g.c_str());
			return E_FAIL;
			}
		else
			Load_Mesh(_path, _device);
		return S_OK;
		};
	if (Meshes.size() > 300) AfxMessageBox("In MESHES_X: Add_Mesh: Warning: More than 300 meshes were downloaded.");
	return S_OK;
	};
HRESULT GRAPHCORE::MESHES_X::Remove_Mesh(string _path)
	{
	if ((!_path.length()) || (!Meshes.size()))
		{
		AfxMessageBox("In MESHES_X: Remove_Mesh: Either name or meshes pool is empty. Cannot proceed with operation.");
		return E_FAIL;
		};

	if (Meshes.find(_path) == Meshes.end())
		{
		string g("In MESHES_X: Remove_Mesh: "); g.append(_path); g.append(" model wasn't found in meshes pool.");
		AfxMessageBox(g.c_str());
		return E_FAIL;
		}
	else
		Meshes.erase(_path);

	return S_OK;
	};
HRESULT GRAPHCORE::MESHES_X::Clean()
	{
	Meshes.clear();
	return S_OK;
	};
HRESULT GRAPHCORE::MESHES_X::Set_Mesh(string _path, MESHES_DATA * _mesh)
	{
	if ((!_path.length()) || (!_mesh) || (!Meshes.size())) return E_FAIL;
		{
		AfxMessageBox("In MESHES_X: Set_Mesh: Either empty name, missing 'Mesh' object or meshes pool is empty. Cannot proceed with operation.");
		return E_FAIL;
		};
	if (Meshes.find(_path) == Meshes.end())
		{
		AfxMessageBox("In MESHES_X: Set_Mesh: Mesh with this name doesn't exist. Nothing to apply to.");
		return E_FAIL;
		};
	Meshes[_path] = *_mesh;
	return S_OK;
	};
HRESULT GRAPHCORE::MESHES_X::Load_Mesh(string _path, LPDIRECT3DDEVICE9 _device)
	{
	Meshes[_path].mesh = new LPD3DXMESH();
	if (!SUCCEEDED(D3DXLoadMeshFromX(_path.c_str(), D3DXMESH_SYSTEMMEM, _device, NULL, &buffer, NULL, &Meshes[_path].materialsQuantity, Meshes[_path].mesh)))
		{
		string g("In MESHES_X: Load_Mesh: Unable to load "); g.append(_path); g.append(" model. Using default.");
		AfxMessageBox(g.c_str());
		OBJDELETE(Meshes[_path].mesh);
		Meshes[_path].mesh = &defaultMesh;
		return S_OK;
		};
	if (!Meshes[_path].materialsQuantity)
		{
		Meshes[_path].meshMaterials = defaultMeshMaterial;
		Meshes[_path].materialsQuantity = 1;
		return S_OK;
		};

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)buffer->GetBufferPointer();

	Meshes[_path].meshMaterials = new D3DMATERIAL9[Meshes[_path].materialsQuantity]; if (!Meshes[_path].meshMaterials) return E_OUTOFMEMORY;

	ZeroMemory(Meshes[_path].meshMaterials, sizeof(D3DMATERIAL9)*Meshes[_path].materialsQuantity);

	for (DWORD i = 0; i < Meshes[_path].materialsQuantity; i++)
		{
		Meshes[_path].meshMaterials[i] = d3dxMaterials[i].MatD3D;

		Texture->Add_Texture(GET_PATH_MATERIAL(d3dxMaterials[i].pTextureFilename), _device);
		Meshes[_path].meshTextures.push_back(GET_PATH_MATERIAL(d3dxMaterials[i].pTextureFilename));
		};
	OBJRELEASE(buffer);
	return S_OK;
	};
HRESULT GRAPHCORE::MESHES_X::Update_Default(LPDIRECT3DDEVICE9 _device)
	{
	if (!defaultMesh)
		{
		if (!SUCCEEDED(D3DXLoadMeshFromX(GET_PATH_MODEL("DefaultMesh.x"), D3DXMESH_SYSTEMMEM, _device, NULL, NULL, NULL, NULL, &defaultMesh)))
			{
			AfxMessageBox("In MESHES_X: Unable to load default model. It is highly recommended to check resources. Cannot proceed operation.");
			return E_FAIL;
			};
		if (!Texture) Texture = new TEXTURES(_device);
		if (!Texture->DefaultTexture)
			{
			OBJDELETE(Texture);
			OBJRELEASE(defaultMesh);
			return E_FAIL;
			};
		};
	if (!defaultMeshMaterial)
		{
		defaultMeshMaterial = new D3DMATERIAL9();
		if (!defaultMeshMaterial)
			{
			OBJDELETE(Texture);
			OBJRELEASE(defaultMesh);
			return E_FAIL;
			};
		ZeroMemory(defaultMeshMaterial, sizeof(D3DMATERIAL9));
		defaultMeshMaterial->Power = 1.0f;
		};
	return S_OK;
	};
long	GRAPHCORE::MESHES_X::Get_Meshes_Quantity()
	{
	return Meshes.size();
	}
GRAPHCORE::MESHES_X::MESHES_DATA * GRAPHCORE::MESHES_X::Get_Mesh(string _path)
	{
	if ((!_path.length()) || (!Meshes.size()))
		{
		AfxMessageBox("In MESHES_X: Get_Mesh: Either name or meshes pool is empty. Cannot return the mesh.");
		return NULL;
		};
	if (Meshes.find(_path) == Meshes.end())
		{
		string g("In MESHES_X: Get_Mesh: "); g.append(_path); g.append(" model wasn't found in meshes pool.");
		AfxMessageBox(g.c_str());
		return NULL;
		};
	return &Meshes[_path];
	};
#pragma endregion
#pragma region GRAPHCORE_MESHESX_MESHESDATA
GRAPHCORE::MESHES_X::MESHES_DATA::MESHES_DATA() : mesh(NULL), meshMaterials(NULL), materialsQuantity(0) {};
GRAPHCORE::MESHES_X::MESHES_DATA::~MESHES_DATA()
	{
	if (mesh)
		{
		if (*mesh)
			{
			OBJRELEASE(*mesh);
			OBJDELETE(mesh);
			};
		};
	OBJSDELETE(meshMaterials);
	meshTextures.clear();
	};
#pragma endregion
#pragma region GRAPHCORE_OBJECTS
		GRAPHCORE::OBJECTS::OBJECTS() { };
		GRAPHCORE::OBJECTS::~OBJECTS() { };
HRESULT GRAPHCORE::OBJECTS::Remove_Object(list<OBJECT_DATA>::iterator _member)
	{

	if ( !Objects.size() )
		{
		AfxMessageBox("In OBJECTS: Remove_Object: Objects pool is empty. Cannot proceed with operation.");
		return E_FAIL;
		};
	Objects.erase(_member);

	//_member->Clean();

	return S_OK;
	};
HRESULT GRAPHCORE::OBJECTS::Clean()
	{
	Objects.clear();
	return S_OK;
	};
int		GRAPHCORE::OBJECTS::Object_Quantity() { return Objects.size(); };
list<GRAPHCORE::OBJECTS::OBJECT_DATA>::iterator GRAPHCORE::OBJECTS::Add_Object(string _name, OBJECT_DATA::MATERIAL_TYPES _type, D3DXVECTOR3 _position)
	{
	//if ( !_name.size() )
	//	{
	//	AfxMessageBox("Empty name was given. Applying default value.");
	//	_name = "Unnamed";
	//	};
	//OBJECT_DATA t(_name, _type, _position);
	//Objects.push_back(t);
	//Objects_Iter = --Objects.end();
	return Objects_Iter;
	};
GRAPHCORE::OBJECTS::OBJECT_DATA * GRAPHCORE::OBJECTS::Get_Object(list<GRAPHCORE::OBJECTS::OBJECT_DATA>::iterator _member)
	{
	//GraphicalCoreLocker.lock();
	if ( !Objects.size() )
		{
		AfxMessageBox("In OBJECTS: Get_Object: Objects pool is empty. Cannot return the object.");
		return NULL;
		};
	//GraphicalCoreLocker.unlock();
	return &( *_member );
	};
GRAPHCORE::OBJECTS * GRAPHCORE::OBJECTS::Set_Current_Object(int _ID, LPCSTR _name)
	{
	return NULL;
	};
#pragma endregion
#pragma region GRAPHCORE_OBJECTS_OBJECTDATA
				GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECT_DATA(string _name = "Unnamed Object", MATERIAL_TYPES _type = Dummy, D3DXVECTOR3 _translation = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 _rotation = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 _scaling = D3DXVECTOR3(1, 1, 1)) : 
					name(_name), Type(_type), ID(quantity++), translation(_translation), rotation(_rotation), scaling(_scaling) { };
				GRAPHCORE::OBJECTS::OBJECT_DATA::~OBJECT_DATA() { };
HRESULT			GRAPHCORE::OBJECTS::OBJECT_DATA::Add_Mesh(LPCSTR _name, D3DXVECTOR3 _translation = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 _angle = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 _scaling = D3DXVECTOR3(1, 1, 1))
	{
	if ( Mesh )
		{
		if ( Mesh->Get_Meshes_Quantity() )
			{
			if ( Mesh->Get_Mesh(_name) )
				{
				LIST_MESH.push_back(OBJECTMESH(*this, _name, _translation, _angle, _scaling));
				}
			else
				{
				AfxMessageBox("No mesh with such name was found. Cannot add this mesh name to object registry.");
				};
			}
		else { AfxMessageBox("Available meshes' quantity is 0. Cannot add any mesh name to object registry."); };
		}
	else
		{
		AfxMessageBox("Mesh isn't initiated. Cannot add any mesh name to object registry.");
		};
	return S_OK;
	};

const string	GRAPHCORE::OBJECTS::OBJECT_DATA::ObjectName() const { return name; };
string			GRAPHCORE::OBJECTS::OBJECT_DATA::ObjectNameChange() { return name; };

void			GRAPHCORE::OBJECTS::OBJECT_DATA::SetXt(float _Xt) { translation.x = _Xt; };
void			GRAPHCORE::OBJECTS::OBJECT_DATA::SetYt(float _Yt) { translation.y = _Yt; };
void			GRAPHCORE::OBJECTS::OBJECT_DATA::SetZt(float _Zt) { translation.z = _Zt; };

const float	&GRAPHCORE::OBJECTS::OBJECT_DATA::GetXt() const { return translation.x; };
const float	&GRAPHCORE::OBJECTS::OBJECT_DATA::GetYt() const { return translation.y; };
const float	&GRAPHCORE::OBJECTS::OBJECT_DATA::GetZt() const { return translation.z; };

HRESULT			GRAPHCORE::OBJECTS::OBJECT_DATA::Apply_Texture(LPDIRECT3DTEXTURE9 * _texture, MESHES_X * Model)
	{
	return S_OK;
	};
HRESULT			GRAPHCORE::OBJECTS::OBJECT_DATA::Add_Mesh(LPDIRECT3DDEVICE9 _device, LPCSTR _meshPath, WORLDPOSITION _pos)
	{
	_GET_LOG_MAKE_RECORD("I try to lock VEC_PUSH for adding mesh...", true);
	while ( !GraphicalCoreLocker.try_lock() ) { _GET_LOG_MAKE_RECORD("Add_Mesh failed... AGAIN!!!", true); Sleep(10); }
		
		_GET_LOG_MAKE_RECORD("Add_Mesh succeeded...", true);
		if ( !Mesh || !_meshPath || !_device ) { GraphicalCoreLocker.unlock(); return E_FAIL; };
		if ( !Mesh->Get_Meshes_Quantity() ) { GraphicalCoreLocker.unlock(); return E_FAIL; };
		if ( !Mesh->Get_Mesh(GET_PATH_MODEL(_meshPath)) ) { GraphicalCoreLocker.unlock(); return E_FAIL; };
		_GET_LOG_MAKE_RECORD("Trying to push Mesh into List...", true);
		LIST_MESH.push_back(OBJECTMESH(*this, GET_PATH_MODEL(_meshPath), D3DXVECTOR3(_pos.X, _pos.Y, _pos.Z), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1)));
		_GET_LOG_MAKE_RECORD("Successfully pushed Mesh into List...", true);
		GraphicalCoreLocker.unlock();
		
	return S_OK;
	};
void			GRAPHCORE::OBJECTS::OBJECT_DATA::ApplyObjectWorldMatrix(LPDIRECT3DDEVICE9 DEVICE)
	{
	D3DXMATRIX TRANSLATION; D3DXMatrixIdentity(&TRANSLATION);
	D3DXMatrixTranslation(&TRANSLATION, translation.x, translation.y, translation.z);
	DEVICE->SetTransform(D3DTS_WORLD, &TRANSLATION);
	};
HRESULT			GRAPHCORE::OBJECTS::OBJECT_DATA::Clean()
	{
	GUI_locker.lock();
	if ( LIST_MESH.size() )
		LIST_MESH.pop_back();
	GUI_locker.unlock();
	return S_OK;
	};
#pragma endregion
#pragma region GRAPHCORE_OBJECTS_OBJECTDATA_OBJECTMESH
				GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::OBJECTMESH(OBJECT_DATA& _parent, LPCSTR _meshName = "NoName", D3DXVECTOR3 _translation = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 _rotation = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 _scaling = D3DXVECTOR3(1, 1, 1)) : 
				meshName(_meshName), Parent(_parent), translation(_translation), rotation(_rotation), scaling(_scaling)
					{
					BYTE* v = 0;
					( *Mesh->Get_Mesh(meshName)->mesh )->LockVertexBuffer(0, ( void** ) &v);
					D3DXComputeBoundingSphere(( D3DXVECTOR3* ) v, ( *Mesh->Get_Mesh(meshName)->mesh )->GetNumVertices(), D3DXGetFVFVertexSize(( *Mesh->Get_Mesh(meshName)->mesh )->GetFVF()), &Sphere._center, &Sphere._radius);
					D3DXComputeBoundingBox(( D3DXVECTOR3* ) v, ( *Mesh->Get_Mesh(meshName)->mesh )->GetNumVertices(), D3DXGetFVFVertexSize(( *Mesh->Get_Mesh(meshName)->mesh )->GetFVF()), &Box._min, &Box._max);
					( *Mesh->Get_Mesh(meshName)->mesh )->UnlockVertexBuffer();
					};
				GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::~OBJECTMESH() { };
void			GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::SetXt(float _Xt) { translation.x = _Xt; };
void			GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::SetYt(float _Yt) { translation.y = _Yt; };
void			GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::SetZt(float _Zt) { translation.z = _Zt; };
void			GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::SetXa(float _Xa) { rotation.x = _Xa; };
void			GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::SetYa(float _Ya) { rotation.y = _Ya; };
void			GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::SetZa(float _Za) { rotation.z = _Za; };
void			GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::SetXs(float _Xs) { scaling.x = _Xs; };
void			GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::SetYs(float _Ys) { scaling.y = _Ys; };
void			GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::SetZs(float _Zs) { scaling.z = _Zs; };

const float	&GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::GetXt() const { return translation.x; };
const float	&GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::GetYt() const { return translation.y; };
const float	&GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::GetZt() const { return translation.z; };
const float	&GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::GetXa() const { return rotation.x; };
const float	&GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::GetYa() const { return rotation.y; };
const float	&GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::GetZa() const { return rotation.z; };
const float	&GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::GetXs() const { return translation.x; };
const float	&GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::GetYs() const { return translation.y; };
const float	&GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::GetZs() const { return translation.z; };

void			GRAPHCORE::OBJECTS::OBJECT_DATA::OBJECTMESH::ApplyMeshWorldMatrix(LPDIRECT3DDEVICE9 _device)
	{
	D3DXMATRIX Translation, Rotation, Scaling;
	D3DXMatrixIdentity(&Translation); D3DXMatrixIdentity(&Rotation); D3DXMatrixIdentity(&Scaling);
	//////////////////////////////////////////////////////////////////////////////////////////////
	D3DXMatrixTranslation(&Translation, /*translation.x + */Parent.translation.x, /*translation.y + */Parent.translation.y, /*translation.z + */Parent.translation.z);
	D3DXMatrixRotationYawPitchRoll(&Rotation, D3DXToRadian(rotation.x + Parent.rotation.x), D3DXToRadian(rotation.y + Parent.rotation.y), D3DXToRadian(rotation.z + Parent.rotation.z));
	D3DXMatrixScaling(&Scaling, scaling.x * Parent.scaling.x, scaling.y * Parent.scaling.y, scaling.z * Parent.scaling.z);
	_device->SetTransform(D3DTS_WORLD, &( Rotation * Scaling * Translation ));
	};
#pragma endregion

#pragma region ENGINE
LPDIRECT3DVERTEXBUFFER9 ENGINE::POINTER::POINTERBUFFER = NULL;

CString ENGINE::DoRayProcedure(int x, int y, LPDIRECT3DDEVICE9 device, GRAPHCORE::OBJECTS * Object)
	{
	//CalculatePickingRay(x, y, device);
	//TransformPickingRay(device);

	//GRAPHCORE::OBJECTS* TempObject = Object->Root;

	//while (TempObject)
	//	{
	//	for (int i = 0; i<Object->LIST_MESH.size();i++)
	//		{
	//		if (RaySphereIntersectionTest(&Object->LIST_MESH[i].Sphere)) return Object->name;
	//		RayCubeIntersectionTest(&Object->LIST_MESH[i].Box);
	//		};
	//	TempObject = TempObject->objNext;
	//	};
	return "No Object Selected";
	};
HRESULT ENGINE::CalculatePickingRay(int x, int y, LPDIRECT3DDEVICE9 device)
	{
	float px = 0.0f;
	float py = 0.0f;

	D3DVIEWPORT9 vp;
	device->GetViewport(&vp);

	D3DXMATRIX proj;
	device->GetTransform(D3DTS_PROJECTION, &proj);

	px = ( ( ( 2.0f*x ) / 515/*vp.Width*/ ) - 1.0f ) / proj(0, 0);
	py = ( ( ( -2.0f*y ) / 290/*vp.Height*/ ) + 1.0f ) / proj(1, 1);

	PickingRay._origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	PickingRay._direction = D3DXVECTOR3(px, py, 1.0f);

	return S_OK;
	};
HRESULT ENGINE::TransformPickingRay(LPDIRECT3DDEVICE9 device)
	{
	D3DXMATRIX view;
	device->GetTransform(D3DTS_VIEW, &view);
	D3DXMATRIX viewInverse;
	D3DXMatrixInverse(&viewInverse, 0, &view);
	// Ïðåîáðàçîâàíèå íà÷àëüíîé òî÷êè ëó÷à, w = 1.
	D3DXVec3TransformCoord(
		&PickingRay._origin,
		&PickingRay._origin,
		&viewInverse);

	// Ïðåîáðàçîâàíèå âåêòîðà íàïðàâëåíèÿ ëó÷à, w = 0.
	D3DXVec3TransformNormal(
		&PickingRay._direction,
		&PickingRay._direction,
		&viewInverse);

	// Íîðìàëèçàöèÿ âåêòîðà íàïðàâëåíèÿ
	D3DXVec3Normalize(&PickingRay._direction, &PickingRay._direction);
	return S_OK;
	};
bool ENGINE::RaySphereIntersectionTest(GRAPHCORE::BOUNDINGSPHERE * sphere)
	{
	D3DXVECTOR3 v = PickingRay._origin - sphere->_center;

	float b = 2.0f * D3DXVec3Dot(&PickingRay._direction, &v);
	float c = D3DXVec3Dot(&v, &v) - ( FLOAT ) ( sphere->_radius * sphere->_radius );

	// Íàõîäèì äèñêðèìèíàíò
	float discriminant = ( b * b ) - ( 4.0f * c );

	// Ïðîâåðÿåì íà ìíèìûå ÷èñëà
	if ( discriminant < 0.0f ) return false;

	discriminant = sqrtf(discriminant);

	float s0 = ( -b + discriminant ) / 2.0f;
	float s1 = ( -b - discriminant ) / 2.0f;

	// Åñëè åñòü ðåøåíèå >= 0, ëó÷ ïåðåñåêàåò ñôåðó
	if ( s0 >= 0.0f || s1 >= 0.0f )
		return true;

	return false;
	}
float * ENGINE::RayCubeIntersectionTest(GRAPHCORE::BOUNDINGBOX * box)
	{
	float tMin[ 3 ], tMax[ 3 ], t1[ 3 ], t2[ 3 ], i[ 3 ], tNear, res[ 3 ];
	VEC_SUB(tMin, box->_min, PickingRay._origin); /* tMin = Cube_Max_MIN - origin */
	VEC_DIVV(tMin, tMin, PickingRay._direction);    /* tMin = tMin - ray        */
	VEC_SUB(tMax, box->_max, PickingRay._origin); /* tMax = Cube_Max_MAX - origin */
	VEC_DIVV(tMax, tMax, PickingRay._direction);    /* tMax /= ray              */
	VEC_MIN(t1, tMin, tMax);   /* t1   = min(tMin, tMax)   */
	VEC_MAX(t2, tMin, tMax);   /* t2   = max(tMin, tMax)   */
	tNear = MAX(MAX(t1[ 0 ], t1[ 1 ]), t1[ 2 ]);
	tNear <= 0 ? tNear = MIN(MIN(t2[ 0 ], t2[ 1 ]), t2[ 2 ]) : 0;
	VEC_ASSIGN(i, PickingRay._direction);              /* i = ray */
	VEC_MULN(i, tNear);            /* i *= tNear */
	VEC_ADD(res, PickingRay._origin, i);      /* res = origin + i */
	return res;
	};
#pragma endregion
