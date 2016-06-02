#include "stdafx.h"
#include "ALL.h"

using namespace WORLD;
using namespace WORLD::DIMENSIONS;

const OBJECTS::OBJECTS_REGISTRY::OBJECT_UNIT::ESSENSE * OBJECTS::OBJECTS_REGISTRY::OBJECT_UNIT::ESSENSE::Self = NULL;
OBJECTS::OBJECTS_REGISTRY* OBJECTS::OBJECTS_REGISTRY::ObjectRegistry = NULL;
int		OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE::quantity = 0;
int		OBJECTS::OBJECTS_REGISTRY::ThreadQuantity = 0;
map<const int, pair<void *, int>> OBJECTS::OBJECTS_BUFFER::Buffer = map<const int, pair<void *, int>>();
CRITICAL_SECTION ps, ps1;

MATERIALS::TRANSFORMATION::ACTION *		MATERIALS::TRANSFORMATION::GetCombinationInfo(SENSOR_METHODS _type, OBJECT_TYPES _arg1, OBJECT_TYPES _arg2)
	{
	for (int i = 0; i < Shedule[_arg1][_arg2].size(); i++)
		{
		if (Shedule[_arg1][_arg2][i].Method == _type) return &Shedule[_arg1][_arg2][i];
		}
	return NULL;
	};

#pragma region OBJECTS_REGISTRY
		OBJECTS::OBJECTS_REGISTRY::OBJECTS_REGISTRY(ARTINTSYSTEMAPPLICATION* _parentClass) : MODULE_BASE(_parentClass)
				{
				if (!ObjectRegistry) ObjectRegistry = this;
				InitializeCriticalSection(&ps);
				InitializeCriticalSection(&ps1);
				}
		OBJECTS::OBJECTS_REGISTRY::~OBJECTS_REGISTRY()
				{
				DeleteCriticalSection(&ps);
				DeleteCriticalSection(&ps1);
				}
UINT	OBJECTS::OBJECTS_REGISTRY::Object_Thread(LPVOID pParam)
	{
	ThreadQuantity++;
	//-----------------------------------------------------------------------CRITICAL 1------------------------------------------------------------------------------//
	EnterCriticalSection(&ps);
	using namespace WORLD::OBJECTS;
	OBJECT_BASE * GObject = (OBJECT_BASE*)pParam;
	OBJECTS_REGISTRY * ObjectRegistry = GetObjectRegistry();
	ObjectRegistry->ObjectsList.push_back(GObject);
	ObjectRegistry->ObjectsCoordinates[GObject->location.x][GObject->location.y][GObject->location.z] = GObject;
	//Creating graphical object, using unique ID - * Object scheme
	_GET_MODULE_GUI->Initiate_Object(GObject->GetName(), GObject->GetID(), GRAPHCORE::OBJECTS::OBJECT_DATA::Active, D3DXVECTOR3(GObject->GetLocation().x, GObject->GetLocation().y, GObject->GetLocation().z));
	//Adding appropriate mesh grid to object, so it could be shown in world
	_GET_MODULE_GUI->GRAPHCORE::MAP_OBJ[ GObject->GetID() ].Add_Mesh(_GET_MODULE_GUI->DEVICE, GObject->GetAssossiation(), GRAPHCORE::WORLDPOSITION(0, 0, 0));
	LeaveCriticalSection(&ps);
	//----------------------------------------------------------------------~CRITICAL 1------------------------------------------------------------------------------//

	GObject->Work();

	//-----------------------------------------------------------------------CRITICAL 2------------------------------------------------------------------------------//
	EnterCriticalSection(&ps1);
	std::vector<OBJECTS_REGISTRY::OBJECT_BASE *>::iterator SubObject = std::find(GetObjectRegistry()->ObjectsList.begin(), GetObjectRegistry()->ObjectsList.end(), GObject);
	if (*SubObject)
		{
		_GET_LOG_MAKE_RECORD(GObject->GetName(), true);
		_GET_LOG_MAKE_RECORD(_CONSOLE_LOG_ACTOR_COMMENT_IAMDEAD, true);
		_GET_MODULE_GUI->Destroy_Object(GObject->GetID());
		ObjectRegistry->ObjectsCoordinates[GObject->location.x][GObject->location.y][GObject->location.z] = NULL;
		OBJECTS_BUFFER::Buffer[GObject->GetID()].second = 2;
		OBJECT_TYPES currentType = GObject->GetType();
		switch (currentType)
			{
			case OBJECT_TYPES::FOOD:
				delete (OBJECT_FOOD*) GObject;
				break;
			case OBJECT_TYPES::HUMAN:
				delete (OBJECT_UNIT*) GObject;
				break;
			case OBJECT_TYPES::HUMAN_BODY:
				delete (OBJECT_BODY*) GObject;
				break;
			case OBJECT_TYPES::HUMAN_EYE:
				delete (OBJECT_EYE*) GObject;
				break;
			default:
				delete GObject;
			};
		ObjectRegistry->ObjectsList.erase(SubObject);
		ObjectRegistry->ObjectsList.shrink_to_fit();
		};
	LeaveCriticalSection(&ps1);
	//----------------------------------------------------------------------~CRITICAL 2------------------------------------------------------------------------------//

	return ThreadQuantity;
	};
