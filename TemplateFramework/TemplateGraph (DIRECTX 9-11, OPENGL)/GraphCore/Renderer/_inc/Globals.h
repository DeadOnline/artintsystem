#pragma once
#ifndef GlobalsHeader
#define GlobalsHeader

#include "Singletons.h"

#include "Cameras.h"
#include "Cursor.h"
#include "Effects.h"
#include "Geometry.h"
#include "Grid.h"
#include "Lights.h"
#include "Materials.h"
#include "Objects.h"
#include "Textstrings.h"
#include "Textures.h"
#include "UpScreen.h"
#include "Animations.h"

#include <map>
#include <vector>
#include <mutex>

#define MAPDELETE(map, iter) for ( ; iter != map.end(); ++iter ) { OBJDELETE( iter->second ); }
#define MAPSINGLETONDELETE(map, iter) for ( ; iter != map.end(); ++iter ) { iter->second->deleteInstance(); }

using namespace std;

namespace GRAPHCORE
	{
	#define ID_CURSOR	0
	#define ID_GRID		1
	#define ID_UPSCREEN 2
	#define ID_SKYBOX	3

	class GLOBALS
		{
	public:

		GLOBALS();
		virtual ~GLOBALS();

	protected:

		////////////////////1 CONTAINERS/////////////////

		/* Singletons contain objects in the next order:
		 * 0 - Cursor
		 * 1 - Grid
		 * 2 - UpScreen
		 * 3 - Skymap
		 */
		map<int, SINGLETONS *>			MAP_SINGLETONS;	

		////////////////////1+ CONTAINERS/////////////////

		map<int, GEOMETRY *>			MAP_GEOMETRY;
		map<int, MATERIALS *>			MAP_MATERIALS;
		map<int, TEXTSTRINGS *>			MAP_TEXTSTRINGS;
		map<int, TEXTURES *>			MAP_TEXTURES;
		map<int, LIGHTS *>				MAP_LIGHTS;
		map<int, ANIMATIONS *>			MAP_ANIMATIONS;
		map<int, CAMERAS *>				MAP_CAMERAS;

		////////////////////0+ CONTAINERS/////////////////

		map<int, OBJECTS *>				MAP_OBJECTS;
		map<int, EFFECTS *>				MAP_EFFECTS;

		////////////////////////////////////////////////////////

		static int						singletonsQuantity;
		static int						effectsQuantity;
		static int						geometryQuantity;
		static int						materialsQuantity;
		static int						textstringsQuantity;
		static int						texturesQuantity;
		static int						camerasQuantity;
		static int						objectsQuantity;
		static int						animationsQuantity;
		static int						lightsQuantity;

	public:

		TEXTSTRINGS * const				GetTextString( const int _ID ) const;
		TEXTURES * const				GetTexture( const int _ID ) const;
		GEOMETRY * const				GetGeometry( const int _ID ) const;
		CAMERAS * const					GetCamera( const int _ID ) const;
		MATERIALS * const				GetMaterial( const int _ID ) const;
		OBJECTS * const					GetObjectI( const int _ID ) const;
		LIGHTS * const					GetLight( const int _ID ) const;
		ANIMATIONS * const				GetAnimation( const int _ID ) const;
		SINGLETONS * const				GetSingleton( const int _ID );

		virtual int					CreateGeometry(_charP _name, GEOMETRY_TYPES _geometryType) = 0;		//Create vertex array (arrays)
		virtual int					CreateTextString( const _charP _string, const _charP _appliedFont = 0, const _charP _appliedColor = 0, const RECT _position = RECT() ) = 0;
		virtual int					CreateTexture( const TEXTURE_TYPES _texture_type = Chess, const DEFAULT_COLORS _color = Black, const RECT _area = RECT() ) = 0;	
		virtual int					CreateMaterial( const MATERIAL_TYPES _materialType = Ambient, const DEFAULT_COLORS _color = Black ) = 0;
		virtual int					CreateCameraFree(WORLDPOSITION& _position, WORLDPOSITION& _look, WORLDPOSITION& _up, WORLDPOSITION * _positionBinded,
														float _angle_Of_View, float _resolution_Of_Screen, float _starting_Point, float _ending_Point) = 0;
		virtual int					CreateCameraTarget(WORLDPOSITION& _position, WORLDPOSITION& _target, WORLDPOSITION& _up,
														WORLDPOSITION * _positionBinded, WORLDPOSITION * _targetBinded, WORLDPOSITION * _upBinded,
														float _angle_Of_View, float _resolution_Of_Screen, float _starting_Point, float _ending_Point) = 0;
		virtual int					CreateObject(_charP _name) = 0;
		virtual int					CreateLight(_charP _name) = 0;
		virtual int					CreateGrid() = 0;
		virtual int					CreateUpScreen(const int _clientWidth, const int _clientHeight) = 0;
		virtual int					CreateAnimation( const _charP _name, const void * _animationSequence ) = 0;

		void							DestroyAnimation( const int _ID );
		void							DestroyCamera( const int _ID );
		void							DestroyGeometry( const int _ID );
		void							DestroyLight( const int _ID );
		void							DestroyMaterial( const int _ID );
		void							DestroyObjectI( const int _ID );
		void							DestroySingleton( const int _ID );
		void							DestroyTextString( const int _ID );
		void							DestroyTexture( const int _ID );

		virtual int					LoadTexture( const _charP& _path, const RECT& _area = RECT() ) = 0;
		virtual vector<int>			LoadGeometry( const _charP& _relativeMeshPath, const _charP& _relativeResFolder, SUPPORTED_FILE_FORMATS _format ) = 0;

		virtual int					CopyMaterial( const void * _material ) = 0;
		};
	};

#endif