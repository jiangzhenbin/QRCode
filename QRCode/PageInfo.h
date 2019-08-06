#pragma once
#include "Settings.h"


// CPageInfo 对话框

class CPageInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CPageInfo)

public:
	CPageInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPageInfo();
	void SetSettingsPtr(CSettings *pSettings);
	void SettingsChanged();
	void SetTotal(unsigned int nTotal);
	void SetNgCount(unsigned int nCount);
	void SetSpeed1H(unsigned int nCount);

private:
	COLORREF m_crBkgnd;
	CBrush   m_brBkgnd;


private:
	CSettings *m_pSettings;


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
