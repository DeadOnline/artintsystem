#pragma once
#ifndef LevelManager
#define LevelManager

#include <vector>

using namespace std;

namespace APP
	{
	class LEVELMANAGER	//Class - controller of Statemanager. It can make Statemanager destroy everythin' on screen and load next bunch of objects to work with
		{				//As well as to create additional HUDS
		public:
			static bool		LoadLevel (); //Follows script and loads game objects into game, while doin' this renderer shows progressbar

			static bool		FreezeLevel ();
			static bool		ShowMenuOnTop ();

			static bool		KeysProcessing ();
			
		protected:

			class LEVELS
				{
				virtual void ProcessKeys () = 0;
				virtual void ProcessMouse () = 0;
				};

			class MENU : public LEVELS //class menu has HUD with controls binded to specific functions
				{};
						
			LEVELMANAGER();
			LEVELMANAGER( const LEVELMANAGER& root );
			~LEVELMANAGER();
			LEVELMANAGER& operator=( const LEVELMANAGER& );	
		};
	};

#endif
