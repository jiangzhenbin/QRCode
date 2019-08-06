#include "stdafx.h"
#include "MilPreview.h"

#define BORDER			5
#define SHADOWWIDE		5


#define GRAPHTAG  _T("CMilPreviewGraphTag")
#define GRAPHWNDCLASS  _T("CMilPreviewGraph")

CMilPreviewGraph::CMilPreviewGraph()
{
	m_hWnd = NULL;
}


CMilPreviewGraph::~CMilPreviewGraph()
{
}

BOOL CMilPreviewGraph::RegisterWndClass()
{
	WNDCLASS wc;
	wc.lpszClassName = GRAPHWNDCLASS;
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

void CMilPreviewGraph::Release()
{
	// delete
	delete this;
}

CMilPreviewGraph * CMilPreviewGraph::FromHandle(HWND hWnd)
{
	CMilPreviewGraph *pMilPreview = (CMilPreviewGraph *)::GetProp(hWnd, GRAPHTAG);
	return pMilPreview;
}

CMilPreviewGraph* CMilPreviewGraph::Hook(HWND hWnd)
{
	CMilPreviewGraph* pGraph = (CMilPreviewGraph*)GetProp(hWnd, GRAPHTAG);
	if (pGraph == NULL) {
		pGraph = new CMilPreviewGraph();
		pGraph->m_hWnd = hWnd;

		SetProp(hWnd, GRAPHTAG, (HANDLE)pGraph);
	}


	return pGraph;
}

void CMilPreviewGraph::Destroy()
{
	if (m_hWnd != NULL) {
		::DestroyWindow(m_hWnd);
	}
}

HWND CMilPreviewGraph::GetSafeHwnd()
{
	return m_hWnd;
}

/*
 * 拦截窗口消息函数
 */
LRESULT CALLBACK CMilPreviewGraph::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CMilPreviewGraph* pGraph = (CMilPreviewGraph *)GetProp(hWnd, GRAPHTAG);
	if (pGraph == NULL && uMsg != WM_NCCREATE)
	{
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}


	// 如果Hook则响应消息
	ASSERT(hWnd);
	switch (uMsg)
	{
	case WM_NCCREATE:
		return CMilPreviewGraph::OnNcCreate(hWnd, wParam, lParam);

	case WM_DESTROY:
		return pGraph->OnDestroy(wParam, lParam);

	default:
		break;
	}

	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/*
 * WM_NCCREATE
 * 窗口创建前的初始化工作
 */
LRESULT CMilPreviewGraph::OnNcCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	CMilPreviewGraph* pGraph = (CMilPreviewGraph *)GetProp(hWnd, GRAPHTAG);
	ASSERT(pGraph == NULL);

	Hook(hWnd);
	return ::DefWindowProc(hWnd, WM_NCCREATE, wParam, lParam);
}

/*
 * WM_DESTROY
 * 窗口销毁时
 */
LRESULT CMilPreviewGraph::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	Release();
	return ::DefWindowProc(m_hWnd, WM_DESTROY, wParam, lParam);
}

CMilPreview::CMilPreview()
{
	m_hWnd = NULL;
	m_crFrame = RGB(238, 238, 238);
	m_crBkgnd = RGB(255, 255, 255);
	m_bShadow = FALSE;
	m_crShadowBkgnd = GetSysColor(COLOR_BTNFACE);
	m_crBkgndLine = RGB(245, 245, 245);
	m_pGraph = NULL;
}

CMilPreview::~CMilPreview()
{
}

