#pragma once
#ifndef SceneControllerHeader
#define SceneControllerHeader

#include "../../_inc/Parameters.h"
//#include "../../../../TemplateCommon/CommonCore/Macroses.h"
#include "../../_inc/Enums.h"

#include <list>

using namespace std;

namespace GRAPHCORE
	{
	class SCENECONTROLLER 
		{
	protected:
		/*
		Draw me:
		1) Singleton with THIS id. Set him THESE parameters.
		2) ObjectS with THESE idS. Cuz each has meshes tree,
		and each mesh has collision, material, texture(S),
		and mb some special effect, provide necessary info
		as well.
		3) Current camera
		Format:
		Send hyerarchy of animations... or specify current mesh hyerarchy animation ID and timespan
		Object ID, World Matrix of the Root,
		Thus, after having thinkin' 'bout that for a while, Object attr tree should be sent for each object in the scene
		
		camID, //CamID
		objID1 - WMP - animIDX1 - treeEntriesY1 
		objID2 - WMP - animIDX2 - treeEntriesY2 
		*/
		
		int		camID;
		bool	cursor;
		bool	grid;
		bool	upScreen;
		bool	skyBox;
		
		vector<OBJECTSREGISTRY> objects;

	public:
		SCENECONTROLLER();
		~SCENECONTROLLER();

		void Update( const SCENECONTROLLER& renderList );

		void SetCamera ( const int _camID );
		void ShowCursor ( const bool _show );
		void ShowGrid ( const bool _show );
		void ShowUpScreen ( const bool _show );
		void ShowSkyBox ( const bool _show );
		void AddObjectMatrix( const int _ID, const TEMPLATEMATRIX& const _matrix ); //MAKE MATRIX CLASS
		void AddObjectAnimationTime ( const int _ID, const int _animationID, const float _time );
		void AddObjectEntry( const int _ID, const TEMPLATEMATRIX& const _matrix, ANIMATIONSET const _animationSet, const ATTRIBUTESMAP _meshEntry );
		void AddObject( const int _ID );

		int	 getCameraID();
		bool getCursor();
		bool getGrid();
		bool getUpScreen();
		bool getSkyBox();

		const vector<OBJECTSREGISTRY>& getObjects() const;
		};
	};

#endif