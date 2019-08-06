#include "stdafx.h"
#include "AccordionWnd.h"


#define ITEM_HEIGHT				32
#define ITEM_SPACE				5
#define TIMER_ID_CHECKHOVER		1
#define EXPAND_ICON_WIDE		12

#define BORDER			5
#define SHADOWWIDE		5

CAccordionWnd::CAccordionWnd()
{
	m_hWnd = NULL;
	m_crFrame = GetSysColor(COLOR_WINDOWFRAME);
	m_crBkgnd = RGB(255, 255, 255);//GetSysColor(COLOR_BTNFACE); ;
	m_nPadding[PADDING_LEFT] = 5;
	m_nPadding[PADDING_TOP] = 5;
	m_nPadding[PADDING_RIGHT] = 5;
	m_nPadding[PADDING_BOTTOM] = 5;
	m_crItemBackground[0] = RGB(218, 218, 218);
	m_crItemBackground[1] = RGB(34, 177, 76);
	m_crItemFrame[0] = RGB(128, 128, 128);
	m_crItemFrame[1] = RGB(128, 128, 128);
	m_crItemText[0] = RGB(0, 0, 0);
	m_crItemText[1] = RGB(0, 0, 0);
	m_crSeparateLine = RGB(222, 222, 222);
	m_crHoverItemBackground = RGB(244, 245, 247);
	m_crHoverItemFrame = RGB(200, 222, 255);
	m_hIconExpand = NULL;
	m_hIconClose = NULL;
	m_nHoverItem = -1;
	m_nCheckHoverItem = -1;
	m_bShadow = FALSE;
	m_crShadowBkgnd = GetSysColor(COLOR_BTNFACE);
}


CAccordionWnd::~CAccordionWnd()
{
	for (size_t i = 0; i < m_vectorItems.size(); i++) {
		delete m_vectorItems[i];
	}
	m_vectorItems.clear();
}

