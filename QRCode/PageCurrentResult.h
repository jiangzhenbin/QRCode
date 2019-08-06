#pragma once
#include "..\CommonUI\\IndicatorListWnd.h"


// CPageCurrentResult �Ի���

class CPageCurrentResult : public CDialogEx
{
	DECLARE_DYNAMIC(CPageCurrentResult)

public:
	CPageCurrentResult(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPageCurrentResult();
	void SetIndicatorCount(int nCount);
	void SetStates(int *pnState, int size);
	void SetStates(int index, int nState);

private:
	void Resize();


private:
	int m_nIndicatorCount;
	CIndicatorListWnd *m_pIndicatorListWnd;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE_CURRENTRESULT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
