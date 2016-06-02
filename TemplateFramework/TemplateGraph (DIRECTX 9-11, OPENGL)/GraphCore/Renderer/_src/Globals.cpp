#include "../_inc/Globals.h"

#pragma region GLOBALS
//----------------------------------GLOBALS----------------------------------//
using namespace GRAPHCORE;

#define GETELEMENT(map) (_ID == -1)?(map.find( 0 )->second):( map.size() )?map.find( _ID )->second:NULL

int GLOBALS::singletonsQuantity = 0;
int GLOBALS::effectsQuantity = 0;
int GLOBALS::geometryQuantity = 0;
int GLOBALS::materialsQuantity = 0;
int GLOBALS::textstringsQuantity = 0;
int GLOBALS::texturesQuantity = 0;
int GLOBALS::camerasQuantity = 0;
int GLOBALS::objectsQuantity = 0;
int GLOBALS::animationsQuantity = 0;
int GLOBALS::lightsQuantity = 0;

TEXTSTRINGS * const	GLOBALS::GetTextString( const int _ID ) const
	{
	return GETELEMENT( MAP_TEXTSTRINGS );
	};
TEXTURES * const	GLOBALS::GetTexture( const int _ID ) const
	{
	return GETELEMENT ( MAP_TEXTURES );
	};
GEOMETRY  * const	GLOBALS::GetGeometry( const int _ID ) const
	{
	return GETELEMENT( MAP_GEOMETRY );
	};
CAMERAS * const		GLOBALS::GetCamera( const int _ID ) const
	{
	return GETELEMENT( MAP_CAMERAS );
	}
MATERIALS * const GLOBALS::GetMaterial ( const int _ID ) const
	{
	return GETELEMENT( MAP_MATERIALS );
	};
OBJECTS * 	const GLOBALS::GetObjectI( const int _ID ) const
	{
	return GETELEMENT( MAP_OBJECTS );
	};
LIGHTS * const		GLOBALS::GetLight( const int _ID ) const
	{
	return GETELEMENT( MAP_LIGHTS );
	};
ANIMATIONS * const	GLOBALS::GetAnimation( const int _ID ) const
	{
	return GETELEMENT( MAP_ANIMATIONS );
	};
SINGLETONS * const	GLOBALS::GetSingleton( const int _ID )
	{
	if ( MAP_SINGLETONS.size() )
		{
		map<int, SINGLETONS *>::iterator Temp = MAP_SINGLETONS.find( _ID );
		if (Temp != MAP_SINGLETONS.end())
			return Temp->second;
		};
	return NULL;
	};

void	GLOBALS::DestroyTextString(int _ID)
	{
	OBJDELETE(MAP_TEXTSTRINGS[_ID]);
	};
void	GLOBALS::DestroyTexture(int _ID)
	{
	OBJDELETE(MAP_TEXTURES[_ID]);
	};
void	GLOBALS::DestroySingleton( int _ID )
	{
	if ( !MAP_SINGLETONS.size () ) return;
	MAP_SINGLETONS[ _ID ]->deleteInstance();			
	MAP_SINGLETONS.erase( _ID );
	};
void	GLOBALS::DestroyGeometry(int _ID)
	{
	if (MAP_GEOMETRY.size())
		{
		map<int, GEOMETRY *>::iterator Temp = MAP_GEOMETRY.find(_ID);
		OBJDELETE((*Temp).second);
		};
	};
void	GLOBALS::DestroyCamera(int _ID)
	{
	OBJDELETE(MAP_CAMERAS[_ID]);
	};
void	GLOBALS::DestroyMaterial( int _ID )
	{
	OBJDELETE( MAP_MATERIALS[ _ID ] );
	};
void	GLOBALS::DestroyObjectI(int _ID)
	{
	OBJDELETE(MAP_OBJECTS[_ID]);
	};
void	GLOBALS::DestroyLight(int _ID)
	{
	OBJDELETE(MAP_LIGHTS[_ID]);
	};
void	GLOBALS::DestroyAnimation(int _ID)
	{
	OBJDELETE(MAP_ANIMATIONS[_ID]);
	};

GLOBALS::GLOBALS() { };
GLOBALS::~GLOBALS()
	{
	map<int, TEXTSTRINGS*>::iterator TextIter = MAP_TEXTSTRINGS.begin();
	map<int, TEXTURES*>::iterator TexIter = MAP_TEXTURES.begin();
	map<int, GEOMETRY*>::iterator GeomIter = MAP_GEOMETRY.begin();
	map<int, CAMERAS*>::iterator CamIter = MAP_CAMERAS.begin();
	map<int, OBJECTS*>::iterator ObjIter = MAP_OBJECTS.begin();
	map<int, LIGHTS*>::iterator LightIter = MAP_LIGHTS.begin();
	map<int, ANIMATIONS*>::iterator AnimIter = MAP_ANIMATIONS.begin();
	map<int, SINGLETONS*>::iterator SingleIter = MAP_SINGLETONS.begin();
	map<int, MATERIALS*>::iterator MaterialIter = MAP_MATERIALS.begin();

	MAPDELETE(MAP_TEXTSTRINGS, TextIter);
	MAPDELETE(MAP_TEXTURES, TexIter);
	MAPDELETE(MAP_GEOMETRY, GeomIter);
	MAPDELETE(MAP_CAMERAS, CamIter);
	MAPDELETE(MAP_OBJECTS, ObjIter);
	MAPDELETE(MAP_LIGHTS, LightIter);
	MAPDELETE(MAP_ANIMATIONS, AnimIter);
	MAPDELETE(MAP_MATERIALS, MaterialIter);
	MAPSINGLETONDELETE(MAP_SINGLETONS, SingleIter);
	};
//---------------------------------~GLOBALS----------------------------------//  
#pragma endregion