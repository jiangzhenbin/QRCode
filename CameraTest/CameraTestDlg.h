
// CameraTestDlg.h : 头文件
//

#pragma once
#include "DeviceProcess.h"


// CCameraTestDlg 对话框
class CCameraTestDlg : public CDialogEx
{
// 构造
public:
	CCameraTestDlg(CWnd* pParent = NULL);	// 标准构造函数


private:
	GxIAPICPP::gxdeviceinfo_vector m_vectorDeviceInfo;          ///< Device information
	void __InitUI(CGXFeatureControlPointer objFeatureControlPtr);
	void __UpdateUI(CDeviceProcess* pDeviceProcess);


private:
	CDeviceProcess *m_pDeviceProcessCurrent;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAMERATEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonSnap();
};
