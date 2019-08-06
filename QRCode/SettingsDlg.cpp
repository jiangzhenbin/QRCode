// SettingsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QRCode.h"
#include "SettingsDlg.h"
#include "afxdialogex.h"


// CSettingsDlg 对话框

IMPLEMENT_DYNAMIC(CSettingsDlg, CDialogEx)

CSettingsDlg::CSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SETTINGS, pParent)
{
	m_pSettings = NULL;
}

CSettingsDlg::~CSettingsDlg()
{
}

void CSettingsDlg::SetSettingsPtr(CSettings *pSettings)
{
	m_pSettings = pSettings;
}

void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_CODEFILTERTYPE1, &CSettingsDlg::OnCbnSelchangeComboCodefiltertype1)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CSettingsDlg::OnBnClickedButtonClear)
	ON_EN_CHANGE(IDC_EDIT_MODEL, &CSettingsDlg::OnEnChangeEditModel)
	ON_EN_CHANGE(IDC_EDIT_CODELENGTH, &CSettingsDlg::OnEnChangeEditCodelength)
	ON_EN_CHANGE(IDC_EDIT_EXPOSURE, &CSettingsDlg::OnEnChangeEditExposure)
	ON_BN_CLICKED(IDOK, &CSettingsDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_MES_ENDPOINT, &CSettingsDlg::OnEnChangeEditMesEndpoint)
END_MESSAGE_MAP()


// CSettingsDlg 消息处理程序


BOOL CSettingsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	CComboBox *pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_CODEFILTERTYPE1);
	pComboBox->InsertString(0, _T("未启用"));
	pComboBox->InsertString(1, _T("小于"));
	pComboBox->InsertString(2, _T("等于"));
	pComboBox->InsertString(3, _T("大于"));

	ASSERT(m_pSettings);
	SetDlgItemText(IDC_EDIT_MODEL, m_pSettings->m_strProductModel);
	SetDlgItemInt(IDC_EDIT_TOTAL, m_pSettings->m_nTestTotal);
	SetDlgItemInt(IDC_EDIT_NGCOUNT, m_pSettings->m_nNgCount);
	pComboBox->SetCurSel(m_pSettings->m_nCodeLengthFilterType);
	SetDlgItemInt(IDC_EDIT_CODELENGTH, m_pSettings->m_nCodeLengthFileterValue);
	GetDlgItem(IDC_EDIT_CODELENGTH)->EnableWindow(m_pSettings->m_nCodeLengthFilterType > 0);
	SetDlgItemInt(IDC_EDIT_EXPOSURE, m_pSettings->m_nCameraExposureTime);
	SetDlgItemText(IDC_EDIT_MES_ENDPOINT, m_pSettings->m_szMesEndPoint);

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSettingsDlg::OnCbnSelchangeComboCodefiltertype1()
{
	CComboBox *pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_CODEFILTERTYPE1);
	int nSel = pComboBox->GetCurSel();
	GetDlgItem(IDC_EDIT_CODELENGTH)->EnableWindow(nSel > 0);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}


void CSettingsDlg::OnBnClickedButtonClear()
{
	SetDlgItemInt(IDC_EDIT_TOTAL, 0);
	SetDlgItemInt(IDC_EDIT_NGCOUNT, 0);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}


void CSettingsDlg::OnEnChangeEditModel()
{
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}


void CSettingsDlg::OnEnChangeEditCodelength()
{
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}


void CSettingsDlg::OnEnChangeEditExposure()
{
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}

void CSettingsDlg::OnEnChangeEditMesEndpoint()
{
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}

void CSettingsDlg::OnBnClickedOk()
{
	ASSERT(m_pSettings);
	GetDlgItemText(IDC_EDIT_MODEL, m_pSettings->m_strProductModel);

	int nValue = GetDlgItemInt(IDC_EDIT_TOTAL);
	if (nValue == 0) {
		m_pSettings->m_nTestTotal = nValue;
	}

	nValue = GetDlgItemInt(IDC_EDIT_NGCOUNT);
	if (nValue == 0) {
		m_pSettings->m_nNgCount = nValue;
	}

	m_pSettings->m_nCodeLengthFilterType = ((CComboBox *)GetDlgItem(IDC_COMBO_CODEFILTERTYPE1))->GetCurSel();
	m_pSettings->m_nCodeLengthFileterValue = GetDlgItemInt(IDC_EDIT_CODELENGTH);
	m_pSettings->m_nCameraExposureTime = GetDlgItemInt(IDC_EDIT_EXPOSURE);
	GetDlgItemText(IDC_EDIT_MES_ENDPOINT, m_pSettings->m_szMesEndPoint, sizeof(m_pSettings->m_szMesEndPoint));

	CDialogEx::OnOK();
}

