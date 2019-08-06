#pragma once
#include "afxcmn.h"


typedef struct tagLISTITEM
{
	int row;
	int col;
	COLORREF crTextBk;
	COLORREF crText;
} LISTITEM;

class CCustomListCtrl :
	public CListCtrl
{
public:
	CCustomListCtrl();
	~CCustomListCtrl();

	
public:
	BOOL SetItemColor(int nIndex, int nSubItem, COLORREF crTextBk, COLORREF crText);
	void ResetAllItem(BOOL bInvalidate = TRUE);

private:
	CPtrArray m_arItem;


protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
};

