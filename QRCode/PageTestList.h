#pragma once
#include "AoiManager.h"
#include "CustomListCtrl.h"


// CPageTestList �Ի���

class CPageTestList : public CDialogEx
{
	DECLARE_DYNAMIC(CPageTestList)

public:
	CPageTestList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPageTestList();


public:
	void AppedCode(CQRCode *pQRCode);
	void UpdateCodeState(CQRCode *pQRCode);
	static CString GetQRCodeStateText(CODESTATE state);


private:
	void Resize();
	static CString GetShortCode(CString &strCode);


private:
	COLORREF m_crBkgnd;
	CBrush   m_brBkgnd;
	CCustomListCtrl m_wndListQRCode;
	COLORREF m_crStateBkgnd[4];
	COLORREF m_crStateText[4];

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE_TESTLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
