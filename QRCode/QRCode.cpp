
// QRCode.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "QRCode.h"
#include "QRCodeDlg.h"
#include "..\CommonUI\AccordionWnd.h"
#include "..\CommonUI\MilPreview.h"
#include "..\CommonUI\IndicatorListWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQRCodeApp

BEGIN_MESSAGE_MAP(CQRCodeApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CQRCodeApp 构造

CQRCodeApp::CQRCodeApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CQRCodeApp 对象

CQRCodeApp theApp;


// CQRCodeApp 初始化

BOOL CQRCodeApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));



	// 本程序文件目录
	TCHAR sDrive[_MAX_DRIVE];
	TCHAR sDir[_MAX_DIR];
	TCHAR sFilename[_MAX_FNAME], sAppFilename[_MAX_FNAME];
	TCHAR sExt[_MAX_EXT];
	GetModuleFileName(AfxGetInstanceHandle(), sAppFilename, _MAX_PATH);
	_tsplitpath_s(sAppFilename, sDrive, sDir, sFilename, sExt);
	m_strAppDir = CString(sDrive) + CString(sDir);
	if (m_strAppDir.Right(1) != _T("\\"))
		m_strAppDir += _T("\\");
	m_strAppFile = CString(sFilename);



	// 注册自定义的窗口控件
	CAccordionWnd::RegisterWndClass();
	CMilPreview::RegisterWndClass();
	CIndicatorListWnd::RegisterWndClass();
	CreateMutexA(NULL, FALSE, "BYSocketDLL_UserLeavel_1006345UUOPafd");
	int nRet = BYS_Initialize(NULL);


	CQRCodeDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



int CQRCodeApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	BYS_Term();

	return CWinApp::ExitInstance();
}
