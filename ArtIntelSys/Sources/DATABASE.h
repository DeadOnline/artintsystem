#pragma once

#include "ALL.h"

namespace WORLD
	{
	enum	SENSOR_METHODS	{ COLOR, SHAPE, PAIN, VITALITY, FATIGUE, COORDINATES };				//Sensors
	enum	MATERIAL_TYPES	{ WATER, TIMBER, SOIL, ORGANICS, FLESH };							//World materials
	enum	OBJECT_TYPES	{ SEA, LAND, FOOD, ROPE, WOOD, HUMAN, HUMAN_EYE, HUMAN_BODY };		//World objects

	typedef std::vector<double>						type_scan_single;
	typedef std::map<LPCSTR, std::vector<double>>		type_scan_all;
	static mutex mtx, mtx1;           // mutex for critical section
	
	namespace DIMENSIONS
		{
		struct Vector1D
			{
			float x;
			Vector1D(float _x = 0): x(_x) {};
			};
		struct Vector2D: public Vector1D
			{
			float y;
			Vector2D(float _x = 0, float _y = 0): Vector1D(_x), y(_y) {};
			};
		struct Vector3D: public Vector2D
			{
			float z;
			Vector3D(float _x = 0, float _y = 0, float _z = 0): Vector2D(_x, _y), z(_z) {};
			};
		};
	namespace MATERIALS
		{
		//Here is a shedule of chemical/physical/natural material intersections. All output data is pre-determined: methods and static essenses.
		class TRANSFORMATION
			{
		public:

			struct ACTION
				{
				SENSOR_METHODS Method;
				double power;
				ACTION(SENSOR_METHODS _method, int _power): Method(_method), power(_power) {};
				ACTION(): Method(SENSOR_METHODS()), power(0) {};
				};

			std::map<OBJECT_TYPES, std::map<OBJECT_TYPES, std::vector<ACTION>>> Shedule;

		TRANSFORMATION() 
			{
			const char * DataBaseName = GET_PATH_DATABASE(_DATA);
			sqlite3 * DataBase;
			char * errorMessage = 0;
			int errorCode;

			errorCode = sqlite3_open(DataBaseName, &DataBase);

			if ( errorCode )
				{
				const char* _res1 = sqlite3_errmsg(DataBase);
				sqlite3_close(DataBase);
				}

			sqlite3_stmt    * res;
			const char      * tail;

			errorCode = sqlite3_prepare_v2(DataBase,"SELECT [ESSENSE A], [ESSENSE B], [SENSOR: EYE: COLOR], [SENSOR: EYE: SHAPE], [SENSOR: BODY: FATIQUE], [SENSOR: BODY: PAIN], [SENSOR: BODY: VITALITY] from [OBJECT LINKAGES]", 10000, &res, &tail);

			if ( errorCode )
				{
				const char* _res1 = sqlite3_errmsg(DataBase);
				sqlite3_close(DataBase);
				}
			
			OBJECT_TYPES essenseAType, essenseBType;
			string essenseA, essenseB, sensorEyeColor, sensorEyeShape, sensorBodyFatique, sensorBodyPain, sensorBodyVitality;

			while (sqlite3_step(res) == SQLITE_ROW)
				{
				const unsigned char * _res1 = sqlite3_column_text(res, 0);
				const unsigned char * _res2 = sqlite3_column_text(res, 1);
				const unsigned char * _res3 = sqlite3_column_text(res, 2);
				const unsigned char * _res4 = sqlite3_column_text(res, 3);
				const unsigned char * _res5 = sqlite3_column_text(res, 4);
				const unsigned char * _res6 = sqlite3_column_text(res, 5);
				const unsigned char * _res7 = sqlite3_column_text(res, 6);

				essenseA = (LPCSTR) _res1;
				essenseB = (LPCSTR) _res2;
				sensorEyeColor = (LPCSTR) _res3;
				sensorEyeShape = (LPCSTR) _res4;
				sensorBodyFatique = (LPCSTR) _res5;
				sensorBodyPain = (LPCSTR) _res6;
				sensorBodyVitality = (LPCSTR) _res7;
				GET_OBJECT_TYPE(essenseA,essenseAType);
				GET_OBJECT_TYPE(essenseB,essenseBType);
				Shedule[essenseAType][essenseBType].push_back(ACTION(COLOR, stoi(sensorEyeColor)));
				Shedule[essenseAType][essenseBType].push_back(ACTION(SHAPE, stoi(sensorEyeShape)));
				Shedule[essenseAType][essenseBType].push_back(ACTION(FATIGUE, stoi(sensorBodyFatique)));
				Shedule[essenseAType][essenseBType].push_back(ACTION(PAIN, stoi(sensorBodyPain)));
				Shedule[essenseAType][essenseBType].push_back(ACTION(VITALITY, stoi(sensorBodyVitality)));
				}
			};
		~TRANSFORMATION() {};

		ACTION * GetCombinationInfo(SENSOR_METHODS _type, OBJECT_TYPES, OBJECT_TYPES);
			};
		static TRANSFORMATION Transformation;
		};
	namespace PHYSICS
		{
		/*
		Methods of filling database
		What is... <> - Essense
		Where is... <> - Global positioning
		Why is... <> - The cause-effect relationship
		Actions
		I need... <> - Goal
		<Optionally> Why do I need... <>? - This will set a rating for current action
		This can be taken from... <list of actions>
			Can I get it?
			Search for ways to reach it
			If no method is found, seek deeper or cancel trying, depending on personal traits of character, and continue to the next task
		Do... <list of actions>
		Outer stimulus
		Every object has it's own outgoing signals (messages)
		It sends messages to outer world about itself
		Every other object will get this message in some area or in other ways
		Filling it's database
		There are two different kinds of messages: permanent and managed
		Permanent are sent every tick
		Managed are under control of "Actions" Tab
		So, let's start our little emulation!
		*/
		using namespace DIMENSIONS;

		class DATABASE: public MODULE_BASE
			{
		public:

			virtual void Module_Init() {};
			virtual void Module_Run() {};
			virtual void Module_Destroy() {};

		DATABASE(LPCSTR _name): MODULE_BASE(NULL) 
			{
			}
		~DATABASE() { }

			void Get_Database_Info()
				{
				//const char * DataBaseName = GET_PATH_DATABASE(_DATA);
				//sqlite3 * DataBase = NULL;
				//char * errorMessage = 0;
				//int errorCode = 0;

				//errorCode = sqlite3_open(DataBaseName, &DataBase);

				//if ( errorCode )
				//	{
				//	const char* _res1 = sqlite3_errmsg(DataBase);
				//	sqlite3_close(DataBase);
				//	}

				//sqlite3_stmt    * res = NULL;
				//const char     * tail = NULL;

				//errorCode = sqlite3_prepare_v2(DataBase,SQLITE_GET_MATERIALS_INFO, 10000, &res, &tail);

				//if ( errorCode )
				//	{
				//	AfxMessageBox(sqlite3_errmsg(DataBase));
				//	sqlite3_close(DataBase);
				//	}
			
				//OBJECT_TYPES essenseAType, essenseBType;
				//string essenseA, essenseB, sensorEyeColor, sensorEyeShape, sensorBodyFatique, sensorBodyPain, sensorBodyVitality;

				//while (sqlite3_step(res) == SQLITE_ROW)
				//	{
				//	LPCSTR _res1 = (LPCSTR) sqlite3_column_text(res, 0);
				//	const unsigned char * _res2 = sqlite3_column_text(res, 1);
				//	const unsigned char * _res3 = sqlite3_column_text(res, 2);
				//	const unsigned char * _res4 = sqlite3_column_text(res, 3);
				//	const unsigned char * _res5 = sqlite3_column_text(res, 4);
				//	const unsigned char * _res6 = sqlite3_column_text(res, 5);
				//	const unsigned char * _res7 = sqlite3_column_text(res, 6);

				//	essenseA = (LPCSTR) _res1;
				//	essenseB = (LPCSTR) _res2;
				//	sensorEyeColor = (LPCSTR) _res3;
				//	sensorEyeShape = (LPCSTR) _res4;
				//	sensorBodyFatique = (LPCSTR) _res5;
				//	sensorBodyPain = (LPCSTR) _res6;
				//	sensorBodyVitality = (LPCSTR) _res7;
				//	GET_OBJECT_TYPE(essenseA,essenseAType);
				//	GET_OBJECT_TYPE(essenseB,essenseBType);
				//	Shedule[essenseAType][essenseBType].push_back(ACTION(COLOR, stoi(sensorEyeColor)));
				//	Shedule[essenseAType][essenseBType].push_back(ACTION(SHAPE, stoi(sensorEyeShape)));
				//	Shedule[essenseAType][essenseBType].push_back(ACTION(FATIGUE, stoi(sensorBodyFatique)));
				//	Shedule[essenseAType][essenseBType].push_back(ACTION(PAIN, stoi(sensorBodyPain)));
				//	Shedule[essenseAType][essenseBType].push_back(ACTION(VITALITY, stoi(sensorBodyVitality)));
				//	}
				}

			//Vector2D WhereIs(OBJECT_ESSENSE * _object)
			//	{
			//	};
			//OBJECT_ESSENSE WhatIs(OBJECT_ESSENSE * _object)
			//	{
			//	};
			//OBJECT_ESSENSE WhyIs(OBJECT_ESSENSE * _object)
			//	{
			//	};
			};
		};
	namespace OBJECTS
		{
		using namespace DIMENSIONS;

		class OBJECTS_BUFFER
			{
			public:
			static map<const int, pair<void *, int>> Buffer;

			OBJECTS_BUFFER() {};
			~OBJECTS_BUFFER() {};

			static void * Get_By_ID(const int _ID);
			static void Set_Value_by_ID(const int _ID, void * _data);
			};
		class OBJECTS_REGISTRY: public MODULE_BASE
			{
		public:

			static const OBJECTS_REGISTRY& Instance()
				{
				static OBJECTS_REGISTRY theSingleInstance;
				ObjectRegistry = &theSingleInstance;
				return theSingleInstance;
				}
			static const OBJECTS_REGISTRY& Instance(ARTINTSYSTEMAPPLICATION * _parentClass)
				{
				static OBJECTS_REGISTRY theSingleInstance(_parentClass);
				ObjectRegistry = &theSingleInstance;
				return theSingleInstance;
				}

		private:

			OBJECTS_REGISTRY(){};
			OBJECTS_REGISTRY(const OBJECTS_REGISTRY& root);
			OBJECTS_REGISTRY& operator=(const OBJECTS_REGISTRY&);
			OBJECTS_REGISTRY(ARTINTSYSTEMAPPLICATION * _parentClass);
			~OBJECTS_REGISTRY();

			static OBJECTS_REGISTRY * ObjectRegistry;
			static int ThreadQuantity;
			static UINT Object_Thread(LPVOID pParam);

		public:

			class OBJECT_BASE
				{
			public:

				LPCSTR					name;
				OBJECT_TYPES			type;
				
				Vector3D				location;
				Vector1D				size;

				static int				quantity;

				const int				ID;
				pair<void *, int> *		BufferCell;
				vector<int>				IDPorts;

			OBJECT_BASE(LPCSTR _name, OBJECT_TYPES _type, Vector3D _coordinates, Vector3D _size);
			~OBJECT_BASE();
				virtual void			TearConnections();
				virtual void			Work() = 0;
				virtual void			Say_Message(int _ID) = 0;
				virtual void			DataAccept(void * _data) = 0;
				virtual LPCSTR			GetAssossiation() = 0;
				virtual LPCSTR			GetName() = 0;
				OBJECT_TYPES			GetType();
				const	int&			GetID();
				static	int				IncreaseQuantity();
				static void			Start();
				void					ConnectTo(const int _IDPort);

				Vector3D&				GetLocation();
				void					SetLocation(Vector3D& _location);

				OBJECTS_REGISTRY *		GetObjectRegistry();
				};
			class OBJECT_SENSOR
				{
			public:

				OBJECT_SENSOR() {};
				~OBJECT_SENSOR() {};

				virtual	 type_scan_all *	Scan() = 0;
				};
			class OBJECT_EYE: public OBJECT_BASE, public OBJECT_SENSOR
				{
			public:

				type_scan_single	FrameColor;
				type_scan_single	FrameShape;

				float				vitality;
				struct FOCUS
					{
					float			focusX;
					float			focusY;
					float			focusZ;
					FOCUS() : focusX(0), focusY(0), focusZ(0) { };
					FOCUS& operator=( FOCUS _focus )
						{ 
						FOCUS Temp;
						Temp.focusX = _focus.focusX;
						Temp.focusX = _focus.focusY;
						Temp.focusX = _focus.focusZ;
						return Temp;
						}
					} Focus;

				OBJECT_EYE(OBJECT_BASE * _source, Vector3D _coordinates);
				~OBJECT_EYE() {};

				LPCSTR					GetName();
				LPCSTR					GetAssossiation();
				void					Say_Message(int _ID);
				void					DataAccept(void *);
				void					SetFocus(FOCUS);
				type_scan_single		Scan_Color();
				type_scan_single		Scan_Shape();

				type_scan_all *			Scan();
				void					Work();
				static OBJECT_BASE *	Start(OBJECT_BASE * _source, Vector3D _coordinates);


				};
			class OBJECT_BODY: public OBJECT_BASE, public OBJECT_SENSOR
				{
			public:

				float	vitality;

			OBJECT_BODY(OBJECT_BASE * _source, Vector3D _coordinates);
			~OBJECT_BODY() {};

				LPCSTR					GetName();
				LPCSTR					GetAssossiation();
				void					Say_Message(int _ID);
				void					DataAccept(void *);

				type_scan_single		Scan_Touch();
				type_scan_single		Scan_Temperature();
				type_scan_single		Scan_Vitality();
				type_scan_single		Scan_Fatigue();

				type_scan_all *			Scan();
				void					Work();

				void					MoveUp();												//Rating 1
				void					MoveDown();												//Rating 2
				void					MoveLeft();												//Rating 3
				void					MoveRight();											//Rating 4
				void					PickItem(OBJECT_BASE* _obj1);							//Rating 5
				void					ThrowItem(OBJECT_BASE* _obj1);							//Rating 6
				void					CombineItems(OBJECT_BASE* _obj1, OBJECT_BASE * _obj2);	//Rating 7
				void					SplitItem(OBJECT_BASE* _obj1);							//Rating 8
					
				virtual void			Feed(OBJECT_BASE *);
				static OBJECT_BASE *	Start(OBJECT_BASE * _source, Vector3D _coordinates);
				};
			class OBJECT_GEOLOCATOR: public OBJECT_SENSOR
				{
			public:
				OBJECT_GEOLOCATOR();
				~OBJECT_GEOLOCATOR();

				type_scan_single	GetDistance() {};
				type_scan_all *		Scan() { };

			private:
				};

			class OBJECT_UNIT: public OBJECT_BASE//, public OBJECT_GEOLOCATOR
				{
				public:

				struct ESSENSE
					{
					static const ESSENSE * Self;
					LPCSTR name;
					
					struct ESSENSE_LINKAGE
						{
						public:

						struct MEMORYCELL
							{
							std::vector<long>		CellNumber;
							
							MEMORYCELL(long _cellNumber, float _priority, float _power) {}

							void AddHistoryCell(int _number) { CellNumber.push_back(_number); };
							};
						//<OBJECT_ESSENCE>=|<OBJECT_ESSENCE>|
						//If something looks similar to whatever exists in database, you can not only make a link between 'em, but create special scene linkage
						//of synonyms (which can be either one-one linkage or multiple-multiple)
						//Thus you gain a control upon "assossiation" branch
						//The synonyms are created if results of actions they do are 
						ESSENSE_LINKAGE(ESSENSE * _obj1) 
							{

							};
						~ESSENSE_LINKAGE() {};

						//The Linkages are connections to all moments in unit's history
						std::map<LPCSTR, MEMORYCELL> SensorsMemory;

						void AddLinkage(MEMORYCELL _essense)
							{
							//Adding new story moment into linkages stack
							//Linkages.push_back(_essense);
							//	//In case of absense of other historical, set priority level to 100
							//	if (Linkages.size() == 1)
							//		{
							//		Linkages[0].Priority = 100;
							//		return;
							//		} else {
							//	//But if more than 1 essense is present, add it into essenses stack and acquire percentages to right levels
							//		double PriorityLevel = 0, PriorityPercent = 0;
							//		for (int i = 0; i < Linkages.size(); i++)
							//			PriorityLevel+=Linkages[i].Priority;
							//		PriorityPercent = (PriorityLevel - 100)/Linkages.size();
							//		for (int i = 0; i < Linkages.size(); i++)
							//			Linkages[i].Priority-=PriorityPercent;
							//		};
							};

						};
					struct ESSENSE_IMAGE
						{
						struct BASE_PROPERTY {};

						struct SHAPES: public BASE_PROPERTY
							{
							enum SHAPETYPE { Circle, Square } ShapeType;
							SHAPES(SHAPETYPE _shape): ShapeType(_shape) {};
							} * Shape;
						struct COLORS: public BASE_PROPERTY
							{
							enum COLORSCHEME { White, Black } ColorType;
							COLORS(COLORSCHEME _shape): ColorType(_shape) {};
							} * Color;
						struct VISUAL_VOLUMES: public BASE_PROPERTY
							{
							enum VOLUMEFRAME { WW, CC } VolumeType;
							VISUAL_VOLUMES(VOLUMEFRAME _shape): VolumeType(_shape) {};
							} * Visual_Volume;
						struct DETAILS: public BASE_PROPERTY
							{
							std::vector<std::string> Links;
							DETAILS() {};
							} * Detail;
						ESSENSE_IMAGE(): Shape(NULL), Color(NULL), Visual_Volume(NULL), Detail(NULL) {};
						};

					ESSENSE(): name("") {};

					std::map<LPCSTR, ESSENSE_LINKAGE *> Linkages;

					void ConnectTo(ESSENSE *) {};
					};
				class	NEURO_DATABASE
					{
				public:


					std::vector<type_scan_all *>	NeuroStatistics;

					NEURO_DATABASE();
					~NEURO_DATABASE();

					void	Update(type_scan_all * _data);
					};
				class	NEURO_DECISION
						{
					public:
						int rate;

						NEURO_DECISION()
							{
						
							};
						~NEURO_DECISION()
							{
						
							};
						};

			OBJECT_UNIT(LPCSTR _name, Vector3D _coordinates);
			~OBJECT_UNIT();
				
				//This function is working until the object is dead (living process)

				void					Work();
				LPCSTR					GetName() { return name; };
				virtual LPCSTR			GetAssossiation();
				void					DataAccept(void *);

				//Functions, controlling overall health

				double&					GetVitality()				{ return vitality; };
				void					SetVitality(float& _life)	{ vitality = _life; };

				//This makes unit say smth

				void					Say_Message(int _iD = 0)	{ AfxMessageBox("The actor died..."); };

				static OBJECT_BASE * 	Start(LPCSTR _name, Vector3D _coordinates);

				friend void			OBJECTS::OBJECTS_REGISTRY::OBJECT_EYE::Work();
				friend void			OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::Work();

			private:

				double			vitality;
				double			fatigue;

				////////////////////////////////////////////////BASE ACTIONS////////////////////////////////////////////////



				typedef void(OBJECT_UNIT::* SelfAction)();
				typedef void(OBJECT_UNIT::* ItemAction)(OBJECT_BASE* _obj1);
				typedef void(OBJECT_UNIT::* ItemCombination)(OBJECT_BASE* _obj1, OBJECT_BASE* _obj2);

				//If CombineItems(FOOD, SELF) => SELF.Vitality++; <INTERIOR_FEELING>
				//If CombineItems(WOOD, SELF) => SELF.Floatage++; <INTERIOR_FEELING>
				//If CombineItems(WOOD, WATER) => WOOD.Weight++; <INTERIOR_FEELING>
				//							   => WOOD.Color = Black;  <EYE_FEELING>
				//							   => WOOD.Color = Black;  <EYE_FEELING>
				//If CombineItems(SELF, WATER) => SELF.Weight++; <INTERIOR_FEELING>
				//							   => SELF.Process.Power-3; <INTERIOR_FEELING>
				//							   => SELF.Color = Black;  <EYE_FEELING>

				std::vector<OBJECT_BASE*>			Inventory;
				std::vector<OBJECT_BASE*>::iterator	InventoryIter;
				map<LPCSTR, OBJECT_BASE *>			Sensors;
				NEURO_DATABASE *					DataBase;

				};
			class OBJECT_FOOD: public OBJECT_BASE
				{
			public:

			OBJECT_FOOD(const int _resistryID, LPCSTR _name, Vector3D _coordinates);
			~OBJECT_FOOD();

				void			Work();
				virtual LPCSTR	GetAssossiation();
				virtual void	Say_Message(LPCTSTR _message);
		
			private:

				double	food;
	
				void	GetInfo() {};
				};
			class OBJECT_WATER: public OBJECT_BASE
				{
			public:

			OBJECT_WATER(LPCSTR _name, Vector3D _coordinates);
			~OBJECT_WATER()
					{
			
					}

				void					Work();
				void					Say_Message(int _ID);
				void					DataAccept(void * _data);
				LPCSTR					GetAssossiation();
				LPCSTR					GetName();
				void					Say_Message(LPCTSTR _message) { AfxMessageBox("The table was destroyed..."); };
				static OBJECT_BASE *	Start(LPCSTR _name, Vector3D _coordinates);
		
				private:

				double food;
	
				};
			class OBJECT_SOIL: public OBJECT_BASE
				{
			public:

			OBJECT_SOIL(const int _resistryID, LPCSTR _name, Vector3D _coordinates);
			~OBJECT_SOIL()
					{
			
					}

				void	Work();

				virtual LPCSTR	GetAssossiation();

				virtual void	Say_Message(LPCTSTR _message) { AfxMessageBox("The table was destroyed..."); };
		
			private:

				double food;
	
				};
			class OBJECT_ROPE: public OBJECT_BASE
				{
			public:

			OBJECT_ROPE(const int _resistryID, LPCSTR _name, Vector3D _coordinates);
			~OBJECT_ROPE()
					{
			
					}

				void	Work();

				virtual LPCSTR	GetAssossiation();

				virtual void	Say_Message(LPCTSTR _message) { AfxMessageBox("The table was destroyed..."); };
				};
			class OBJECT_WOOD: public OBJECT_BASE
				{
			public:

			OBJECT_WOOD(const int _resistryID, LPCSTR _name, Vector3D _coordinates);
			~OBJECT_WOOD();

			void	Work();
			virtual LPCSTR	GetAssossiation();
			virtual void	Say_Message(LPCTSTR _message);
				};

		public:

			void AddObject(OBJECT_BASE * _object);
			void DeleteObject(OBJECT_BASE * _object);
			void DeleteObject(int _num);
			void ClearObjects();
			OBJECT_BASE * GetBaseObject(int _num);
			static OBJECTS_REGISTRY * GetObjectRegistry() { return ObjectRegistry; };
		
			virtual void Module_Init();
			virtual void Module_Run();
			virtual void Module_Destroy();

			vector<OBJECT_BASE *> ObjectsList;
			map<float, map<float, map<float, OBJECT_BASE *>>> ObjectsCoordinates;
			};
		};
	};