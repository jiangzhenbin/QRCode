
// SYCameraTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SYCameraTest.h"
#include "SYCameraTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSYCameraTestDlg 对话框



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


// CSYCameraTestDlg 消息处理程序

BOOL CSYCameraTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSYCameraTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSYCameraTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSYCameraTestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pSYCam = new CGeniCAMCapture();
	CGeniCAMCapture::OpenFactory();
	if (m_pSYCam->OpenCamera(0)) {
		m_pSYCam->SetTriggerMode(ContinueMode);
		m_pSYCam->StartCapture();

		// 启动线程
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
	// 在线程中上传code到Mes系统
	while (1) {
		DWORD dwRet = WaitForSingleObject(m_pSYCam->m_hFinishCapture, 2000);
		if (dwRet == WAIT_OBJECT_0) {
			if (m_pSYCam->m_pImageBuffer != NULL) {
				TRACE("收到图像, %d x %d\n", m_pSYCam->m_iWidth, m_pSYCam->m_iHeight);

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


	TRACE("CAoiManager::AoiThreadProcInner 线程退出...\n");
	return 0;
}