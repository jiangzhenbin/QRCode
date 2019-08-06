// ResendDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QRCode.h"
#include "ResendDlg.h"
#include "afxdialogex.h"
#include "PageTestList.h"


// CResendDlg 对话框

IMPLEMENT_DYNAMIC(CResendDlg, CDialogEx)

CResendDlg::CResendDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_RESEND, pParent)
{
	m_pAoiManager = NULL;
}

CResendDlg::~CResendDlg()
{
}

void CResendDlg::SetAoiManager(CAoiManager * pAoiManager)
{
	m_pAoiManager = pAoiManager;
}

void CResendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CResendDlg, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CResendDlg::OnBnClickedOk)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CResendDlg 消息处理程序


BOOL CResendDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST1);
	DWORD dwStyle = pListCtrl->GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;			// 选中整行高亮
	dwStyle |= LVS_EX_GRIDLINES;				// 网格线
	pListCtrl->SetExtendedStyle(dwStyle); // 设置扩展风格

	HIMAGELIST imageList = ImageList_Create(24, 24, ILC_COLOR24, 1, 1);
	ListView_SetImageList(pListCtrl->GetSafeHwnd(), imageList, LVSIL_SMALL);

	pListCtrl->InsertColumn(0, _T(""), LVCFMT_RIGHT, 0);
	pListCtrl->InsertColumn(1, _T("Code"), LVCFMT_LEFT, 260);
	pListCtrl->InsertColumn(2, _T("状态"), LVCFMT_LEFT, 120);


	SetTimer(1, 200, NULL);


	ASSERT(m_pAoiManager);
	auto onCodeStateChanged = [&](CQRCode *pQRCode) -> void {
		CListCtrl *pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
		if (pList != NULL) {
			for (int i = 0; i < pList->GetItemCount(); i++) {
				CString strCode = pList->GetItemText(i, 1);
				if (strCode.Compare(pQRCode->code) == 0) {
					pList->SetItemText(i, 2, CPageTestList::GetQRCodeStateText(pQRCode->state));
					if (pQRCode->state == CODESTATE::SUCCEED) {
						POSITION pos = m_strCodeList.GetHeadPosition();
						while (pos != NULL) {
							POSITION pos2 = pos;
							CString strCode2 = m_strCodeList.GetNext(pos);
							if (strCode2.Compare(strCode) == 0) {
								m_strCodeList.RemoveAt(pos2);
								break;
							}
						}

						pList->DeleteItem(i);
					}
					break;
				}
			}

			if (pList->GetItemCount() == 0) {
				CWnd *pItem = GetDlgItem(IDOK);
				if (pItem != NULL) {
					pItem->EnableWindow(TRUE);
				}
			}
		}
	};
	m_pAoiManager->SetOnCodeStateChangedListener(onCodeStateChanged);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CResendDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1) {
		KillTimer(1);

		CString strFilepath;
		strFilepath.Format(_T("%s\\CacheCode.txt"), theApp.m_strAppDir);
		ReadCacheCodes(strFilepath, m_strCodeList);
		UpdateList();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CResendDlg::ReadCacheCodes(CString strFilepath, CStringList &stringList)
{
	stringList.RemoveAll();
	CStdioFile file;
	if (file.Open(strFilepath, CFile::modeRead)) {
		CString strCode;
		while (file.ReadString(strCode)) {
			stringList.AddTail(strCode);
		}

		file.Close();
	}
}

void CResendDlg::SaveCacheCodes(CString strFilepath, CStringList &stringList)
{
	CStdioFile file;
	if (file.Open(strFilepath, CFile::modeCreate|CFile::modeWrite)) {
		POSITION pos = stringList.GetHeadPosition();
		while (pos != NULL) {
			CString strCode = stringList.GetNext(pos);
			file.WriteString(strCode +"\r\n");
		}

		file.Close();
	}
}

void CResendDlg::UpdateList()
{
	CListCtrl *pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	pList->DeleteAllItems();

	POSITION pos = m_strCodeList.GetHeadPosition();
	while (pos != NULL) {
		CString strCode = m_strCodeList.GetNext(pos);

		int nIndex = pList->InsertItem(pList->GetItemCount(), _T(""));
		pList->SetItemText(nIndex, 1, strCode);
		pList->SetItemText(nIndex, 2, _T(""));
	}

	GetDlgItem(IDOK)->EnableWindow(pList->GetItemCount() > 0);
}

void CResendDlg::OnBnClickedOk()
{
	// CDialogEx::OnOK();

	ASSERT(m_pAoiManager != NULL);
	if (m_strCodeList.GetCount() > 0) {
		m_pAoiManager->ResendCodes(m_strCodeList);
		GetDlgItem(IDOK)->EnableWindow(FALSE);
	}
}


void CResendDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	CString strFilepath;
	strFilepath.Format(_T("%s\\CacheCode.txt"), theApp.m_strAppDir);
	SaveCacheCodes(strFilepath, m_strCodeList);
}
