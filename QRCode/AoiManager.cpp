#include "stdafx.h"
#include "AoiManager.h"
#include "Utils.h"
#include "..\MesWebService\MesManager.h"

CAoiManager *CAoiManager::m_pAoiManager = NULL;
CAoiManager::CAoiManager()
{
	m_nPlcEvent = 0;
	m_bRunning = FALSE;
	m_hEventGetCode = CreateEventA(NULL, TRUE, FALSE, NULL);
	m_hEventGetImage = CreateEventA(NULL, TRUE, FALSE, NULL);
	m_hEventSemThreadExit = CreateEventA(NULL, TRUE, FALSE, NULL);
	m_hEventAoiThreadExit = CreateEventA(NULL, TRUE, FALSE, NULL);
	for (int i = 0; i < 4; i++) {
		m_hWndPreview[i] = NULL;
		m_pProcess[i] = NULL;
	}
	::InitializeCriticalSection(&m_lock);
	m_fGetNewCode = nullptr;
	m_fCodeStateChanged = nullptr;
	m_fPlcStateChanged = nullptr;
	m_pSettings = NULL;
	m_bExecuteAoi = FALSE;

	for (int i = 0; i < 4; i++)
	{
		m_isOk[i] = FALSE;
	}
	m_getStartTime = 0;
	m_isExecute = FALSE;
}


CAoiManager::~CAoiManager()
{
	::DeleteCriticalSection(&m_lock);
}

BOOL CAoiManager::IsAoiExecute()
{
	return m_bExecuteAoi;
}

