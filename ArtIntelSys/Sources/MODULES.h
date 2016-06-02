#pragma once

#include "ALL.h"

class MODULE_BASE
	{
public:
	MODULE_BASE(ARTINTSYSTEMAPPLICATION * _Root = NULL);
	~MODULE_BASE();
	
	virtual void Module_Init() = 0;
	virtual void Module_Run() = 0;
	virtual void Module_Destroy() = 0;

	ARTINTSYSTEMAPPLICATION * GetApplication();

private:
	static ARTINTSYSTEMAPPLICATION * Application;
	};