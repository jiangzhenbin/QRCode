#pragma once

#ifndef MILPREVIEW_TAG

#ifdef _WIN32

#define MILPREVIEW_CLASSA		"MilPreviewWnd"
#define MILPREVIEW_CLASSW		L"MilPreviewWnd"

#ifdef UNICODE
#define MILPREVIEW_CLASS		MILPREVIEW_CLASSW
#else
#define MILPREVIEW_CLASS		MILPREVIEW_CLASSA
#endif

#else
#define MILPREVIEW_CLASS      "MilPreviewWnd"
#endif


#define MILPREVIEW_TAG			_T("MILPREVIEW_TAG")

#define MILPREVIEW_FIRST		(0U-3990U)
#define MILPREVIEW_LAST			(0U-5950U)
#define MILPREVIEW_				(MILPREVIEW_FIRST - 1)

typedef struct tagMILPREVIEW_NMHDR
{
	NMHDR		nmhdr;
	DWORD		dwData;
	DWORD		dwData1;
	DWORD		dwData2;
}  MILPREVIEW_NMHDR;

#endif

class CMilPreviewGraph
{
public:
	CMilPreviewGraph();
	~CMilPreviewGraph();

public:
	static BOOL RegisterWndClass();
	static CMilPreviewGraph * FromHandle(HWND hWnd);
	void Destroy();
	HWND GetSafeHwnd();

private:
	void Release();
	static CMilPreviewGraph* Hook(HWND hWnd);
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT OnNcCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);

private:
	HWND		m_hWnd;
};

class CMilPreview
{
public:
	CMilPreview();
	~CMilPreview();

public:
	static BOOL RegisterWndClass();
	static CMilPreview * FromHandle(HWND hWnd);
	HWND GetSafeHwnd();
	HWND GetGraphHwnd();
	void SetFrameColor(COLORREF color, BOOL bShadow = FALSE);
	void SetBkgndColor(COLORREF color);
	void SetShadowBkgnd(COLORREF color);

private:
	void Resize();
	void Notify(int nCode, int dwData, int dwData1 = 0, int dwData2 = 0);
	void Release();
	static CMilPreview* Hook(HWND hWnd);
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT OnNcCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
	LRESULT OnNcPaint(WPARAM wParam, LPARAM lParam);
	LRESULT OnNcCalcsize(WPARAM wParam, LPARAM lParam);
	LRESULT OnPaint(WPARAM wParam, LPARAM lParam);
	LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);
	LRESULT OnMouseWheel(WPARAM wParam, LPARAM lParam);
	LRESULT OnSize(WPARAM wParam, LPARAM lParam);

private:
	HWND		m_hWnd;
	COLORREF	m_crBkgnd;
	COLORREF	m_crFrame;	
	BOOL		m_bShadow;				// 阴影
	COLORREF	m_crShadowBkgnd;		// 阴影背景色(即父窗口的颜色)
	COLORREF	m_crBkgndLine;

private:
	CMilPreviewGraph *m_pGraph;
};

