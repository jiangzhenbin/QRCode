
// SYCameraTestDlg.h : 头文件
//

#pragma once

#include "GCAMDevice.h"
#pragma comment(lib, "SY_GCamDeVice_15UR_X64.lib")

// CSYCameraTestDlg 对话框
class CSYCameraTestDlg : public CDialogEx
{
// 构造
public:
	CSYCameraTestDlg(CWnd* pParent = NULL);	// 标准构造函数


private:
	static UINT AoiThreadProc(LPVOID lParam);
	UINT AoiThreadProcInner();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYCAMERATEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CGeniCAMCapture *m_pSYCam;
	BITMAPINFO         *m_pBmpInfo;	                     ///< BITMAPINFO Structure pointer
	char               m_chBmpBuf[2048];	             ///< BIMTAPINFO Memory buffer
	BYTE               *m_pImageBuffer;                  ///< Save the flipped image for display
	HDC                m_hDC;
	HDC                m_hMemDC;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnDestroy();
};