BOOL CMilPreview::RegisterWndClass()
{
	CMilPreviewGraph::RegisterWndClass();

	WNDCLASS wc;
	wc.lpszClassName = MILPREVIEW_CLASS;
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

CMilPreview * CMilPreview::FromHandle(HWND hWnd)
{
	CMilPreview *pMilPreview = (CMilPreview *)::GetProp(hWnd, MILPREVIEW_TAG);
	return pMilPreview;
}

HWND CMilPreview::GetSafeHwnd()
{
	return m_hWnd;
}

HWND CMilPreview::GetGraphHwnd()
{
	if (m_pGraph == NULL) {
		HWND hWnd = ::CreateWindowEx(0, GRAPHWNDCLASS, _T(""), WS_CHILD | WS_VISIBLE, 0, 0, 300, 300, m_hWnd, NULL, NULL, NULL);
		if (hWnd != NULL) {
			m_pGraph = CMilPreviewGraph::FromHandle(hWnd);
			Resize();
		}
	}

	if (m_pGraph == NULL) {
		return NULL;
	}

	return m_pGraph->GetSafeHwnd();
}


CMilPreview* CMilPreview::Hook(HWND hWnd)
{
	CMilPreview* pMilPreview = (CMilPreview*)GetProp(hWnd, MILPREVIEW_TAG);
	if (pMilPreview == NULL) {
		pMilPreview = new CMilPreview();
		pMilPreview->m_hWnd = hWnd;

		SetProp(hWnd, MILPREVIEW_TAG, (HANDLE)pMilPreview);
	}


	return pMilPreview;
}

void CMilPreview::Release()
{
	// delete
	delete this;
}

void CMilPreview::Notify(int nCode, int dwData, int dwData1/* = 0*/, int dwData2/* = 0*/)
{
	HWND hParent;
	hParent = GetParent(m_hWnd);
	if (hParent != NULL) {
		MILPREVIEW_NMHDR midPreviewNmhdr;
		midPreviewNmhdr.nmhdr.hwndFrom = m_hWnd;
		midPreviewNmhdr.nmhdr.idFrom = GetWindowLong(m_hWnd, GWL_ID);
		midPreviewNmhdr.nmhdr.code = nCode;
		midPreviewNmhdr.dwData = dwData;
		midPreviewNmhdr.dwData1 = dwData1;
		midPreviewNmhdr.dwData2 = dwData2;
		SendMessage(hParent, WM_NOTIFY, (WPARAM)midPreviewNmhdr.nmhdr.idFrom, (LPARAM)&midPreviewNmhdr);
	}
}

void CMilPreview::Resize()
{
	if (m_pGraph != NULL) {
		HWND hWnd = m_pGraph->GetSafeHwnd();
		RECT rcClient;
		GetClientRect(m_hWnd, &rcClient);

		int nImgWidth = 16384;
		int nImgHeight = 12000;
		double fZoom = min((double)(rcClient.right-40) / (double)nImgWidth, (double)(rcClient.bottom-40) / (double)nImgHeight);
		int nGraphWidth = int(fZoom * nImgWidth);
		int nGraphHeight = int(fZoom * nImgHeight);
		::MoveWindow(hWnd, (rcClient.right - nGraphWidth)/2, (rcClient.bottom - nGraphHeight) / 2, nGraphWidth, nGraphHeight, TRUE);
	}

	RECT rcClient;
	GetClientRect(m_hWnd, &rcClient);
	::InvalidateRect(m_hWnd, &rcClient, TRUE);
}

/*
 * 拦截窗口消息函数
 */
LRESULT CALLBACK CMilPreview::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CMilPreview* pMilPreview = (CMilPreview *)GetProp(hWnd, MILPREVIEW_TAG);
	if (pMilPreview == NULL && uMsg != WM_NCCREATE)
	{
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}


	// 如果Hook则响应消息
	ASSERT(hWnd);
	switch (uMsg)
	{
	case WM_NCCREATE:
		return CMilPreview::OnNcCreate(hWnd, wParam, lParam);

	case WM_DESTROY:
		return pMilPreview->OnDestroy(wParam, lParam);

	case WM_NCCALCSIZE:
		return pMilPreview->OnNcCalcsize(wParam, lParam);

	case WM_NCPAINT:
		return pMilPreview->OnNcPaint(wParam, lParam);

	case WM_PAINT:
		return pMilPreview->OnPaint(wParam, lParam);

	case WM_MOUSEMOVE:
		return pMilPreview->OnMouseMove(wParam, lParam);

	case WM_LBUTTONDOWN:
		return pMilPreview->OnLButtonDown(wParam, lParam);

	case WM_LBUTTONUP:
		return pMilPreview->OnLButtonUp(wParam, lParam);

	case WM_MOUSEWHEEL:
		return pMilPreview->OnMouseWheel(wParam, lParam);

	case WM_SIZE:
		return pMilPreview->OnSize(wParam, lParam);

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
LRESULT CMilPreview::OnNcCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	CMilPreview* pMilPreview = (CMilPreview *)GetProp(hWnd, MILPREVIEW_TAG);
	ASSERT(pMilPreview == NULL);

	Hook(hWnd);
	return ::DefWindowProc(hWnd, WM_NCCREATE, wParam, lParam);
}

/*
* WM_NCCALCSIZE
*/
LRESULT CMilPreview::OnNcCalcsize(WPARAM wParam, LPARAM lParam)
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
LRESULT CMilPreview::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	if (m_pGraph != NULL) {
		m_pGraph->Destroy();
	}

	Release();
	return ::DefWindowProc(m_hWnd, WM_DESTROY, wParam, lParam);
}

