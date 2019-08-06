// PageCurrentResult.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QRCode.h"
#include "PageCurrentResult.h"
#include "afxdialogex.h"


// CPageCurrentResult �Ի���

IMPLEMENT_DYNAMIC(CPageCurrentResult, CDialogEx)

CPageCurrentResult::CPageCurrentResult(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE_CURRENTRESULT, pParent)
{
	m_pIndicatorListWnd = NULL;
	m_nIndicatorCount = 4;
}

CPageCurrentResult::~CPageCurrentResult()
{
}

void CPageCurrentResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageCurrentResult, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
END_MESSAGE_MAP()


void CPageCurrentResult::SetIndicatorCount(int nCount)
{
	m_nIndicatorCount = nCount;
}

void CPageCurrentResult::SetStates(int index, int nState)
{
	if (index < 4) {
		m_pIndicatorListWnd->SetItemState(index, nState);
	}
}

void CPageCurrentResult::SetStates(int *pnState, int size)
{
	for (int i = 0; i < size; i++) {
		m_pIndicatorListWnd->SetItemState(i, pnState[i]);
		if (i >= 4) {
			break;
		}
	}
}

// CPageCurrentResult ��Ϣ�������


BOOL CPageCurrentResult::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Resize();

	
	// �Ŀ��Ĳ��Խ��ָʾ
	m_pIndicatorListWnd = CIndicatorListWnd::FromHandle(GetDlgItem(IDC_INDICATORLISTWND1)->GetSafeHwnd());
	m_pIndicatorListWnd->SetItemWide(40);
	for (int i = 0; i < m_nIndicatorCount; i++) {
		CString strText;
		strText.Format("%d", i+1);
		m_pIndicatorListWnd->AddIndicator(i, strText);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CPageCurrentResult::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CPageCurrentResult::Resize()
{
	CWnd *pItem = GetDlgItem(IDC_INDICATORLISTWND1);
	if (pItem == NULL) {
		return;
	}

	CRect rcWnd, rcClient;
	GetWindowRect(&rcWnd);
	pItem->MoveWindow(0, 0, rcWnd.Width(), rcWnd.Height());
}

void CPageCurrentResult::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	Resize();
}