void CAoiManager::ExecuteAoi(BOOL bExecute)
{
	m_bExecuteAoi = bExecute;

	if (!m_bExecuteAoi) {
		POINT pt1 = { 0, 0 }, pt2 = { 0, 0 };
		for (int i = 0; i < 4; i++) {
			if (m_pProcess[i] != NULL) {
				m_pProcess[i]->SetRoiRegion(&pt1, &pt2);
				m_pProcess[i]->StopSnap();
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (m_pProcess[i] != NULL) {
				m_pProcess[i]->StartSnap();
			}
		}
	}
}

void CAoiManager::SetSettingsPtr(CSettings *pSettings)
{
	m_pSettings = pSettings;
}

void CAoiManager::SetWindows(HWND *pHwnd, int count)
{
	for (int i = 0; i < count; i++) {
		m_hWndPreview[i] = pHwnd[i];
		if (i >= count) {
			break;
		}
	}
}

void CAoiManager::SetOnPlcStateChangedListener(ONPLCSTATECHANGED listener)
{
	m_fPlcStateChanged = listener;
}

void CAoiManager::SetOnNewCodeListener(ONGETNEWCODE listener)
{
	m_fGetNewCode = listener;
}

void CAoiManager::SetOnCodeStateChangedListener(ONCODESTATECHANGED listener)
{
	m_fCodeStateChanged = listener;
}

ONCODESTATECHANGED CAoiManager::GetOnCodeStateChangedListener()
{
	return m_fCodeStateChanged;
}


void CAoiManager::Init()
{
	// 网络服务 
	m_pAoiManager = this;
	UINT port = 9602;
	BYS_SetMSGDFunction(Socket_DispathFunction);
	m_hChannelForPlc = BYS_CreateChannelsTCPS(_T("ForPLC"), port);
	if (m_hChannelForPlc != NULL) {
		CUtils::Log("创建TCP服务端成功[端口:%d]", port);
	}


	m_hChannelForTransferFile = BYS_CreateChannelsTCPS(_T("ForPLC"), 19602);
	if (m_hChannelForTransferFile != NULL) {
		CUtils::Log("创建TCP传文件服务成功[端口:%d]", 19602);
	}


	// ImageData对象池
	InitImageDataPool(50, 1292, 964);
	// InitImageDataPool(50, 1280, 1024);

	// 相机
	auto onRecvImageListener = [&](unsigned int deviceId, unsigned int width, unsigned int height, void *pBuffer, unsigned int nDataLen) -> void {
		Lock();
		if (m_nPlcEvent >= 0) {

			// 加入待处理的图像列表
			if (m_bExecuteAoi) {
				CImageData *pImgData = AllocImageData(deviceId, pBuffer, nDataLen, width, height);
				if (pImgData != NULL) {
					m_listWaitForProcessImg.push_back(pImgData);
					SetEvent(m_hEventGetImage);
				}
				else {
					//CUtils::Log("AllocImageData失败了");
				}
			}

			m_nPlcEvent = 0;
		}
		Unlock();
	};

	ASSERT(m_pSettings);
	// m_syCameraEngine.Init(onRecvImageListener);
	// for (int i = 0; i < 4; i++) {
	//	 m_syCameraEngine.OpenCamera(i, m_hWndPreview[i]);
	// }
	
	m_cameraEngine.Init(m_pSettings->m_nCameraExposureTime);
	m_cameraEngine.SortIndex(&m_pSettings->m_mapCameraSN);
	int nCameraCount = m_cameraEngine.GetCameraCount();
	CUtils::Log("发现 %d 个相机", nCameraCount);
	if (m_cameraEngine.GetCameraCount() > 0) {
		for (int i = 0; i < nCameraCount; i++) {
			m_pProcess[i] = m_cameraEngine.OpenCamera(i, m_hWndPreview[i], m_pSettings->m_fFrameRate);
			if (m_pProcess[i] != NULL) {
				CUtils::Log("[%d], OpenCamera %s", i, m_pProcess[i]->GetDeviceSN().c_str());

				m_pProcess[i]->SetOnRecvImageListener(onRecvImageListener);
				m_pProcess[i]->StartSnap();
				m_pProcess[i]->RefreshDeviceSNFPS();
				m_pProcess[i]->SetShowFPS(FALSE);
			}
			
			if (i >= 3) {
				break;
			}
		}
	}
	ExecuteAoi(FALSE);


	// 启动线程
	CWinThread* pWinThread = AfxBeginThread(MesThreadProc, this);
	if (pWinThread != NULL) {

	}

	pWinThread = AfxBeginThread(AoiThreadProc, this);
	if (pWinThread != NULL) {

	}
}

void CAoiManager::UnInit()
{
	// 触发使SEM线程退出
	m_bRunning = FALSE;
	SetEvent(m_hEventGetCode);
	SetEvent(m_hEventGetImage);
	WaitForSingleObject(m_hEventSemThreadExit, 2000);
	CloseHandle(m_hEventSemThreadExit);
	m_hEventSemThreadExit = NULL;
	WaitForSingleObject(m_hEventAoiThreadExit, 2000);	
	CloseHandle(m_hEventAoiThreadExit);
	m_hEventAoiThreadExit = NULL;
	CloseHandle(m_hEventGetCode);
	m_hEventGetCode = NULL;
	CloseHandle(m_hEventGetImage);
	m_hEventGetImage = NULL;

	int nEnableCameraCount = min(4, m_pSettings->m_nEnableCameraCount);
	for (int i = 0; i < nEnableCameraCount; i++) {
		if (m_pProcess[i] != NULL) {
			m_pProcess[i]->StopSnap();
			m_pProcess[i]->CloseDevice();
			CUtils::Log("关闭相机 %d", i);
			m_pProcess[i] = NULL;
		}
	}
	m_cameraEngine.UnInit();

	Lock();
	for (auto item : m_listGetCode) {
		delete item;
	}
	m_listGetCode.clear();

	for (auto item : m_listSendingCode) {
		delete item;
	}
	m_listSendingCode.clear();

	for (auto item : m_listOkCode) {
		delete item;
	}
	m_listOkCode.clear();
	Unlock();

	FreeImageDataPool();
}

long CAoiManager::Socket_DispathFunction(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == BYSWM_BYSMSG) {
		if (wParam == BYS_MSG_INITING)
			CUtils::Log("正在初始化BYS网络组件...\n");
		else if (wParam == BYS_MSG_INITOK)
			CUtils::Log("初始化BYS网络成功.\n");
		else if (wParam == BYS_MSG_CREATECHANNELSOK)
			CUtils::Log("初始新通道成功.\n");
	}
	else if (uMsg == BYSWM_READ) {
		CUtils::Log("收到数据...\n");
		m_pAoiManager->Socket_OnBYSRead(wParam, lParam);
	}

	else if (uMsg == BYSWM_ACCEPT) {
		m_pAoiManager->Socket_OnAccept(wParam, lParam);
	}

	else if (uMsg == BYSWM_WRITE) {
	}

	else if (uMsg == BYSWM_CONNECT) {
		m_pAoiManager->Socket_OnConnect(wParam, lParam);
	}

	else if (uMsg == BYSWM_CLOSE) {
		m_pAoiManager->Socket_OnClose(wParam, lParam);
	}

	else if (uMsg == BYSWM_WORKTHREAD_ENTER) {

	}

	else if (uMsg == BYSWM_WORKTHREAD_LEAVE) {

	}

	return 0;
}

