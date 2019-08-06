#include "stdafx.h"
#include "IndicatorListWnd.h"

CIndicatorListWnd::CIndicatorListWnd()
{
	m_hWnd = NULL;
	m_crFrame = GetSysColor(COLOR_WINDOWFRAME);
	m_crBkgnd = RGB(255, 255, 255);
	m_onPosChanged = nullptr;
	m_nItemSpace = 5;
	m_nItemWide = 20;
	m_crItemBackground[0] = RGB(218, 218, 218);
	m_crItemBackground[1] = RGB(34, 177, 76);
	m_crItemBackground[2] = RGB(255, 0, 0);
	m_crItemBackground[3] = RGB(255, 174, 201);
	m_crItemFrame[0] = RGB(128, 128, 128);
	m_crItemFrame[1] = RGB(128, 128, 128);
	m_crItemFrame[2] = RGB(128, 128, 128);
	m_crItemFrame[3] = RGB(128, 128, 128);
	m_crItemText[0] = RGB(0, 0, 0);
	m_crItemText[1] = RGB(0, 0, 0);
	m_crItemText[2] = RGB(0, 0, 0);
	m_crItemText[3] = RGB(0, 0, 0);
	m_nItemRound = 0;
}


CIndicatorListWnd::~CIndicatorListWnd()
{
	for (int i = 0; i < m_arIndicator.GetCount(); i++) {
		INDICATOR *pItem = (INDICATOR *)m_arIndicator.GetAt(i);
		delete pItem;
	}
	m_arIndicator.RemoveAll();
}

BOOL CIndicatorListWnd::RegisterWndClass()
{
	WNDCLASS wc;
	wc.lpszClassName = INDICATORLISTWND_CLASS;
	wc.hInstance = AfxGetInstanceHandle();
	wc.lpfnWndProc = WindowProc;
	wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = 0;
	wc.lpszMenuName = NULL;
	wc.hbrBackground = NULL;
	wc.style = CS_GLOBALCLASS | CS_DBLCLKS;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	// 注册自定义类
	return (::RegisterClass(&wc) != 0);
}

CIndicatorListWnd * CIndicatorListWnd::FromHandle(HWND hWnd)
{
	CIndicatorListWnd *pIndicatorListWnd = (CIndicatorListWnd *)::GetProp(hWnd, INDICATORLISTWND_TAG);
	return pIndicatorListWnd;
}

CIndicatorListWnd* CIndicatorListWnd::Hook(HWND hWnd)
{
	CIndicatorListWnd* pIndicatorListWnd = (CIndicatorListWnd*)GetProp(hWnd, INDICATORLISTWND_TAG);
	if (pIndicatorListWnd == NULL) {
		pIndicatorListWnd = new CIndicatorListWnd();
		pIndicatorListWnd->m_hWnd = hWnd;

		SetProp(hWnd, INDICATORLISTWND_TAG, (HANDLE)pIndicatorListWnd);
	}


	return pIndicatorListWnd;
}

void CIndicatorListWnd::SetItemSpace(unsigned int nItemSpace)
{
	m_nItemSpace = MAX(2, nItemSpace);
}

void CIndicatorListWnd::SetItemWide(unsigned int nItemWide)
{
	m_nItemWide = MAX(5, nItemWide);
}

void CIndicatorListWnd::SetItemRound(int nRound)
{
	m_nItemRound = nRound;
}

void CIndicatorListWnd::SetDefaultItemBackgroundColor(COLORREF crNormal, COLORREF crSel)
{
	m_crItemBackground[0] = crNormal;
	m_crItemBackground[1] = crSel;
}

void CIndicatorListWnd::SetDefaultItemFrameColor(COLORREF crNormal, COLORREF crSel)
{
	m_crItemFrame[0] = crNormal;
	m_crItemFrame[1] = crSel;
}

void CIndicatorListWnd::SetDefaultItemTextColor(COLORREF crNormal, COLORREF crSel)
{
	m_crItemText[0] = crNormal;
	m_crItemText[1] = crSel;
}

