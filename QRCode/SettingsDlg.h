#pragma once
#include "Settings.h"

// CSettingsDlg �Ի���

class CSettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingsDlg)

public:
	CSettingsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSettingsDlg();
	void SetSettingsPtr(CSettings *pSettings);

private:
	CSettings *m_pSettings;


// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTINGS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboCodefiltertype1();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnEnChangeEditModel();
	afx_msg void OnEnChangeEditCodelength();
	afx_msg void OnEnChangeEditExposure();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditMesEndpoint();
};
