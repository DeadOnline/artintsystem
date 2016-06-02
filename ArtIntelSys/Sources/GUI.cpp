#include "stdafx.h"
#include "ALL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char _temp[20] = {};
std::string _command;

BEGIN_MESSAGE_MAP(GUI, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(CONSOLE_COMMAND_PANEL, &GUI::OnEnChangeCommandPanel)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CScreen, CStatic)							// таблица откликов на сообщени€
	ON_WM_MOUSEMOVE()										// средн€€ кнопка отпущена
	ON_WM_PAINT()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CConsole, CListBox)							// таблица откликов на сообщени€
	ON_WM_MOUSEMOVE()										// средн€€ кнопка отпущена
END_MESSAGE_MAP()

void	CScreen::OnPaint()
	{
	((GUI*) Parent)->DirectXDraw();
	((GUI*) Parent)->ConsoleRecording();
	};

void	CConsole::OnPaint()
	{
	//((GUI*) Parent)->ConsoleRecording();
	};

		GUI::GUI(CWnd* pParent): CDialogEx(GUI::IDD, pParent), MODULE_BASE(NULL), Smth(NULL), m_hIcon(NULL)
			{
			m_hIcon = AfxGetApp()->LoadIcon(MAINFRAMEICON);
			}
		GUI::GUI(ARTINTSYSTEMAPPLICATION* _parentClass, CWnd* pParent): CDialogEx(GUI::IDD, pParent), MODULE_BASE(_parentClass), Smth(NULL), m_hIcon(NULL)
			{
			m_hIcon = AfxGetApp()->LoadIcon(MAINFRAMEICON);
			};
void	GUI::DoDataExchange(CDataExchange* pDX)
	{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, CONSOLE_COMMAND_PANEL, controlConsoleInputCommand);
	DDX_Control(pDX, CONSOLE_HISTORY, controlConsoleHistory);
	DDX_Control(pDX, GRAPHIC_REPRESENTATION, controlConsoleGraphic);
	}
BOOL	GUI::OnInitDialog()
	{
	CDialogEx::OnInitDialog();
	controlConsoleGraphic.Set_Parent(this);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	Smth = this->GetDlgItem(GRAPHIC_REPRESENTATION);
	if (!D3D)
		{
		Initiate_D3D(Smth->GetSafeHwnd());
		Initiate_Device(Smth->GetSafeHwnd(), false, 515, 290);
		Initiate_MaterialsAndTextures();
		Fill_Grid(10, 8, D3DXCOLOR(120, 70, 60, 0));
		Load_Geometry(_ACTOR);
		Load_Geometry(_SEA);
		Load_Geometry(_WOOD);
		Load_Geometry(_ROPE);
		Load_Geometry(_LAND);
		Load_Geometry(_FOOD);
		Load_Geometry(_BODY);
		Load_Geometry(_EYE);
		Initiate_Text("DXGameMaker", 0, CRect(10, 160, 300, 100));
		Initiate_Color(0xff0000ff, 0);
		}
	RECT  _rect;
	((CStatic *) Smth)->GetWindowRect(&_rect);
	Initiate_Camera(_rect.right-_rect.left, _rect.bottom-_rect.top, 8, 8, -15);
	Camera->Fill_Matrix_Camera(DEVICE);
	Camera->Fill_Matrix_Projection(DEVICE);

	return TRUE;  // return TRUE  unless you set the focus to a control
	};
void	GUI::DirectXDraw()
	{
		{
		FPS.Time_End = GetTickCount64() - FPS.Time_Start; FPS.Time_Start = GetTickCount64();
		FPS.FrameCnt++; FPS.TimeElapsed += (FPS.Time_End/1000);
		if(FPS.TimeElapsed >= 1.0f)
			{
			FPS.fps = (float)FPS.FrameCnt / FPS.TimeElapsed;
			FPS.TimeElapsed = 0.0f;
			FPS.FrameCnt = 0;
			}
		char Dest[60]; sprintf_s(Dest, "%s","DXGameMaker "); sprintf(Dest+12, "%f", FPS.fps);
		Text->Change_TextString((LPCSTR) Dest);
		}
	Camera->SetPresentation(DEVICE, 0.3);
	Camera->Fill_Matrix_Camera(DEVICE);
	DEVICE->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(220,220,220,0), 1.0f, 0 );
	DEVICE->BeginScene();
	Render_Grid();
	Render_Text(Text);
	Render_Meshes();
	Render_UpScreen();
	DEVICE->EndScene();
	DEVICE->Present(NULL, NULL, NULL, NULL);
	};