void CIndicatorListWnd::Init()
{
}

void CIndicatorListWnd::Release()
{
	// delete
	delete this;
}

void CIndicatorListWnd::SetOnPosChangedListener(ONPOSCHANGED listener)
{
	m_onPosChanged = listener;
}

INDICATOR * CIndicatorListWnd::AddIndicator(int index, CString strText)
{
	INDICATOR *pItem = new INDICATOR;
	memset(pItem, 0, sizeof(INDICATOR));
	
	int len = MIN(255, strText.GetLength());
	memcpy(pItem->text, (LPTSTR)(LPCTSTR)strText, len);
	pItem->text[len] = '\0';
	m_arIndicator.Add(pItem);
	
	RECT rcClient;
	GetClientRect(m_hWnd, &rcClient);
	::InvalidateRect(m_hWnd, &rcClient, TRUE);

	return pItem;
}

/*
 * 设置子项的选中状态
 */
void CIndicatorListWnd::SetItemState(int nIndex, int nState)
{
	if (nIndex >= m_arIndicator.GetCount()) {
		return;
	}

	if (nState < 0 || 3 < nState) {
		return;
	}

	INDICATOR *pItem = (INDICATOR *)m_arIndicator.GetAt(nIndex);
	pItem->state = nState;

	RECT rcClient;
	GetClientRect(m_hWnd, &rcClient);
	::InvalidateRect(m_hWnd, &rcClient, TRUE);
}

void CIndicatorListWnd::DrawAllText(BOOL bClearWindow)
{

}

void CIndicatorListWnd::Notify(int nCode, int dwData, int dwData1/* = 0*/, int dwData2/* = 0*/)
{
	HWND hParent;
	hParent = GetParent(m_hWnd);
	if (hParent != NULL) {
		INDICATORLIST_NMHDR indicatorWndnmhdr;
		indicatorWndnmhdr.nmhdr.hwndFrom = m_hWnd;
		indicatorWndnmhdr.nmhdr.idFrom = GetWindowLong(m_hWnd, GWL_ID);
		indicatorWndnmhdr.nmhdr.code = nCode;
		indicatorWndnmhdr.dwData = dwData;
		indicatorWndnmhdr.dwData1 = dwData1;
		indicatorWndnmhdr.dwData2 = dwData2;
		SendMessage(hParent, WM_NOTIFY, (WPARAM)indicatorWndnmhdr.nmhdr.idFrom, (LPARAM)&indicatorWndnmhdr);
	}
}

/*
 * 拦截窗口消息函数
 */
LRESULT CALLBACK CIndicatorListWnd::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CIndicatorListWnd* pIndicatorListWnd = (CIndicatorListWnd *)GetProp(hWnd, INDICATORLISTWND_TAG);
	if (pIndicatorListWnd == NULL && uMsg != WM_NCCREATE)
	{
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}


	// 如果Hook则响应消息
	ASSERT(hWnd);
	switch (uMsg)
	{
	case WM_NCCREATE:
		return CIndicatorListWnd::OnNcCreate(hWnd, wParam, lParam);

	case WM_DESTROY:
		return pIndicatorListWnd->OnDestroy(wParam, lParam);

	case WM_NCPAINT:
		return pIndicatorListWnd->OnNcPaint(wParam, lParam);

	case WM_PAINT:
		return pIndicatorListWnd->OnPaint(wParam, lParam);

	case WM_TIMER:
		return pIndicatorListWnd->OnTimer(wParam, lParam);

	case WM_MOUSEMOVE:
		return pIndicatorListWnd->OnMouseMove(wParam, lParam);

	case WM_LBUTTONDOWN:
		return pIndicatorListWnd->OnLButtonDown(wParam, lParam);

	case WM_MOUSEWHEEL:
		return pIndicatorListWnd->OnMouseWheel(wParam, lParam);

	case WM_SIZE:
		return pIndicatorListWnd->OnSize(wParam, lParam);

	case WM_GETDLGCODE:
		return DLGC_WANTALLKEYS;

	default:
		break;
	}

	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/*
 * WM_NCCREATE
 * 窗口创建前的初始化工作
 */
