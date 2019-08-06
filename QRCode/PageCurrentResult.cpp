// PageCurrentResult.cpp : 实现文件
//

#include "stdafx.h"
#include "QRCode.h"
#include "PageCurrentResult.h"
#include "afxdialogex.h"


// CPageCurrentResult 对话框

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

// CPageCurrentResult 消息处理程序


BOOL CPageCurrentResult::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Resize();

	
	// 四块板的测试结果指示
	m_pIndicatorListWnd = CIndicatorListWnd::FromHandle(GetDlgItem(IDC_INDICATORLISTWND1)->GetSafeHwnd());
	m_pIndicatorListWnd->SetItemWide(40);
	for (int i = 0; i < m_nIndicatorCount; i++) {
		CString strText;
		strText.Format("%d", i+1);
		m_pIndicatorListWnd->AddIndicator(i, strText);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH CPageCurrentResult::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
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