//////////////////////////////////////////////////////////////
// BYSocket.dll发来的有收到数据的消息
// wParam -- 数据结构的指针
void CAoiManager::Socket_OnBYSRead(WPARAM wParam, LPARAM lParam)
{
	// CUtils::Log("Socket_OnBYSRead 有数据\n");
	if ((HANDLE)lParam == m_hChannelForPlc) {
		if (m_fPlcStateChanged != nullptr) {
			m_fPlcStateChanged(PLCSTATE::ACTIVE);
		}

		BYSRECVDATA * pBrdata = (BYSRECVDATA *)wParam;
		m_nActiveSocket = pBrdata->sock;
		//CUtils::Log("m_nActiveSocket:%d\n", m_nActiveSocket);
		//for (DWORD i = 0; i < pBrdata->dwLen; i++) {
			//CUtils::Log("%d:%x\n", i, (byte)pBrdata->pData[i]);
		//}

		Lock();
		if (pBrdata->dwLen >= 4) {
			DishStatus ds;
			ds.status = pBrdata->pData[2];
			ds.currenceTime = clock();
			m_dishAnalyse.Execute(ds);
		}
		Unlock();


		// 模拟得到一个code
		/*
		if (pBrdata->dwLen >= 4
			&& (byte)pBrdata->pData[2] == (byte)0x88
			&& (byte)pBrdata->pData[3] == (byte)0x88) {
			Lock();
			static int i = 0; i++;
			CString strText;
			strText.Format(_T("1504319852XXXXXEEEEE2019%03d"), i);
			AppedCode(strText, 1, GetTickCount());
			Unlock();
		}*/
	}


	else if ((HANDLE)lParam == m_hChannelForTransferFile) {
		BYSRECVDATA * pBrdata = (BYSRECVDATA *)wParam;
		
		static BOOL bStart = FALSE;
		if (!bStart) {
			if (pBrdata->dwLen >= sizeof(AOIFILE)) {

				AOIFILE *paoiFile = (AOIFILE *)pBrdata->pData;
				if (paoiFile->dwHead == 10086) {
					memcpy(&m_aoiFile, paoiFile, sizeof(AOIFILE));

					// 本程序文件目录
					TCHAR sDrive[_MAX_DRIVE];
					TCHAR sDir[_MAX_DIR];
					TCHAR sFilename[_MAX_FNAME], sAppFilename[_MAX_FNAME];
					TCHAR sExt[_MAX_EXT];
					GetModuleFileName(AfxGetInstanceHandle(), sAppFilename, _MAX_PATH);
					_tsplitpath_s(sAppFilename, sDrive, sDir, sFilename, sExt);
					CString strAppDir = CString(sDrive) + CString(sDir);
					if (strAppDir.Right(1) != _T("\\"))
						strAppDir += _T("\\");


					CString strFileName = m_aoiFile.szFileName;
					CString strFilepath = strAppDir + strFileName;
					if (m_file.Open(strFilepath, CFile::modeCreate | CFile::modeWrite)) {
						bStart = TRUE;
						m_nRecvLength = 0;
					}
				}
			}

			BYS_Send(m_hChannelForTransferFile, "1", 1, pBrdata->sock);
		}
		else {
			m_file.Write(pBrdata->pData, pBrdata->dwLen);
			m_nRecvLength += pBrdata->dwLen;

			CUtils::Log("正在接收文件: %d/%d", m_nRecvLength, m_aoiFile.dwLength);

			if (m_nRecvLength == m_aoiFile.dwLength) {
				m_file.Close();
				CUtils::Log("接收完成");
				bStart = FALSE;
				BYS_Send(m_hChannelForTransferFile, "3", 1, pBrdata->sock);
			}
			else {
				BYS_Send(m_hChannelForTransferFile, "2", 1, pBrdata->sock);
			}
		}
	}


	else if ((HANDLE)lParam == m_hChannelForTransferFileClient) {
		BYSRECVDATA * pBrdata = (BYSRECVDATA *)wParam;
		if (pBrdata->pData[0] == 0x31) {
			char szBuffer[4096];

			int nLen = m_file2.Read(szBuffer, 4096);
			if (nLen > 0) {
				BYS_Send(m_hChannelForTransferFileClient, szBuffer, nLen);
			}
		}
		else if (pBrdata->pData[0] == 0x32) {
			char szBuffer[4096];

			int nLen = m_file2.Read(szBuffer, 4096);
			if (nLen > 0) {
				BYS_Send(m_hChannelForTransferFileClient, szBuffer, nLen);
			}
		}
		else if (pBrdata->pData[0] == 0x33) {
			m_file2.Close();
			CUtils::Log("发送完成");
		}
	}
}

