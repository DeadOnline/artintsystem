#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "ARTINTSYSTEMDIALOG.h"
#include "resource.h"		// main symbols

class ARTINTSYSTEMAPPLICATION : public CWinApp
{
public:
	ARTINTSYSTEMAPPLICATION();

public:
	virtual BOOL				InitInstance();
	
	//ARTINTSYSTEMDIALOG								* GUI;
	//OBJECT_DATABASE_NAMESPACE::DATABASE				* DATA;
	//std::vector<OBJECT_NAMESPACE::Object_Base *>	* WORLD;

	DECLARE_MESSAGE_MAP()
};

extern ARTINTSYSTEMAPPLICATION theApp;