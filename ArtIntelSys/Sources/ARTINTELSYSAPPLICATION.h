#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "ALL.h"

class ARTINTSYSTEMAPPLICATION : public CWinApp//MFCAPPLICATIONCORE::APPLICATIONCORE
	{
public:
	ARTINTSYSTEMAPPLICATION();
	~ARTINTSYSTEMAPPLICATION();

public:
	virtual BOOL				InitInstance();
	void						CreateModules();

	MODULE_BASE *				GetModuleByName(LPCSTR);

	DECLARE_MESSAGE_MAP()
private:

	std::map<LPCSTR, MODULE_BASE *>				MODULES;
	std::map<LPCSTR, MODULE_BASE *>::iterator	MODULES_ITER;
	};

extern ARTINTSYSTEMAPPLICATION theApp;