LRESULT CIndicatorListWnd::OnNcCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	CIndicatorListWnd* pIndicatorListWnd = (CIndicatorListWnd *)GetProp(hWnd, INDICATORLISTWND_TAG);
	ASSERT(pIndicatorListWnd == NULL);

	Hook(hWnd);
	return ::DefWindowProc(hWnd, WM_NCCREATE, wParam, lParam);
}

/*
 * WM_DESTROY
 * 窗口销毁时
 */
LRESULT CIndicatorListWnd::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	Release();
	return ::DefWindowProc(m_hWnd, WM_DESTROY, wParam, lParam);
}


/*
 * WM_TIMER
 */
LRESULT CIndicatorListWnd::OnTimer(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_TIMER, wParam, lParam);
}

/*
 * WM_MOUSEMOVE
 * 鼠标移动时，检测鼠标位置并回调给主窗口
 */
LRESULT CIndicatorListWnd::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_MOUSEMOVE, wParam, lParam);
}

/*
 * WM_MOUSEMOVE
 * 鼠标左键下压时，拖动图像
 */
LRESULT CIndicatorListWnd::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_LBUTTONDOWN, wParam, lParam);
}

/*
 * WM_MOUSEWHEEL
 * 鼠标滚轮滚动时，缩放图像
 */
LRESULT CIndicatorListWnd::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_MOUSEWHEEL, wParam, lParam);
}

/*
 * WM_NCPAINT
 */
LRESULT CIndicatorListWnd::OnNcPaint(WPARAM wParam, LPARAM lParam)
{
	LRESULT lRet = ::DefWindowProc(m_hWnd, WM_NCPAINT, wParam, lParam);


	// 然后画边框
	long styleEx = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if ((styleEx & WS_EX_CLIENTEDGE) == WS_EX_CLIENTEDGE) {

		RECT rect, rcClient;
		GetClientRect(m_hWnd, &rcClient);
		::ClientToScreen(m_hWnd, (LPPOINT)&rcClient.left);
		::ClientToScreen(m_hWnd, (LPPOINT)&rcClient.right);
		GetWindowRect(m_hWnd, &rect);
		::OffsetRect(&rcClient, -rect.left, -rect.top);

		rect.right -= rect.left;
		rect.bottom -= rect.top;
		rect.left = 0;
		rect.top = 0;

		HRGN hRgnWnd = CreateRectRgnIndirect(&rect);
		HRGN hRgnClient = CreateRectRgnIndirect(&rcClient);

		HBRUSH hBrushBK, hBrushFrame;
		HDC hDC = GetWindowDC(m_hWnd);
		::SelectClipRgn(hDC, hRgnWnd);
		::ExtSelectClipRgn(hDC, hRgnClient, RGN_DIFF);

		hBrushBK = CreateSolidBrush(m_crBkgnd);
		::FillRect(hDC, &rect, hBrushBK);
		DeleteObject(hBrushBK);

		hBrushFrame = CreateSolidBrush(m_crFrame);
		::FrameRect(hDC, &rect, hBrushFrame);

		::DeleteObject(hRgnWnd);
		::DeleteObject(hRgnClient);
		DeleteObject(hBrushFrame);
		ReleaseDC(m_hWnd, hDC);
	}
	
	return lRet;
}

/*
 * WM_PAINT
 */
