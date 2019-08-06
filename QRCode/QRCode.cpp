
// QRCode.cpp : ����Ӧ�ó��������Ϊ��
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


// CQRCodeApp ����

CQRCodeApp::CQRCodeApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CQRCodeApp ����

CQRCodeApp theApp;


// CQRCodeApp ��ʼ��

BOOL CQRCodeApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));



	// �������ļ�Ŀ¼
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



	// ע���Զ���Ĵ��ڿؼ�
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
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



int CQRCodeApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	BYS_Term();

	return CWinApp::ExitInstance();
}