void CAoiManager::Socket_OnClose(WPARAM wParam, LPARAM lParam)
{
	if ((HANDLE)lParam == m_hChannelForPlc) {
		if (m_fPlcStateChanged != nullptr) {
			m_fPlcStateChanged(PLCSTATE::DISCONNECTED);
		}
	}
	CUtils::Log("已断开，等待重新连接\n");
}

void CAoiManager::Socket_OnAccept(WPARAM wParam, LPARAM lParam)
{
	ACCEPTClient *pAcceptClient = (ACCEPTClient *)wParam;
	if ((HANDLE)lParam == m_hChannelForPlc) {
		m_nActiveSocket = pAcceptClient->socket;
		Welcome();
		if (m_fPlcStateChanged != nullptr) {
			m_fPlcStateChanged(PLCSTATE::CONNECTED);
		}
	}
	CUtils::Log("连接进入[%d(%d):%d] socket:%d\n", pAcceptClient->address, pAcceptClient->address, pAcceptClient->port, pAcceptClient->socket);
}

void CAoiManager::Socket_OnConnect(WPARAM wParam, LPARAM lParam)
{
	if ((HANDLE)lParam == m_hChannelForTransferFileClient) {
		CUtils::Log("连接文件服务端成功");

		if (m_file2.Open(m_strSendFilepath, CFile::modeRead)) {
			AOIFILE aoifile;
			memset(&aoifile, 0, sizeof(AOIFILE));
			aoifile.dwHead = 10086;
			aoifile.dwLength = m_file2.GetLength();

			int nIndex = m_strSendFilepath.ReverseFind('\\');
			CString strFileName = m_strSendFilepath.Right(m_strSendFilepath.GetLength() - nIndex - 1);
			memcpy(aoifile.szFileName, (LPTSTR)(LPCTSTR)strFileName, min(strFileName.GetLength(), _MAX_PATH-1));

			BYS_Send(m_hChannelForTransferFileClient, (char *)&aoifile, sizeof(AOIFILE));
			CUtils::Log("发送文件头");
		}
	}

}

UINT CAoiManager::MesThreadProc(LPVOID lParam)
{
	CAoiManager * pManager = (CAoiManager *)lParam;
	return pManager->MesThreadProcInner();
}