LRESULT CIndicatorListWnd::OnPaint(WPARAM wParam, LPARAM lParam)
{
	HDC hDC, hMemDC;
	HBITMAP hBitmap;
	RECT rcClient;
	CString strText;
	HFONT hFont;
	HBRUSH hBrushBK;


	// BeginPaint
	PAINTSTRUCT ps;
	hDC = BeginPaint(m_hWnd, &ps);
	GetClientRect(m_hWnd, &rcClient);

	hMemDC = ::CreateCompatibleDC(hDC);
	hBitmap = ::CreateCompatibleBitmap(hDC, rcClient.right - rcClient.left,
		rcClient.bottom - rcClient.top);
	::SelectObject(hMemDC, hBitmap);

	hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	::SelectObject(hMemDC, hFont);


	// 背景颜色
	hBrushBK = CreateSolidBrush(m_crBkgnd);
	::FillRect(hMemDC, &rcClient, hBrushBK);
	DeleteObject(hBrushBK);


	// 窗口标题
	{
		char szTitle[256];
		GetWindowText(m_hWnd, szTitle, 256);
		RECT rcTitle;
		rcTitle.left = rcClient.left + 2;
		rcTitle.top = rcClient.top + 2;
		rcTitle.bottom = rcClient.bottom - 2;
		rcTitle.right = rcClient.right - 2;
		::DrawText(hMemDC, szTitle, (int)strlen(szTitle), &rcTitle, DT_LEFT|DT_TOP);
	}


	// 绘子项列表
	{
		int nCount = (int)m_arIndicator.GetCount();
		int x = ((rcClient.right - rcClient.left) - (nCount - 1) * m_nItemSpace - nCount*m_nItemWide) / 2;
		int y = ((rcClient.bottom - rcClient.top) - m_nItemWide) / 2;

		RECT rcFrame, rcText;
		rcFrame.left = x;
		rcFrame.top = y;
		rcFrame.bottom = rcFrame.top + m_nItemWide;
		rcText.left = x;
		rcText.top = rcFrame.bottom + 5;
		rcText.bottom = rcText.top + 30;

		for (int i = 0; i < m_arIndicator.GetCount(); i++) {
			INDICATOR *pItem = (INDICATOR *)m_arIndicator.GetAt(i);
			rcFrame.right = rcFrame.left + m_nItemWide;


			// 没有圆角
			HBRUSH hbrItemBackground = CreateSolidBrush(m_crItemBackground[pItem->state]);
			HBRUSH hbrItemFrame = CreateSolidBrush(m_crItemFrame[pItem->state]);
			if (m_nItemRound == 0) {
				::FillRect(hMemDC, &rcFrame, hbrItemBackground);
				::DeleteObject(hbrItemBackground);

				::FrameRect(hMemDC, &rcFrame, hbrItemFrame);
				::DeleteObject(hbrItemFrame);
			}
			else {
				HRGN hRgn = CreateRoundRectRgn(rcFrame.left, rcFrame.top, rcFrame.right, rcFrame.bottom, m_nItemRound, m_nItemRound);
				::FillRgn(hMemDC, hRgn, hbrItemBackground);
				::FrameRgn(hMemDC, hRgn, hbrItemFrame, 1, 1);
				::DeleteObject(hbrItemBackground);
				::DeleteObject(hbrItemFrame);
				::DeleteObject(hRgn);
			}
			

			rcText.right = rcFrame.right;
			rcText.left -= 10;
			rcText.right += 10;
			::SetTextColor(hMemDC, m_crItemText[pItem->state]);
			::DrawText(hMemDC, pItem->text, (int)strlen(pItem->text), &rcText, DT_CENTER | DT_TOP);

			rcFrame.left = rcFrame.right + m_nItemSpace;
			rcText.left = rcFrame.left;
		}
	}




	// EndPaint
	::BitBlt(hDC, 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
		hMemDC, 0, 0, SRCCOPY);
	EndPaint(m_hWnd, &ps);
	::DeleteObject(hBitmap);
	::DeleteDC(hMemDC);


	return 1;
}

/*
 * WM_SIZE
 */
LRESULT CIndicatorListWnd::OnSize(WPARAM wParam, LPARAM lParam)
{
	LRESULT lRet = ::DefWindowProc(m_hWnd, WM_SIZE, wParam, lParam);

	return lRet;
}

/*
 * 设置背景色
 * color -- 背景色
 */
void CIndicatorListWnd::SetBkgndColor(COLORREF color)
{
	m_crBkgnd = color;
}

/*
 * 设置边框颜色
 * color -- 边框颜色
 */
void CIndicatorListWnd::SetFrameColor(COLORREF color)
{
	m_crFrame = color;
}