void	OBJECTS::OBJECTS_REGISTRY::AddObject(OBJECT_BASE * _object) { };
void	OBJECTS::OBJECTS_REGISTRY::DeleteObject(OBJECT_BASE * _object)
	{};
void	OBJECTS::OBJECTS_REGISTRY::DeleteObject(int _num)
{};
void	OBJECTS::OBJECTS_REGISTRY::ClearObjects()
{};
void	OBJECTS::OBJECTS_REGISTRY::Module_Init()
	{
	int y = 0;
	};
void	OBJECTS::OBJECTS_REGISTRY::Module_Run() { };
void	OBJECTS::OBJECTS_REGISTRY::Module_Destroy() { };
OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE * OBJECTS::OBJECTS_REGISTRY::GetBaseObject(int _num)
	{
	return NULL;
	};
#pragma endregion
#pragma region OBJECTS_REGISTRY_OBJECT_BASE
							OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE::OBJECT_BASE(LPCSTR _name, 
																				OBJECT_TYPES _type, 
																				Vector3D _coordinates = Vector3D(0, 0, 0),
																				Vector3D _size = Vector3D(1, 1, 1)) :
								size(_size), location(_coordinates), ID(IncreaseQuantity()), name(_name), type(_type)
									{
									BufferCell = &OBJECTS_BUFFER::Buffer[GetID()];
									};
							OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE::~OBJECT_BASE()
			{
			ThreadQuantity--;
			};
LPCSTR						OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE::GetName()
	{
	return name;
	};
void						OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE::TearConnections() {};
OBJECT_TYPES				OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE::GetType() { return type; };
const	 int&				OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE::GetID() { return ID; };
int							OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE::IncreaseQuantity() { return ++quantity; };
void						OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE::ConnectTo(const int _IDPort) { IDPorts.push_back(_IDPort); };
Vector3D&					OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE::GetLocation() { return location; };
void						OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE::SetLocation(Vector3D& _location)
	{
	//Version 1 - Erasing empty cells
	//GetObjectRegistry()->ObjectsCoordinates[location.x].erase(location.y);
	//if (GetObjectRegistry()->ObjectsCoordinates[location.x].size() == 0)
	//	GetObjectRegistry()->ObjectsCoordinates.erase(location.x);
	//Version 2 - Leaving cells existing, but empty
	GetObjectRegistry()->ObjectsCoordinates[location.x][location.y][location.z] = NULL;
	location = _location;
	GetObjectRegistry()->ObjectsCoordinates[location.x][location.y][location.z] = this;
	};
