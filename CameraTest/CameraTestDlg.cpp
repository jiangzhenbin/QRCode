
// CameraTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CameraTest.h"
#include "CameraTestDlg.h"
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


// CCameraTestDlg 对话框



CCameraTestDlg::CCameraTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CAMERATEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pDeviceProcessCurrent = NULL;
}

void CCameraTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCameraTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CCameraTestDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, &CCameraTestDlg::OnBnClickedButtonSnap)
END_MESSAGE_MAP()


// CCameraTestDlg 消息处理程序

BOOL CCameraTestDlg::OnInitDialog()
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


	IGXFactory::GetInstance().Init();
	IGXFactory::GetInstance().UpdateDeviceList(1000, m_vectorDeviceInfo);
	if (m_vectorDeviceInfo.size() == 0) {
		MessageBox("No device found,please make sure the device is properly connected and then restart the program!");
	}
	else {
		CComboBox *pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_CAMERAS);
		for (uint32_t i = 0; i < m_vectorDeviceInfo.size(); i++) {
			gxstring strDeviceInformation = "";
			strDeviceInformation = m_vectorDeviceInfo[i].GetDisplayName();
			pComboBox->SetItemData(pComboBox->AddString(strDeviceInformation.c_str()), i);
			//m_mapDeviceInformation.insert(map<int, CDeviceProcess*>::value_type(i, m_pDeviceProcess[i]));
		}
		pComboBox->SetCurSel(0);
	}



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCameraTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCameraTestDlg::OnPaint()
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
HCURSOR CCameraTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCameraTestDlg::OnBnClickedButtonOpen()
{
	CComboBox *pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_CAMERAS);
	int nCurSel = pComboBox->GetCurSel();
	if (nCurSel < 0) {
		return;
	}



	try
	{
		// Get the child window handle of displaying area
		CWnd*  pWnd = this;


		// Get device index
		int nDeviceIndex = nCurSel + 1;

		// Open device
		m_pDeviceProcessCurrent = new CDeviceProcess;
		m_pDeviceProcessCurrent->OpenDevice(m_vectorDeviceInfo[nCurSel].GetSN(), pWnd, nDeviceIndex);

		// initialize UI
		__InitUI(m_pDeviceProcessCurrent->m_objFeatureControlPtr);

		// Update UI
		__UpdateUI(m_pDeviceProcessCurrent);

	}
	catch (CGalaxyException& e)
	{
		MessageBox(e.what());
		return;
	}
	catch (std::exception& e)
	{
		MessageBox(e.what());
		return;
	}
}

void CCameraTestDlg::OnBnClickedButtonSnap()
{
	// TODO: Add your control notification handler code here
	try
	{
		// Start acquisition
		m_pDeviceProcessCurrent->StartSnap();

		// Update UI
		__UpdateUI(m_pDeviceProcessCurrent);

		// Update equipment model and frame rate information
		m_pDeviceProcessCurrent->RefreshDeviceSNFPS();

		//SetTimer(1, 1000, NULL);
	}
	catch (CGalaxyException& e)
	{
		MessageBox(e.what());
		return;
	}
	catch (std::exception& e)
	{
		MessageBox(e.what());
		return;
	}
}

