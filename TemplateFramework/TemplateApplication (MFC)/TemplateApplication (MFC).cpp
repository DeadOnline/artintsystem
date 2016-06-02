#include "stdafx.h"
#include "TemplateApplication (MFC).h"

using namespace MFCAPPLICATIONCORE;

BEGIN_MESSAGE_MAP(APPLICATIONCORE, CWinApp)
END_MESSAGE_MAP()

APPLICATIONCORE::APPLICATIONCORE() : CWinApp()
{

}

APPLICATIONCORE::~APPLICATIONCORE()
{

}

BOOL APPLICATIONCORE::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}