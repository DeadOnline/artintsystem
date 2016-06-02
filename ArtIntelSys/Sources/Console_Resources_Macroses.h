//These are to get pointers to MAIN modules
#define _GET_MODULE_GUI ((GUI*) WORLD::OBJECTS::OBJECTS_REGISTRY::GetObjectRegistry()->GetApplication()->GetModuleByName(_MODULE_GUI))
#define _GET_MODULE_OBJREG ((WORLD::OBJECTS::OBJECTS_REGISTRY*)WORLD::OBJECTS::OBJECTS_REGISTRY::GetObjectRegistry()->GetApplication()->GetModuleByName(_MODULE_OBJECTREGISTRY))

//These are used for logging
#define _GET_GUI_CONSOLE_MAKE_RECORD(message) _GET_MODULE_GUI->controlConsoleHistory.AddString(message); 
#define _GET_LOG_MAKE_RECORD(message, isRecordable) LOG::Instance().RecordLine(message, isRecordable);
#define _GET_LOG_GET_RECORD LOG::Instance().ReadLine();

//This gets object's type for WORLD module
#define GET_OBJECT_TYPE(a,b) (a=="SEA")?b=SEA:(a=="LAND")?b=LAND:(a=="FOOD")?b=FOOD:(a=="ROPE")?b=ROPE:(a=="WOOD")?b=WOOD:(a=="HUMAN")?b=HUMAN:(a=="HUMAN_EYE")?b=HUMAN_EYE:b=HUMAN_BODY;

//These are used to get paths to interior directories
#define PATH_DATABASE "../Resources/SQL database/"
#define PATH_MATERIAL "../Resources/Materials/"
#define PATH_MODEL "../Resources/Models/"

//These are full adresses of interior resources
#define GET_PATH_DATABASE(name) string(PATH_DATABASE).append(name).c_str()
#define GET_PATH_MODEL(name) string(PATH_MODEL).append(name).c_str()
#define GET_PATH_MATERIAL(name) (name==NULL)?PATH_MATERIAL:string(PATH_MATERIAL).append(name).c_str()

//#define CHECK_FOR_EXISTENCE_NAME(a) if (!a) { AfxMessageBox("Empty name was given. Cannot proceed with operation."); return E_FAIL; };
#define CHECK_FOR_EXISTENCE_NAME_DEVICE(module, a, b) if ((!a) || (!b)) { AfxMessageBox("In "##module##": either empty name or rendering device is missing. Cannot proceed with operation."); return E_FAIL; };
#define CHECK_FOR_EXISTENCE_NAME_PATH_DEVICE(module, a, b, c) if ((!a) || (!b) || (!c)) { AfxMessageBox("In "##module##": Some of 3 arguments are missing. Cannot proceed with operation."); return E_FAIL; };

#define SQLITE_GET_MATERIALS_INFO "SELECT [ESSENSE A], [ESSENSE B], [SENSOR: EYE: COLOR], [SENSOR: EYE: SHAPE], [SENSOR: BODY: FATIQUE], [SENSOR: BODY: PAIN], [SENSOR: BODY: VITALITY] from [OBJECT LINKAGES]"
#define CREATE_TABLE_SQLite "CREATE TABLE IF NOT EXISTS foo(a,b,c); INSERT INTO FOO VALUES(1,2,3); INSERT INTO FOO SELECT * FROM FOO;"