OBJECTS::OBJECTS_REGISTRY *	OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE::GetObjectRegistry() { return ObjectRegistry; };
#pragma endregion
#pragma region OBJECTS_REGISTRY_OBJECT_EYE
							OBJECTS::OBJECTS_REGISTRY::OBJECT_EYE::OBJECT_EYE(OBJECT_BASE * _source, Vector3D _coordinates) : OBJECT_BASE("EYE", HUMAN_EYE, _coordinates), vitality(1)
								{
								IDPorts.push_back(_source->GetID());
								_source->ConnectTo(ID);
								};
		LPCSTR				OBJECTS::OBJECTS_REGISTRY::OBJECT_EYE::GetName() { return name; };
		LPCSTR				OBJECTS::OBJECTS_REGISTRY::OBJECT_EYE::GetAssossiation() { return _EYE; };
		void				OBJECTS::OBJECTS_REGISTRY::OBJECT_EYE::Say_Message(int _iD = 0)
			{
			AfxMessageBox("The eye died...");
			};
		void				OBJECTS::OBJECTS_REGISTRY::OBJECT_EYE::SetFocus(FOCUS _focus)
			{
			Focus = _focus;
			};
		void				OBJECTS::OBJECTS_REGISTRY::OBJECT_EYE::Work()
			{
			pair<void *, int> * SourceBuffer = &OBJECTS_BUFFER::Buffer[IDPorts[0]];
			while (vitality)
				{
				vitality--;
				if (!BufferCell->first)
					{
					BufferCell->first = Scan();
					BufferCell->second = 1;
					char Temp[ 100 ];
					sprintf_s(Temp, "%s%d%s%s%s%f", "Object ", GetID(), ": \"", GetName(), "\": has sent new data package... HP level: ", vitality);
					_GET_LOG_MAKE_RECORD(Temp, false);
					}
				if (SourceBuffer->second == 2) break; else vitality++;
				Sleep(100);
				};
			type_scan_all * temp = (type_scan_all *)BufferCell->first;
			OBJDELETE(temp);
			};
		type_scan_all *		OBJECTS::OBJECTS_REGISTRY::OBJECT_EYE::Scan()
			{
			type_scan_all *	FrameBuffer = new type_scan_all();
			(*FrameBuffer)["EYECOLOR"] = Scan_Color();
			(*FrameBuffer)["EYESHAPE"] = Scan_Shape();
			return FrameBuffer;
			};
		type_scan_single	OBJECTS::OBJECTS_REGISTRY::OBJECT_EYE::Scan_Color()
			{

			//Function of standart EYE object. It can only scan definite area for recording objects in it. Until further development, world contains 
			//cubic spaces that can be scanned.

			//Scans for any color presented in this area (x, y).

			//Clearing our buffer
			FrameColor.clear();
			OBJECTS_REGISTRY * ObjectRegistry = GetObjectRegistry();
			MATERIALS::TRANSFORMATION::ACTION * Action = NULL;///
			
			//Getting an object, located in the area of eye-focus
			//If object exists inside this cell (variant 1 - no empty cells)

			map<float, map<float, map<float, OBJECT_BASE *>>>::iterator	ObjectsCoordinatesXIter;
			map<float, map<float, OBJECT_BASE *>>::iterator				ObjectsCoordinatesYIter;
			map<float, OBJECT_BASE *>::iterator								ObjectsCoordinatesZIter;

			ObjectsCoordinatesXIter = ObjectRegistry->ObjectsCoordinates.find(Focus.focusX);
			if ( ObjectsCoordinatesXIter != ObjectRegistry->ObjectsCoordinates.end() )
				{
				ObjectsCoordinatesYIter = ObjectsCoordinatesXIter->second.find(Focus.focusY);
				if ( ObjectsCoordinatesYIter != ObjectsCoordinatesXIter->second.end() )
					{
					ObjectsCoordinatesZIter = ObjectsCoordinatesYIter->second.find(Focus.focusZ);
					if ( ObjectsCoordinatesZIter != ObjectsCoordinatesYIter->second.end() )
						Action = MATERIALS::Transformation.GetCombinationInfo(COLOR, ObjectsCoordinatesZIter->second->GetType(), ObjectsCoordinatesZIter->second->GetType());
					}
				}
			//If visual info exists
			if (Action)
				//Add it into buffer
				FrameColor.push_back(Action->power);
			else
				FrameColor.push_back(0);

			return FrameColor;
			};
		type_scan_single	OBJECTS::OBJECTS_REGISTRY::OBJECT_EYE::Scan_Shape()
			{
			//Scans for any color presented in this area (x, y)

			//Clearing our buffer
			FrameShape.clear();
			OBJECTS_REGISTRY * ObjectRegistry = GetObjectRegistry();
			MATERIALS::TRANSFORMATION::ACTION * Action = NULL;
			map<float, map<float, map<float, OBJECT_BASE *>>>::iterator	ObjectsCoordinatesXIter;
			map<float, map<float, OBJECT_BASE *>>::iterator				ObjectsCoordinatesYIter;
			map<float, OBJECT_BASE *>::iterator								ObjectsCoordinatesZIter;

			ObjectsCoordinatesXIter = ObjectRegistry->ObjectsCoordinates.find(Focus.focusX);
			if ( ObjectsCoordinatesXIter != ObjectRegistry->ObjectsCoordinates.end() )
				{
				ObjectsCoordinatesYIter = ObjectsCoordinatesXIter->second.find(Focus.focusY);
				if ( ObjectsCoordinatesYIter != ObjectsCoordinatesXIter->second.end() )
					{
					ObjectsCoordinatesZIter = ObjectsCoordinatesYIter->second.find(Focus.focusZ);
					if ( ObjectsCoordinatesZIter != ObjectsCoordinatesYIter->second.end() )
						Action = MATERIALS::Transformation.GetCombinationInfo(SHAPE, ObjectsCoordinatesZIter->second->GetType(), ObjectsCoordinatesZIter->second->GetType());
					}
				}
			//If visual info exists
			if (Action)
				//Add it into buffer
				FrameShape.push_back(Action->power);
			else
				FrameShape.push_back(0);

			return FrameShape;
			};
		void				OBJECTS::OBJECTS_REGISTRY::OBJECT_EYE::DataAccept(void * _data = NULL) { };
OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE *	OBJECTS::OBJECTS_REGISTRY::OBJECT_EYE::Start(OBJECT_BASE * _source, Vector3D _coordinates)
	{
	OBJECT_EYE * Temp = NULL;
	AfxBeginThread(Object_Thread, Temp = new OBJECT_EYE(_source, _coordinates));
	return Temp;
	};
#pragma endregion
#pragma region OBJECTS_REGISTRY_OBJECT_BODY
					OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::OBJECT_BODY(OBJECT_BASE * _source, Vector3D _coordinates) : OBJECT_BASE("BODY", HUMAN_BODY, _coordinates), vitality(100)
			{
			IDPorts.push_back(_source->GetID());
			_source->ConnectTo(ID);
			};
LPCSTR				OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::GetName()
			{
			return name;
			};
LPCSTR				OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::GetAssossiation()
			{
			return _BODY;
			};
void				OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::Say_Message(int _iD = 0)
			{
			AfxMessageBox("The actor died...");
			};
void				OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::Work()
			{
			pair<void *, int> * SourceBuffer = &OBJECTS_BUFFER::Buffer[IDPorts[0]];
			while (vitality)
				{
				vitality--;
				if (!BufferCell->first)
					{
					BufferCell->first = Scan();
					BufferCell->second = 1;
					char Temp[ 100 ];
					sprintf(Temp, "%s%d%s%s%s%f", "Object ", GetID(), ": \"", GetName(), "\": has sent new data package... HP level: ", vitality);
					_GET_LOG_MAKE_RECORD(Temp, false);
					}
				if (SourceBuffer->second == 2) break; else vitality++;
				Sleep(100);
				};
			type_scan_all * temp = (type_scan_all *)BufferCell->first;
			OBJDELETE(temp);
			};
