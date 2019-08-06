// PageState.cpp : 实现文件
//

#include "stdafx.h"
#include "QRCode.h"
#include "PageState.h"
#include "afxdialogex.h"


// CPageState 对话框

IMPLEMENT_DYNAMIC(CPageState, CDialogEx)

CPageState::CPageState(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE_STATE, pParent)
{
	m_crBkgnd = RGB(255, 255, 255);
	m_brBkgnd.CreateSolidBrush(m_crBkgnd);
	m_crPlcStateText = RGB(255, 0, 0);
	m_fOnClicked = nullptr;
}

CPageState::~CPageState()
{

}

void CPageState::SetPLCStateText(CString strText, COLORREF color)
{
	m_crPlcStateText = color;
	SetDlgItemText(IDC_TEXT_PLCSTATE, strText);
}

void CPageState::EnableItem(UINT nCtrlId, BOOL bEnable)
{
	GetDlgItem(nCtrlId)->EnableWindow(bEnable);
}

void CPageState::SetOnClickedListener(ONCLICKED listener)
{
	m_fOnClicked = listener;
}

void CPageState::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageState, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_START, &CPageState::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CPageState::OnBnClickedButtonStop)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPageState 消息处理程序


BOOL CPageState::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH CPageState::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkColor(m_crBkgnd);
		if (pWnd->GetDlgCtrlID() == IDC_TEXT_PLCSTATE) {
			pDC->SetTextColor(m_crPlcStateText);
		}
	}


	return m_brBkgnd;
}


void CPageState::OnBnClickedButtonStart()
{
	if (m_fOnClicked != nullptr) {
		m_fOnClicked(IDC_BUTTON_START);
	}
}


void CPageState::OnBnClickedButtonStop()
{
	if (m_fOnClicked != nullptr) {
		m_fOnClicked(IDC_BUTTON_STOP);
	}
}


void CPageState::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (GetDlgItem(IDC_BUTTON_STOP) == NULL) {
		return;
	}


	CWnd *pItem;
	CRect rcClient, rcItem;	
	GetClientRect(&rcClient);
	int x = rcClient.right - 12;

	pItem = (CWnd *)GetDlgItem(IDC_BUTTON_STOP);
	pItem->GetWindowRect(&rcItem);
	pItem->SetWindowPos(NULL, x - rcItem.Width(), (rcClient.Height() - rcItem.Height()) / 2, 0, 0, SWP_NOSIZE);
	x -= rcItem.Width();
	x -= 5;

	pItem = (CWnd *)GetDlgItem(IDC_BUTTON_START);
	pItem->GetWindowRect(&rcItem);
	pItem->SetWindowPos(NULL, x - rcItem.Width(), (rcClient.Height() - rcItem.Height()) / 2, 0, 0, SWP_NOSIZE);
	x -= rcItem.Width();
	x -= 5;

	pItem = (CWnd *)GetDlgItem(IDC_TEXT_PLCSTATE);
	pItem->GetWindowRect(&rcItem);
	pItem->MoveWindow(50, (rcClient.Height() - rcItem.Height()) / 2, x - 50, rcItem.Height());
}
