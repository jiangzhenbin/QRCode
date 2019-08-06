// PageInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QRCode.h"
#include "PageInfo.h"
#include "afxdialogex.h"


// CPageInfo �Ի���

IMPLEMENT_DYNAMIC(CPageInfo, CDialogEx)

CPageInfo::CPageInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE_INFO, pParent)
{
	m_crBkgnd = RGB(255, 255, 255);
	m_brBkgnd.CreateSolidBrush(m_crBkgnd);
}

CPageInfo::~CPageInfo()
{
}

void CPageInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CPageInfo::SetSettingsPtr(CSettings *pSettings)
{
	m_pSettings = pSettings;
}

void CPageInfo::SetTotal(unsigned int nTotal)
{
	SetDlgItemInt(IDC_EDIT_TOTAL, nTotal);
	SetDlgItemInt(IDC_EDIT_NGCOUNT, m_pSettings->m_nNgCount);
}

void CPageInfo::SetNgCount(unsigned int nCount)
{
	SetDlgItemInt(IDC_EDIT_NGCOUNT, nCount);
}

void CPageInfo::SetSpeed1H(unsigned int nCount)
{
	CString strText;
	strText.Format(_T("%d / H"), nCount);
	SetDlgItemText(IDC_EDIT_SPEED, strText);
}

void CPageInfo::SettingsChanged()
{
	ASSERT(m_pSettings);
	SetDlgItemText(IDC_EDIT_MODEL, m_pSettings->m_strProductModel);
	SetDlgItemInt(IDC_EDIT_TOTAL, m_pSettings->m_nTestTotal);
	SetDlgItemInt(IDC_EDIT_NGCOUNT, m_pSettings->m_nNgCount);
}

BEGIN_MESSAGE_MAP(CPageInfo, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CPageInfo::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CPageInfo::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPageInfo ��Ϣ�������


void CPageInfo::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// CDialogEx::OnCancel();
}


void CPageInfo::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// CDialogEx::OnOK();
}


BOOL CPageInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT(m_pSettings);
	SetDlgItemText(IDC_EDIT_MODEL, m_pSettings->m_strProductModel);
	SetDlgItemInt(IDC_EDIT_TOTAL, m_pSettings->m_nTestTotal);
	SetDlgItemInt(IDC_EDIT_NGCOUNT, m_pSettings->m_nNgCount);
	SetDlgItemText(IDC_EDIT_SPEED, _T("- / H"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CPageInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkColor(m_crBkgnd);
	}


	return m_brBkgnd;
}
