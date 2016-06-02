#pragma once
#ifndef RendererHeader
#define RendererHeader

#include "Globals.h"
#include "SceneController.h"
#include "Frustum.h"

#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <mutex>

namespace GRAPHCORE
	{
	class RENDERER
		{
		private:

			struct FPS
				{
				__int64 Time_Start, Time_End;
				int FrameCnt;
				float TimeElapsed;
				FPS ();
				} TimeDelta;

		protected:

			FRUSTUM			* Frustum;

			GLOBALS			* Global;

			SCENECONTROLLER * SceneController;

			mutex			RendererMutex;

		public:

			RENDERER();
			virtual ~RENDERER();

		public:

			////--------------INITIATION-------------//

			/*Temporary, delete*/
			FRUSTUM * GetFrustum();

			virtual HRESULT Initiate( HWND hWnd, int sizeX, int sizeY ) = 0;
			HRESULT Render();
			virtual HRESULT Destroy() = 0;

			virtual int		Initiate_Camera_Free( WORLDPOSITION& _position, WORLDPOSITION& _look, WORLDPOSITION& _up, WORLDPOSITION * _positionBinded = NULL,
											   float _angle_Of_View = 75.0f, float _resolution_Of_Screen = 4.0f / 3.0f, float _starting_Point = 0.1f, float _ending_Point = 1000.0f ) = 0;
			virtual int		Initiate_Camera_Target( WORLDPOSITION& _position, WORLDPOSITION& _target, WORLDPOSITION& _up,
												 WORLDPOSITION * _positionBinded = NULL, WORLDPOSITION * _targetBinded = NULL, WORLDPOSITION * _upBinded = NULL,
												 float _angle_Of_View = 75.0f, float _resolution_Of_Screen = 4.0f / 3.0f, float _starting_Point = 0.1f, float _ending_Point = 1000.0f ) = 0;

			virtual int		Initiate_Geometry( _charP _name, VERTEX_TYPES _formatType, GEOMETRY_TYPES _geometryType ) = 0;
			virtual HRESULT			Initiate_Light( _charP _name, LIGHT_TYPES _type ) = 0;
			virtual vector<int>		Load_Geometry( const _charP& _relativeMeshPath, const _charP& _relativeResFolder, const SUPPORTED_FILE_FORMATS _format, const COLLISION_TYPES _collisionType ) = 0;
			virtual HRESULT			Initiate_MeshAnimation( _charP name, COLLISION_TYPES _collisionType ) = 0;
			virtual int		Initiate_Object( _charP _name ) = 0;
			virtual HRESULT Initiate_Surface( int height, int width, _charP name ) = 0;
			virtual HRESULT Initiate_Terrain( string _fileName ) = 0;
			virtual HRESULT Initiate_Text( _charP _name, _charP _string, _charP _font, _charP _color, RECT _position = RECT() ) = 0;
			virtual HRESULT Initiate_Text_Font( _charP _faceName, int _Height = 10, int _Weight = 400, bool _IsItalic = false ) = 0;
			virtual HRESULT Initiate_Text_Color( _charP _colorName, DWORD _color ) = 0;
			virtual int		Initiate_Texture( const _charP _name ) = 0;
			virtual HRESULT Initiate_SpecialEffect( _charP _name ) = 0;
			////---------------~INITIATION--------------//



			////----------------RENDERING---------------//
			//------------------SINGLETONS--------------//
			virtual HRESULT Render_Singletons( vector<int> _IDs ) const = 0;
			virtual HRESULT Render_Cursor() const = 0;
			virtual HRESULT Render_SkyBox() const = 0;
			virtual HRESULT Render_UpScreen() const = 0;
			virtual HRESULT Render_Grid() const = 0;
			//-----------------~SINGLETONS--------------//

			virtual HRESULT Render_Sprite( RECT _src, RECT _dest ) = 0;
			virtual HRESULT Render_Text( int _textKey, RECT _rec ) = 0;
			virtual HRESULT Render_Objects( const vector<OBJECTSREGISTRY>& IDList ) const = 0;
			virtual HRESULT Render_Effect() = 0;
			////----------------~RENDERING--------------//



			//////---------------SETTINGS---------------//
			////-----------------RENDERER---------------//
			virtual HRESULT Set_RenderOptions() = 0;
			virtual HRESULT	Set_RenderState( DWORD _type, DWORD _value ) = 0;
			void			UpdateSceneController( const SCENECONTROLLER& _sceneController );
			////----------------~RENDERER---------------//
			////----------------SINGLETONS--------------//
			//-------------------CURSORS----------------//
			void			Change_Cursor( const int _textureID );
			void			Set_Cursor_Position( int m_fCursorX, int m_fCursorY );
			//------------------~CURSORS----------------//
			//-------------------UPSCREEN---------------//
			void			Set_UpScreen_Alpha( const int _alpha );
			void			Set_UpScreen_Color( const DEFAULT_COLORS _color );
			virtual void	Set_UpScreen ( const int _clientWidth, const int _clientHeight, const int _textureID ) = 0;
			//------------------~UPSCREEN---------------//
			//---------------------GRID-----------------//
			virtual void	Set_Grid( int _width = 16, float _callSize = 10.0f, DWORD _newColor = 0 ) = 0;
			//--------------------~GRID-----------------//
			//--------------------SKYMAP----------------//
			void			Set_SkyMap( /*TODO: FILL IN CORRECT VALUES*/ );
			//-------------------~SKYMAP----------------//

			//--------------------CAMERAS----------------//
			virtual void	Set_CameraPosition( int _ID, float _xPos, float _yPos, float _xAng, float _yAng ) = 0;
			virtual void	Change_CameraPosition( int _ID, float _xPos, float _yPos, float _xAng, float _yAng ) = 0;
			//-------------------~CAMERAS----------------//
			//////--------------~SETTINGS---------------//

			virtual HRESULT	Add_Geometry_To_Object ( const int _objID, OBJECTS::MESHES_TREE * _parent, MESH_ARGUMENTS_DEFAULT ) = 0;

			virtual HRESULT StartScene() = 0;
			virtual HRESULT EndScene() = 0;

			void			CalculateFPS();

			GLOBALS *		GetGlobal();
		};
	};

#endif