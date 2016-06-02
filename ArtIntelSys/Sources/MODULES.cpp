#include "stdafx.h"
#include "ALL.h"

ARTINTSYSTEMAPPLICATION * MODULE_BASE::Application = NULL;

MODULE_BASE::MODULE_BASE(ARTINTSYSTEMAPPLICATION * _application) 
	{
	if (_application) Application = _application;
	}
MODULE_BASE::~MODULE_BASE()
	{ }

ARTINTSYSTEMAPPLICATION * MODULE_BASE::GetApplication()
	{
	return Application;
	};