type_scan_all *		OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::Scan()
			{
			type_scan_all *		FrameBuffer = new type_scan_all();
			(*FrameBuffer)["BODYTOUCH"] = Scan_Touch();
			(*FrameBuffer)["BODYTEMPERATURE"] = Scan_Temperature();
			(*FrameBuffer)["BODYVITALITY"] = Scan_Vitality();
			(*FrameBuffer)["BODYFATIGUE"] = Scan_Fatigue();
			return FrameBuffer;
			};
type_scan_single	OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::Scan_Touch()		{ return type_scan_single(); };
type_scan_single	OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::Scan_Temperature()	{ return type_scan_single(); };
type_scan_single	OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::Scan_Vitality()		{ return type_scan_single(); };
type_scan_single	OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::Scan_Fatigue()		{ return type_scan_single(); };
void				OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::DataAccept(void * _data = NULL) { };
void				OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::MoveDown()
			{
			GetLocation().y--;
			};
void				OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::MoveLeft()
			{
			GetLocation().x--;
			};
void				OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::MoveRight()
			{
			GetLocation().x++;
			};
void				OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::MoveUp()
			{
			GetLocation().y++;
			};
void				OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::PickItem(OBJECT_BASE* _obj1)
	{
	//Inventory.push_back(_obj1);
	};
void				OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::ThrowItem(OBJECT_BASE* _obj1)
	{
	//std::vector<OBJECT_BASE*>::iterator Temp = std::find(Inventory.begin(), Inventory.end(), _obj1);
	//Inventory.erase(Temp);
	};
void				OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::SplitItem(OBJECT_BASE* _obj1) { };
void				OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::CombineItems(OBJECT_BASE* _obj1, OBJECT_BASE * _obj2)
	{
	using namespace WORLD::MATERIALS;
	using namespace WORLD::PHYSICS;
	//6 parameters:
	//EYE
	//EAR
	//NOSE
	//TONGUE
	//SKIN
	//EXPERIENCE
	//Firstly, check our database for the presence or miss of Objects you combine
	//if (DataBase->ObjectEssenses.find(_obj1->GetName()) == DataBase->ObjectEssenses.end()) DataBase->ObjectEssenses[_obj1->GetName()];
	//if (DataBase->ObjectEssenses.find(_obj2->GetName()) == DataBase->ObjectEssenses.end()) DataBase->ObjectEssenses[_obj2->GetName()];
	//DATABASE::OBJECT_ESSENSE * _Object1 = &DataBase->ObjectEssenses[_obj1->GetName()];
	//DATABASE::OBJECT_ESSENSE * _Object2 = &DataBase->ObjectEssenses[_obj2->GetName()];
	//_Object1->ConnectTo(_Object2);
	//std::vector<TRANSFORMATION::ACTION> NewData = TRANSFORMATION::GetCombinationInfo(_obj1->GetName(), _obj2->GetName());
	//for (int i = 0; i < NewData.size(); i++)
	//	{
	//	if (NewData[i].Method==WORLD::SENSOR_METHODS::COLOR)		_Object1->Assosiation[_Object2->name].Linkage->AddSubEssense(DATABASE::OBJECT_ESSENSE::ESSENSE_LINKAGE::MEMORYCELL(&DataBase->ObjectEssenses["COLOR"], 10, NewData[i].power));
	//	if (NewData[i].Method==WORLD::SENSOR_METHODS::FATIGUE)		_Object1->Assosiation[_Object2->name].Linkage->AddSubEssense(DATABASE::OBJECT_ESSENSE::ESSENSE_LINKAGE::MEMORYCELL(&DataBase->ObjectEssenses["FATIGUE"], 10, NewData[i].power));
	//	if (NewData[i].Method==WORLD::SENSOR_METHODS::PAIN)			_Object1->Assosiation[_Object2->name].Linkage->AddSubEssense(DATABASE::OBJECT_ESSENSE::ESSENSE_LINKAGE::MEMORYCELL(&DataBase->ObjectEssenses["PAIN"], 10, NewData[i].power));
	//	if (NewData[i].Method==WORLD::SENSOR_METHODS::SHAPE)		_Object1->Assosiation[_Object2->name].Linkage->AddSubEssense(DATABASE::OBJECT_ESSENSE::ESSENSE_LINKAGE::MEMORYCELL(&DataBase->ObjectEssenses["SHAPE"], 10, NewData[i].power));
	//	if (NewData[i].Method==WORLD::SENSOR_METHODS::VITALITY)		_Object1->Assosiation[_Object2->name].Linkage->AddSubEssense(DATABASE::OBJECT_ESSENSE::ESSENSE_LINKAGE::MEMORYCELL(&DataBase->ObjectEssenses["VITALITY"], 10, NewData[i].power));
	//	if (NewData[i].Method==WORLD::SENSOR_METHODS::COORDINATES)	_Object1->Assosiation[_Object2->name].Linkage->AddSubEssense(DATABASE::OBJECT_ESSENSE::ESSENSE_LINKAGE::MEMORYCELL(&DataBase->ObjectEssenses["COORDINATES"], 10, NewData[i].power));
	//	};
	};
