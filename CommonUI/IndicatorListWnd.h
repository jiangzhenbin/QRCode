#pragma once

#include <functional>


#ifndef INDICATORLISTWND_TAG

#ifdef _WIN32

#define INDICATORLISTWND_CLASSA		"IndicatorListWnd"
#define INDICATORLISTWND_CLASSW		L"IndicatorListWnd"

#ifdef UNICODE
#define INDICATORLISTWND_CLASS		INDICATORLISTWND_CLASSW
#else
#define INDICATORLISTWND_CLASS		INDICATORLISTWND_CLASSA
#endif

#else
#define INDICATORLISTWND_CLASS      "IndicatorListWnd"
#endif


#define INDICATORLISTWND_TAG		_T("INDICATORLISTWND_TAG")

#define INDICATORLISTWND_FIRST		(0U-2890U)
#define INDICATORLISTWND_LAST		(0U-2850U)
#define INDICATORLISTWND_			(INDICATORLISTWND_FIRST - 1)


#ifndef MIN
#define MIN(X,Y) (((X)>(Y))?(Y):(X))
#endif

#ifndef MAX
#define MAX(X,Y) (((X)>(Y))?(X):(Y))
#endif

typedef struct tagINDICATORLIST_NMHDR
{
	NMHDR		nmhdr;
	DWORD		dwData;
	DWORD		dwData1;
	DWORD		dwData2;
} INDICATORLIST_NMHDR;

typedef struct tagINDICATOR
{
	unsigned int id;
	char text[256];
	void *pData;
	int state;			/* 0:¾ÍÐ÷ 1:Pass 2:NG */
} INDICATOR;

#endif

typedef std::function<void(double, double)> ONPOSCHANGED;

class CIndicatorListWnd
{
public:
	CIndicatorListWnd();
	~CIndicatorListWnd();


public:
	static BOOL RegisterWndClass();
	static CIndicatorListWnd * FromHandle(HWND hWnd);
	void SetFrameColor(COLORREF color);
	void SetBkgndColor(COLORREF color);

public:
	void SetItemSpace(unsigned int nItemSpace);
	void SetItemWide(unsigned int nItemWide);
	void SetItemRound(int nRound);
	void SetDefaultItemBackgroundColor(COLORREF crNormal, COLORREF crSel);
	void SetDefaultItemFrameColor(COLORREF crNormal, COLORREF crSel);
	void SetDefaultItemTextColor(COLORREF crNormal, COLORREF crSel);
	void SetOnPosChangedListener(ONPOSCHANGED listener);
	INDICATOR * AddIndicator(int index, CString strText);
	void SetItemState(int nIndex, int nState);

private:
	void Init();
	void DrawAllText(BOOL bClearWindow);
	void Notify(int nCode, int dwData, int dwData1 = 0, int dwData2 = 0);
	void Release();
	static CIndicatorListWnd* Hook(HWND hWnd);
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT OnNcCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
	LRESULT OnTimer(WPARAM wParam, LPARAM lParam);
	LRESULT OnNcPaint(WPARAM wParam, LPARAM lParam);
	LRESULT OnPaint(WPARAM wParam, LPARAM lParam);
	LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
	LRESULT OnMouseWheel(WPARAM wParam, LPARAM lParam);
	LRESULT OnSize(WPARAM wParam, LPARAM lParam);

private:
	HWND		m_hWnd;
	COLORREF	m_crBkgnd;
	COLORREF	m_crFrame;


private:
	unsigned int m_nItemSpace;
	unsigned int m_nItemWide;
	COLORREF m_crItemBackground[4];
	COLORREF m_crItemFrame[4];
	COLORREF m_crItemText[4];
	ONPOSCHANGED m_onPosChanged;
	CPtrArray m_arIndicator;
	int m_nItemRound;
};