BOOL CAccordionWnd::RegisterWndClass()
{
	WNDCLASS wc;
	wc.lpszClassName = ACCORDIONWND_CLASS;
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

CAccordionWnd * CAccordionWnd::FromHandle(HWND hWnd)
{
	CAccordionWnd *pAccordionWnd = (CAccordionWnd *)::GetProp(hWnd, ACCORDIONWND_TAG);
	return pAccordionWnd;
}

CAccordionWnd* CAccordionWnd::Hook(HWND hWnd)
{
	CAccordionWnd* pAccordionWnd = (CAccordionWnd*)GetProp(hWnd, ACCORDIONWND_TAG);
	if (pAccordionWnd == NULL) {
		pAccordionWnd = new CAccordionWnd();
		pAccordionWnd->m_hWnd = hWnd;

		SetProp(hWnd, ACCORDIONWND_TAG, (HANDLE)pAccordionWnd);
	}


	return pAccordionWnd;
}

void CAccordionWnd::LoadExpandIcon(CString strExpandFile, CString strCloseFile)
{
	m_hIconExpand = (HICON)::LoadImage(AfxGetInstanceHandle(), strExpandFile, IMAGE_ICON, EXPAND_ICON_WIDE, EXPAND_ICON_WIDE,
		LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
	m_hIconClose = (HICON)::LoadImage(AfxGetInstanceHandle(), strCloseFile, IMAGE_ICON, EXPAND_ICON_WIDE, EXPAND_ICON_WIDE,
		LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
}

void CAccordionWnd::Setpadding(int type, unsigned int nPadding)
{
	if (type >= PADDING_LEFT && PADDING_LEFT <= PADDING_BOTTOM) {
		m_nPadding[type] = nPadding;
	}
}

void CAccordionWnd::SetDefaultItemBackgroundColor(COLORREF crNormal, COLORREF crSel)
{
	m_crItemBackground[0] = crNormal;
	m_crItemBackground[1] = crSel;
}

void CAccordionWnd::SetDefaultItemFrameColor(COLORREF crNormal, COLORREF crSel)
{
	m_crItemFrame[0] = crNormal;
	m_crItemFrame[1] = crSel;
}

void CAccordionWnd::SetDefaultItemTextColor(COLORREF crNormal, COLORREF crSel)
{
	m_crItemText[0] = crNormal;
	m_crItemText[1] = crSel;
}

void CAccordionWnd::Init()
{
}

void CAccordionWnd::Release()
{
	// delete
	delete this;
}

/*
 * 添加项目
 * pszName -- 名称
 * pWnd -- 绑定的窗口
 * nExpandHeight -- 展开高度，如果为0则自动设置为窗口高
 */
void CAccordionWnd::AddItem(char *pszName, CWnd *pWnd, int nExpandHeight, BOOL bExpand/* = TRUE*/, BOOL bEnable/* = TRUE*/)
{
	ACCORDIONITEM *pItem = new ACCORDIONITEM;
	memset(pItem, 0, sizeof(ACCORDIONITEM));
	pItem->pWnd = pWnd;
	pItem->bExpand = bExpand;
	pItem->bEnable = bEnable;
	strcpy_s(pItem->text, sizeof(pItem->text), pszName);
	if (nExpandHeight == 0) {
		RECT rect;
		pWnd->GetWindowRect(&rect);
		pItem->nExpandHeight = rect.bottom - rect.top;
	}
	else if (nExpandHeight == -1) {
		pItem->nExpandHeight = -1;
	}
	else {
		pItem->nExpandHeight = nExpandHeight;
	}
	m_vectorItems.push_back(pItem);

	
	// 重新调整个子窗口的位置
	ResizeItemWnd();
}

void CAccordionWnd::ResizeItemWnd()
{
	RECT rcClient, rcItemClient;
	GetClientRect(m_hWnd, &rcClient);

	for (size_t i = 0; i < m_vectorItems.size(); i++) {
		ACCORDIONITEM *pItem = m_vectorItems.at(i);
		if (pItem->pWnd != NULL) {
			GetItemRect(rcClient, i, &rcItemClient);
			rcItemClient.top += ITEM_HEIGHT;
			if (pItem->nExpandHeight == -1) {
				rcItemClient.bottom = rcClient.bottom;
			}
			else {
				rcItemClient.bottom = rcItemClient.top + pItem->nExpandHeight;
			}

			pItem->pWnd->MoveWindow(&rcItemClient);
			pItem->pWnd->ShowWindow(pItem->bExpand ? SW_SHOW : SW_HIDE);
		}
	}
}

BOOL CAccordionWnd::GetItemHeaderRect(RECT rcClient, unsigned int nIndex, LPRECT lpRect)
{
	RECT rcItem;
	if (!GetItemRect(rcClient, nIndex, &rcItem)) {
		return FALSE;
	}

	rcItem.bottom = rcItem.top + ITEM_HEIGHT;
	CopyRect(lpRect, &rcItem);
	return TRUE;
}

BOOL CAccordionWnd::GetItemRect(RECT rcClient, unsigned int nIndex, LPRECT lpRect)
{
	if (nIndex >= m_vectorItems.size()) {
		return FALSE;
	}

	RECT rcItemHeader;
	rcItemHeader.left = rcClient.left + m_nPadding[PADDING_LEFT];
	rcItemHeader.right = rcClient.right - m_nPadding[PADDING_RIGHT];
	rcItemHeader.top = rcClient.top + m_nPadding[PADDING_TOP];
	rcItemHeader.bottom = rcItemHeader.top + ITEM_HEIGHT;
	for (size_t i = 0; i < m_vectorItems.size(); i++) {
		ACCORDIONITEM *pItem = m_vectorItems.at(i);
		if (pItem->bExpand) {
			rcItemHeader.bottom += pItem->nExpandHeight;
		}

		if (i == nIndex) {
			break;;
		}

		rcItemHeader.top = rcItemHeader.bottom + ITEM_SPACE;
		rcItemHeader.bottom = rcItemHeader.top + ITEM_HEIGHT;
	}


	CopyRect(lpRect, &rcItemHeader);
	return TRUE;
}

int CAccordionWnd::HitTest(POINT pt, int &nHitTest)
{
	int nRet = -1;
	nHitTest = -1;
	RECT rcClient;
	GetClientRect(m_hWnd, &rcClient);
	if (PtInRect(&rcClient, pt)) {
		nRet = 1;
	}

	int nItemIndex = -1;
	RECT rcItemHeader;
	for (size_t i = 0; i < m_vectorItems.size(); i++) {
		GetItemHeaderRect(rcClient, (unsigned int)i, &rcItemHeader);

		if (PtInRect(&rcItemHeader, pt)) {
			nItemIndex = (unsigned int)i;

			break;
		}
	}

	if (nItemIndex != -1) {
		nRet = 2;
		nHitTest = nItemIndex;
	}

	return nRet;
}

BOOL CAccordionWnd::Togle(unsigned int nIndex)
{
	if (nIndex >= m_vectorItems.size()) {
		return FALSE;
	}

	ACCORDIONITEM *pItem = m_vectorItems[nIndex];
	pItem->bExpand = !pItem->bExpand;


	// 重新调整个子窗口的位置
	ResizeItemWnd();

	RECT rcClient;
	GetClientRect(m_hWnd, &rcClient);
	::InvalidateRect(m_hWnd, &rcClient, TRUE);

	return TRUE;
}

void CAccordionWnd::Notify(int nCode, int dwData, int dwData1/* = 0*/, int dwData2/* = 0*/)
{
	HWND hParent;
	hParent = GetParent(m_hWnd);
	if (hParent != NULL) {
		ACCORDION_NMHDR accordionWndnmhdr;
		accordionWndnmhdr.nmhdr.hwndFrom = m_hWnd;
		accordionWndnmhdr.nmhdr.idFrom = GetWindowLong(m_hWnd, GWL_ID);
		accordionWndnmhdr.nmhdr.code = nCode;
		accordionWndnmhdr.dwData = dwData;
		accordionWndnmhdr.dwData1 = dwData1;
		accordionWndnmhdr.dwData2 = dwData2;
		SendMessage(hParent, WM_NOTIFY, (WPARAM)accordionWndnmhdr.nmhdr.idFrom, (LPARAM)&accordionWndnmhdr);
	}
}

/*
 * 拦截窗口消息函数
 */
LRESULT CALLBACK CAccordionWnd::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CAccordionWnd* pAccordionWnd = (CAccordionWnd *)GetProp(hWnd, ACCORDIONWND_TAG);
	if (pAccordionWnd == NULL && uMsg != WM_NCCREATE)
	{
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}


	// 如果Hook则响应消息
	ASSERT(hWnd);
	switch (uMsg)
	{
	case WM_NCCREATE:
		return CAccordionWnd::OnNcCreate(hWnd, wParam, lParam);

	case WM_DESTROY:
		return pAccordionWnd->OnDestroy(wParam, lParam);

	case WM_NCCALCSIZE:
		return pAccordionWnd->OnNcCalcsize(wParam, lParam);

	case WM_NCPAINT:
		return pAccordionWnd->OnNcPaint(wParam, lParam);

	case WM_PAINT:
		return pAccordionWnd->OnPaint(wParam, lParam);

	case WM_TIMER:
		return pAccordionWnd->OnTimer(wParam, lParam);

	case WM_MOUSEMOVE:
		return pAccordionWnd->OnMouseMove(wParam, lParam);

	case WM_LBUTTONDOWN:
		return pAccordionWnd->OnLButtonDown(wParam, lParam);

	case WM_LBUTTONUP:
		return pAccordionWnd->OnLButtonUp(wParam, lParam);

	case WM_MOUSEWHEEL:
		return pAccordionWnd->OnMouseWheel(wParam, lParam);

	case WM_SIZE:
		return pAccordionWnd->OnSize(wParam, lParam);

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
LRESULT CAccordionWnd::OnNcCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	CAccordionWnd* pAccordionWnd = (CAccordionWnd *)GetProp(hWnd, ACCORDIONWND_TAG);
	ASSERT(pAccordionWnd == NULL);

	Hook(hWnd);
	return ::DefWindowProc(hWnd, WM_NCCREATE, wParam, lParam);
}

/*
 * WM_NCCALCSIZE
 */
LRESULT CAccordionWnd::OnNcCalcsize(WPARAM wParam, LPARAM lParam)
{
	if (!m_bShadow) {
		return ::DefWindowProc(m_hWnd, WM_NCCALCSIZE, wParam, lParam);
	}


	LPRECT lprcWnd = (LPRECT)lParam;
	lprcWnd->left += BORDER;
	lprcWnd->top += BORDER;
	lprcWnd->right -= (BORDER + SHADOWWIDE);
	lprcWnd->bottom -= (BORDER + SHADOWWIDE);

	return 0;
}

/*
 * WM_DESTROY
 * 窗口销毁时
 */
LRESULT CAccordionWnd::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	Release();
	return ::DefWindowProc(m_hWnd, WM_DESTROY, wParam, lParam);
}


/*
 * WM_TIMER
 */
LRESULT CAccordionWnd::OnTimer(WPARAM wParam, LPARAM lParam)
{
	int nTimerId = (int)wParam;
	if (m_nTimerId == nTimerId) {

		POINT pt;
		::GetCursorPos(&pt);
		::ScreenToClient(m_hWnd, &pt);

		int nRet, nHitTest;
		nRet = HitTest(pt, nHitTest);
		if (m_nCheckHoverItem != nHitTest) {
			KillTimer(m_hWnd, m_nTimerId);
			m_nHoverItem = nHitTest;
			m_nCheckHoverItem = nHitTest;

			RECT rcClient;
			GetClientRect(m_hWnd, &rcClient);
			::InvalidateRect(m_hWnd, &rcClient, TRUE);
		}
	}


	return ::DefWindowProc(m_hWnd, WM_TIMER, wParam, lParam);
}

/*
 * WM_MOUSEMOVE
 * 鼠标移动时，检测鼠标位置并回调给主窗口
 */
LRESULT CAccordionWnd::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	pt.x = (int)LOWORD(lParam);
	pt.y = (int)HIWORD(lParam);

	int nRet, nHitTest;
	nRet = HitTest(pt, nHitTest);

	if (nRet == 2) {
		ACCORDIONITEM *pItem = m_vectorItems[nHitTest];
		if (pItem != NULL && pItem->bEnable) {
			::SetCursor(LoadCursor(NULL, IDC_HAND));
		}
	}
	else {
		::SetCursor(LoadCursor(NULL, IDC_ARROW));
	}

	int nLastItem = m_nHoverItem;
	if (m_nHoverItem != nHitTest) {
		m_nHoverItem = nHitTest;

		RECT rcClient, rcLastItemClient, rcCurItemClient;
		GetClientRect(m_hWnd, &rcClient);
		GetItemRect(rcClient, nLastItem, &rcLastItemClient);
		::InvalidateRect(m_hWnd, &rcLastItemClient, nHitTest < 0);

		if (nHitTest >= 0) {
			ACCORDIONITEM *pItem = m_vectorItems.at(nHitTest);
			if (!pItem->bEnable) {
				m_nHoverItem = -1;
			}
			else {
				KillTimer(m_hWnd, m_nTimerId);
				m_nTimerId = SetTimer(m_hWnd, TIMER_ID_CHECKHOVER, 200, NULL);
				m_nCheckHoverItem = m_nHoverItem;

				GetItemRect(rcClient, m_nHoverItem, &rcCurItemClient);
				::InvalidateRect(m_hWnd, &rcCurItemClient, TRUE);
			}
		}
	}


	return ::DefWindowProc(m_hWnd, WM_MOUSEMOVE, wParam, lParam);
}

/*
 * WM_LBUTTONDOWN
 * 鼠标左键下压
 */
LRESULT CAccordionWnd::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	pt.x = (int)LOWORD(lParam);
	pt.y = (int)HIWORD(lParam);

	int nRet, nHitTest;
	nRet = HitTest(pt, nHitTest);

	if (nRet == 2) {
		ACCORDIONITEM *pItem = m_vectorItems[nHitTest];
		if (pItem != NULL && pItem->bEnable) {
			::SetCursor(LoadCursor(NULL, IDC_HAND));
		}
	}
	else {
		::SetCursor(LoadCursor(NULL, IDC_ARROW));
	}


	return ::DefWindowProc(m_hWnd, WM_LBUTTONDOWN, wParam, lParam);
}

