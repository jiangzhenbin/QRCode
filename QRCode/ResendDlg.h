#pragma once
#include "AoiManager.h"


// CResendDlg �Ի���

class CResendDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CResendDlg)

public:
	CResendDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CResendDlg();
	void SetAoiManager(CAoiManager * pAoiManager);


private:
	void ReadCacheCodes(CString strFilepath, CStringList &stringList);
	void SaveCacheCodes(CString strFilepath, CStringList &stringList);
	void UpdateList();

private:
	CAoiManager *m_pAoiManager;
	CStringList m_strCodeList;


// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RESEND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
	afx_msg void OnDestroy();
};