UINT CAoiManager::MesThreadProcInner()
{
	std::string functionId = "062";
	std::string strOut;


	// 在线程中上传code到Mes系统
	m_bRunning = TRUE;
	while (m_bRunning) {
		DWORD dwRet = WaitForSingleObject(m_hEventGetCode, INFINITE);
		ResetEvent(m_hEventGetCode);
		CUtils::Log("CAoiManager::TestThreadProcInner 有信号...");


		// 如果识别到的code List不为空，则取出并
		// 发送到MES
		Lock();
		while (!m_listGetCode.empty()) {
			CQRCode *pItem = m_listGetCode.front();
			pItem->state = CODESTATE::SENDING;
			m_listGetCode.pop_front();
			m_listSendingCode.push_back(pItem);
		}
		Unlock();


		while (m_bRunning) {
			CQRCode *pItem = NULL;
			Lock();
			if (!m_listSendingCode.empty()) {
				pItem = m_listSendingCode.front();
			}
			Unlock();

			if (pItem == NULL) {
				break;
			}


			CUtils::Log("正在发 Code<%s> 到MES", pItem->code);
			if (m_fCodeStateChanged != nullptr) {
				m_fCodeStateChanged(pItem);
			}

			BOOL bSendOk = FALSE;
			int nRet = MesManager::SendCode(m_pSettings->m_szMesEndPoint, functionId,
				m_pSettings->szUVId, (LPTSTR)(LPCTSTR)pItem->code, true, strOut);
			if (nRet == 0) {
				if (strOut.length() > 2) {
					if (strOut.substr(0, 2).compare("1,") == 0) {
						bSendOk = TRUE;
					}
				}
				CUtils::Log("strOut:%s.....", strOut.c_str());
			}
			CUtils::Log("MesManager::SendCode<%s> %s", pItem->code, bSendOk ? _T("成功") : _T("失败"));


			pItem->state = bSendOk ? CODESTATE::SUCCEED : CODESTATE::FAILED;
			if (m_fCodeStateChanged != nullptr) {
				m_fCodeStateChanged(pItem);
			}

			Lock();
			if (!m_listSendingCode.empty()) {
				m_listSendingCode.pop_front();
				m_listOkCode.push_back(pItem);

				while (m_listOkCode.size() > m_pSettings->m_nQRCodeBufferSize) {
					auto item = m_listOkCode.front();
					delete item;
					m_listOkCode.pop_front();
				}
			}
			Unlock();

		}
	}


	SetEvent(m_hEventSemThreadExit);
	CUtils::Log("CAoiManager::TestThreadProcInner 线程退出...");
	return 0;
}

UINT CAoiManager::AoiThreadProc(LPVOID lParam)
{
	CAoiManager * pManager = (CAoiManager *)lParam;
	return pManager->AoiThreadProcInner();
}

