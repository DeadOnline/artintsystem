#include "stdafx.h"
#include "ALL.h"

BEGIN_MESSAGE_MAP(ARTINTSYSTEMAPPLICATION, CWinApp)
END_MESSAGE_MAP()

ARTINTSYSTEMAPPLICATION::ARTINTSYSTEMAPPLICATION() : CWinApp()//MFCAPPLICATIONCORE::APPLICATIONCORE()
					{
				
					};
				ARTINTSYSTEMAPPLICATION::~ARTINTSYSTEMAPPLICATION() 
					{ 
					//delete (WORLD::OBJECTS::OBJECTS_REGISTRY *) MODULES["WORLD"];
					delete (WORLD::PHYSICS::DATABASE*) MODULES["DATABASE"];
					//delete (GUI*) MODULES["GUI"];
					MODULES.clear();
					};

BOOL			ARTINTSYSTEMAPPLICATION::InitInstance()
					{
					CWinApp::InitInstance();
					CShellManager *pShellManager = new CShellManager;
					CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
					SetRegistryKey(_T("Local AppWizard-Generated Applications"));

					CreateModules();
					
					if (pShellManager != NULL)
						{
						delete pShellManager;
						}
					return FALSE;
					};
void			ARTINTSYSTEMAPPLICATION::CreateModules()
					{
					srand(time(0));
					char temp[ 100 ] = { };
					LoadString(( ( CWinApp * ) this )->m_hInstance, _MODULE_GUI1, temp, 100);

					if (MODULES.find("DATABASE") == MODULES.end()) MODULES["DATABASE"] = new WORLD::PHYSICS::DATABASE("DATABASE");
					((WORLD::PHYSICS::DATABASE*) MODULES["DATABASE"])->Module_Init();
					if (MODULES.find("WORLD") == MODULES.end()) MODULES["WORLD"] = (MODULE_BASE *) &WORLD::OBJECTS::OBJECTS_REGISTRY::Instance(this);
					((WORLD::OBJECTS::OBJECTS_REGISTRY*) MODULES["WORLD"])->Module_Init();
					if (MODULES.find("GUI") == MODULES.end()) MODULES["GUI"] = (MODULE_BASE *) &GUI::Instance(this);
					((GUI*) MODULES["GUI"])->Module_Init();
					};
MODULE_BASE *	ARTINTSYSTEMAPPLICATION::GetModuleByName(LPCSTR _name)
					{
					if (MODULES.find(_name) != MODULES.end())
						return MODULES[_name];
					else
						return NULL;
					};

ARTINTSYSTEMAPPLICATION theApp;