void				OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::Feed(OBJECT_BASE* _obj1)
	{
	////Increase your Vitality level by adding _obj1 power. For we still don't have _obj->Vitality boost, use our WORLD database
	//Vitality+=DataBase->ObjectEssenses["SELF"].Assosiation[_obj1->GetName()].Linkage->Linkages["VITALITY"]->Power;
	////After getting vitality boost, permanently delete object
	//InventoryIter = std::find(Inventory.begin(), Inventory.end(), _obj1);
	//if (*InventoryIter)
	//	{
	//	delete &InventoryIter;
	//	Inventory.erase(InventoryIter);
	//	};
	};
					OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE * OBJECTS::OBJECTS_REGISTRY::OBJECT_BODY::Start(OBJECT_BASE * _source, Vector3D _coordinates)
			{
			OBJECT_BODY * Temp = NULL;
			AfxBeginThread(Object_Thread, Temp = new OBJECT_BODY(_source, _coordinates));
			return Temp;
			};
#pragma endregion
#pragma region OBJECTS_REGISTRY_OBJECT_UNIT
		OBJECTS::OBJECTS_REGISTRY::OBJECT_UNIT::OBJECT_UNIT(LPCSTR _name, Vector3D _coordinates) : DataBase(NULL), OBJECT_BASE(_name, HUMAN, _coordinates), vitality(100), fatigue(100) 
			{
			DataBase = new NEURO_DATABASE();
			Sensors["EYE"] = OBJECT_EYE::Start(this, Vector3D(location.x, location.y, location.z + 20));
			Sensors["BODY"] = OBJECT_BODY::Start(this, Vector3D(location.x, location.y, location.z + 10));
			};
		OBJECTS::OBJECTS_REGISTRY::OBJECT_UNIT::~OBJECT_UNIT()
			{
			OBJDELETE(DataBase);
			};
void	OBJECTS::OBJECTS_REGISTRY::OBJECT_UNIT::DataAccept(void * _data = NULL)
	{
	//DataBase->Update(* (type_scan_all *) _data);
	};
