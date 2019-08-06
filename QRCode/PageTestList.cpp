// PageTestList.cpp : 实现文件
//

#include "stdafx.h"
#include "QRCode.h"
#include "PageTestList.h"
#include "afxdialogex.h"


// CPageTestList 对话框

IMPLEMENT_DYNAMIC(CPageTestList, CDialogEx)

CPageTestList::CPageTestList(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE_TESTLIST, pParent)
{
	m_crBkgnd = RGB(255, 255, 255);
	m_brBkgnd.CreateSolidBrush(m_crBkgnd);

	m_crStateBkgnd[0] = RGB(255, 255, 255);
	m_crStateBkgnd[1] = RGB(222, 222, 222);
	m_crStateBkgnd[2] = RGB(255, 255, 255);
	m_crStateBkgnd[3] = RGB(255, 0, 0);
	m_crStateText[0] = RGB(0, 0, 0);
	m_crStateText[1] = RGB(0, 0, 0);
	m_crStateText[2] = RGB(0, 0, 0);
	m_crStateText[3] = RGB(255, 255, 255);
}

CPageTestList::~CPageTestList()
{
}

void CPageTestList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CODE, m_wndListQRCode);
}


BEGIN_MESSAGE_MAP(CPageTestList, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CPageTestList::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CPageTestList::OnBnClickedOk)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPageTestList 消息处理程序


void CPageTestList::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// CDialogEx::OnOK();
}

void CPageTestList::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	// CDialogEx::OnCancel();
}


CString CPageTestList::GetShortCode(CString &strCode)
{
	if (strCode.GetLength() > 15) {
		CString strRet;
		strRet.Format(_T("%s...%s"), strCode.Left(3), strCode.Right(9));
		return strRet;
	}
	else {
		return strCode;
	}
}

CString CPageTestList::GetQRCodeStateText(CODESTATE state)
{
	if (state == READY) {
		return _T("就绪");
	}
	else if (state == SENDING) {
		return _T("发送中");
	}
	else if (state == SUCCEED) {
		return _T("发送成功");
	}
	else if (state == FAILED) {
		return _T("发送失败");
	}

	return _T("");
}

void CPageTestList::AppedCode(CQRCode *pQRCode)
{
	int nIndex = m_wndListQRCode.GetItemCount();
	m_wndListQRCode.InsertItem(nIndex, _T(""));
	m_wndListQRCode.SetItemText(nIndex, 1, GetShortCode(pQRCode->code));

	CString strCameraId;
	strCameraId.Format(_T("%d"), pQRCode->cameraId);
	m_wndListQRCode.SetItemText(nIndex, 2, strCameraId);
	m_wndListQRCode.SetItemText(nIndex, 3, GetQRCodeStateText(pQRCode->state));
	m_wndListQRCode.SetItemColor(nIndex, 3, m_crStateBkgnd[pQRCode->state], m_crStateText[pQRCode->state]);

	m_wndListQRCode.SetItemData(nIndex, (DWORD_PTR)pQRCode);
	m_wndListQRCode.EnsureVisible(nIndex, FALSE);

	if (nIndex >= 10) {
		m_wndListQRCode.DeleteItem(0);
	}
}

void CPageTestList::UpdateCodeState(CQRCode *pQRCode)
{
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_CODE);
	for (int i = 0; i < pListCtrl->GetItemCount(); i++) {
		CQRCode *pItem = (CQRCode *)pListCtrl->GetItemData(i);
		if (pItem == pQRCode) {
			pListCtrl->SetItemText(i, 3, GetQRCodeStateText(pQRCode->state));
			m_wndListQRCode.SetItemColor(i, 3, m_crStateBkgnd[pQRCode->state], m_crStateText[pQRCode->state]);
			break;
		}
	}
}

BOOL CPageTestList::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_CODE);
	DWORD dwStyle = pListCtrl->GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;			// 选中整行高亮
	dwStyle |= LVS_EX_GRIDLINES;				// 网格线
	pListCtrl->SetExtendedStyle(dwStyle); // 设置扩展风格

	HIMAGELIST imageList = ImageList_Create(24, 24, ILC_COLOR24, 1, 1);
	ListView_SetImageList(pListCtrl->GetSafeHwnd(), imageList, LVSIL_SMALL);

	pListCtrl->InsertColumn(0, _T(""), LVCFMT_RIGHT, 0);
	pListCtrl->InsertColumn(1, _T("Code"), LVCFMT_LEFT, 160);
	pListCtrl->InsertColumn(2, _T("摄像头"), LVCFMT_LEFT, 70);
	pListCtrl->InsertColumn(3, _T("状态"), LVCFMT_LEFT, 90);


	Resize();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH CPageTestList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkColor(m_crBkgnd);
	}


	return m_brBkgnd;
}

void CPageTestList::Resize()
{
	CWnd *pItem = GetDlgItem(IDC_LIST_CODE);
	if (pItem == NULL) {
		return;
	}

	CRect rcClient, rcItem;
	GetClientRect(&rcClient);
	pItem->GetWindowRect(&rcItem);
	pItem->MoveWindow(12, 12, rcClient.Width() - 12 * 2, rcClient.Height() - 12 * 2);
}

void CPageTestList::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	Resize();
}
