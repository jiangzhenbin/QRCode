#pragma once


// CPageTest �Ի���

class CPageTest : public CDialogEx
{
	DECLARE_DYNAMIC(CPageTest)

public:
	CPageTest(CWnd* pParent = NULL);   // ��׼���캯��
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
	BOOL		m_bShadow;				// ��Ӱ
	COLORREF	m_crShadowBkgnd;		// ��Ӱ����ɫ(�������ڵ���ɫ)


// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