UINT CAoiManager::AoiThreadProcInner()
{
	// 在线程中上传code到Mes系统
	m_bRunning = TRUE;
	while (m_bRunning) {
		DWORD dwRet = WaitForSingleObject(m_hEventGetImage, INFINITE);
		ResetEvent(m_hEventGetImage);
		//CUtils::Log("CAoiManager::AoiThreadProcInner 有信号...");


		while (m_bRunning) {
			CImageData *pItem = NULL;
			Lock();
			if (!m_listWaitForProcessImg.empty()) {
				pItem = m_listWaitForProcessImg.front();
				m_listWaitForProcessImg.pop_front();
			}
			Unlock();

			if (pItem == NULL) {
				break;
			}


//			CUtils::Log("正在处理AOI [%d], 列队：%d ", pItem->m_nDeviceId, m_listWaitForProcessImg.size());
			std::string strCode;
			double costTime;
			RoiRegion roiRegion;
			if (0 == m_pSettings->m_codeType || 3 == m_pSettings->m_codeType || m_pSettings->m_nEnableCameraCount < 3)
			{
				if (m_visionProcess[1 - 1].Process8BitImage(pItem->m_pData, pItem->m_nWidth, pItem->m_nHeight, m_pSettings->m_codeType, strCode, costTime, &roiRegion) >= 0) {
					if (1 <= pItem->m_nDeviceId && pItem->m_nDeviceId <= 4) {
						Lock();
						AppedCode(strCode.c_str(), pItem->m_nDeviceId, pItem->m_dwTickCount);
						Unlock();

						POINT ptLeftTop = { 0, 0 }, ptRightBottom = { 0, 0 };
						RoiPoint2WndPoint(m_hWndPreview[pItem->m_nDeviceId - 1], pItem->m_nWidth, pItem->m_nHeight, roiRegion.pt0.x, roiRegion.pt0.y, &ptLeftTop);
						RoiPoint2WndPoint(m_hWndPreview[pItem->m_nDeviceId - 1], pItem->m_nWidth, pItem->m_nHeight, roiRegion.pt1.x, roiRegion.pt1.y, &ptRightBottom);
						if (m_pProcess[pItem->m_nDeviceId - 1] != NULL) {
							m_pProcess[pItem->m_nDeviceId - 1]->SetRoiRegion(&ptLeftTop, &ptRightBottom);
						}
					}
					// CUtils::Log("正在处理AOI [%d], 列队：%d ", pItem->m_nDeviceId, m_listWaitForProcessImg.size());
				}
			}
			else
			{
				if (GetTickCount() - m_getStartTime > m_pSettings->m_nAoiMaxTickCount)
				{
					m_isOk[0] = false;
					m_isOk[1] = false;
					m_isOk[2] = false;
					m_isOk[3] = false;
					m_isExecute = false;
				}

				if (!m_isExecute)
				{
					if (pItem->m_nDeviceId == 1 )
					{
						DWORD dd1 = GetTickCount();
						if (m_visionProcess[1 - 1].Process8BitImage(pItem->m_pData, pItem->m_nWidth, pItem->m_nHeight, m_pSettings->m_codeType, strCode, costTime, &roiRegion) >= 0)
						{
							if (pItem->m_nDeviceId < 1 || pItem->m_nDeviceId > 4) {
								RecyleImageData(pItem);
								continue;
							}

							Lock();
							AppedCode(strCode.c_str(), pItem->m_nDeviceId, pItem->m_dwTickCount);
							Unlock();

							POINT ptLeftTop = { 0, 0 }, ptRightBottom = { 0, 0 };
							RoiPoint2WndPoint(m_hWndPreview[pItem->m_nDeviceId - 1], pItem->m_nWidth, pItem->m_nHeight, roiRegion.pt0.x, roiRegion.pt0.y, &ptLeftTop);
							RoiPoint2WndPoint(m_hWndPreview[pItem->m_nDeviceId - 1], pItem->m_nWidth, pItem->m_nHeight, roiRegion.pt1.x, roiRegion.pt1.y, &ptRightBottom);
							if (m_pProcess[pItem->m_nDeviceId - 1] != NULL) {
								m_pProcess[pItem->m_nDeviceId - 1]->SetRoiRegion(&ptLeftTop, &ptRightBottom);
							}

							if (m_pSettings->m_nCodeLengthFilterType == 1) {
								if (strCode.length() < m_pSettings->m_nCodeLengthFileterValue) {
									m_isOk[pItem->m_nDeviceId - 1] = TRUE;
									m_getStartTime = GetTickCount();
									m_isExecute = true;
								}
							} else if (m_pSettings->m_nCodeLengthFilterType == 2) {
								if (strCode.length() == m_pSettings->m_nCodeLengthFileterValue) {
									m_isOk[pItem->m_nDeviceId - 1] = TRUE;
									m_getStartTime = GetTickCount();
									m_isExecute = true;
								}
							} else if (m_pSettings->m_nCodeLengthFilterType == 3) {
								if (strCode.length() > m_pSettings->m_nCodeLengthFileterValue) {
									m_isOk[pItem->m_nDeviceId - 1] = TRUE;
									m_getStartTime = GetTickCount();
									m_isExecute = true;
								}
							}

						    // CUtils::Log("处理AOI完成 %d, %d", pItem->m_nDeviceId, GetTickCount() - dd1);
						} //if (m_visionProcess[1 - 1].Process8BitImage(pItem->m_pData, pItem->m_nWidth, pItem->m_nHeight, m_pSettings->m_codeType, strCode, costTime, &roiRegion) >= 0)
					} //if (pItem->m_nDeviceId == 1 || pItem->m_nDeviceId == 2)
				}
				else
				{
					if (m_isOk[pItem->m_nDeviceId - 1]) {
						RecyleImageData(pItem);
						continue;
					}

					DWORD dd1 = GetTickCount();
					if (m_visionProcess[1 - 1].Process8BitImage(pItem->m_pData, pItem->m_nWidth, pItem->m_nHeight, m_pSettings->m_codeType, strCode, costTime, &roiRegion) >= 0)
					{
						if (pItem->m_nDeviceId < 1 || pItem->m_nDeviceId > 4) {
							RecyleImageData(pItem);
							continue;
						}

						Lock();
						AppedCode(strCode.c_str(), pItem->m_nDeviceId, pItem->m_dwTickCount);
						Unlock();

						POINT ptLeftTop = { 0, 0 }, ptRightBottom = { 0, 0 };
						RoiPoint2WndPoint(m_hWndPreview[pItem->m_nDeviceId - 1], pItem->m_nWidth, pItem->m_nHeight, roiRegion.pt0.x, roiRegion.pt0.y, &ptLeftTop);
						RoiPoint2WndPoint(m_hWndPreview[pItem->m_nDeviceId - 1], pItem->m_nWidth, pItem->m_nHeight, roiRegion.pt1.x, roiRegion.pt1.y, &ptRightBottom);
						if (m_pProcess[pItem->m_nDeviceId - 1] != NULL) {
							m_pProcess[pItem->m_nDeviceId - 1]->SetRoiRegion(&ptLeftTop, &ptRightBottom);
						}

						if (m_pSettings->m_nCodeLengthFilterType == 1) {
							if (strCode.length() < m_pSettings->m_nCodeLengthFileterValue) {
								m_isOk[pItem->m_nDeviceId - 1] = TRUE;
							}
						}
						else if (m_pSettings->m_nCodeLengthFilterType == 2) {
							if (strCode.length() == m_pSettings->m_nCodeLengthFileterValue) {
								m_isOk[pItem->m_nDeviceId - 1] = TRUE;
							}
						}
						else if (m_pSettings->m_nCodeLengthFilterType == 3) {
							if (strCode.length() > m_pSettings->m_nCodeLengthFileterValue) {
								m_isOk[pItem->m_nDeviceId - 1] = TRUE;
							}
						}

						// CUtils::Log("处理AOI完成xxxx %d, %d", pItem->m_nDeviceId, GetTickCount() - dd1);
					}

				}
			}
			//CUtils::Log("处理AOI完成 %d, %f", pItem->m_nDeviceId, costTime);


			RecyleImageData(pItem);
		}
	}


	SetEvent(m_hEventAoiThreadExit);
	CUtils::Log("CAoiManager::AoiThreadProcInner 线程退出...");
	return 0;
}

