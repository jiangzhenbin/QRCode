
// QRCodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QRCode.h"
#include "QRCodeDlg.h"
#include "afxdialogex.h"
#include "..\CommonUI\AccordionWnd.h"
#include "..\MesWebService\MesManager.h"
#include "Utils.h"
#include "SettingsDlg.h"
#include "ResendDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CQRCodeDlg *CQRCodeDlg::m_pThis = NULL;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CQRCodeDlg 对话框



CQRCodeDlg::CQRCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_QRCODE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pPageInfo = NULL;
	m_pPageTestList = NULL;
	m_pPageState = NULL;
	m_pPageCurrentResult = NULL;
	for (int i = 0; i < 4; i++) {
		m_pPageTest[i] = NULL;
		m_nCurrentTest[i] = 0;
	}

	m_nTestTotal = 0;
	m_nNgTotal = 0;
	m_nTempTotal = 0;
}

void CQRCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CQRCodeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_FILE_EXIT, &CQRCodeDlg::OnFileExit)
	ON_COMMAND(ID_FILE_SETTINGS, &CQRCodeDlg::OnFileSettings)
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_RESENDCODE, &CQRCodeDlg::OnFileResendcode)
	ON_UPDATE_COMMAND_UI(ID_FILE_RESENDCODE, &CQRCodeDlg::OnUpdateFileResendcode)
END_MESSAGE_MAP()


// CQRCodeDlg 消息处理程序

BOOL CQRCodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	ReadSettings(&m_settings);
	m_nTestTotal = m_settings.m_nTestTotal;
	m_nNgTotal = m_settings.m_nNgCount;
	m_strCacheCodeFile.Format(_T("%s\\CacheCode.txt"), theApp.m_strAppDir);


	// 检查相机是否匹配  chen BoounionSoft
	BOOL bValidCamera = TRUE;
#if 1
	for (auto item : m_settings.m_mapCameraSN) {
		CString strSN = item.second.c_str();
		strSN = strSN.Right(3);
		strSN.Format(_T("%d"), atoi(strSN) + 111);
		strSN = strSN.Right(3);
		if (m_settings.m_strCameraKey.Find(strSN) < 0) {
			bValidCamera = FALSE;
			break;
		}
	}
