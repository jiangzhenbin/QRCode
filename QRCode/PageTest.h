#pragma once


// CPageTest 对话框

class CPageTest : public CDialogEx
{
	DECLARE_DYNAMIC(CPageTest)

public:
	CPageTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPageTest();


public:
	HWND GetGraphWnd();
	void SetTopTextl(CString &strText);
	void SetTopTextl2(CString strText);
	void RoiPoint2WndPoint(int imgWidth, int imgHeight, double x, double y, LPPOINT pt);

private:
	void Resize();


private:
	COLORREF	m_crBkgnd;
	CBrush		m_brBkgnd;
	COLORREF	m_crFrame;
	BOOL		m_bShadow;				// 阴影
	COLORREF	m_crShadowBkgnd;		// 阴影背景色(即父窗口的颜色)


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnNcPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
