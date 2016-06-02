#pragma once

#include "ALL.h"

#define ARTINTELSYSTEM_FRAME 102

#define _CONSOLE_MAKE_RECORD(message) controlConsoleHistory.AddString(message); controlConsoleInputCommand.SetWindowText("");
#define _GUI_CONSOLE_SCRIPT_FILL_HISTORY(message) controlConsoleHistory.AddString(message.c_str());
static mutex GUI_locker;

class CScreen : public CStatic							// Rendered frame window
	{
public:
	CWnd * Smth, * Parent;
	double pi;
	int X, Y;
	CScreen(CWnd * _parent = NULL): Smth(NULL), Parent(_parent), pi(10), X(0), Y(0) {};		// конструктор диалога
	~CScreen(){};

	afx_msg void OnPaint();
	void Set_Parent(CWnd * _parent)	{ Parent = _parent; };
	CWnd * Get_Parent() { return Parent; };
	afx_msg void OnMouseMove(UINT, CPoint P) {};
	BOOL PreTranslateMessage(MSG * pMsg) { return S_OK; };
	DECLARE_MESSAGE_MAP();
	};
class CConsole : public CListBox							
	{
public:
	CWnd * Smth, * Parent;
	CConsole(CWnd * _parent = NULL): Smth(NULL), Parent(_parent) {};		// конструктор диалога
	~CConsole(){};								

	afx_msg void OnPaint();
	void Set_Parent(CWnd * _parent)	{ Parent = _parent; };
	CWnd * Get_Parent() { return Parent; };
	BOOL PreTranslateMessage(MSG * pMsg) { return S_OK; };
	DECLARE_MESSAGE_MAP();
	};
// GUI dialog
class GUI : public CDialogEx, public MODULE_BASE, public GRAPHCORE, public ENGINE
	{
	// Construction
public:

	static const GUI& Instance()
		{
		static GUI theSingleInstance;
		return theSingleInstance;
		}
	static const GUI& Instance(ARTINTSYSTEMAPPLICATION * _parentClass)
		{
		static GUI theSingleInstance(_parentClass);
		return theSingleInstance;
		}

private:
	GUI(CWnd* pParent = NULL);	// standard constructor
	GUI(ARTINTSYSTEMAPPLICATION *, CWnd* pParent = NULL);	// standard constructor
	~GUI() { };

public:
	// Dialog Data
	enum { IDD = ARTINTELSYSTEM_FRAME };

	virtual void	Module_Init();
	virtual void	Module_Run();
	virtual void	Module_Destroy();
	void			DirectXDraw();
	void			ConsoleRecording();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	
	//static afx_msg UINT Objects_Draw(LPVOID pParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeCommandPanel();
	CEdit controlConsoleInputCommand; //Console textbox control
	CConsole controlConsoleHistory; //Console history listbox control
	CScreen controlConsoleGraphic;
	CWnd * Smth;
	};