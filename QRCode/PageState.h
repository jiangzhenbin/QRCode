#pragma once
#include <functional>

typedef std::function<void(UINT nCtrlId)> ONCLICKED;


// CPageState �Ի���

class CPageState : public CDialogEx
{
	DECLARE_DYNAMIC(CPageState)

public:
	CPageState(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPageState();
	void SetPLCStateText(CString strText, COLORREF color);
	void EnableItem(UINT nCtrlId, BOOL bEnable);
	void SetOnClickedListener(ONCLICKED listener);


private:
	COLORREF m_crBkgnd;
	CBrush   m_brBkgnd;
	COLORREF m_crPlcStateText;
	ONCLICKED m_fOnClicked;


// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE_STATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
