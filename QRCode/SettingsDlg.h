#pragma once
#include "Settings.h"

// CSettingsDlg 对话框

class CSettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingsDlg)

public:
	CSettingsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingsDlg();
	void SetSettingsPtr(CSettings *pSettings);

private:
	CSettings *m_pSettings;


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTINGS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
