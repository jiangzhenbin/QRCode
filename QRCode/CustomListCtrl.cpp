#include "stdafx.h"
#include "CustomListCtrl.h"


CCustomListCtrl::CCustomListCtrl()
{
}


CCustomListCtrl::~CCustomListCtrl()
{
	ResetAllItem(FALSE);
}

BEGIN_MESSAGE_MAP(CCustomListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CCustomListCtrl::OnNMCustomdraw)
END_MESSAGE_MAP()

void CCustomListCtrl::ResetAllItem(BOOL bInvalidate/* = FALSE*/)
{
	for (int i = 0; i < m_arItem.GetCount(); i++) {
		LISTITEM *pItem = (LISTITEM *)m_arItem.GetAt(i);
		delete pItem;
	}

	m_arItem.RemoveAll();

	if (bInvalidate) {
		Invalidate();
	}
}

BOOL CCustomListCtrl::SetItemColor(int nIndex, int nSubItem, COLORREF crTextBk, COLORREF crText)
{
	if (nIndex >= GetItemCount()) {
		return FALSE;
	}

	LISTITEM *pItem = new LISTITEM;
	memset(pItem, 0, sizeof(LISTITEM));
	pItem->row = nIndex;
	pItem->col = nSubItem;
	pItem->crTextBk = crTextBk;
	pItem->crText = crText;
	m_arItem.Add(pItem);

	Invalidate();
	return TRUE;
}

void CCustomListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	*pResult = CDRF_DODEFAULT;


	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.

	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage) {
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage) {
		// This is the notification message for an item. We'll request
		// notifications before each subitem's prepaint stage.
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ((CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage) {  
		// 仅当pLVCD结构体中nmcd成员的dwDrawStage状态为CDDS_ITEMPREPAINT | CDDS_SUBITEM时
		// 我们就可以判断“行”和“列”，从而来设置文字颜色和文字背景颜色了。
		// This is the prepaint stage for a subitem. Here's where we set the
		// item's text and background colors. Our return value will tell 
		// Windows to draw the subitem itself, but it will use the new colors
		// we set here. 

		pLVCD->clrTextBk = RGB(255, 255, 255);
		pLVCD->clrText = RGB(0, 0, 0);

		for (int i = 0; i < m_arItem.GetCount(); i++) {
			LISTITEM *pItem = (LISTITEM *)m_arItem.GetAt(i);
			if (pItem->col == -1 && pItem->row == pLVCD->nmcd.dwItemSpec) {
				pLVCD->clrTextBk = pItem->crTextBk;
				pLVCD->clrText = pItem->crText;
			}
			else if (pItem->col == pLVCD->iSubItem && pItem->row == pLVCD->nmcd.dwItemSpec) {
				pLVCD->clrTextBk = pItem->crTextBk;
				pLVCD->clrText = pItem->crText;
			}
		}

		*pResult = CDRF_DODEFAULT;
	}
}
