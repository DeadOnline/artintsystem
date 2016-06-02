#pragma once
#ifndef StateManager
#define StateManager



#include <vector>

using namespace std;

namespace APP
	{
	class STATEMANAGER
		{
		public:
			static	bool		Update ();
			virtual void		InnerProcess ();
			virtual void		OuterProcess ();

		protected:

			static vector<int> DataBase; //Should be changed to lightSQL

			//Go go level manager

			STATEMANAGER();
			STATEMANAGER( const STATEMANAGER& root );
			~STATEMANAGER();
			STATEMANAGER& operator=( const STATEMANAGER& );	
		};
	};

#endif