/*
 * WM_MOUSEMOVE
 * 鼠标移动时，检测鼠标位置并回调给主窗口
 */
LRESULT CMilPreview::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_MOUSEMOVE, wParam, lParam);
}

/*
 * WM_LBUTTONDOWN
 * 鼠标左键下压
 */
LRESULT CMilPreview::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_LBUTTONDOWN, wParam, lParam);
}

/*
 * WM_LBUTTONUP
 * 鼠标左键释放
 */
LRESULT CMilPreview::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{

	return ::DefWindowProc(m_hWnd, WM_LBUTTONUP, wParam, lParam);
}

/*
 * WM_MOUSEWHEEL
 * 鼠标滚轮滚动时，缩放图像
 */
LRESULT CMilPreview::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_MOUSEWHEEL, wParam, lParam);
}

/*
 * WM_NCPAINT
 */
LRESULT CMilPreview::OnNcPaint(WPARAM wParam, LPARAM lParam)
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
LRESULT CMilPreview::OnPaint(WPARAM wParam, LPARAM lParam)
{
	HDC hDC, hMemDC;
	HBITMAP hBitmap;
	RECT rcClient;
	CString strText;
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

	
	// 背景线
	HPEN hPen = CreatePen(PS_SOLID, 1, m_crBkgndLine);
	HPEN hOldPen = (HPEN)::SelectObject(hMemDC, hPen);
	int nStep = (rcClient.bottom - rcClient.top) / 9;
	for (int y = 1; y < 9; y++) {
		MoveToEx(hMemDC, rcClient.left, y * nStep, NULL);
		LineTo(hMemDC, rcClient.right, y * nStep);
	}
	nStep = (rcClient.right - rcClient.left) / 9;
	for (int x = 1; x < 9; x++) {
		MoveToEx(hMemDC, x * nStep, 0, NULL);
		LineTo(hMemDC, x * nStep, rcClient.bottom);
	}
	SelectObject(hMemDC, hOldPen);


	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	::SelectObject(hMemDC, hFont);


	// 窗口文本
	char szTitle[256];
	GetWindowText(m_hWnd, szTitle, 256);
	RECT rcTitle;
	rcTitle.left = rcClient.left + 2;
	rcTitle.top = rcClient.top + 2;
	rcTitle.bottom = rcClient.bottom - 2;
	rcTitle.right = rcClient.right - 2;
	::SetTextColor(hMemDC, RGB(118, 118, 118));
	::DrawText(hMemDC, szTitle, (int)strlen(szTitle), &rcTitle, DT_CENTER | DT_VCENTER | DT_SINGLELINE);



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
LRESULT CMilPreview::OnSize(WPARAM wParam, LPARAM lParam)
{
	LRESULT lRet = ::DefWindowProc(m_hWnd, WM_SIZE, wParam, lParam);

	Resize();

	return lRet;
}

/*
 * 设置背景色
 * color -- 背景色
 */
void CMilPreview::SetBkgndColor(COLORREF color)
{
	m_crBkgnd = color;
}


/*
 * 设置阴影的背景色(即父窗口的背景)
 * color -- 背景色
 */
void CMilPreview::SetShadowBkgnd(COLORREF color)
{
	m_crShadowBkgnd = color;
}

/*
 * 设置边框颜色
 * color -- 边框颜色
 */
void CMilPreview::SetFrameColor(COLORREF color, BOOL bShadow/* = FALSE*/)
{
	m_crFrame = color;
	m_bShadow = bShadow;
	SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

