#pragma once

#include "stdafx.h"
#include "afxdialogex.h"
#include "ARTINTSYSTEMDIALOG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char _temp[20] = {};
std::string _command;

ARTINTSYSTEMDIALOG::ARTINTSYSTEMDIALOG(ARTINTSYSTEMAPPLICATION* _parentClass, CWnd* pParent)
	: CDialogEx(ARTINTSYSTEMDIALOG::IDD, pParent), parentClass(_parentClass)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void ARTINTSYSTEMDIALOG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, CONSOLE_COMMAND_PANEL, cConsoleInputCommand);
	DDX_Control(pDX, CONSOLE_HISTORY, mConsoleHistory);
}

BEGIN_MESSAGE_MAP(ARTINTSYSTEMDIALOG, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(CONSOLE_COMMAND_PANEL, &ARTINTSYSTEMDIALOG::OnEnChangeCommandPanel)
END_MESSAGE_MAP()

BOOL ARTINTSYSTEMDIALOG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//AfxBeginThread(&Objects_Draw,this);

	SetIcon(m_hIcon, TRUE);			// Set big icon

	return TRUE;  // return TRUE  unless you set the focus to a control
}
void ARTINTSYSTEMDIALOG::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
HCURSOR ARTINTSYSTEMDIALOG::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
UINT ARTINTSYSTEMDIALOG::Objects_Draw(LPVOID pParam)
	{
	//using namespace OBJECT_NAMESPACE;

	//int _currentQuantity = 0;
	//std::string Temp;
	//while (1)
	//	{
	//	if (Objects.size() != _currentQuantity)
	//		{
	//		(Objects.size() > _currentQuantity)?(_currentQuantity++):(_currentQuantity--);
	//		_CONSOLE_SCRIPT_FILL_HISTORY("Total amount of objects has changed to " + std::to_string(_currentQuantity));
	//		};
	//	};
	//
	//AfxMessageBox("Drawing thread had been stopped.");
	return 0;
	};

void ARTINTSYSTEMDIALOG::OnEnChangeCommandPanel()
	{
	using namespace OBJECT_NAMESPACE;

	cConsoleInputCommand.GetWindowTextA(_temp, 20);
	_command = _temp;

	if (_command == _CONSOLE_COMMAND_QUIT)
		{
		_CONSOLE_SCRIPT_FILL_HISTORY_AND_CLEAR_INPUT(_CONSOLE_COMMAND_QUIT_COMMENT);
		OnCancel();
		};
	if (_command == _CONSOLE_COMMAND_ADDACTOR)
		{
		_CONSOLE_SCRIPT_FILL_HISTORY_AND_CLEAR_INPUT(_CONSOLE_COMMAND_ADDACTOR_COMMENT);
		Objects.push_back(new Object_Unit(Objects.size()));
		////Create 'Table' Essense
		////Create 'Table' Control having 'Click' event
		////'Click' event is used for getting information about current state of a table
		};
	if (_command == _CONSOLE_COMMAND_ADDTABLE)
		{
		_CONSOLE_SCRIPT_FILL_HISTORY_AND_CLEAR_INPUT(_CONSOLE_COMMAND_ADDTABLE_COMMENT);
		Objects.push_back(new Object_Table(Objects.size()));
		////GUI_Designer->CreateNewUnit(this);
		////Create 'Table' Essense
		////Create 'Table' Control having 'Click' event
		////'Click' event is used for getting information about current state of a table
		//((ListBox ^)(this->Controls["CONSOLE_HISTORY"]))->Items->Add("Unit was added...");
		//((TextBox ^)(this->Controls["CONSOLE_COMMAND_PANEL"]))->Text = "";
		};
	if (_command == _CONSOLE_COMMAND_STARTEMULATION)
		{
		_CONSOLE_SCRIPT_FILL_HISTORY_AND_CLEAR_INPUT(_CONSOLE_COMMAND_STARTEMULATION_COMMENT);
		//Objects.push_back(new Object_Unit());
		////GUI_Designer->CreateNewUnit(this);
		////Create 'Table' Essense
		////Create 'Table' Control having 'Click' event
		////'Click' event is used for getting information about current state of a table
		//((ListBox ^)(this->Controls["CONSOLE_HISTORY"]))->Items->Add("Unit was added...");
		//((TextBox ^)(this->Controls["CONSOLE_COMMAND_PANEL"]))->Text = "";
		};
	if (_command == _CONSOLE_COMMAND_PAUSEEMULATION)
		{
		_CONSOLE_SCRIPT_FILL_HISTORY_AND_CLEAR_INPUT(_CONSOLE_COMMAND_PAUSEEMULATION_COMMENT);
		//Objects.push_back(new Object_Unit());
		////GUI_Designer->CreateNewUnit(this);
		////Create 'Table' Essense
		////Create 'Table' Control having 'Click' event
		////'Click' event is used for getting information about current state of a table
		//((ListBox ^)(this->Controls["CONSOLE_HISTORY"]))->Items->Add("Unit was added...");
		//((TextBox ^)(this->Controls["CONSOLE_COMMAND_PANEL"]))->Text = "";
		};
	if (_command == _CONSOLE_COMMAND_GETINFO)
		{
		_CONSOLE_SCRIPT_FILL_HISTORY_AND_CLEAR_INPUT(_CONSOLE_COMMAND_GETINFO_COMMENT);
		//Objects.push_back(new Object_Unit());
		////GUI_Designer->CreateNewUnit(this);
		////Create 'Table' Essense
		////Create 'Table' Control having 'Click' event
		////'Click' event is used for getting information about current state of a table
		//((ListBox ^)(this->Controls["CONSOLE_HISTORY"]))->Items->Add("Unit was added...");
		//((TextBox ^)(this->Controls["CONSOLE_COMMAND_PANEL"]))->Text = "";
		};
		//ShellExecute(0,0,Application->ExeName.c_str(),0,0,SW_SHOW); //Запускаем новую копию
		//exit(0); //Закрываем старую
	};