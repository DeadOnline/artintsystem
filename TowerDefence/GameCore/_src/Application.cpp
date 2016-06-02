#include "../_inc/Application.h"
#include "../_inc/StateManager.h"

#define DIRECTX9_RENDER() DirectXObject->StartScene(); UserComsRun(); RenderingRun(); CheckingRun(); DirectXObject->EndScene();

#define ISKEY(x) !GetInputter()->KeyPressed( x )
#define ISMOUSE(x) GetInputter()->x

#define VEC_BOT D3DXVECTOR3(0,-1,0)

#define GETGLOBAL() GetRenderer()->GetGlobal()
#define GETOBJECT(objectID) GetRenderer()->GetGlobal()->GetObjectI(objectID)
#define GETCAMERA(cameraID) GetRenderer()->GetGlobal()->GetCamera(cameraID)

using namespace APP;

using namespace WINAPIAPPLICATIONCORE;
using namespace DEBUGLOGCODE;
using namespace GRAPHCORE;
using namespace INPUTCORE;

#define SPEEDBOOSTLIMIT(x) ( x < -90.0f ) ? x = -90.0f : ( x > 90.0f ) ? x = 90.0f : 0
#define TORADIANSFROMANGLE(x) (x * 3.14 / 180)
#define BRAKE_SPEED 3.0f

#define GRID_COLOR 158900
#define YolochkaZ 100 //TODO remove
#define YolochkaZSpread 100

WORLDPOSITION translation, rotation, scaling; float Zr = 0; //TODO this must be in database

bool IsLocked = true;
int currentCameraID = 0;

SCENECONTROLLER SceneController;

APPLICATION::APPLICATION( LPCSTR _caption, DWORD _style, int _sizeX, int _sizeY, RENDERER_TYPES _renderType ) :
APPLICATIONCORE( _caption, _style, _sizeX, _sizeY ),
GRAPHICSCORE( GethWnd(), _style, GetAreaRect( Client ).right - GetAreaRect( Client ).left, GetAreaRect( Client ).bottom - GetAreaRect( Client ).top, _renderType ),
INOUTSHELL( GethWnd() ),
ObjectsDataBase(NULL) {}
APPLICATION::~APPLICATION() {};