/*
 * WM_LBUTTONUP
 * 鼠标左键释放
 */
LRESULT CAccordionWnd::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	pt.x = (int)LOWORD(lParam);
	pt.y = (int)HIWORD(lParam);

	int nRet, nHitTest;
	nRet = HitTest(pt, nHitTest);

	if (nRet == 2) {
		ACCORDIONITEM *pItem = m_vectorItems[nHitTest];
		if (pItem != NULL && pItem->bEnable) {
			::SetCursor(LoadCursor(NULL, IDC_HAND));
			Togle(nHitTest);
		}
	}
	else {
		::SetCursor(LoadCursor(NULL, IDC_ARROW));
	}


	return ::DefWindowProc(m_hWnd, WM_LBUTTONUP, wParam, lParam);
}

/*
 * WM_MOUSEWHEEL
 * 鼠标滚轮滚动时，缩放图像
 */
LRESULT CAccordionWnd::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_MOUSEWHEEL, wParam, lParam);
}

/*
 * WM_NCPAINT
 */
LRESULT CAccordionWnd::OnNcPaint(WPARAM wParam, LPARAM lParam)
{
	LRESULT lRet = ::DefWindowProc(m_hWnd, WM_NCPAINT, wParam, lParam);


	// 然后画边框
	long styleEx = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if ((styleEx & WS_EX_CLIENTEDGE) == WS_EX_CLIENTEDGE) {

		RECT rcWindow, rcClient;
		GetClientRect(m_hWnd, &rcClient);
		::ClientToScreen(m_hWnd, (LPPOINT)&rcClient.left);
		::ClientToScreen(m_hWnd, (LPPOINT)&rcClient.right);
		GetWindowRect(m_hWnd, &rcWindow);
		::OffsetRect(&rcClient, -rcWindow.left, -rcWindow.top);
		::OffsetRect(&rcWindow, -rcWindow.left, -rcWindow.top);

		HRGN hRgnWnd = CreateRectRgnIndirect(&rcWindow);
		HRGN hRgnClient = CreateRectRgnIndirect(&rcClient);

		HDC hDC = GetWindowDC(m_hWnd);
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
		ReleaseDC(m_hWnd, hDC);
	}

	return lRet;
}