#endif
	if (!bValidCamera) {
		AfxMessageBox(_T("无效的相机或连接相机出错，请联系管理员协助解决问题！"));
		PostMessage(WM_CLOSE);
	}


	// 初始化左侧栏
	CString strExpandIcon, strCloseIcon;
	strExpandIcon.Format(_T("%s\\res\\arrow_down.ico"), theApp.m_strAppDir);
	strCloseIcon.Format(_T("%s\\res\\arrow_right.ico1"), theApp.m_strAppDir);

	CAccordionWnd *m_pAccordionWnd = CAccordionWnd::FromHandle(GetDlgItem(IDC_ACCORDION_WND1)->m_hWnd);
	m_pAccordionWnd->SetFrameColor(RGB(220, 220, 220), TRUE);
	m_pAccordionWnd->Setpadding(PADDING_LEFT, 2);
	m_pAccordionWnd->Setpadding(PADDING_TOP, 2);
	m_pAccordionWnd->Setpadding(PADDING_RIGHT, 2);
	m_pAccordionWnd->Setpadding(PADDING_BOTTOM, 2);
	m_pAccordionWnd->LoadExpandIcon(strExpandIcon, strCloseIcon);

	m_pPageInfo = new CPageInfo();
	m_pPageInfo->SetSettingsPtr(&m_settings);
	m_pPageInfo->Create(IDD_PAGE_INFO, GetDlgItem(IDC_ACCORDION_WND1));
	m_pPageInfo->ShowWindow(SW_SHOW);
	m_pAccordionWnd->AddItem("生产信息", m_pPageInfo, 0, TRUE, FALSE);

	
	m_pPageState = new CPageState();
	m_pPageState->Create(IDD_PAGE_STATE, GetDlgItem(IDC_ACCORDION_WND1));
	m_pPageState->ShowWindow(SW_SHOW);
	m_pPageState->EnableItem(IDC_BUTTON_STOP, FALSE);
	m_pPageState->SetOnClickedListener([&](UINT nCtrlId) -> void {
		if (nCtrlId == IDC_BUTTON_START) {
			m_pPageState->EnableItem(IDC_BUTTON_START, FALSE);
			m_pPageState->EnableItem(IDC_BUTTON_STOP, TRUE);
			m_aoiManager.ExecuteAoi(TRUE);
			SetTimer(3, 10*1000, NULL);
		}
		else if (nCtrlId == IDC_BUTTON_STOP) {
			m_pPageState->EnableItem(IDC_BUTTON_START, TRUE);
			m_pPageState->EnableItem(IDC_BUTTON_STOP, FALSE);
			m_aoiManager.ExecuteAoi(FALSE);
			KillTimer(3);
		}
	});
	m_pAccordionWnd->AddItem("状态", m_pPageState, 0, TRUE, FALSE);
	

	m_pPageCurrentResult = new CPageCurrentResult();
	m_pPageCurrentResult->SetIndicatorCount(m_settings.m_nEnableCameraCount);
	m_pPageCurrentResult->Create(IDD_PAGE_CURRENTRESULT, GetDlgItem(IDC_ACCORDION_WND1));
	m_pPageCurrentResult->ShowWindow(SW_SHOW);
	m_pAccordionWnd->AddItem("当前检测", m_pPageCurrentResult, 0, TRUE, FALSE);


	m_pPageTestList = new CPageTestList();
	m_pPageTestList->Create(IDD_PAGE_TESTLIST, GetDlgItem(IDC_ACCORDION_WND1));
	m_pPageTestList->ShowWindow(SW_SHOW);
	m_pAccordionWnd->AddItem("检测列表", m_pPageTestList, -1, TRUE, FALSE);


	// 四个图像预览框
	for (int i = 0; i < 4; i++) {
		m_pPageTest[i] = new CPageTest();
		m_pPageTest[i]->Create(IDD_DIALOG_TEST, this);
		m_pPageTest[i]->SetTopTextl2(_T(""));
		m_pPageTest[i]->ShowWindow(SW_SHOW);
	}


	// 加载菜单资源
	m_menu.LoadMenu(IDR_MENU1);
	this->SetMenu(&m_menu);
	ShowWindow(SW_MAXIMIZE);


	// init
	SetTimer(1, 750, NULL);
	SetTimer(4, 5000, NULL);
	SetTimer(99, 500, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CQRCodeDlg::InitAoiManager()
{
	auto onPlcStateChanged = [&](PLCSTATE state) -> void {
		if (m_pPageState != NULL) {
			if (state == PLCSTATE::CONNECTED) {
				m_pPageState->SetPLCStateText(_T("PLC已连接！"), RGB(34, 177, 75));
			}
			else if (state == PLCSTATE::DISCONNECTED) {
				m_pPageState->SetPLCStateText(_T("PLC已断开！"), RGB(255, 0, 0));
			}
			else if (state == PLCSTATE::ACTIVE) {
				static int i = 0; i++; i = i % 4;
				static char *pText[] = { "|", "/", "-", "\\" };
				CString strText;
				strText.Format(_T("PLC已连接(%s)！"), pText[i]);
				m_pPageState->SetPLCStateText(strText, RGB(34, 177, 75));
			}
		}
	};
	m_aoiManager.SetOnPlcStateChangedListener(onPlcStateChanged);

	auto onGetNewCode = [&](CQRCode *pQRCode) -> void {
		if (m_pPageTestList != NULL) {
			m_pPageTestList->AppedCode(pQRCode);
		}

		static BYTE byteFlag[4] = { 0x01, 0x02, 0x03, 0x04 };
		static DWORD dwLastTickCount = 0;
		if (pQRCode->dwTickCount - dwLastTickCount > m_settings.m_nAoiMaxTickCount) {
			for (int i = 0; i < 4; i++) {
				m_bDishStatus[i] = FALSE;
				m_nCurrentTest[i] = 2;
			}

			SetTimer(2, m_settings.m_nAoiMaxTickCount, NULL);
			dwLastTickCount = pQRCode->dwTickCount;
		}
		m_nCurrentTest[pQRCode->cameraId - 1] = 1;
		m_bDishStatus[pQRCode->cameraId - 1] = m_aoiManager.m_dishAnalyse.GetResult(clock()) & byteFlag[pQRCode->cameraId - 1];


		if (m_pPageTest[pQRCode->cameraId - 1] != NULL) {
			m_pPageTest[pQRCode->cameraId - 1]->SetTopTextl(pQRCode->code);
		}
	};
	m_aoiManager.SetOnNewCodeListener(onGetNewCode);

	auto onCodeStateChanged = [&](CQRCode *pQRCode) -> void {
		if (m_pPageTestList != NULL) {
			m_pPageTestList->UpdateCodeState(pQRCode);
		}

		/*
		if (m_pPageCurrentResult != NULL && pQRCode->state == CODESTATE::FAILED) {
			m_nCurrentTest[pQRCode->cameraId - 1] = 3;
			m_pPageCurrentResult->SetStates(pQRCode->cameraId-1, 3);
		}
		*/

		if (pQRCode->state == CODESTATE::FAILED) {
			m_nCurrentTest[pQRCode->cameraId - 1] = 3;
			m_aoiManager.Alert();
			SaveCacheCode(m_strCacheCodeFile, pQRCode->code);
		}

	};
	m_aoiManager.SetOnCodeStateChangedListener(onCodeStateChanged);

	HWND hWnd[4] = { NULL };
	for (int i = 0; i < 4; i++) {
		hWnd[i] = m_pPageTest[i]->GetGraphWnd();
	}
	m_aoiManager.SetWindows(hWnd, 4);
	m_aoiManager.SetSettingsPtr(&m_settings);
	m_aoiManager.Init();
}

void CQRCodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQRCodeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CQRCodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CQRCodeDlg::OnDestroy()
{
	SaveSettings(&m_settings);
	m_aoiManager.SetOnNewCodeListener(nullptr);
	m_aoiManager.SetOnCodeStateChangedListener(nullptr);
	m_aoiManager.UnInit();


	if (m_pPageInfo != NULL) {
		m_pPageInfo->DestroyWindow();
		delete m_pPageInfo;
		m_pPageInfo = NULL;
	}

	if (m_pPageTestList != NULL) {
		m_pPageTestList->DestroyWindow();
		delete m_pPageTestList;
		m_pPageTestList = NULL;
	}

	if (m_pPageState != NULL) {
		m_pPageState->DestroyWindow();
		delete m_pPageState;
		m_pPageState = NULL;
	}
	
	if (m_pPageCurrentResult != NULL) {
		m_pPageCurrentResult->DestroyWindow();
		delete m_pPageCurrentResult;
		m_pPageCurrentResult = NULL;
	}

	for (int i = 0; i < 4; i++) {
		if (m_pPageTest[i] != NULL) {
			m_pPageTest[i]->DestroyWindow();
			delete m_pPageTest[i];
			m_pPageTest[i] = NULL;
		}
	}

	CDialogEx::OnDestroy();
}



BOOL CQRCodeDlg::PreTranslateMessage(MSG* pMsg)
{
	// 防止按Esc或回车键退出程序
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) {
		return TRUE;
	}

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		return TRUE;
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}