HRESULT APPLICATION::Init()
	{
	#pragma region PRE INIT
					//------------------------------------------------PRE INIT------------------------------------------------//
	// Call Console 
	CreateConsole ();

	//Considered to use database

	//First blood
	//Get mysql version
	printf ( "MySQL client version: %s\n", mysql_get_client_info () );

	// Получаем дескриптор соединения
	ObjectsDataBase = mysql_init ( NULL );
	if ( !ObjectsDataBase )
		{
		// Если дескриптор не получен – выводим сообщение об ошибке
		fprintf ( stderr, "Error: can't create MySQL-descriptor\n" );
		LOG ( GethWnd (), "SQL object failed to initialize" );
		return S_FALSE; //Если используется оконное приложение
		}
	// Подключаемся к серверу
	if ( !mysql_real_connect ( ObjectsDataBase, "localhost", "root", "Millenium", NULL, NULL, NULL, 0 ) ) //As must be, login 'n' password should be taken from variables
		{
		// Если нет возможности установить соединение с сервером 
		// базы данных выводим сообщение об ошибке
		fprintf ( stderr, "Error: can't connect to server %s\n", mysql_error ( ObjectsDataBase ) );
		LOG ( GethWnd (), "No connection to server" );
		}
	else
		{
		// Если соединение успешно установлено выводим фразу - "Success!"
		fprintf ( stdout, "SERVER Success!\n" );
		LOG ( GethWnd (), "SERVER Success!" );
		}

	// Пробнем создать какую-нить бд
	if ( mysql_query ( ObjectsDataBase, "CREATE DATABASE IF NOT EXISTS artintsys" ) )
		{
		fprintf ( stderr, "%s\n", mysql_error ( ObjectsDataBase ) );
		LOG ( GethWnd (), "Database failed to create!" );
		return S_FALSE;
		}

	mysql_set_character_set ( ObjectsDataBase, "utf8" );
	//Смотрим изменилась ли кодировка на нужную, по умалчанию идёт latin1
	cout << "connection character set: " << mysql_character_set_name ( ObjectsDataBase ) << endl;

	srand ( time ( NULL ) ); //Preinitialize random func

	LOG ( GethWnd (), "APPLICATION::Init()" );

	//------------------------------------------------~PRE INIT------------------------------------------------//  
	#pragma endregion
	
	vector<int> GeomTreeIDs, GeomBoardID, GeomBoneIDs, GeomBonePlate1, GeomTestIDs, GeomActorIDs, GeomTexIDs; //These are IDs of Objects

	//////////////////SCENE: OPTIONS DIRECTX 9-11///////////////
	EnterCriticalSection( &GraphicsCoreCriticalSection );
	GetRenderer()->Set_RenderOptions();

	//------------------------------------------------LOAD TEMPLATES------------------------------------------------//

	//------------------------TEXTURES INITIATION------------------------//
	GeomTexIDs.push_back( GetRenderer()->Initiate_Texture( GET_CONJOINED_PATH( PATH_TEXTURES, "Domino Game Menu Top.png" ))); //1
	GeomTexIDs.push_back( GetRenderer()->Initiate_Texture( GET_CONJOINED_PATH( PATH_TEXTURES, "Domino Game Menu Background.bmp" ))); //2
	//------------------------~TEXTURES INITIATION------------------------//

	GetRenderer()->Set_Grid( 100, 50, GRID_COLOR ); //1
	GetRenderer()->Set_UpScreen (GetClientX(), GetClientY(), GeomTexIDs[0]);

	currentCameraID = GetRenderer()->Initiate_Camera_Free( WORLDPOSITION( 2000, 2000, 2000 ), //TODO MAGIC NUMBER
														   WORLDPOSITION( 0, -1, 0 ),
														   WORLDPOSITION( 1, 0, 0 ),
														   NULL, ANGLE_OF_VIEW, SCREEN_DIMENSION, NEAR_DISTANCE, FAR_DISTANCE );

	//------------------------MESHES INITIATION------------------------//
	//TreeIDs = GetRenderer()->Load_Geometry( GET_CONJOINED_PATH( PATH_MODEL, "Christmas Tree.x" ), PATH_TEXTURES, _X, None ); //3
	//BoardID = GetRenderer()->Load_Geometry( GET_CONJOINED_PATH( PATH_MODEL, "Domino Board.X" ), PATH_TEXTURES, _X, None ); //1
	GeomBoneIDs = GetRenderer()->Load_Geometry( GET_CONJOINED_PATH( PATH_MODEL, "Domino Bone.X" ), PATH_TEXTURES, _X, None ); //1
	//GeomBonePlate1 = GetRenderer()->Load_Geometry( GET_CONJOINED_PATH( PATH_MODEL, "Domino Bone Plate 1.X" ), PATH_TEXTURES, _X, None ); //1
	//ActorIDs = GetRenderer()->Load_Geometry( GET_CONJOINED_PATH( PATH_MODEL, "ACTOR 1.X" ), PATH_TEXTURES, _X, None ); //1
	//GeomTestIDs = GetRenderer()->Load_Geometry( GET_CONJOINED_PATH( PATH_MODEL, "Test.X" ), PATH_TEXTURES, _X, None ); //1

	int GeomPlaneID = GetRenderer()->GetGlobal()->CreateGeometry( "Plane", GEOMETRY_TYPES::Plane ); //1
	//------------------------~MESHES INITIATION------------------------//

	#pragma region GRAPHICAL OBJECTS INITIATION
			//------------------------GRAPHICAL OBJECTS INITIATION------------------------//
	int dominoRainID = GetRenderer ()->Initiate_Object ( "Domino Rain" ); //0
	int cubeID = GetRenderer ()->Initiate_Object ( "Cube" ); //0
	int planesID = GetRenderer ()->Initiate_Object ( "Planes" ); //1
	int actorID = GetRenderer ()->Initiate_Object ( "Actor" ); //1
	int dominoBoneID = GetRenderer ()->Initiate_Object ( "Domino Bone" ); //1
	int dominoBonePlate1ID = GetRenderer ()->Initiate_Object ( "Domino Bone Plate 1" ); //1
	int treeID = GetRenderer ()->Initiate_Object ( "Christmas Tree Instance" ); //2
	int dominoBoardID = GetRenderer ()->Initiate_Object ( "Domino Board" ); //3
	int testID = GetRenderer ()->Initiate_Object ( "Test" ); //3

	GetRenderer ()->Add_Geometry_To_Object ( cubeID, NULL, "Cube Shell" );

	GETOBJECT ( cubeID )->GetMeshTree ()->SetXtBinded ( GETCAMERA ( 0 )->GetStaticPosition ().GetXBinded () );
	GETOBJECT ( cubeID )->GetMeshTree ()->SetYtBinded ( GETCAMERA ( 0 )->GetStaticPosition ().GetYBinded () );
	GETOBJECT ( cubeID )->GetMeshTree ()->SetZtBinded ( GETCAMERA ( 0 )->GetStaticPosition ().GetZBinded () );

	//for ( size_t i = 0; i < YolochkaZ; i++ )
	//	{
	//	translation.SetXDefault( rand() % ( YolochkaZ * YolochkaZSpread + 1 ) - ( YolochkaZ * YolochkaZSpread/2 ) );
	//	translation.SetYDefault( 1.0f );
	//	translation.SetZDefault( rand() % ( YolochkaZ * YolochkaZSpread + 1 ) - ( YolochkaZ * YolochkaZSpread/2 ) );
	//	GETOBJECT( treeID )->AddMesh( NULL, "Christmas Tree Trunk", TreeIDs[ 0 ], 0, 3, 0, translation, WORLDPOSITION(), WORLDPOSITION(5.0f,5.0f,5.0f) );
	//	GETOBJECT( treeID )->AddMesh( NULL, "Christmas Tree Leaves", TreeIDs[ 1 ], 0, 4, 0, translation, WORLDPOSITION(), WORLDPOSITION(5.0f,5.0f,5.0f) );
	//	GETOBJECT( treeID )->AddMesh( NULL, "Christmas Tree Branches", TreeIDs[ 2 ], 0, 3, 0, translation, WORLDPOSITION(), WORLDPOSITION(5.0f,5.0f,5.0f) );
	//	}

	//GETOBJECT( planesID )->AddMesh( NULL, "Planes_Near", geometryPlaneID );

	//GETOBJECT( actorID )->AddMesh( NULL, "Actor", ActorIDs[0], -1, 5 );

	//GETOBJECT( dominoBoardID )->AddMesh( NULL, "Domino Board", BoardID[0], -1, 5 );

	//GETOBJECT( testID )->AddMesh( NULL, "Test 1", TestIDs[0] );
	//GETOBJECT( testID )->AddMesh( NULL, "Test 2", TestIDs[1] );

	//GETOBJECT( dominoBoneID )->AddMesh( NULL, "dominoBoneID", BoneIDs[0], -1, 6 );
	//GETOBJECT( dominoBonePlate1ID )->AddMesh( NULL, "dominoBonePlate1ID", BonePlate1[0], -1, 7 );

	/*GETOBJECT( planesID )->AddMesh( NULL, "Planes_Far", geometryPlaneID, -1, -1, false,
																 WORLDPOSITION(), WORLDPOSITION(), WORLDPOSITION( 8.0f, 8.0f, 8.0f) );*/
	//GETOBJECT( planesID )->AddMesh( NULL, "Planes_Left", geometryPlaneID );
	//GETOBJECT( planesID )->AddMesh( NULL, "Planes_Right", geometryPlaneID );

	//GETOBJECT( planesID )->GetMesh( "Planes_Near" )->SetXtBinded( GetRenderer()->GetFrustum()->GetXna() );
	//GETOBJECT( planesID )->GetMesh( "Planes_Near" )->SetYtBinded( GetRenderer()->GetFrustum()->GetYna() );
	//GETOBJECT( planesID )->GetMesh( "Planes_Near" )->SetZtBinded( GetRenderer()->GetFrustum()->GetZna() );
	//GETOBJECT( planesID )->GetMesh( "Planes_Near" )->SetXaBinded( GetRenderer()->GetFrustum()->GetXn() );
	//GETOBJECT( planesID )->GetMesh( "Planes_Near" )->SetYaBinded( GetRenderer()->GetFrustum()->GetYn() );
	//GETOBJECT( planesID )->GetMesh( "Planes_Near" )->SetZaBinded( GetRenderer()->GetFrustum()->GetZn() );

	/*GETOBJECT( planesID )->GetMesh( "Planes_Far" )->SetXtBinded( GetRenderer()->GetFrustum()->GetXnb() );
	GETOBJECT( planesID )->GetMesh( "Planes_Far" )->SetYtBinded( GetRenderer()->GetFrustum()->GetYnb() );
	GETOBJECT( planesID )->GetMesh( "Planes_Far" )->SetZtBinded( GetRenderer()->GetFrustum()->GetZnb() );
	GETOBJECT( planesID )->GetMesh( "Planes_Far" )->SetXaBinded( GetRenderer()->GetFrustum()->GetXf() );
	GETOBJECT( planesID )->GetMesh( "Planes_Far" )->SetYaBinded( GetRenderer()->GetFrustum()->GetYf() );
	GETOBJECT( planesID )->GetMesh( "Planes_Far" )->SetZaBinded( GetRenderer()->GetFrustum()->GetZf() );*/
	//------------------------~GRAPHICAL OBJECTS INITIATION------------------------//  
	#pragma endregion
	
	//-----------------------------------------------~LOAD TEMPLATES------------------------------------------------//

	//-------------------------------------------PREPATE LIST OF DRAWABLES------------------------------------------//

	SceneController.SetCamera( 1 );
	SceneController.ShowGrid( true );

	SceneController.AddObject( cubeID );
	//SceneController.AddObject( planesID );
	//SceneController.AddObject( treeID );
	//SceneController.AddObject( actorID );
	//SceneController.AddObject( dominoBoardID );
	//SceneController.AddObject( dominoBoneID );
	//SceneController.AddObject( dominoBonePlate1ID );
	//SceneController.AddObject( testID );
	GetRenderer()->UpdateSceneController( SceneController );

	//-------------------PREPATE LIST OF DRAWABLES------------------//

	LeaveCriticalSection( &GraphicsCoreCriticalSection );
	return S_OK;
	};