void CCameraTestDlg::__InitUI(CGXFeatureControlPointer objFeatureControlPtr)
{
	/*
	if (objFeatureControlPtr.IsNull()) {
		return;
	}

	bool bIsBalanceWhiteAutoRead = false;        // The flag indicate whether white balance can be read 
	bool bBalanceWhiteAuto = false;        // The flag indicate whether white balance is supported

										   // The flag indicate whether Bayer format is supported
	m_bIsColorFilter = objFeatureControlPtr->IsImplemented("PixelColorFilter");

	if (m_bIsColorFilter) {
		// whether white balance is supported
		bBalanceWhiteAuto = objFeatureControlPtr->IsImplemented("BalanceWhiteAuto");

		// whether white balance can be read 
		bIsBalanceWhiteAutoRead = objFeatureControlPtr->IsReadable("BalanceWhiteAuto");
		if (bBalanceWhiteAuto) {
			if (bIsBalanceWhiteAutoRead) {
				m_strBalanceWhiteAuto = objFeatureControlPtr->GetEnumFeature("BalanceWhiteAuto")->GetValue();
			}

			int nCursel = 0;
			gxstring strCurEnumList = "";
			GxIAPICPP::gxstring_vector vectorEnumEntryList;

			// Get the current device function value
			strCurEnumList = objFeatureControlPtr->GetEnumFeature("BalanceWhiteAuto")->GetValue();

			// Get all enumerations for this feature
			vectorEnumEntryList = objFeatureControlPtr->GetEnumFeature("BalanceWhiteAuto")->GetEnumEntryList();

			// Clear device list
			m_comboxBalanceWhiteAuto.ResetContent();
			for (uint32_t i = 0; i<vectorEnumEntryList.size(); i++) {
				std::string strEnumList = vectorEnumEntryList[i].c_str();
				m_comboxBalanceWhiteAuto.SetItemData(m_comboxBalanceWhiteAuto.AddString(strEnumList.c_str()), i);

				if (strCurEnumList == vectorEnumEntryList[i])
				{
					nCursel = i;
				}

			}
			m_nCurrentBalanceAutoWhiteSel = nCursel;
			m_comboxBalanceWhiteAuto.SetCurSel(nCursel);
		}
	}


	// Initialize exposure time
	CString  strShutterTimeRange = "";          // Exposure time range
	gxstring strShutterTimeUint = "";          // Exposure time unit

	m_dEditShutter = objFeatureControlPtr->GetFloatFeature("ExposureTime")->GetValue();
	strShutterTimeUint = objFeatureControlPtr->GetFloatFeature("ExposureTime")->GetUnit();
	m_dShutterMax = objFeatureControlPtr->GetFloatFeature("ExposureTime")->GetMax();
	m_dShutterMin = objFeatureControlPtr->GetFloatFeature("ExposureTime")->GetMin();

	strShutterTimeRange.Format("Exposure time(%.4f~%.4f)%s", m_dShutterMin, m_dShutterMax, strShutterTimeUint.c_str());
	m_staticShutterTime.SetWindowText(strShutterTimeRange);

	// Initialize gain
	CString  strGainRange = "";                // Gain range
	gxstring strGainUint = "";                // Gain unit

	m_dEditGain = objFeatureControlPtr->GetFloatFeature("Gain")->GetValue();
	strGainUint = objFeatureControlPtr->GetFloatFeature("Gain")->GetUnit();
	m_dGainMax = objFeatureControlPtr->GetFloatFeature("Gain")->GetMax();
	m_dGainMin = objFeatureControlPtr->GetFloatFeature("Gain")->GetMin();

	strGainRange.Format("Gain(%.4f~%.4f)%s", m_dGainMin, m_dGainMax, strGainUint.c_str());
	m_staticGain.SetWindowText(strGainRange);

	// Initialize acquisition speed level
	// whether acquisition speed level can be read 
	m_bIsSnapSpeed = objFeatureControlPtr->IsImplemented("AcquisitionSpeedLevel");
	if (m_bIsSnapSpeed)
	{
		CString  strSnapSpeedRange = "";
		m_nEditSnapSpeed = objFeatureControlPtr->GetIntFeature("AcquisitionSpeedLevel")->GetValue();
		m_nSnapSpeedMax = objFeatureControlPtr->GetIntFeature("AcquisitionSpeedLevel")->GetMax();
		m_nSnapSpeedMin = objFeatureControlPtr->GetIntFeature("AcquisitionSpeedLevel")->GetMin();

		strSnapSpeedRange.Format("AcquisitionSpeedLevel(%lld~%lld)", m_nSnapSpeedMin, m_nSnapSpeedMax);
		m_staticSnapSpeed.SetWindowText(strSnapSpeedRange);

	}
	else
	{
		// Update Edit
		m_nEditSnapSpeed = NULL;
	}

	// Get whether the frame rate flag is displayed
	m_bCheckShowDevice = m_pDeviceProcessCurrent->GetShowFPS();

	UpdateData(FALSE);
	*/
}

void CCameraTestDlg::__UpdateUI(CDeviceProcess* pDeviceProcess)
{
	if (pDeviceProcess == NULL) {
		return;
	}

	bool IsOpen = pDeviceProcess->IsOpen();
	bool IsSnap = pDeviceProcess->IsSnap();
}

