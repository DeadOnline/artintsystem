#include <afxwin.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <list>
#include "resource.h"
#include "sqlite3.h"
#include <vld.h>
#include <mutex>
#include <dos.h>
#include <time.h>

#include "Console_Resources_Strings.h"
#include "Console_Resources_Macroses.h"
#include "GUI.h"
#include "DATABASE.h"
#include <TemplateApplication (MFC).h>
#include "ARTINTELSYSAPPLICATION.h"
#include "MODULES.h"
#include "LOG.h"
#include "TemplateInputCore.h"
#include "TemplateGraphicsCore.h"
#include "Local_Files_List.h"

using namespace std;

extern class	MODULE_BASE;
extern class	GRAPHCORE;
extern class	ENGINE;
extern class	INPUTCORE;
extern class	ARTINTSYSTEMAPPLICATION;
extern class	GUI;
extern class	OBJECTS_REGISTRY;
extern class	TRANSFORMATION;

//extern mutex mtx;