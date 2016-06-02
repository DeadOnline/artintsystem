#include "../_inc/Renderer.h"

#pragma region RENDERER
//------------------------------------------------------------------------------RENDERER-------------------------------------------------------------------------------//
using namespace GRAPHCORE;

RENDERER::FPS::FPS() { FrameCnt = TimeElapsed = Time_Start = Time_End = 0; };

RENDERER::RENDERER() : Frustum( NULL ), Global( NULL ), SceneController( NULL ) {}
RENDERER::~RENDERER()
	{
	OBJDELETE( Frustum );
	OBJDELETE( Global );
	OBJDELETE( SceneController );
	}

GLOBALS * RENDERER::GetGlobal()
	{
	return Global;
	}
void RENDERER::CalculateFPS()
	{
	TimeDelta.Time_End = GetTickCount64() - TimeDelta.Time_Start; TimeDelta.Time_Start = GetTickCount64();
	TimeDelta.FrameCnt++; TimeDelta.TimeElapsed += (TimeDelta.Time_End * .001f);
	if(TimeDelta.TimeElapsed >= 1.0f)
		{
		TimeDelta.TimeElapsed = 0.0f;
		TimeDelta.FrameCnt = 0;
		}
	};
FRUSTUM * RENDERER::GetFrustum()
	{
	return Frustum;
	};
void RENDERER::UpdateSceneController( const SCENECONTROLLER& _sceneController )
	{
	SceneController->Update( _sceneController );
	}
void RENDERER::Change_Cursor( const int _textureID )
	{
	( ( CURSOR * ) Global->GetSingleton( ID_GRID ) )->ChangeCursorTexture( _textureID );
	}
void RENDERER::Set_Cursor_Position( int m_fCursorX, int m_fCursorY )
	{
	( ( CURSOR * ) Global->GetSingleton( ID_GRID ) )->ChangeCursorCoords( m_fCursorX, m_fCursorY );
	};
void RENDERER::Set_UpScreen_Alpha( const int _alpha )
	{
	( ( UPSCREEN * ) Global->GetSingleton( ID_UPSCREEN ) )->ChangeUpScreenAlpha( _alpha );
	}
void RENDERER::Set_UpScreen_Color( const DEFAULT_COLORS _color )
	{
	( ( UPSCREEN * ) Global->GetSingleton( ID_UPSCREEN ) )->ChangeUpScreenColor( _color );
	}
void RENDERER::Set_SkyMap() {};

HRESULT RENDERER::Render()
	{
	StartScene();

	//Considering time delta as shift in between animations we may determine current percentage position for current animation

	if ( SceneController->getUpScreen () )
		{
		Set_RenderState (7, FALSE);
		Set_RenderState (27, FALSE);
		( ( UPSCREEN * ) Global->GetSingleton( ID_UPSCREEN ) )->ChangeUpScreenTexture( 2 );
		Render_UpScreen ();
		Set_RenderState (7, TRUE);
		Set_RenderState (27, TRUE);
		}
	if ( SceneController->getCursor() ) Render_Cursor();
	if ( SceneController->getGrid() ) Render_Grid();	
	if ( SceneController->getSkyBox() ) Render_SkyBox();

	/*
	* Read objects from scenecontroller. Objects should be inserted into vector structure.
	*/
	Render_Objects( SceneController->getObjects() );

	if ( SceneController->getUpScreen () )
		{
		( ( UPSCREEN * ) Global->GetSingleton( ID_UPSCREEN ) )->ChangeUpScreenTexture( 1 );
		Render_UpScreen ();
		}

	EndScene();
	return S_OK;
	};
//-----------------------------------------------------------------------------~RENDERER-------------------------------------------------------------------------------//
#pragma endregion