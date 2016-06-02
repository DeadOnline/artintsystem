#pragma once

#include "afxwin.h"
#include "ARTINTELSYS.h"
#include "DATABASE.h"
#include "Console_Resources_Strings.h"
#include "Console_Resources_Macroses.h"
#include <string>
#include <iostream>

#define ARTINTELSYSTEM_FRAME 102

extern class ARTINTSYSTEMAPPLICATION;

// ARTINTSYSTEMDIALOG dialog
class ARTINTSYSTEMDIALOG : public CDialogEx
{
// Construction
public:
	ARTINTSYSTEMDIALOG(ARTINTSYSTEMAPPLICATION *, CWnd*);	// standard constructor

// Dialog Data
	enum { IDD = ARTINTELSYSTEM_FRAME };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	static afx_msg UINT Objects_Draw(LPVOID pParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	ARTINTSYSTEMAPPLICATION *	parentClass;
	afx_msg void OnEnChangeCommandPanel();
	CEdit cConsoleInputCommand; //Console textbox control
	CListBox mConsoleHistory; //Console history listbox control
};