void	OBJECTS::OBJECTS_REGISTRY::OBJECT_UNIT::Work()
	{
	//primary objective: SELF-BODY-VITALITY essense shouldn't reach 0
	//primary objective: SELF-BODY-FATIGUE essense shouldn't reach 0
	//so, must seek methods to increase it
	//Priority is:
	//Vitality is always decreasing, having the speed equal to .0001 hp/sec, and can be increased by special methods (VITALITY, >0)
	//Fatigue can be increased, if SELF stays on static object or executes special method (FATIGUE, >0)
	//Principle of algorythm is: one 'while' tick - one 'decision'
	while (this && (vitality > 0) && fatigue)
		{
		vitality--;
		for (int i = 0; i < IDPorts.size(); i++)
			{
			void * pTemp = OBJECTS_BUFFER::Get_By_ID(IDPorts[i]);
			if (pTemp)
				{
				DataBase->Update((type_scan_all *)pTemp);
				OBJECTS_BUFFER::Set_Value_by_ID(IDPorts[i], NULL);
				char Temp [100];
				sprintf(Temp, "%s%d%s%s%s%f", "Object ", GetID(), ": \"", GetName(), "\": has accepted new data package... HP level: ", vitality);
				_GET_LOG_MAKE_RECORD(Temp, true);
				Sleep(100);
				};
			};
		};
	OBJECTS_BUFFER::Buffer[GetID()].second = 2;
	};
LPCSTR	OBJECTS::OBJECTS_REGISTRY::OBJECT_UNIT::GetAssossiation()
	{
	return _ACTOR;
	};
		OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE *	OBJECTS::OBJECTS_REGISTRY::OBJECT_UNIT::Start(LPCSTR _name, Vector3D _coordinates)
	{
	OBJECT_UNIT * Temp = NULL;
	AfxBeginThread(Object_Thread, Temp = new OBJECT_UNIT(_name, _coordinates));
	return Temp;
	};
#pragma endregion
#pragma region OBJECTS_REGISTRY_OBJECT_UNIT_NEURO_DATABASE
		OBJECTS::OBJECTS_REGISTRY::OBJECT_UNIT::NEURO_DATABASE::NEURO_DATABASE() {};
		OBJECTS::OBJECTS_REGISTRY::OBJECT_UNIT::NEURO_DATABASE::~NEURO_DATABASE()
			{
			for (int i = 0; i < NeuroStatistics.size(); i++)
				{
				type_scan_all * temp = (type_scan_all *)NeuroStatistics[i];
				OBJDELETE(temp);
				};
			};
void	OBJECTS::OBJECTS_REGISTRY::OBJECT_UNIT::NEURO_DATABASE::Update(type_scan_all * _data)
	{
	//-----------------------------------------------------------------------CRITICAL 1------------------------------------------------------------------------------//
	EnterCriticalSection(&ps1);
	NeuroStatistics.push_back(_data);
	LeaveCriticalSection(&ps1);
	//----------------------------------------------------------------------~CRITICAL 1------------------------------------------------------------------------------//
	};
#pragma endregion
#pragma region OBJECTS_REGISTRY_OBJECT_WATER
		OBJECTS::OBJECTS_REGISTRY::OBJECT_WATER::OBJECT_WATER(LPCSTR _name, Vector3D _coordinates) : OBJECT_BASE(_name, SEA, _coordinates), food(1000000000) { };
void	OBJECTS::OBJECTS_REGISTRY::OBJECT_WATER::Work()
	{
	while (true) {};
	};
LPCSTR	OBJECTS::OBJECTS_REGISTRY::OBJECT_WATER::GetAssossiation()
	{
	return _SEA;
	};
		OBJECTS::OBJECTS_REGISTRY::OBJECT_BASE *	OBJECTS::OBJECTS_REGISTRY::OBJECT_WATER::Start(LPCSTR _name, Vector3D _coordinates)
	{
	OBJECT_WATER * Temp = NULL;
	AfxBeginThread(Object_Thread, Temp = new OBJECT_WATER(_name, _coordinates));
	return Temp;
	};
