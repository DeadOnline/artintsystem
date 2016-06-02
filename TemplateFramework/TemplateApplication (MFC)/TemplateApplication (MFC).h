#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

// APPLICATIONCORE
// See TemplateApplication (MFC).cpp for the implementation of this class
//
#ifdef MFCAPPLICATIONCORE_EXPORTS
#define MFCAPPLICATIONCORE_API __declspec(dllexport) 
#else
#define MFCAPPLICATIONCORE_API __declspec(dllimport) 
#endif

namespace MFCAPPLICATIONCORE
{

	class APPLICATIONCORE : public CWinApp
	{
	public:
		APPLICATIONCORE();
		virtual ~APPLICATIONCORE();

		// Overrides
	public:
		virtual BOOL InitInstance();

		DECLARE_MESSAGE_MAP()
	};

};