#define LEFT_BAR_WIDTH		400
#define MIN_BLOCK_WIDE		300

void CQRCodeDlg::Resize()
{
	CWnd *pItem;
	pItem = GetDlgItem(IDC_ACCORDION_WND1);
	if (pItem == NULL && m_pPageTest[0] == NULL) {
		return;
	}

	CRect rcClient, rcItem;
	GetClientRect(&rcClient);

	int x = 12;
	pItem->MoveWindow(x, 12, LEFT_BAR_WIDTH, rcClient.Height() - 12 * 2);
	x += 400;
	x += 12;


	BOOL bShowOne = FALSE;
	if (bShowOne) {
		int nRemainHeight = rcClient.Height() - 12 * 2;
		int nRemainWidth = rcClient.Width() - x - 12;
		m_pPageTest[0]->MoveWindow(x, 12, nRemainWidth, nRemainHeight);
		m_pPageTest[1]->ShowWindow(SW_HIDE);
		m_pPageTest[2]->ShowWindow(SW_HIDE);
		m_pPageTest[3]->ShowWindow(SW_HIDE);
	}
	else {
		// 如果右侧剩余空间小于MIN_BLOCK_WIDE， 则显示一列(2个或1个框)
		if (rcClient.Width() - 12 - LEFT_BAR_WIDTH < MIN_BLOCK_WIDE * 2) {

			// 如果高剩余是宽的1.5倍以上，则显示两行，否则显示一行
			int nRemainHeight = rcClient.Height() - 12 * 2;
			int nRemainWidth = rcClient.Width() - x - 12;
			if (nRemainHeight >= 2 * MIN_BLOCK_WIDE) {
				int nBlockWidth = rcClient.Width() - x - 12;
				int nBlockHeight = (nRemainHeight - 12) / 2;
				m_pPageTest[0]->ShowWindow(SW_SHOW);
				m_pPageTest[0]->MoveWindow(x, 12, nBlockWidth, nBlockHeight);
				m_pPageTest[1]->ShowWindow(SW_SHOW);
				m_pPageTest[1]->MoveWindow(x, 12 + nBlockHeight + 12, nBlockWidth, nBlockHeight);
				m_pPageTest[2]->ShowWindow(SW_HIDE);
				m_pPageTest[3]->ShowWindow(SW_HIDE);
			}
			else {
				m_pPageTest[0]->ShowWindow(SW_SHOW);
				m_pPageTest[0]->MoveWindow(x, 12, rcClient.Width() - x - 12, rcClient.Height() - 12 * 2);
				m_pPageTest[1]->ShowWindow(SW_HIDE);
				m_pPageTest[2]->ShowWindow(SW_HIDE);
				m_pPageTest[3]->ShowWindow(SW_HIDE);
			}
		}
		else {
			// 否则显示2列
			// 如果高剩余是宽的1.5倍以上，则显示两行，否则显示一行
			int nRemainHeight = rcClient.Height() - 12 * 2;
			int nRemainWidth = rcClient.Width() - x - 12 * 2;
			if (nRemainHeight >= 2 * MIN_BLOCK_WIDE) {
				int nBlockWidth = (nRemainWidth - 12) / 2;
				int nBlockHeight = (nRemainHeight - 12) / 2;

				m_pPageTest[0]->ShowWindow(SW_SHOW);
				m_pPageTest[0]->MoveWindow(x, 12, nBlockWidth, nBlockHeight);
				m_pPageTest[1]->ShowWindow(SW_SHOW);
				m_pPageTest[1]->MoveWindow(x + nBlockWidth + 12, 12, nBlockWidth, nBlockHeight);
				m_pPageTest[2]->ShowWindow(SW_SHOW);
				m_pPageTest[2]->MoveWindow(x, 12 + nBlockHeight + 12, nBlockWidth, nBlockHeight);
				m_pPageTest[3]->ShowWindow(SW_SHOW);
				m_pPageTest[3]->MoveWindow(x + nBlockWidth + 12, 12 + nBlockHeight + 12, nBlockWidth, nBlockHeight);
			}
			else {
				int nBlockWidth = (nRemainWidth - 12) / 2;
				int nBlockHeight = nRemainHeight;
				m_pPageTest[0]->ShowWindow(SW_SHOW);
				m_pPageTest[0]->MoveWindow(x, 12, nBlockWidth, nBlockHeight);
				m_pPageTest[1]->ShowWindow(SW_SHOW);
				m_pPageTest[1]->MoveWindow(x + nBlockWidth + 12, 12, nBlockWidth, nBlockHeight);
				m_pPageTest[2]->ShowWindow(SW_HIDE);
				m_pPageTest[3]->ShowWindow(SW_HIDE);
			}
		}
	}
}

void CQRCodeDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	Resize();
}


void CQRCodeDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CDialogEx::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	ASSERT(pPopupMenu != NULL);
	// Check the enabled state of various menu items.

	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// Determine if menu is popup in top-level menu and set m_pOther to
	// it if so (m_pParentMenu == NULL indicates that it is secondary popup).
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL) {
		CWnd* pParent = this;
		if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL) {
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++) {
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu) {
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}

	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
		state.m_nIndex++) {
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // Menu separator or invalid cmd - ignore it.

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1) {
			// Possibly a popup menu, route to first item of that popup.
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;       // First item of popup can't be routed to.
			}
			state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
		}
		else {
			// Normal menu item.
			// Auto enable/disable if frame window has m_bAutoMenuEnable
			// set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE);
		}

		// Adjust for menu deletions and additions.
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax) {
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID) {
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}



void CQRCodeDlg::OnFileExit()
{
	// TODO: 在此添加命令处理程序代码
	PostMessage(WM_CLOSE);
}


void CQRCodeDlg::OnFileSettings()
{
	CSettingsDlg dlg;
	dlg.SetSettingsPtr(&m_settings);
	if (IDOK == dlg.DoModal()) {
		SaveSettings(&m_settings);
		m_nTestTotal = m_settings.m_nTestTotal;
		m_nNgTotal = m_settings.m_nNgCount;
		m_pPageInfo->SettingsChanged();
	}
}

