#pragma once
#include <functional>
#include <vector>

#ifndef ACCORDIONWND_TAG

#ifdef _WIN32

#define ACCORDIONWND_CLASSA		"AccordionWnd"
#define ACCORDIONWND_CLASSW		L"AccordionWnd"

#ifdef UNICODE
#define ACCORDIONWND_CLASS		ACCORDIONWND_CLASSW
#else
#define ACCORDIONWND_CLASS		ACCORDIONWND_CLASSA
#endif

#else
#define ACCORDIONWND_CLASS      "AccordionWnd"
#endif


#define ACCORDIONWND_TAG		_T("ACCORDIONWND_TAG")

#define ACCORDIONWND_FIRST		(0U-3590U)
#define ACCORDIONWND_LAST		(0U-5350U)
#define ACCORDIONWND_			(ACCORDIONWND_FIRST - 1)

typedef struct tagACCORDION_NMHDR
{
	NMHDR		nmhdr;
	DWORD		dwData;
	DWORD		dwData1;
	DWORD		dwData2;
} ACCORDION_NMHDR;

typedef struct tagACCORDIONITEM
{
	unsigned int id;
	int nExpandHeight;
	COLORREF crBackground[2];
	COLORREF crFrame[2];
	COLORREF crText[2];
	char text[256];
	CWnd *pWnd;
	BOOL bExpand;
	BOOL bEnable;				// 是否可以点击展开和收起
} ACCORDIONITEM;

#endif

#define PADDING_LEFT		0
#define PADDING_TOP			1
#define PADDING_RIGHT		2
#define PADDING_BOTTOM		3

class CAccordionWnd
{
public:
	CAccordionWnd();
	~CAccordionWnd();


public:
	static BOOL RegisterWndClass();
	static CAccordionWnd * FromHandle(HWND hWnd);
	void SetFrameColor(COLORREF color, BOOL bShadow = FALSE);
	void SetBkgndColor(COLORREF color);
	void SetShadowBkgnd(COLORREF color);

public:
	void LoadExpandIcon(CString strExpandFile, CString strCloseFile);
	void Setpadding(int type, unsigned int nPadding);
	void SetDefaultItemBackgroundColor(COLORREF crNormal, COLORREF crSel);
	void SetDefaultItemFrameColor(COLORREF crNormal, COLORREF crSel);
	void SetDefaultItemTextColor(COLORREF crNormal, COLORREF crSel);
	void AddItem(char *pszName, CWnd *pWnd, int nExpandHeight, BOOL bExpand = TRUE, BOOL bEnable = TRUE);
	BOOL Togle(unsigned int nIndex);

private:
	void Init();
	void Notify(int nCode, int dwData, int dwData1 = 0, int dwData2 = 0);
	void Release();
	void ResizeItemWnd();
	static CAccordionWnd* Hook(HWND hWnd);
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT OnNcCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
	LRESULT OnTimer(WPARAM wParam, LPARAM lParam);
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
	HICON		m_hIconClose;
	HICON		m_hIconExpand;
	int			m_nHoverItem;
	int			m_nCheckHoverItem;
	BOOL		m_bShadow;				// 阴影
	COLORREF	m_crShadowBkgnd;		// 阴影背景色(即父窗口的颜色)

private:
	unsigned int m_nPadding[4];
	COLORREF m_crItemBackground[2];
	COLORREF m_crItemFrame[2];
	COLORREF m_crItemText[2];
	COLORREF m_crSeparateLine;
	COLORREF m_crHoverItemBackground;
	COLORREF m_crHoverItemFrame;
	CString m_strExpandIconFilepath[2];

private:
	std::vector<ACCORDIONITEM *> m_vectorItems;
	int m_nTimerId;

private:
	int HitTest(POINT pt, int &nHitTest);
	BOOL GetItemHeaderRect(RECT rcClient, unsigned int nIndex, LPRECT lpRect);
	BOOL GetItemRect(RECT rcClient, unsigned int nIndex, LPRECT lpRect);
};

