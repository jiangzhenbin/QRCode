// PageTest.cpp : 实现文件
//

#include "stdafx.h"
#include "QRCode.h"
#include "PageTest.h"
#include "afxdialogex.h"


#define BORDER			5
#define SHADOWWIDE		5


// CPageTest 对话框

IMPLEMENT_DYNAMIC(CPageTest, CDialogEx)

CPageTest::CPageTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TEST, pParent)
{
	m_crBkgnd = RGB(255, 255, 255);
	m_brBkgnd.CreateSolidBrush(m_crBkgnd);
	m_crFrame = RGB(220, 220, 220); //GetSysColor(COLOR_WINDOWFRAME);
	m_bShadow = TRUE;
	m_crShadowBkgnd = GetSysColor(COLOR_BTNFACE);
}

CPageTest::~CPageTest()
{
}

void CPageTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageTest, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPageTest::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPageTest::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPageTest 消息处理程序


void CPageTest::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// CDialogEx::OnOK();
}


void CPageTest::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	// CDialogEx::OnCancel();
}


BOOL CPageTest::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH CPageTest::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkColor(m_crBkgnd);
	}


	return m_brBkgnd;
}

void CPageTest::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// CDialogEx::OnNcCalcSize(bCalcValidRects, lpncsp);

	if (!m_bShadow) {
		LPRECT lprcWnd = (LPRECT)&lpncsp->rgrc;
		lprcWnd->left += BORDER;
		lprcWnd->top += BORDER;
		lprcWnd->right -= (BORDER);
		lprcWnd->bottom -= (BORDER);
	}
	else {
		LPRECT lprcWnd = (LPRECT)&lpncsp->rgrc;
		lprcWnd->left += BORDER;
		lprcWnd->top += BORDER;
		lprcWnd->right -= (BORDER + SHADOWWIDE);
		lprcWnd->bottom -= (BORDER + SHADOWWIDE);
	}
}


void CPageTest::OnNcPaint()
{
	// 然后画边框
	long styleEx = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	//if ((styleEx & WS_EX_CLIENTEDGE) == WS_EX_CLIENTEDGE)
	{

		RECT rcWindow, rcClient;
		GetClientRect(&rcClient);
		::ClientToScreen(m_hWnd, (LPPOINT)&rcClient.left);
		::ClientToScreen(m_hWnd, (LPPOINT)&rcClient.right);
		GetWindowRect(&rcWindow);
		::OffsetRect(&rcClient, -rcWindow.left, -rcWindow.top);
		::OffsetRect(&rcWindow, -rcWindow.left, -rcWindow.top);

		HRGN hRgnWnd = CreateRectRgnIndirect(&rcWindow);
		HRGN hRgnClient = CreateRectRgnIndirect(&rcClient);

		HDC hDC = ::GetWindowDC(m_hWnd);
		::SelectClipRgn(hDC, hRgnWnd);
		::ExtSelectClipRgn(hDC, hRgnClient, RGN_DIFF);


		// 没有阴影的边框
		if (!m_bShadow) {
			HBRUSH hBrushBK, hBrushFrame;
			hBrushBK = CreateSolidBrush(m_crBkgnd);
			::FillRect(hDC, &rcWindow, hBrushBK);
			DeleteObject(hBrushBK);

			hBrushFrame = CreateSolidBrush(m_crFrame);
			::FrameRect(hDC, &rcWindow, hBrushFrame);
			DeleteObject(hBrushFrame);
		}

		// 有阴影的边框
		else {

			RECT rcFrame0, rcFrame1;
			rcFrame0.left = rcWindow.left + SHADOWWIDE;
			rcFrame0.top = rcWindow.top + SHADOWWIDE;
			rcFrame0.right = rcWindow.right;
			rcFrame0.bottom = rcWindow.bottom;
			rcFrame1.left = rcWindow.left;
			rcFrame1.top = rcWindow.top;
			rcFrame1.right = rcWindow.right - SHADOWWIDE;
			rcFrame1.bottom = rcWindow.bottom - SHADOWWIDE;


			// 背景框和对话框(父窗体)背景色一致
			HBRUSH hBrushBK, hBrushFrame;
			hBrushBK = CreateSolidBrush(m_crShadowBkgnd);
			::FillRect(hDC, &rcWindow, hBrushBK);
			DeleteObject(hBrushBK);


			// 阴影框
			BYTE r = GetRValue(m_crShadowBkgnd);
			BYTE g = GetGValue(m_crShadowBkgnd);
			BYTE b = GetBValue(m_crShadowBkgnd);
			BYTE rstep = (r - GetRValue(m_crFrame)) / SHADOWWIDE;
			BYTE gstep = (r - GetGValue(m_crFrame)) / SHADOWWIDE;
			BYTE bstep = (r - GetBValue(m_crFrame)) / SHADOWWIDE;

			for (int i = 0; i < SHADOWWIDE; i++) {
				hBrushBK = CreateSolidBrush(RGB(r - i*rstep, g - i*gstep, b - i*bstep));
				::FillRect(hDC, &rcFrame0, hBrushBK);
				DeleteObject(hBrushBK);
				rcFrame0.bottom -= 1;
				rcFrame0.right -= 1;
			}


			// 前景框
			hBrushBK = CreateSolidBrush(m_crBkgnd);
			::FillRect(hDC, &rcFrame1, hBrushBK);
			DeleteObject(hBrushBK);

			hBrushFrame = CreateSolidBrush(m_crFrame);
			::FrameRect(hDC, &rcFrame1, hBrushFrame);
			DeleteObject(hBrushFrame);
		}


		::DeleteObject(hRgnWnd);
		::DeleteObject(hRgnClient);
		::ReleaseDC(m_hWnd, hDC);
	}

	//return 0;
}