void CQRCodeDlg::ReadSettings(CSettings *pSettings)
{
	char szBuffer[256];
	CString strAppIni;
	strAppIni.Format("%s\\%s.ini", theApp.m_strAppDir, theApp.m_strAppFile);


	GetPrivateProfileString(_T("Settings"), _T("ProductModel"), _T("P007"), szBuffer, sizeof(szBuffer), strAppIni);
	pSettings->m_strProductModel = szBuffer;

	pSettings->m_nTestTotal = GetPrivateProfileInt(_T("Settings"), _T("TestTotal"), 0, strAppIni);
	pSettings->m_nNgCount = GetPrivateProfileInt(_T("Settings"), _T("NgCount"), 0, strAppIni);

	pSettings->m_codeType = GetPrivateProfileInt(_T("Settings"), _T("CodeType"), 0, strAppIni);         /* jiang, Barcode Type */

	pSettings->m_nCodeLengthFilterType = GetPrivateProfileInt(_T("Settings"), _T("CodeLengthFilterType"), 0, strAppIni);
	pSettings->m_nCodeLengthFileterValue = GetPrivateProfileInt(_T("Settings"), _T("CodeLengthFileterValue"), 27, strAppIni);
	pSettings->m_nCameraExposureTime = GetPrivateProfileInt(_T("Settings"), _T("CameraExprose"), 1000, strAppIni);


	// 相机顺序
	pSettings->m_nEnableCameraCount = GetPrivateProfileInt(_T("Cameras"), _T("EnableCamera"), 4, strAppIni);
	CString strCameraIndex;
	for (int i = 0; i < pSettings->m_nEnableCameraCount; i++) {
		strCameraIndex.Format(_T("Camera%d"), i+1);
		GetPrivateProfileString(_T("Cameras"), strCameraIndex, _T("CAMER00007"), szBuffer, sizeof(szBuffer), strAppIni);
		pSettings->m_mapCameraSN[i+1] = szBuffer;
	}
	GetPrivateProfileString(_T("Settings"), _T("Time"), _T("118118118118"), szBuffer, sizeof(szBuffer), strAppIni);
	pSettings->m_strCameraKey = szBuffer;
	GetPrivateProfileString(_T("Cameras"), _T("FrameRate"), _T("7"), szBuffer, sizeof(szBuffer), strAppIni);
	pSettings->m_fFrameRate = atof(szBuffer);


	// aoi
	pSettings->m_bDishCheck = GetPrivateProfileInt(_T("AOI"), _T("DishCheck"), 1, strAppIni) > 0;
	pSettings->m_nAoiMaxTickCount = GetPrivateProfileInt(_T("AOI"), _T("MaxTickCount"), 700, strAppIni);
	pSettings->m_nQRCodeBufferSize = GetPrivateProfileInt(_T("AOI"), _T("QRCodeBufferSize"), 12, strAppIni);

	// mes
	GetPrivateProfileString(_T("Mes"), _T("EndPoint"), _T("http://10.1.100.52/meswebservice/Print.asmx"), pSettings->m_szMesEndPoint, sizeof(pSettings->m_szMesEndPoint), strAppIni);
	GetPrivateProfileString(_T("Mes"), _T("UVId"), _T("001#"), pSettings->szUVId, sizeof(pSettings->szUVId), strAppIni);
}