void CAoiManager::Lock()
{
	::EnterCriticalSection(&m_lock);
}

void CAoiManager::Unlock()
{
	::LeaveCriticalSection(&m_lock);
}

void CAoiManager::RoiPoint2WndPoint(HWND hWnd, int imgWidth, int imgHeight, double x, double y, LPPOINT pt)
{
	CRect rcClient;
	::GetClientRect(hWnd, &rcClient);

	double d1 = (double)rcClient.Width() / (double)imgWidth;
	double d2 = (double)rcClient.Height() / (double)imgHeight;

	pt->x = int((double)rcClient.Width() / (double)imgWidth * x);
	pt->y = int((double)rcClient.Height() / (double)imgHeight * y);
}

/*
 * 得到新的code，加入列表并检查是否重复
 * 同时做必要的判断，如长度
 */
int CAoiManager::AppedCode(CString strCode, const int nCameraId, DWORD dwTickCount)
{
	// 字符串长度检查
	if (m_pSettings->m_nCodeLengthFilterType == 1) {
		if (strCode.GetLength() >= m_pSettings->m_nCodeLengthFileterValue) {
			return -1;
		}
	}
	else if (m_pSettings->m_nCodeLengthFilterType == 2) {
		if (strCode.GetLength() != m_pSettings->m_nCodeLengthFileterValue) {
			return -1;
		}
	}
	else if (m_pSettings->m_nCodeLengthFilterType == 3) {
		if (strCode.GetLength() <= m_pSettings->m_nCodeLengthFileterValue) {
			return -1;
		}
	}


	for (auto item : m_listGetCode) {
		if (item->code.CompareNoCase(strCode) == 0) {
			return -1;
		}
	}

	for (auto item : m_listSendingCode) {
		if (item->code.CompareNoCase(strCode) == 0) {
			return -1;
		}
	}

	for (auto item : m_listOkCode) {
		if (item->code.CompareNoCase(strCode) == 0) {
			return -1;
		}
	}

	CQRCode *pQRCode = new CQRCode(strCode, nCameraId, dwTickCount);
	m_listGetCode.push_back(pQRCode);
	SetEvent(m_hEventGetCode);
	if (m_fGetNewCode != nullptr) {
		m_fGetNewCode(pQRCode);
	}

	return 0;
}