/*
 * WM_PAINT
 */
LRESULT CAccordionWnd::OnPaint(WPARAM wParam, LPARAM lParam)
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
	::SetBkMode(hMemDC, TRANSPARENT);


	// 背景颜色
	hBrushBK = CreateSolidBrush(m_crBkgnd);
	::FillRect(hMemDC, &rcClient, hBrushBK);
	DeleteObject(hBrushBK);


	// 绘子项列表
	hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	::SelectObject(hMemDC, hFont);

	HPEN hPenSeparate = ::CreatePen(PS_SOLID, 1, m_crSeparateLine);
	RECT rcItem, rcItemHeader;
	for (size_t i = 0; i < m_vectorItems.size(); i++) {
		ACCORDIONITEM *pItem = m_vectorItems[i];
		GetItemRect(rcClient, i, &rcItem);
		GetItemHeaderRect(rcClient, i, &rcItemHeader);


		// 热点项的背景色和边框
		if (m_nHoverItem == (int)i) {
			HBRUSH hbrItemHeaderBackground = CreateSolidBrush(m_crHoverItemBackground);
			HBRUSH hbrItemFrame = CreateSolidBrush(m_crHoverItemFrame);

			HRGN hRgn = CreateRoundRectRgn(rcItemHeader.left, rcItemHeader.top, rcItemHeader.right, rcItemHeader.bottom, 2, 2);
			::FillRgn(hMemDC, hRgn, hbrItemHeaderBackground);
			::FrameRgn(hMemDC, hRgn, hbrItemFrame, 1, 1);
			::DeleteObject(hbrItemHeaderBackground);
			::DeleteObject(hbrItemFrame);
			::DeleteObject(hRgn);
		}


		// 箭头
		BOOL bDrawIcon = DrawIconEx(hMemDC, rcItemHeader.left + (ITEM_HEIGHT - EXPAND_ICON_WIDE) / 2, rcItemHeader.top + (ITEM_HEIGHT - EXPAND_ICON_WIDE)/2,
			pItem->bExpand ? m_hIconExpand : m_hIconClose, EXPAND_ICON_WIDE, EXPAND_ICON_WIDE, 0, 0, DI_NORMAL);


		// 文本
		::SetTextColor(hMemDC, RGB(0, 0, 0));
		RECT rcText;
		rcText.left = rcItemHeader.left + (bDrawIcon ? ITEM_HEIGHT : (ITEM_HEIGHT - EXPAND_ICON_WIDE) / 2);
		rcText.top = rcItemHeader.top;
		rcText.right = rcItemHeader.right;
		rcText.bottom = rcItemHeader.bottom;
		::DrawText(hMemDC, pItem->text, (int)strlen(pItem->text), &rcText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);


		// 文本右边分隔线
		SIZE sizeText;
		GetTextExtentPoint32(hMemDC, pItem->text, (int)strlen(pItem->text), &sizeText);


		HPEN hOldPen = (HPEN)::SelectObject(hMemDC, hPenSeparate);
		MoveToEx(hMemDC, rcText.left + sizeText.cx + 10, rcItemHeader.top+(rcItemHeader.bottom- rcItemHeader.top-1)/2, NULL);
		LineTo(hMemDC, rcItemHeader.right-10, rcItemHeader.top+(rcItemHeader.bottom - rcItemHeader.top - 1) / 2);
		::SelectObject(hMemDC, hOldPen);


		rcItemHeader.top = rcItemHeader.bottom + ITEM_SPACE;
		rcItemHeader.bottom = rcItemHeader.top + ITEM_HEIGHT;
	}
	::DeleteObject(hPenSeparate);


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
LRESULT CAccordionWnd::OnSize(WPARAM wParam, LPARAM lParam)
{
	LRESULT lRet = ::DefWindowProc(m_hWnd, WM_SIZE, wParam, lParam);

	ResizeItemWnd();

	return lRet;
}

/*
 * 设置背景色
 * color -- 背景色
 */
void CAccordionWnd::SetBkgndColor(COLORREF color)
{
	m_crBkgnd = color;
}


/*
 * 设置阴影的背景色(即父窗口的背景)
 * color -- 背景色
 */
void CAccordionWnd::SetShadowBkgnd(COLORREF color)
{
	m_crShadowBkgnd = color;
}

/*
 * 设置边框颜色
 * color -- 边框颜色
 */
void CAccordionWnd::SetFrameColor(COLORREF color, BOOL bShadow/* = FALSE*/)
{
	m_crFrame = color;
	m_bShadow = bShadow;
	SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