HWND CPageTest::GetGraphWnd()
{
	CWnd *pItem = GetDlgItem(IDC_MILPREVIEE1);
	if (pItem == NULL) {
		return NULL;
	}

	return pItem->GetSafeHwnd();
}

void CPageTest::SetTopTextl(CString &strText)
{
	if (GetDlgItem(IDC_TEXT_CODE) != NULL) {
		SetDlgItemText(IDC_TEXT_CODE, strText);
	}
}

void CPageTest::SetTopTextl2(CString strText)
{
	if (GetDlgItem(IDC_TEXT_CODE) != NULL) {
		SetDlgItemText(IDC_TEXT_CODE, strText);
	}
}

void CPageTest::Resize()
{
	CWnd *pItem = GetDlgItem(IDC_TEXT_CODE);
	if (pItem == NULL) {
		return;
	}

	CRect rcClient, rcItem;
	GetClientRect(&rcClient);
	pItem = GetDlgItem(IDC_TEXT_CODE);
	pItem->GetWindowRect(&rcItem);
	pItem->MoveWindow(12, 12, rcItem.Width(), rcItem.Height());
	int y = 12 + rcItem.Height();
	y += 5;


	// 预览画面
	pItem = GetDlgItem(IDC_MILPREVIEE1);
	pItem->GetWindowRect(&rcItem);
	pItem->MoveWindow(12, y, rcClient.Width() - 12 * 2, rcClient.Height() - y - 12);


	// 检测结果文字，PASS/NG
	//pItem = GetDlgItem(IDC_TEXT_RESULT);
	//ASSERT(pItem);
	//pItem->GetWindowRect(&rcItem);
	//ScreenToClient(&rcItem);
	//pItem->MoveWindow((rcClient.Width() - rcItem.Width()) / 2, y + (rcClient.bottom - y - rcItem.Height()) / 2, rcItem.Width(), rcItem.Height());
}

void CPageTest::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	Resize();
}

void CPageTest::RoiPoint2WndPoint(int imgWidth, int imgHeight, double x, double y, LPPOINT pt)
{
	CWnd *pItem = GetDlgItem(IDC_MILPREVIEE1);
	if (pItem != NULL) {
		CRect rcClient;
		pItem->GetClientRect(&rcClient);

		double d1 = (double)rcClient.Width() / (double)imgWidth;
		double d2 = (double)rcClient.Height() / (double)imgHeight;

		pt->x = int((double)rcClient.Width() / (double)imgWidth * x);
		pt->y = int((double)rcClient.Height() / (double)imgHeight * y);
	}
}