void CAoiManager::InitImageDataPool(const unsigned int count, const unsigned int imgWidth, const unsigned int imgHeight)
{
	Lock();
	for (int i = 0; i < count; i++) {
		CImageData *pImageData = new CImageData();
		pImageData->Init(imgWidth, imgHeight);
		m_listImageDataPool.push_back(pImageData);
	}
	Unlock();
}

void CAoiManager::FreeImageDataPool()
{
	Lock();
	for (auto item : m_listImageDataPool) {
		delete item;
	}
	m_listImageDataPool.clear();
	Unlock();
}

CImageData * CAoiManager::AllocImageData(const int nDeviceId, void *pBuffer, const unsigned int nDataLen, const int width, const int height)
{
	CImageData * pImageData = NULL;
	Lock();
	if (!m_listImageDataPool.empty()) {
		CImageData *pItem = m_listImageDataPool.front();
		if (pItem->m_nWidth == width
			&& pItem->m_nHeight == height
			&& pItem->m_nDataLength == nDataLen ) {
			ASSERT(pItem->m_pData);
			memcpy(pItem->m_pData, pBuffer, nDataLen);
			pItem->m_nDeviceId = nDeviceId;
			pItem->m_dwTickCount = GetTickCount();
			m_listImageDataPool.pop_front();
			pImageData = pItem;
		}
		else {
			CUtils::Log("AllocImageData %d x %d", pItem->m_nWidth, width);
		}
	}
	Unlock();

	return pImageData;
}

void CAoiManager::RecyleImageData(CImageData *pImageData)
{
	Lock();
	m_listImageDataPool.push_back(pImageData);
	Unlock();


}

void CAoiManager::TransferFile(CString strFilepath, CString strServer)
{
	m_hChannelForTransferFileClient = BYS_CreateChannelsTCPC("ddd", (LPTSTR)(LPCTSTR)strServer, 19602);
	m_strSendFilepath = strFilepath;
	CUtils::Log("正在连接");
}

void CAoiManager::ResendCodes(CStringList &strCodeList)
{
	Lock();

	POSITION pos = strCodeList.GetHeadPosition();
	while (pos != NULL) {
		CString strCode = strCodeList.GetNext(pos);
		CQRCode *pQRCode = new CQRCode(strCode, 0, 0);
		m_listGetCode.push_back(pQRCode);
	}
	SetEvent(m_hEventGetCode);

	Unlock();
}

void CAoiManager::Welcome()
{
	static char szBuffer[4] = { 0x80, 0x80, 0x03, 0x00 };
	if (m_hChannelForPlc != NULL) {
		BYS_Send(m_hChannelForPlc, szBuffer, 4, m_nActiveSocket);
	}
}

void CAoiManager::Alert()
{
	static char szBuffer[4] = {0x80, 0x80, 0x02, 0x00};
	if (m_hChannelForPlc != NULL) {
		BYS_Send(m_hChannelForPlc, szBuffer, 4, m_nActiveSocket);
	}
}

void CAoiManager::Heart()
{
	static char szBuffer[4] = { 0x80, 0x80, 0x05, 0x00 };
	if (m_hChannelForPlc != NULL) {
		BYS_Send(m_hChannelForPlc, szBuffer, 4, m_nActiveSocket);
	}
}


