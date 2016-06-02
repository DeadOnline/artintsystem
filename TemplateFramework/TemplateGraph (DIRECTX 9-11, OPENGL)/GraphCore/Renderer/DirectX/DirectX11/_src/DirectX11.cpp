////------------------------------------------------------------------------------DIRECTX11------------------------------------------------------------------------------//
//
//#define SETVERTEXBUFFER(_bytewidth, _vrectangle) BufferDesc.ByteWidth = _bytewidth; BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; BufferData.pSysMem = _vrectangle; d3d11Device->CreateBuffer(&BufferDesc, &BufferData, &vertBuffer);
//#define SETINDEXBUFFER(_bytewidth, _irectangle) BufferDesc.ByteWidth = _bytewidth; BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER; BufferData.pSysMem = _irectangle; d3d11Device->CreateBuffer(&BufferDesc, &BufferData, &indexBuffer);
//#define SETPRERENDEROPTIONS(_devCon, _primitiveTopology, _layout, _vBuffer, _stride, _offset, _iBuffer, _VS, _PS) _devCon->IASetPrimitiveTopology( _primitiveTopology ); _devCon->IASetInputLayout( _layout ); _devCon->IASetVertexBuffers( 0, 1, &_vBuffer, &_stride, &_offset ); _devCon->IASetIndexBuffer( _iBuffer, DXGI_FORMAT_R32_UINT, 0); _devCon->VSSetShader(_VS, 0, 0); d3d11DevCon->PSSetShader(_PS, 0, 0);
//ID3D11Device			* DIRECTX11::FVF_BASE::d3d11Device = NULL;
//ID3D11DeviceContext		* DIRECTX11::FVF_BASE::d3d11DevCon = NULL;
//IDXGISwapChain			* DIRECTX11::FVF_BASE::d3d11SwapChain = NULL;
//ID3D11RasterizerState	* DIRECTX11::FVF_BASE::CCWcullMode = NULL;
//ID3D11RasterizerState	* DIRECTX11::FVF_BASE::WireFrame = NULL;
//ID3D11RasterizerState	* DIRECTX11::FVF_BASE::CWcullMode = NULL;
//ID3D11RasterizerState	* DIRECTX11::FVF_BASE::RSCullNone = NULL;
//ID3D11DepthStencilState	* DIRECTX11::FVF_BASE::DepthStencilStateLessEqual = NULL;
//ID3D11DepthStencilState	* DIRECTX11::FVF_BASE::DepthStencilStateNone = NULL;
//ID3D11Buffer			* DIRECTX11::LIGHTS::constantBuffer = NULL;
//D3D11_DEPTH_STENCIL_DESC DIRECTX11::FVF_BASE::DepthStencilDescriptionOn = {true, D3D11_DEPTH_WRITE_MASK_ALL, D3D11_COMPARISON_LESS_EQUAL, false, D3D11_DEFAULT_STENCIL_READ_MASK, D3D11_DEFAULT_STENCIL_WRITE_MASK, {D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_REPLACE, D3D11_COMPARISON_ALWAYS}, {D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_REPLACE, D3D11_COMPARISON_ALWAYS}};
//D3D11_DEPTH_STENCIL_DESC DIRECTX11::FVF_BASE::DepthStencilDescriptionOff = {false, D3D11_DEPTH_WRITE_MASK_ALL, D3D11_COMPARISON_LESS_EQUAL, false, D3D11_DEFAULT_STENCIL_READ_MASK, D3D11_DEFAULT_STENCIL_WRITE_MASK, {D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_REPLACE, D3D11_COMPARISON_ALWAYS}, {D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_REPLACE, D3D11_COMPARISON_ALWAYS}};
//D3D11_RASTERIZER_DESC	DIRECTX11::FVF_BASE::d3d11RasterizerDescription = {D3D11_FILL_SOLID,D3D11_CULL_BACK,0,0,0,0,0,0,0,0};
//D3D11_BUFFER_DESC		DIRECTX11::FVF_BASE::BufferDesc = {0, D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER, 0, 0};
//D3D11_SUBRESOURCE_DATA	DIRECTX11::FVF_BASE::BufferData = {0,0,0};
//D3D11_SAMPLER_DESC		DIRECTX11::FVF_POS_TEX::samplerDescription = {D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP, 0, 0, D3D11_COMPARISON_NEVER, {0,0,0,0}, 0, D3D11_FLOAT32_MAX};
//D3D11_BUFFER_DESC		DIRECTX11::LIGHTS::BufferDesc = {80, D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0, 0};
//
//HRESULT DIRECTX11::Initiate_D3D(HWND hWnd)
//	{
//	return S_OK;
//	};
//HRESULT DIRECTX11::Initiate_GraphDevice( HWND hWnd, DWORD style, int sizeX, int sizeY )
//	{
//	BackBufferDescription.Width = sizeX;
//	BackBufferDescription.Height = sizeY;
//
//	SwapChainDescription.OutputWindow = hWnd;
//
//	DepthStencilDescription.Width     = sizeX;
//	DepthStencilDescription.Height    = sizeY;
//	
//	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &SwapChainDescription, &d3d11SwapChain, &d3d11Device, NULL, &d3d11DevCon);
//	d3d11SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (void**)&d3d11BackBuffer ); //Create our d3d11BackBuffer
//	d3d11Device->CreateRenderTargetView( d3d11BackBuffer, NULL, &d3d11RenderTargetView );
//
//	FVF_BASE::d3d11Device		= d3d11Device;
//	FVF_BASE::d3d11DevCon		= d3d11DevCon;
//	FVF_BASE::d3d11SwapChain	= d3d11SwapChain;
//
//	return S_OK;
//	};
//
//HRESULT DIRECTX11::Initiate_Camera(CAMERA_TYPES _cameraType)
//	{
//	return S_OK;
//	};
//HRESULT DIRECTX11::Initiate_Light(LPCSTR _name, LIGHT_TYPES _type)
//	{
//	if (_type == LIGHTS::TYPES::point)
//	Light[_name] = new LIGHTS_POINT(d3d11Device);
//	else
//	Light[_name] = new LIGHTS_SPOT(d3d11Device);
//
//	return S_OK;
//	};
//HRESULT DIRECTX11::Load_Geometry(LPCSTR _name, DIRECTX_SUPPORTED_FILE_FORMATS _fileFormat, char _geometryType = 'c', COLLISION_TYPES _collisionType = Box)
//	{
//	//?_collisionType?
//	MeshGeometry[_name].Load_Geometry(d3d11Device);
//	return S_OK;
//	};
//HRESULT DIRECTX11::Initiate_MeshAnimation(LPCSTR name, DIRECTX_SUPPORTED_FILE_FORMATS _fileFormat, COLLISION_TYPES _collisionType)
//	{
//	return S_OK;
//	};
//HRESULT DIRECTX11::Initiate_Shader(LPCSTR _name, LPCSTR _adress)
//	{
//	if (Shader.find(_name) != Shader.end()) Shader[_name];
//	Shader[_name].LoadShader(_adress, d3d11Device);
//	return S_OK;
//	};
//HRESULT DIRECTX11::Initiate_SkyMap(LPCSTR _name)
//	{
//	SkyMap[_name].Initiate_SkyMap(d3d11Device);
//	return S_OK;
//	};
//HRESULT DIRECTX11::Initiate_SpecialEffect(LPCSTR _name)
//	{
//	return S_OK;
//	};
//HRESULT DIRECTX11::Initiate_Surface(int height, int width, LPCSTR name)
//	{
//	return S_OK;
//	};
//HRESULT DIRECTX11::Initiate_Text(LPCSTR _name, LPCSTR _string, int _fontNumber, int _color)
//	{
//	return S_OK;
//	};
//HRESULT DIRECTX11::Initiate_Text_Font(LPCSTR facename, int Height, int Weight, bool IsItalic)
//	{
//	return S_OK;
//	};
//HRESULT DIRECTX11::Initiate_Text_Color(D3DCOLOR _color, int _position)
//	{
//	return S_OK;
//	};
//HRESULT DIRECTX11::Initiate_Texture(LPCSTR _name)
//	{
//	return S_OK;
//	};
//HRESULT DIRECTX11::Initiate_TextureScreen(float X1, float Y1, float X2, float Y2, float X3, float Y3, float X4, float Y4)
//	{
//	return S_OK;
//	};
//HRESULT DIRECTX11::Initiate_UpScreen()
//	{
//	//if (UpScreen.find("UpScreen") != UpScreen.end()) return E_FAIL;
//	UpScreen["UpScreen"].Initiate_UpScreen(d3d11Device);
//	return S_OK;
//	};
//
//HRESULT DIRECTX11::Render_UpScreen() 
//	{ 
//	UpScreen["UpScreen"].opacity = 50/*_percentage*/;
//	UpScreen["UpScreen"].Render(d3d11DevCon);
//	return S_OK; 
//	};
//HRESULT DIRECTX11::Render_Mesh(LPCSTR _meshKey)
//	{
//	MeshGeometry[_meshKey].Render(d3d11DevCon, (CAMERAS_FREE*)CurrentCamera);
//	return S_OK;
//	};
//HRESULT DIRECTX11::Render_ObjGeometry_DirectX11(LPCSTR _name)
//	{
//	Light["Torch"]->Apply_Light(d3d11DevCon, (CAMERAS_FREE*)CurrentCamera);
//	ObjGeometry[_name].Render((CAMERAS_FREE*)CurrentCamera);
//	return S_OK;
//	};
//HRESULT DIRECTX11::Render_Scene()
//	{
//	return S_OK;
//	};
//HRESULT DIRECTX11::Render_SkyMap(LPCSTR _name, CAMERAS_FREE * _camera)
//	{
//	SkyMap[_name].Render(d3d11DevCon, (CAMERAS_FREE*)CurrentCamera);
//	return S_OK;
//	};
//HRESULT DIRECTX11::Render_AnimatedMesh(LPCSTR _meshAnimKey)
//	{
//	return S_OK;
//	};
//HRESULT DIRECTX11::Render_Cursor(LPCSTR _textureKey, int m_fCursorX, int m_fCursorY, int m_iHotSpotX, int m_iHotSpotY)
//	{
//	return S_OK;
//	};
//HRESULT DIRECTX11::Render_Sprite(RECT src1, RECT dest1) 
//	{
//	return S_OK;
//	};
//HRESULT DIRECTX11::Render_Text(LPCSTR _textKey, RECT _rec) 
//	{ return S_OK; };
//HRESULT DIRECTX11::Render_Texture(LPCSTR _textureKey) 
//	{ return S_OK; };
//
//HRESULT DIRECTX11::Change_TextureMap(LPDIRECT3DTEXTURE9 texture)
//	{
//	return S_OK;
//	};
//HRESULT DIRECTX11::Change_UpScreenAlpha(int alpha)
//	{
//	return S_OK;
//	};
//
//HRESULT DIRECTX11::Set_RenderOptions(int _sizeX, int _sizeY)
//	{
//
//	//-------------------------Z Buffering-------------------------//
//	d3d11Device->CreateTexture2D(&DepthStencilDescription, NULL, &d3d11DepthStencilBuffer);			//Create the Depth and
//	d3d11Device->CreateDepthStencilView(d3d11DepthStencilBuffer, NULL, &d3d11DepthStencilView);			//Stencil View
//	d3d11Device->CreateDepthStencilState(&FVF_BASE::DepthStencilDescriptionOn, &FVF_BASE::DepthStencilStateLessEqual);
//	d3d11Device->CreateDepthStencilState(&FVF_BASE::DepthStencilDescriptionOff, &FVF_BASE::DepthStencilStateNone);
//	d3d11DevCon->OMSetDepthStencilState(FVF_BASE::DepthStencilStateLessEqual, 0);
//	d3d11DevCon->OMSetRenderTargets( 1, &d3d11RenderTargetView, d3d11DepthStencilView );			//Set our Render Target
//	//------------------------~Z Buffering-------------------------//
//
//	//---------------------------Shaders---------------------------//
//	Initiate_Shader("Shader_UpScreen_YellowOpacity", "EffectsUpScreenYellowOpacity.fx");	//POS COLOR						| opacity
//	Initiate_Shader("Shader_UpScreen_Opacity", "EffectsUpScreenOpacity.fx");				//POS COLOR						| opacity
//	Initiate_Shader("Shader_Camera", "EffectsCam.fx");										//POS COLOR						| CONSTANTBUFFERPEROBJECT(WVP)
//	Initiate_Shader("Shader_TempMeshTex", "EffectsTex.fx");									//POS TEXCOORDS					| CONSTANTBUFFERPEROBJECT(WVP) Texture2D SamplerState
//	Initiate_Shader("Shader_Skymap", "EffectsTextureSkymap.fx");							//POS TEXCOORDS3D				| CONSTANTBUFFERPEROBJECT(WVP) TextureCube SamplerState
//	Initiate_Shader("Shader_TexNormal", "EffectsTexNormals.fx");							//POS TEXCOORDS NORMAL			| CONSTANTBUFFERPEROBJECT(WVP) Texture2D SamplerState
//	Initiate_Shader("Shader_TexNormalSpotLight", "EffectsTexNormalSpotLight.fx");			//POS TEXCOORDS NORMAL LIGHT	| CONSTANTBUFFERPEROBJECT(WVP) CONSTANTBUFFERPERFRAME LIGHT(...x1) Texture2D SamplerState
//	Initiate_Shader("Shader_TexNormalPointLight", "EffectsTexNormalPointLight.fx");			//POS TEXCOORDS NORMAL LIGHT	| CONSTANTBUFFERPEROBJECT(WVP) CONSTANTBUFFERPERFRAME LIGHT(...x2) Texture2D SamplerState
//	//--------------------------~Shaders---------------------------//
//
//	//---------------------------UpScreen--------------------------//
//	Initiate_UpScreen();																	//POS COLOR
//	//--------------------------~UpScreen--------------------------//
//	
//	//-------------------------Mesh example------------------------//
//	Load_Geometry("Temp", _g, 'c', None);																		//POS TEX
//	//------------------------~Mesh example------------------------//
//	
//	//---------------------------SkyMap----------------------------//
//	Initiate_SkyMap("Sky");																//POS TEX NORMAL
//	//--------------------------~SkyMap----------------------------//
//
//	//---------------------------Light----------------------------//
//	Initiate_Light("Torch", LIGHT_TYPES::Spotlight);
//	Initiate_Light("Lamp", LIGHT_TYPES::Directed);
//	//--------------------------~Light----------------------------//
//	
//	//------------------------Loading models-----------------------//
//	//Initiate_Mesh_From_File("spaceCompound.obj", _obj, None);											//POS TEX NORMAL
//	//Initiate_Mesh_From_File("bottle.obj", _obj, None);											        //POS TEX NORMAL
//	////------------------------Loading models-----------------------//
//	
//	//-----------------------Applying shaders----------------------//
//	UpScreen["UpScreen"].AddShader("Dead", &Shader["Shader_UpScreen_Opacity"]);
//	MeshGeometry["Temp"].AddShader("TexturingShader", &Shader["Shader_TempMeshTex"]);
//	SkyMap["Sky"].AddShader("SkymapShader", &Shader["Shader_Skymap"]);
//	ObjGeometry["spaceCompound.obj"].Add_Shader(0, "Wall", &Shader["Shader_TexNormalPointLight"]);
//	ObjGeometry["bottle.obj"].Add_Shader(0, "bottle", &Shader["Shader_TexNormalPointLight"]);
//	//----------------------~Applying shaders----------------------//
//
//
//
//
//
//
//
//	//-----------------------------Blending----------------------------//
//	d3d11BlendDescription.AlphaToCoverageEnable = false;
//	d3d11BlendDescription.RenderTarget[0] = d3d11RenderTargetBlendDescription;
//	d3d11Device->CreateBlendState(&d3d11BlendDescription, &Transparency);
//	//----------------------------~Blending----------------------------//
//	
//
//	d3d11DevCon->RSSetState(FVF_BASE::RSCullNone);
//	d3d11DevCon->RSSetViewports(1, &d3d11Viewport);
//	d3d11DevCon->OMSetBlendState(Transparency, 0, 0xffffffff);
//
//
//	
//
//	///////////////**************picking**************////////////////////
//	int* bottleHit = new int[20];
//	int bottleSubsets = 0;
//	int numBottles = 20;
//	int ClientWidth = 0;
//	int ClientHeight = 0;
//	int score = 0;
//	bool isShoot = false;
//	float pickedDist = 0.0f;
//	float bottleXPos = -30.0f;
//	float bottleZPos = 30.0f;
//	float bxadd = 0.0f;
//	float bzadd = 0.0f;
//
//	for(int i = 0; i < numBottles; i++)
//	{
//		bottleHit[i] = 0;
//
//		//set the loaded bottles world space
//		D3DXMatrixIdentity(&bottleWorld[i]);
//
//		bxadd++;
//
//		if(bxadd == 10)
//		{
//			bzadd -= 1.0f;
//			bxadd = 0;
//		}
//
//		D3DXMatrixRotationY(&Rotation, 3.14f);
//		D3DXMatrixScaling(&Scale, 1.0f, 1.0f, 1.0f);
//		D3DXMatrixTranslation(&Translation, bottleXPos + bxadd*10.0f, 4.0f, bottleZPos + bzadd*10.0f );
//
//		bottleWorld[i] = Rotation * Scale * Translation;
//	}
//	///////////////*************~picking**************////////////////////
//	//--------------------------------~Render options for DirectX 11-----------------------------------//
//	return true;
//	};
//
//void DIRECTX11::UPSCREEN::Initiate_UpScreen(ID3D11Device * d3d11Device)
//			{
//
//			VERTEX triangles[] = {
//				VERTEX( 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f ),
//				VERTEX( 1.0f, -1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f ),
//				VERTEX( -1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f ),
//				VERTEX( -1.0f, -1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f ),
//			};
//
//			SETVERTEXBUFFER(sizeof( VERTEX ) * 4, triangles);
//
//			};
//void DIRECTX11::UPSCREEN::Render(ID3D11DeviceContext * d3d11DevCon)
//			{
//			//SETPRERENDEROPTIONS(d3d11DevCon, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, ShaderLayout[currentShader].second, vertBuffer, stride, offset, indexBuffer, ShaderLayout[currentShader].first->VS, ShaderLayout[currentShader].first->PS);
//
//			d3d11DevCon->UpdateSubresource( ClipBoardShaderBuffer, 0, NULL, &opacity, 0, 0 );
//			d3d11DevCon->VSSetConstantBuffers( 0, 1, &ClipBoardShaderBuffer );
//
//			d3d11DevCon->OMSetDepthStencilState(DepthStencilStateNone, 0);
//			d3d11DevCon->Draw( 4, 0);
//			d3d11DevCon->OMSetDepthStencilState(DepthStencilStateLessEqual, 0);
//			};
//
//void DIRECTX11::TEMPORARYMESH::Load_Geometry(ID3D11Device * d3d11Device)
//			{
//
//			VERTEX vRectangle[] =
//				{
//				// Back Face
//				VERTEX( -30.9f, -30.9f, 0.5f, 0.0f, 0.0f), //0
//				VERTEX( -30.9f, 30.9f, 0.5f, 1.0f, 0.0f),
//				VERTEX( 30.9f, 30.9f, 0.5f, 1.0f, 1.0f),
//				VERTEX( 30.9f, -30.9f, 0.5f, 0.0f, 1.0f), //3
//				// Front Face
//				VERTEX(-30.9f, -30.9f, -0.9f, 0.0f, 1.0f), //4
//				VERTEX(-30.9f,  30.9f, -0.9f, 1.0f, 1.0f),
//				VERTEX( 30.9f,  30.9f, -0.9f, 1.0f, 0.0f),
//				VERTEX( 30.9f, -30.9f, -0.9f, 0.0f, 0.0f) //7
//				};
//
//			DWORD iRectangle[] = 
//				{
//				// Front Face
//				0,  1,  2,
//				0,  2,  3,
//
//				// Back Face
//				0,  1,  5,
//				0,  5,  4,
//
//				// Top Face
//				0,  4, 7,
//				0, 2, 7,
//
//				// Bottom Face
//				6, 5, 4,
//				6, 7, 4,
//
//				// Left Face
//				6, 2, 3,
//				6, 3, 7,
//
//				// Right Face
//				6, 5, 2,
//				6, 2, 1
//				};
//
//			SETVERTEXBUFFER(sizeof( VERTEX ) * 8, vRectangle);
//			SETINDEXBUFFER(sizeof(DWORD) * 36, iRectangle);
//
//			D3DX11CreateShaderResourceViewFromFile( d3d11Device, "metalpanel.jpg", NULL, NULL, &Texture, NULL );
//			};
//void DIRECTX11::TEMPORARYMESH::Render(ID3D11DeviceContext * d3d11DevCon, CAMERAS_FREE * SceneCamera)
//			{
//			//SETPRERENDEROPTIONS(d3d11DevCon, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, ShaderLayout[currentShader].second, vertBuffer, stride, offset, indexBuffer, ShaderLayout[currentShader].first->VS, ShaderLayout[currentShader].first->PS);
//
//			//Set the WVP matrix and send it to the constant buffer in effect file
//			D3DXMatrixTranspose(&constantBufferPerObject.WVP, &(*SceneCamera->getCameraMatrixView() * SceneCamera->Camera_Matrix_Projection));
//
//			//Set to shader valuables tex
//			d3d11DevCon->PSSetShaderResources( 0, 1, &Texture ); //Bind an array of shader resources to the pixel shader stage.
//			d3d11DevCon->PSSetSamplers( 0, 1, &TextureSamplerState ); //Set an array of sampler states to the pixel shader stage.
//			d3d11DevCon->VSSetConstantBuffers( 0, 1, &ClipBoardShaderBuffer ); //Sets the constant buffers used by the vertex shader stage.
//
//			//Send to shader valuables
//			d3d11DevCon->UpdateSubresource( ClipBoardShaderBuffer, 0, NULL, &constantBufferPerObject, 0, 0 ); //The CPU copies data from memory to a subresource created in non-mappable memory
//
//			d3d11DevCon->DrawIndexed( 36, 0, 0 );
//			};
//
//void DIRECTX11::OBJGEOMETRY::Initiate_ObjGeometry(LPCSTR filename, bool isRHCoordSys, bool computeNormals/*, std::vector<XMFLOAT3>& vertPosArray, std::vector<DWORD>& vertIndexArray*/)
//	{
//	std::wstring meshMatLib;								//String to hold our obj material library filename
//
//	std::vector<DWORD> indices;
//	std::vector<D3DXVECTOR3> vertPos;
//	std::vector<D3DXVECTOR2> vertTexCoords;
//	std::vector<D3DXVECTOR3> vertNormals;
//
//	std::vector<VERTEX> vertPosUnOptimized;
//	//Check to see if the file was opened
//
//	std::ifstream FileIF(filename);
//	char currString[100] = {}, start [100] = {}, first [100] = {}, second [100] = {}, third [100] = {};
//	char position[10] = {}, tex[10] = {}, normal[10] = {};
//	int vertexTexQuantity = 0, vertexNormalQuantity = 0;
//	
//	if (FileIF)
//		{
//		bool isNewGroup = false;
//		SubMesh.push_back(SUBMESHES());
//		while(FileIF.getline(currString, 100))
//			{
//			int indexNumb = 0, texNumb = -1, normalNumb = -1;
//			sscanf (currString, "%s %s %s %s", start, first, second, third);
//			
//			if (!strcmp(start, "v"))
//				{
//				vertPos.push_back(D3DXVECTOR3((float)strtod(first,NULL), (float)strtod(second,NULL), (float)strtod(third,NULL)));
//				};
//			if (!strcmp(start, "vt"))
//				{
//				vertTexCoords.push_back(D3DXVECTOR2((float)strtod(first,NULL), (float)strtod(second,NULL)));
//				};
//			if (!strcmp(start, "vn"))
//				{
//				vertNormals.push_back(D3DXVECTOR3((float)strtod(first,NULL), (float)strtod(second,NULL), (float)strtod(third,NULL)));
//				};
//			if (!strcmp(start, "f"))
//				{
//				sscanf (first, "%d%*[/]%d%*[/]%d", &indexNumb, &texNumb, &normalNumb); if (strstr(first, "//")) { normalNumb = texNumb; texNumb = -1; };
//				vertPosUnOptimized.push_back(VERTEX(vertPos[indexNumb-1].x,	vertPos[indexNumb-1].y,	vertPos[indexNumb-1].z, 0, 0, 0, 0, 0));
//				if (texNumb != -1) vertPosUnOptimized[vertPosUnOptimized.size()-1].texCoord = vertTexCoords[texNumb-1];
//				if (normalNumb != -1) vertPosUnOptimized[vertPosUnOptimized.size()-1].normal = vertNormals[normalNumb-1];
//
//				sscanf (second, "%d%*[/]%d%*[/]%d", &indexNumb, &texNumb, &normalNumb); if (strstr(first, "//")) { normalNumb = texNumb; texNumb = -1; };
//				vertPosUnOptimized.push_back(VERTEX(vertPos[indexNumb-1].x,	vertPos[indexNumb-1].y,	vertPos[indexNumb-1].z, 0, 0, 0, 0, 0));
//				if (texNumb != -1) vertPosUnOptimized[vertPosUnOptimized.size()-1].texCoord = vertTexCoords[texNumb-1];
//				if (normalNumb != -1) vertPosUnOptimized[vertPosUnOptimized.size()-1].normal = vertNormals[normalNumb-1];
//
//				sscanf (third, "%d%*[/]%d%*[/]%d", &indexNumb, &texNumb, &normalNumb); if (strstr(first, "//")) { normalNumb = texNumb; texNumb = -1; };
//				vertPosUnOptimized.push_back(VERTEX(vertPos[indexNumb-1].x,	vertPos[indexNumb-1].y,	vertPos[indexNumb-1].z, 0, 0, 0, 0, 0));
//				if (texNumb != -1) vertPosUnOptimized[vertPosUnOptimized.size()-1].texCoord = vertTexCoords[texNumb-1];
//				if (normalNumb != -1) vertPosUnOptimized[vertPosUnOptimized.size()-1].normal = vertNormals[normalNumb-1];
//				}
//			if (!strcmp(start, "s")) { }
//			if (!strcmp(start, "u")) { }
//			if (!strcmp(start, "g")) { };
//			};
//		VertQuantity = vertPosUnOptimized.size(); 
//		};
//	SETVERTEXBUFFER(sizeof( VERTEX ) * VertQuantity, &vertPosUnOptimized[0]);
//
//	D3DX11CreateShaderResourceViewFromFile( d3d11Device, "metalpanel.jpg", NULL, NULL, &Material.Texture_Diffuse, NULL );
//
//	};
//void DIRECTX11::OBJGEOMETRY::Add_Shader(int _meshNumber, LPCSTR _name, SHADERS* _shader)
//	{
//	AddShader(_name, _shader);
//	};
//void DIRECTX11::OBJGEOMETRY::Render(CAMERAS_FREE * _camera)
//	{
//	for (int y = 0; y<SubMesh.size(); y++)
//		{
//
//		//SETPRERENDEROPTIONS(d3d11DevCon, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, ShaderLayout[currentShader].second, vertBuffer, stride, offset, indexBuffer, ShaderLayout[currentShader].first->VS, ShaderLayout[currentShader].first->PS);
//
//		//Set the WVP matrix and send it to the constant buffer in effect file
//		D3DXMatrixTranspose(&constantBufferPerObject.WVP, &(*_camera->getCameraMatrixView() * _camera->Camera_Matrix_Projection));
//
//		//Send to shader valuables tex
//		d3d11DevCon->PSSetShaderResources( 0, 1, &Material.Texture_Diffuse );
//		d3d11DevCon->PSSetSamplers( 0, 1, &TextureSamplerState );
//		d3d11DevCon->VSSetConstantBuffers( 0, 1, &ClipBoardShaderBuffer ); 
//
//		//Send to shader valuables
//		//d3d11DevCon->PSSetConstantBuffers( 1, 1, &ClipBoardShaderBuffer );
//		d3d11DevCon->UpdateSubresource( ClipBoardShaderBuffer, 0, NULL, &constantBufferPerObject, 0, 0 );
//		
//		d3d11DevCon->Draw( VertQuantity, 0);
//		};
//	};
//
//void DIRECTX11::SKYMAP::Initiate_SkyMap(ID3D11Device * d3d11Device)
//	{
//	//-----------------~DirectX 11 SkyMap-----------------//
//	CreateSphere(10, 10);
//
//	//Tell D3D we will be loading a cube texture
//	D3DX11_IMAGE_LOAD_INFO loadSMInfo;
//	loadSMInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
//
//	//Load the texture
//	ID3D11Texture2D* SMTexture = 0;
//	D3DX11CreateTextureFromFile(d3d11Device, "skymap.dds", &loadSMInfo, 0, (ID3D11Resource**)&SMTexture, 0);
//
//	//Create the textures description
//	D3D11_TEXTURE2D_DESC SMTextureDesc;
//	SMTexture->GetDesc(&SMTextureDesc);
//
//	//Tell D3D We have a cube texture, which is an array of 2D textures
//	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
//	SMViewDesc.Format = SMTextureDesc.Format;
//	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
//	SMViewDesc.TextureCube.MipLevels = SMTextureDesc.MipLevels;
//	SMViewDesc.TextureCube.MostDetailedMip = 0;
//
//	//Create the Resource view
//	d3d11Device->CreateShaderResourceView(SMTexture, &SMViewDesc, &smrv);
//	//-----------------~DirectX 11 SkyMap-----------------//
//	};
//void DIRECTX11::SKYMAP::Render(ID3D11DeviceContext * d3d11DevCon, CAMERAS_FREE * SceneCamera)
//	{
//	//SETPRERENDEROPTIONS(d3d11DevCon, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, ShaderLayout[currentShader].second, vertBuffer, stride, offset, indexBuffer, ShaderLayout[currentShader].first->VS, ShaderLayout[currentShader].first->PS);
//
//	D3DXMATRIX sphereWorld, Scale, Translation;
//	D3DXMatrixIdentity(&sphereWorld);
//	D3DXMatrixScaling(&Scale, 5.0f, 5.0f, 5.0f );
//	D3DXMatrixTranslation(&Translation, SceneCamera->Camera_Vector_Pos.x + SceneCamera->Camera_Vector_Pivot->x, SceneCamera->Camera_Vector_Pos.y + SceneCamera->Camera_Vector_Pivot->y, SceneCamera->Camera_Vector_Pos.z + SceneCamera->Camera_Vector_Pivot->z );
//	sphereWorld = Scale * Translation;
//
//	//Set the WVP matrix and send it to the constant buffer in effect file
//	D3DXMatrixTranspose(&constantBufferPerObject.WVP, &(sphereWorld * *SceneCamera->getCameraMatrixView() * SceneCamera->Camera_Matrix_Projection));
//
//	d3d11DevCon->UpdateSubresource( ClipBoardShaderBuffer, 0, NULL, &constantBufferPerObject, 0, 0 );
//	d3d11DevCon->VSSetConstantBuffers( 0, 1, &ClipBoardShaderBuffer );
//
//	//Send our skymap resource view to pixel shader
//	d3d11DevCon->PSSetShaderResources( 0, 1, &smrv );
//	d3d11DevCon->PSSetSamplers( 0, 1, &TextureSamplerState );
//
//	d3d11DevCon->DrawIndexed( NumSphereFaces * 3, 0, 0 );
//	};
//void DIRECTX11::SKYMAP::CreateSphere(int LatLines, int LongLines)
//{
//	NumSphereVertices = ((LatLines-2) * LongLines) + 2;
//	NumSphereFaces  = ((LatLines-3)*(LongLines)*2) + (LongLines*2);
//
//	float sphereYaw = 0.0f;
//	float spherePitch = 0.0f;
//
//	std::vector<VERTEX> vertices(NumSphereVertices);
//
//	D3DXVECTOR3 currVertPos(0.0f, 0.0f, 1.0f);
//
//	vertices[0].pos.x = 0.0f;
//	vertices[0].pos.y = 0.0f;
//	vertices[0].pos.z = 1.0f;
//
//	for(DWORD i = 0; i < LatLines-2; ++i)
//	{
//		spherePitch = (i+1) * (3.14/(LatLines-1));
//		D3DXMatrixRotationX(&Rotationx, spherePitch);
//		for(DWORD j = 0; j < LongLines; ++j)
//		{
//			sphereYaw = j * (6.28/(LongLines));
//			D3DXMatrixRotationZ(&Rotationy, sphereYaw);
//			D3DXVec3TransformNormal(&currVertPos, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &(Rotationx * Rotationy) );	
//			D3DXVec3Normalize(&currVertPos, &currVertPos);
//			vertices[i*LongLines+j+1].pos.x = currVertPos.x;
//			vertices[i*LongLines+j+1].pos.y = currVertPos.y;
//			vertices[i*LongLines+j+1].pos.z = currVertPos.z;
//		}
//	}
//
//	vertices[NumSphereVertices-1].pos.x =  0.0f;
//	vertices[NumSphereVertices-1].pos.y =  0.0f;
//	vertices[NumSphereVertices-1].pos.z = -1.0f;
//
//	std::vector<DWORD> indices(NumSphereFaces * 3);
//
//	int k = 0;
//	for(DWORD l = 0; l < LongLines-1; ++l)
//	{
//		indices[k] = 0;
//		indices[k+1] = l+1;
//		indices[k+2] = l+2;
//		k += 3;
//	}
//
//	indices[k] = 0;
//	indices[k+1] = LongLines;
//	indices[k+2] = 1;
//	k += 3;
//
//	for(DWORD i = 0; i < LatLines-3; ++i)
//	{
//		for(DWORD j = 0; j < LongLines-1; ++j)
//		{
//			indices[k]   = i*LongLines+j+1;
//			indices[k+1] = i*LongLines+j+2;
//			indices[k+2] = (i+1)*LongLines+j+1;
//
//			indices[k+3] = (i+1)*LongLines+j+1;
//			indices[k+4] = i*LongLines+j+2;
//			indices[k+5] = (i+1)*LongLines+j+2;
//
//			k += 6; // next quad
//		}
//
//		indices[k]   = (i*LongLines)+LongLines;
//		indices[k+1] = (i*LongLines)+1;
//		indices[k+2] = ((i+1)*LongLines)+LongLines;
//
//		indices[k+3] = ((i+1)*LongLines)+LongLines;
//		indices[k+4] = (i*LongLines)+1;
//		indices[k+5] = ((i+1)*LongLines)+1;
//
//		k += 6;
//	}
//
//	for(DWORD l = 0; l < LongLines-1; ++l)
//	{
//		indices[k] = NumSphereVertices-1;
//		indices[k+1] = (NumSphereVertices-1)-(l+1);
//		indices[k+2] = (NumSphereVertices-1)-(l+2);
//		k += 3;
//	}
//
//	indices[k] = NumSphereVertices-1;
//	indices[k+1] = (NumSphereVertices-1)-LongLines;
//	indices[k+2] = NumSphereVertices-2;
//
//	SETVERTEXBUFFER(sizeof( VERTEX ) * NumSphereVertices, &vertices[0]);
//	SETINDEXBUFFER(sizeof(DWORD) * NumSphereFaces * 3, &indices[0]);
//
//}
//
//void DIRECTX11::LIGHTS_POINT::Apply_Light(ID3D11DeviceContext * d3d11DevCon, CAMERAS_FREE * Scene_Camera)
//	{
//	Light.pos.x = Scene_Camera->Camera_Vector_Pos.x + Scene_Camera->Camera_Vector_Pivot->x;
//	Light.pos.y = Scene_Camera->Camera_Vector_Pos.y + Scene_Camera->Camera_Vector_Pivot->y;
//	Light.pos.z = Scene_Camera->Camera_Vector_Pos.z + Scene_Camera->Camera_Vector_Pivot->z;
//
//	d3d11DevCon->UpdateSubresource( constantBuffer, 0, NULL, &Light, 0, 0 );
//	d3d11DevCon->PSSetConstantBuffers(0, 1, &constantBuffer);	
//	};
//void DIRECTX11::LIGHTS_SPOT::Apply_Light(ID3D11DeviceContext * d3d11DevCon, CAMERAS_FREE * Scene_Camera)
//	{
//	Light.pos = Scene_Camera->Camera_Vector_Pos + *Scene_Camera->Camera_Vector_Pivot;
//	Light.dir = Scene_Camera->Camera_Vector_Look;
//	d3d11DevCon->UpdateSubresource( constantBuffer, 0, NULL, &Light, 0, 0 );
//	d3d11DevCon->PSSetConstantBuffers(0, 1, &constantBuffer);	
//	};
//
//void DIRECTX11::pickRayVector(float mouseX, float mouseY, D3DXVECTOR3& pickRayInWorldSpacePos, D3DXVECTOR3& pickRayInWorldSpaceDir, CAMERAS_FREE * _camera, int _sizeX, int _sizeY)
//{
//	D3DXVECTOR3 pickRayInViewSpaceDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	D3DXVECTOR3 pickRayInViewSpacePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//	float PRVecX, PRVecY, PRVecZ;
//
//	//Transform 2D pick position on screen space to 3D ray in View space
//	PRVecX =  ((( 2.0f * mouseX) / ClientWidth ) - 1 ) / _camera->Camera_Matrix_Projection(0,0);
//	PRVecY = -((( 2.0f * mouseY) / ClientHeight) - 1 ) / _camera->Camera_Matrix_Projection(1,1);
//	PRVecZ =  1.0f;	//View space's Z direction ranges from 0 to 1, so we set 1 since the ray goes "into" the screen
//
//	pickRayInViewSpaceDir = D3DXVECTOR3(PRVecX, PRVecY, PRVecZ);
//
//	//Uncomment this line if you want to use the center of the screen (client area)
//	//to be the point that creates the picking ray (eg. first person shooter)
//	pickRayInViewSpaceDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//
//	// Transform 3D Ray from View space to 3D ray in World space
//	D3DXMATRIX pickRayToWorldSpaceMatrix;
//	float matInvDeter;	//We don't use this, but the xna matrix inverse function requires the first parameter to not be null
//
//	D3DXMatrixInverse(&pickRayToWorldSpaceMatrix, &matInvDeter, _camera->getCameraMatrixView());	//Inverse of View Space matrix is World space matrix
//
//	D3DXVec3TransformCoord(&pickRayInWorldSpacePos, &pickRayInViewSpacePos, &pickRayToWorldSpaceMatrix);
//	D3DXVec3TransformCoord(&pickRayInWorldSpaceDir, &pickRayInViewSpaceDir, &pickRayToWorldSpaceMatrix);
//}
//bool DIRECTX11::PointInTriangle(D3DXVECTOR3& triV1, D3DXVECTOR3& triV2, D3DXVECTOR3& triV3, D3DXVECTOR3& point )
//{
//	//To find out if the point is inside the triangle, we will check to see if the point
//	//is on the correct side of each of the triangles edges.
//
//	D3DXVECTOR3 cp1, cp2;
//	D3DXVec3Cross(&cp1, &(triV3 - triV2), &(point - triV2));
//	D3DXVec3Cross(&cp2, &(triV3 - triV2), &(triV1 - triV2));
//
//	if(D3DXVec3Dot(&cp1, &cp2) >= 0)
//	{
//		D3DXVec3Cross(&cp1, &(triV3 - triV1), &(point - triV1));
//		D3DXVec3Cross(&cp2, &(triV3 - triV1), &(triV2 - triV1));
//		if(D3DXVec3Dot(&cp1, &cp2) >= 0)
//		{
//			D3DXVec3Cross(&cp1, &(triV2 - triV1), &(point - triV1));
//			D3DXVec3Cross(&cp2, &(triV2 - triV1), &(triV3 - triV1));
//			if(D3DXVec3Dot(&cp1, &cp2) >= 0) return true; else return false;
//		}
//		else
//			return false;
//	}
//	return false;
//}
//float DIRECTX11::pick(D3DXVECTOR3 pickRayInWorldSpacePos, D3DXVECTOR3 pickRayInWorldSpaceDir, std::vector<D3DXVECTOR3>& vertPosArray, std::vector<DWORD>& indexPosArray, D3DXMATRIX& worldSpace)
//{ 		
//	//Loop through each triangle in the object
//	for(int i = 0; i < indexPosArray.size()/3; i++)
//	{
//		//Triangle's vertices V1, V2, V3
//		D3DXVECTOR3 tri1V1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		D3DXVECTOR3 tri1V2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		D3DXVECTOR3 tri1V3 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//Temporary 3d floats for each vertex
//		D3DXVECTOR3 tV1, tV2, tV3;
//
//		//Get triangle 
//		tV1 = vertPosArray[indexPosArray[(i*3)+0]];
//		tV2 = vertPosArray[indexPosArray[(i*3)+1]];
//		tV3 = vertPosArray[indexPosArray[(i*3)+2]];
//
//		tri1V1 = D3DXVECTOR3(tV1.x, tV1.y, tV1.z);
//		tri1V2 = D3DXVECTOR3(tV2.x, tV2.y, tV2.z);
//		tri1V3 = D3DXVECTOR3(tV3.x, tV3.y, tV3.z);
//
//		//Transform the vertices to world space
//		D3DXVec3TransformCoord(&tri1V1, &tri1V1, &worldSpace);
//		D3DXVec3TransformCoord(&tri1V2, &tri1V2, &worldSpace);
//		D3DXVec3TransformCoord(&tri1V3, &tri1V3, &worldSpace);
//
//		//Find the normal using U, V coordinates (two edges)
//		D3DXVECTOR3 U = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		D3DXVECTOR3 V = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		D3DXVECTOR3 faceNormal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		U = tri1V2 - tri1V1;
//		V = tri1V3 - tri1V1;
//
//		//Compute face normal by crossing U, V
//		D3DXVec3Cross(&faceNormal, &U, &V);
//
//		D3DXVec3Normalize(&faceNormal, &faceNormal);
//
//		//Calculate a point on the triangle for the plane equation
//		D3DXVECTOR3 triPoint = tri1V1;
//
//		//Get plane equation ("Ax + By + Cz + D = 0") Variables
//		float tri1A = faceNormal.x;
//		float tri1B = faceNormal.y;
//		float tri1C = faceNormal.z;
//		float tri1D = (-tri1A*triPoint.x - tri1B*triPoint.y - tri1C*triPoint.z);
//
//		//Now we find where (on the ray) the ray intersects with the triangles plane
//		float ep1, ep2, t = 0.0f;
//		float planeIntersectX, planeIntersectY, planeIntersectZ = 0.0f;
//		D3DXVECTOR3 pointInPlane = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		ep1 = (pickRayInWorldSpacePos.x * tri1A) + (pickRayInWorldSpacePos.y * tri1B) + (pickRayInWorldSpacePos.z * tri1C);
//		ep2 = (pickRayInWorldSpaceDir.x * tri1A) + (pickRayInWorldSpaceDir.y * tri1B) + (pickRayInWorldSpaceDir.z * tri1C);
//
//		//Make sure there are no divide-by-zeros
//		if(ep2 != 0.0f)
//			t = -(ep1 + tri1D)/(ep2);
//
//		if(t > 0.0f)    //Make sure you don't pick objects behind the camera
//		{
//			//Get the point on the plane
//			planeIntersectX = pickRayInWorldSpacePos.x + pickRayInWorldSpaceDir.x * t;
//			planeIntersectY = pickRayInWorldSpacePos.y + pickRayInWorldSpaceDir.y * t;
//			planeIntersectZ = pickRayInWorldSpacePos.z + pickRayInWorldSpaceDir.z * t;
//
//			pointInPlane = D3DXVECTOR3(planeIntersectX, planeIntersectY, planeIntersectZ);
//
//			//Call function to check if point is in the triangle
//			if(PointInTriangle(tri1V1, tri1V2, tri1V3, pointInPlane))
//			{
//				//Return the distance to the hit, so you can check all the other pickable objects in your scene
//				//and choose whichever object is closest to the camera
//				return t/2.0f;
//			}
//		}
//	}
//	//return the max float value (near infinity) if an object was not picked
//	return FLT_MAX;
//}
//
////-----------------------------------------------------------------------------~DIRECTX11------------------------------------------------------------------------------////HRESULT DIRECTX9::DIRECTX9_TEXTSTRINGS::Render_Texture(LPDIRECT3DDEVICE9 device, LPDIRECT3DVERTEXBUFFER9 d3dTexBuffer)
//{
//device->SetFVF(VertexexFVFTex);
//device->SetStreamSource(0, d3dTexBuffer, 0, sizeof(VERTEXARRAY2DTEX));
//device->SetTexture(0,texture);
//device->DrawPrimitive (D3DPT_TRIANGLESTRIP, 0, 2);
//device->SetTexture(0,NULL);
//return S_OK; 
//};

//RELEASES
/*
//d3d11SwapChain->Release();
//d3d11Device->Release();
//d3d11DevCon->Release();
//d3d11BackBuffer->Release();
*/