void CQRCodeDlg::SaveSettings(CSettings *pSettings)
{
	CString strAppIni, strValue;
	strAppIni.Format("%s\\%s.ini", theApp.m_strAppDir, theApp.m_strAppFile);


	WritePrivateProfileString(_T("Settings"), _T("ProductModel"), pSettings->m_strProductModel, strAppIni);
	
	strValue.Format(_T("%d"), pSettings->m_nTestTotal);
	WritePrivateProfileString(_T("Settings"), _T("TestTotal"), strValue, strAppIni);

	strValue.Format(_T("%d"), pSettings->m_nNgCount);
	WritePrivateProfileString(_T("Settings"), _T("NgCount"), strValue, strAppIni);

	strValue.Format(_T("%d"), pSettings->m_nCodeLengthFilterType);
	WritePrivateProfileString(_T("Settings"), _T("CodeLengthFilterType"), strValue, strAppIni);

	strValue.Format(_T("%d"), pSettings->m_nCodeLengthFileterValue);
	WritePrivateProfileString(_T("Settings"), _T("CodeLengthFileterValue"), strValue, strAppIni);

	strValue.Format(_T("%d"), pSettings->m_nCameraExposureTime);
	WritePrivateProfileString(_T("Settings"), _T("CameraExprose"), strValue, strAppIni);

	WritePrivateProfileString(_T("MES"), _T("EndPoint"), pSettings->m_szMesEndPoint, strAppIni);
}


void CQRCodeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1) {
		KillTimer(1);
		InitAoiManager();
	}


	else if (nIDEvent == 2) {
		KillTimer(2);

		BOOL bAlert = FALSE;
		for (int i = 0; i < m_settings.m_nEnableCameraCount; i++) {

			if ((m_nCurrentTest[i] == 2 || m_nCurrentTest[i] == 3) && ((m_bDishStatus[i] && m_settings.m_bDishCheck)
				|| !m_settings.m_bDishCheck)) {
				m_nNgTotal++;
				if (m_pPageTest[i] != NULL) {
					m_pPageTest[i]->SetTopTextl2(_T(""));
				}

				bAlert = TRUE;
			}

			m_nTestTotal++;
		}


		if (bAlert) {
			m_aoiManager.Alert();
		}


		if (m_pPageInfo != NULL) {
			m_pPageInfo->SetTotal(m_nTestTotal);
			m_pPageInfo->SetNgCount(m_nNgTotal);
			m_settings.m_nTestTotal = m_nTestTotal;
			m_settings.m_nNgCount = m_nNgTotal;
		}


		if (m_pPageCurrentResult != NULL) {
			m_pPageCurrentResult->SetStates(m_nCurrentTest, 4);
		}
	}


	else if (nIDEvent == 3) {
		static unsigned int nLastTotal = m_nTestTotal;
		int nCurrentCount = m_nTestTotal - nLastTotal;
		m_nTempTotal += nCurrentCount;
		m_listCount10s.push_back(nCurrentCount);
		if (m_listCount10s.size() > 20) {
			int nFront = m_listCount10s.front();
			m_listCount10s.pop_front();
			m_nTempTotal -= nFront;
		}

		unsigned int nSpeed = unsigned int((double)m_nTempTotal / ((double)m_listCount10s.size() * 10.0) * 3600.0);
		if (m_pPageInfo != NULL) {
			m_pPageInfo->SetSpeed1H(nSpeed);
		}

		nLastTotal = m_nTestTotal;
	}


	else if (nIDEvent == 4) {
		KillTimer(4);

		CString strFilepath = "d:\\123.bin";
		CFile file;
		if (file.Open(strFilepath, CFile::modeRead) ){
			file.Close();

			m_aoiManager.TransferFile(strFilepath, "10.1.13.48");
		}
	}

	else if (nIDEvent == 99) {
		m_aoiManager.Heart();
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CQRCodeDlg::OnFileResendcode()
{
	ONCODESTATECHANGED listener = m_aoiManager.GetOnCodeStateChangedListener();

	CResendDlg dlg;
	dlg.SetAoiManager(&m_aoiManager);
	dlg.DoModal();

	m_aoiManager.SetOnCodeStateChangedListener(listener);
}


void CQRCodeDlg::OnUpdateFileResendcode(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_aoiManager.IsAoiExecute());
}

void CQRCodeDlg::SaveCacheCode(CString strFilepath, CString strCode)
{
	CStdioFile file;
	if (!file.Open(strFilepath, CFile::modeWrite)) {
		if (!file.Open(strFilepath, CFile::modeCreate | CFile::modeWrite)) {
			return;
		}
	}

	file.SeekToEnd();
	file.WriteString(strCode + "\r\n");
	file.Close();
}
