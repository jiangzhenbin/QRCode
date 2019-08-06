
// SYCameraTestDlg.h : ͷ�ļ�
//

#pragma once

#include "GCAMDevice.h"
#pragma comment(lib, "SY_GCamDeVice_15UR_X64.lib")

// CSYCameraTestDlg �Ի���
class CSYCameraTestDlg : public CDialogEx
{
// ����
public:
	CSYCameraTestDlg(CWnd* pParent = NULL);	// ��׼���캯��


private:
	static UINT AoiThreadProc(LPVOID lParam);
	UINT AoiThreadProcInner();


// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYCAMERATEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CGeniCAMCapture *m_pSYCam;
	BITMAPINFO         *m_pBmpInfo;	                     ///< BITMAPINFO Structure pointer
	char               m_chBmpBuf[2048];	             ///< BIMTAPINFO Memory buffer
	BYTE               *m_pImageBuffer;                  ///< Save the flipped image for display
	HDC                m_hDC;
	HDC                m_hMemDC;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnDestroy();
};
