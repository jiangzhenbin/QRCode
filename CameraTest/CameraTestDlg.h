
// CameraTestDlg.h : ͷ�ļ�
//

#pragma once
#include "DeviceProcess.h"


// CCameraTestDlg �Ի���
class CCameraTestDlg : public CDialogEx
{
// ����
public:
	CCameraTestDlg(CWnd* pParent = NULL);	// ��׼���캯��


private:
	GxIAPICPP::gxdeviceinfo_vector m_vectorDeviceInfo;          ///< Device information
	void __InitUI(CGXFeatureControlPointer objFeatureControlPtr);
	void __UpdateUI(CDeviceProcess* pDeviceProcess);


private:
	CDeviceProcess *m_pDeviceProcessCurrent;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAMERATEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonSnap();
};
