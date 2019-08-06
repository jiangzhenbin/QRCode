
// SYCameraTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SYCameraTest.h"
#include "SYCameraTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSYCameraTestDlg �Ի���



CSYCameraTestDlg::CSYCameraTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SYCAMERATEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pSYCam = NULL;
	m_pBmpInfo = NULL;
	m_pImageBuffer = NULL;
	m_hDC = NULL;
	m_hMemDC = NULL;
}

void CSYCameraTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSYCameraTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSYCameraTestDlg::OnBnClickedButton1)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CSYCameraTestDlg ��Ϣ�������

BOOL CSYCameraTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSYCameraTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSYCameraTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSYCameraTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSYCameraTestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pSYCam = new CGeniCAMCapture();
	CGeniCAMCapture::OpenFactory();
	if (m_pSYCam->OpenCamera(0)) {
		m_pSYCam->SetTriggerMode(ContinueMode);
		m_pSYCam->StartCapture();

		// �����߳�
		CWinThread* pWinThread = AfxBeginThread(AoiThreadProc, this);
		if (pWinThread != NULL) {

		}
	}
}


void CSYCameraTestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_pSYCam != NULL) {
		m_pSYCam->StopCapture();
		m_pSYCam->CloseCamera();
		delete m_pSYCam;
		m_pSYCam = NULL;
		CGeniCAMCapture::CloseFactory();
	}
}

UINT CSYCameraTestDlg::AoiThreadProc(LPVOID lParam)
{
	CSYCameraTestDlg * pManager = (CSYCameraTestDlg *)lParam;
	return pManager->AoiThreadProcInner();
}

UINT CSYCameraTestDlg::AoiThreadProcInner()
{
	// ���߳����ϴ�code��Mesϵͳ
	while (1) {
		DWORD dwRet = WaitForSingleObject(m_pSYCam->m_hFinishCapture, 2000);
		if (dwRet == WAIT_OBJECT_0) {
			if (m_pSYCam->m_pImageBuffer != NULL) {
				TRACE("�յ�ͼ��, %d x %d\n", m_pSYCam->m_iWidth, m_pSYCam->m_iHeight);

				if (m_pBmpInfo == NULL) {
					m_pBmpInfo = (BITMAPINFO *)new char[2048];;
					m_pBmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
					m_pBmpInfo->bmiHeader.biWidth = (LONG)m_pSYCam->m_iWidth;
					m_pBmpInfo->bmiHeader.biHeight = 0 - (LONG)m_pSYCam->m_iHeight;

					m_pBmpInfo->bmiHeader.biPlanes = 1;
					m_pBmpInfo->bmiHeader.biBitCount = 8; // black and white image is 8
					m_pBmpInfo->bmiHeader.biCompression = BI_RGB;
					m_pBmpInfo->bmiHeader.biSizeImage = 0;
					m_pBmpInfo->bmiHeader.biXPelsPerMeter = 0;
					m_pBmpInfo->bmiHeader.biYPelsPerMeter = 0;
					m_pBmpInfo->bmiHeader.biClrUsed = 0;
					m_pBmpInfo->bmiHeader.biClrImportant = 0;

					// black and white image need initialize palette
					for (int i = 0; i<256; i++)
					{
						m_pBmpInfo->bmiColors[i].rgbBlue = i;
						m_pBmpInfo->bmiColors[i].rgbGreen = i;
						m_pBmpInfo->bmiColors[i].rgbRed = i;
						m_pBmpInfo->bmiColors[i].rgbReserved = i;
					}

					m_pImageBuffer = new BYTE[(size_t)(m_pSYCam->m_iWidth * m_pSYCam->m_iHeight)];


					m_hDC = ::GetDC(m_hWnd);
				}


				memcpy(m_pImageBuffer, m_pSYCam->m_pImageBuffer, m_pSYCam->m_iWidth * m_pSYCam->m_iHeight);

				int nWndWidth = 0;
				int nWndHeight = 0;

				// Prepare for drawing images
				RECT objRect;
				::GetClientRect(m_hWnd, &objRect);
				nWndWidth = objRect.right - objRect.left;
				nWndHeight = objRect.bottom - objRect.top;

				HDC      objMemDC = ::CreateCompatibleDC(m_hDC);
				HBITMAP  objMemBmp = CreateCompatibleBitmap(m_hDC, nWndWidth, nWndHeight);
				::SelectObject(objMemDC, objMemBmp);

				::SetStretchBltMode(objMemDC, COLORONCOLOR);
				::StretchDIBits(objMemDC,
					0,
					0,
					nWndWidth,
					nWndHeight,
					0,
					0,
					(int)m_pSYCam->m_iWidth,
					(int)m_pSYCam->m_iHeight,
					m_pImageBuffer,
					m_pBmpInfo,
					DIB_RGB_COLORS,
					SRCCOPY
				);

				StretchBlt(m_hDC,
					0,
					0,
					nWndWidth,
					nWndHeight,
					objMemDC,
					0,
					0,
					nWndWidth,
					nWndHeight,
					SRCCOPY);

				::DeleteDC(objMemDC);
				DeleteObject(objMemBmp);
			}
		}
		else {
			break;
		}
	}


	TRACE("CAoiManager::AoiThreadProcInner �߳��˳�...\n");
	return 0;
}