LPCSTR	OBJECTS::OBJECTS_REGISTRY::OBJECT_WATER::GetName() { return S_OK; };
void	OBJECTS::OBJECTS_REGISTRY::OBJECT_WATER::Say_Message(int _ID) {};
void	OBJECTS::OBJECTS_REGISTRY::OBJECT_WATER::DataAccept(void * _data){};
#pragma endregion
#pragma region OBJECTS_REGISTRY_OBJECT_FOOD
							OBJECTS::OBJECTS_REGISTRY::OBJECT_FOOD::OBJECT_FOOD(const int _resistryID, LPCSTR _name, Vector3D _coordinates) : OBJECT_BASE(_name, FOOD, _coordinates), food(1000000000) { };
							OBJECTS::OBJECTS_REGISTRY::OBJECT_FOOD::~OBJECT_FOOD() { };
		void				OBJECTS::OBJECTS_REGISTRY::OBJECT_FOOD::Work()
			{
			while (this && food)
				{
				--food;
				};
			};
		LPCSTR				OBJECTS::OBJECTS_REGISTRY::OBJECT_FOOD::GetAssossiation()
			{
			return _FOOD;
			};
		void				OBJECTS::OBJECTS_REGISTRY::OBJECT_FOOD::Say_Message(LPCTSTR _message) { AfxMessageBox("The table was destroyed..."); };

#pragma endregion
#pragma region OBJECTS_REGISTRY_OBJECT_SOIL
		WORLD::OBJECTS::OBJECTS_REGISTRY::OBJECT_SOIL::OBJECT_SOIL(const int _resistryID, LPCSTR _name, Vector3D _coordinates) : OBJECT_BASE(_name, LAND, _coordinates), food(1000000000) { };
		void				OBJECTS::OBJECTS_REGISTRY::OBJECT_SOIL::Work()
			{
			while (true) {};
			};
		LPCSTR				OBJECTS::OBJECTS_REGISTRY::OBJECT_SOIL::GetAssossiation()
			{
			return _LAND;
			};
#pragma endregion
#pragma region OBJECTS_REGISTRY_OBJECT_ROPE
		WORLD::OBJECTS::OBJECTS_REGISTRY::OBJECT_ROPE::OBJECT_ROPE(const int _resistryID, LPCSTR _name, Vector3D _coordinates) : OBJECT_BASE(_name, ROPE, _coordinates) { };
		void				OBJECTS::OBJECTS_REGISTRY::OBJECT_ROPE::Work() { };
		LPCSTR				OBJECTS::OBJECTS_REGISTRY::OBJECT_ROPE::GetAssossiation()
			{
			return _ROPE;
			};
#pragma endregion
#pragma region OBJECTS_REGISTRY_OBJECT_WOOD
		OBJECTS::OBJECTS_REGISTRY::OBJECT_WOOD::OBJECT_WOOD(const int _resistryID, LPCSTR _name, Vector3D _coordinates) : OBJECT_BASE(_name, WOOD, _coordinates) { };
void	OBJECTS::OBJECTS_REGISTRY::OBJECT_WOOD::Work() {};
LPCSTR	OBJECTS::OBJECTS_REGISTRY::OBJECT_WOOD::GetAssossiation() { return _WOOD; };
void	OBJECTS::OBJECTS_REGISTRY::OBJECT_WOOD::Say_Message(LPCTSTR _message) {};
#pragma endregion
#pragma region OBJECTS_BUFFER
void * OBJECTS::OBJECTS_BUFFER::Get_By_ID(const int _ID)
	{
	mtx.lock();
	pair<void *, int> * Temp = &Buffer[_ID];
	mtx.unlock();
	return Temp->first;
	};
void OBJECTS::OBJECTS_BUFFER::Set_Value_by_ID(const int _ID, void * _data)
	{
	mtx.lock();
	pair<void *, int> * Temp = &Buffer[_ID];
	Temp->first = _data;
	mtx.unlock();
	};
#pragma endregion