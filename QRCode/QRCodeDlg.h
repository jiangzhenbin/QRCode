
// QRCodeDlg.h : ͷ�ļ�
//

#pragma once
#include "../CameraSDK/CameraEngine.h"
#include "VisionProcess.h"
#include "PageInfo.h"
#include "PageTestList.h"
#include "PageTest.h"
#include "PageCurrentResult.h"
#include "PageState.h"
#include <list>
#include "AoiManager.h"
#include "Settings.h"

// CQRCodeDlg �Ի���
class CQRCodeDlg : public CDialogEx
{
// ����
public:
	CQRCodeDlg(CWnd* pParent = NULL);	// ��׼���캯��


private:
	void Resize();
	void ReadSettings(CSettings *pSettings);
	void SaveSettings(CSettings *pSettings);
	void InitAoiManager();
	void SaveCacheCode(CString strFilepath, CString strCode);

public:
	static CQRCodeDlg *m_pThis;
	CAoiManager m_aoiManager;
	BOOL m_bDishStatus[4];
	CString m_strCacheCodeFile;

private:
	CMenu m_menu;
	CPageInfo *m_pPageInfo;
	CPageTestList *m_pPageTestList;
	CPageTest *m_pPageTest[4];
	CPageState *m_pPageState;
	CPageCurrentResult *m_pPageCurrentResult;
	CSettings m_settings;
	int m_nCurrentTest[4];
	unsigned int m_nTestTotal;
	unsigned int m_nNgTotal;
	std::list<unsigned int> m_listCount10s;
	unsigned int m_nTempTotal;


// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QRCODE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;


	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnFileExit();
	afx_msg void OnFileSettings();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnFileResendcode();
	afx_msg void OnUpdateFileResendcode(CCmdUI *pCmdUI);
};