void	GUI::OnPaint()
	{
	if ( IsIconic() )
		{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>( dc.GetSafeHdc() ), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = ( rect.Width() - cxIcon + 1 ) / 2;
		int y = ( rect.Height() - cyIcon + 1 ) / 2;
		dc.DrawIcon(x, y, m_hIcon);
		}
	else
		{
		CDialog::OnPaint();
		};
	};
void	GUI::ConsoleRecording()
	{
	string h = _GET_LOG_GET_RECORD;
	if (h != "")
		_GET_GUI_CONSOLE_MAKE_RECORD(h.c_str());
	};
void	GUI::Module_Init() 
	{
	this->DoModal();
	};
void	GUI::Module_Run() { };
void	GUI::Module_Destroy() { };
HCURSOR GUI::OnQueryDragIcon()
	{
	return static_cast<HCURSOR>(m_hIcon);
	}
void	GUI::OnEnChangeCommandPanel()
	{
	using namespace WORLD::OBJECTS;

	controlConsoleInputCommand.GetWindowTextA(_temp, 40);
	_command = _temp;

	if (_command == _CONSOLE_COMMAND_QUIT)
		{
		_GET_LOG_MAKE_RECORD(_CONSOLE_COMMAND_QUIT_COMMENT, false);
		OnOK();
		};
	if (_command == _CONSOLE_COMMAND_ADDACTOR)
		{
		_GET_LOG_MAKE_RECORD(_CONSOLE_COMMAND_ADDACTOR_COMMENT, true);
		controlConsoleInputCommand.SetWindowTextA("");
		WORLD::OBJECTS::OBJECTS_REGISTRY::OBJECT_UNIT::Start(_ACTOR, Vector3D(2, 4, 4));
		};
	if (_command == _CONSOLE_COMMAND_ADDWATER)
		{
		_GET_LOG_MAKE_RECORD(_CONSOLE_COMMAND_ADDACTOR_COMMENT, true);
		controlConsoleInputCommand.SetWindowTextA("");
		WORLD::OBJECTS::OBJECTS_REGISTRY::OBJECT_WATER::Start(_SEA, Vector3D(rand() % 10, rand() % 10, rand() % 10));
		};
	//if (_command == _CONSOLE_COMMAND_ADDLAND)
	//	{
	//	_GUI_CONSOLE_SCRIPT_FILL_HISTORY_AND_CLEAR_INPUT(_CONSOLE_COMMAND_ADDLAND_COMMENT);
	//	new WORLD::OBJECTS::OBJECTS_REGISTRY::OBJECT_SOIL(0, _OBJ4);
	//	};
	//if (_command == _CONSOLE_COMMAND_ADDFOOD)
	//	{
	//	_GUI_CONSOLE_SCRIPT_FILL_HISTORY_AND_CLEAR_INPUT(_CONSOLE_COMMAND_ADDFOOD_COMMENT);
	//	new WORLD::OBJECTS::OBJECTS_REGISTRY::OBJECT_FOOD(0, _OBJ2);
	//	};
	//if (_command == _CONSOLE_COMMAND_STARTEMULATION)
	//	{
	//	_GUI_CONSOLE_SCRIPT_FILL_HISTORY_AND_CLEAR_INPUT(_CONSOLE_COMMAND_STARTEMULATION_COMMENT);
	//	};
	//if (_command == _CONSOLE_COMMAND_PAUSEEMULATION)
	//	{
	//	_GUI_CONSOLE_SCRIPT_FILL_HISTORY_AND_CLEAR_INPUT(_CONSOLE_COMMAND_PAUSEEMULATION_COMMENT);
	//	};
	//if (_command == _CONSOLE_COMMAND_GETINFO)
	//	{
	//	_GUI_CONSOLE_SCRIPT_FILL_HISTORY_AND_CLEAR_INPUT(_CONSOLE_COMMAND_GETINFO_COMMENT);
	//	};
	};