HRESULT APPLICATION::Shutdown()
	{
	// Закрываем соединение с сервером базы данных
	mysql_close( ObjectsDataBase );
	LOG_STOP();
	return S_OK;
	};
HRESULT APPLICATION::Frame()
	{
	//State switcher
	STATEMANAGER::Update();
	return S_OK;
	};

HRESULT	APPLICATION::SendInputData()
	{
	if ( !GetRenderer() ) return E_FAIL;

	( ISKEY( DIK_E ) )?
		IsLocked = false:
		IsLocked = true;

	if ( IsLocked ) return E_FAIL;

#pragma region CAMERA_MOVEMENT_SPECIAL
	static double	speedBoostForward = 0.0f, speedBoostSide = 0.0f,
		currentSpeedForward = 0.0f, currentSpeedSide = 0.0f,
		deltaSpeedBoostForwardPrev = 0.0f, deltaSpeedBoostSidePrev = 0.0f;

	deltaSpeedBoostForwardPrev = sin( TORADIANSFROMANGLE( speedBoostForward ) );
	deltaSpeedBoostSidePrev = sin( TORADIANSFROMANGLE( speedBoostSide ) );

	Zr = currentSpeedForward * 5;

	( ISKEY( DIK_W ) == ISKEY( DIK_S ) && speedBoostForward )?
		( abs( speedBoostForward ) >= BRAKE_SPEED )?
		( speedBoostForward -= ( speedBoostForward / abs( speedBoostForward ) ) * BRAKE_SPEED ):
		speedBoostForward = 0:
		speedBoostForward += ( ISKEY( DIK_W ) - ISKEY( DIK_S ) );

	( ISKEY( DIK_A ) == ISKEY( DIK_D ) && speedBoostSide )?
		( abs( speedBoostSide ) >= BRAKE_SPEED )?
		( speedBoostSide -= ( speedBoostSide / abs( speedBoostSide ) ) * BRAKE_SPEED ):
		speedBoostSide = 0:
		speedBoostSide += ( ISKEY( DIK_A ) - ISKEY( DIK_D ) );

	( ISKEY( DIK_G ) )?
		SceneController.ShowGrid( false ):
		SceneController.ShowGrid( true );

	( !ISKEY( DIK_M ) )?
		SceneController.ShowUpScreen( false ):
		SceneController.ShowUpScreen( true );

	( ISKEY( DIK_N ) )?
		GetRenderer()->Set_RenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME ):
		GetRenderer()->Set_RenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

	SPEEDBOOSTLIMIT( speedBoostForward ); //make sure 0 < speedBoostForward < 90
	SPEEDBOOSTLIMIT( speedBoostSide );

	currentSpeedForward += ( sin( TORADIANSFROMANGLE( speedBoostForward ) ) - deltaSpeedBoostForwardPrev );
	currentSpeedSide += ( sin( TORADIANSFROMANGLE( speedBoostSide ) ) - deltaSpeedBoostSidePrev );

	GetRenderer()->UpdateSceneController( SceneController );

	GetRenderer()->Change_CameraPosition(
		currentCameraID,
		currentSpeedForward * ( ISKEY( DIK_LSHIFT ) * 5.0f + 1 ) * 2.5f,
		currentSpeedSide * ( ISKEY( DIK_LSHIFT ) * 5.0f + 1 ) * 2.5f,
		-ISMOUSE( GetRelativeX() ), ISMOUSE( GetRelativeY() ) );
#pragma endregion

	return S_OK;
	};