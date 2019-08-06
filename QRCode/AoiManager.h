#pragma once
#include "../CameraSDK/CameraEngine.h"
#include "VisionProcess.h"
#include "Settings.h"
#include "DishAnalyse.h"


enum CODESTATE {
	READY = 0,				/* 就绪 */
	SENDING,				/* 发送中 */
	SUCCEED,				/* 成功 */
	FAILED,					/* 失败 */
};

enum PLCSTATE {
	UNKNOW = 0,				/* 未知 */
	CONNECTED,				/* 已连接 */
	DISCONNECTED,			/* 断开 */
	ACTIVE,					/* 活动，即收到数据 */
};

struct AOIFILE
{
	DWORD dwHead;
	DWORD dwLength;
	char szFileName[_MAX_PATH];
};

class CQRCode
{
public:
	CQRCode() { };
	CQRCode(CString code, int cameraId, DWORD tickCount) {
		this->code = code;
		this->cameraId = cameraId;
		this->state = READY;
		this->dwTickCount = tickCount;
	};
	~CQRCode() { };


public:
	CString code;
	int cameraId;
	CODESTATE state;
	DWORD dwTickCount;			// 相当于时间戳

};

class CImageData
{
public:
	CImageData() { 
		this->m_pData = NULL;
		this->m_nWidth = 0;
		this->m_nHeight = 0;
	};
	CImageData(unsigned int nDeviceId, void *pData, const unsigned int nDataLength, const unsigned int nWidth, const unsigned int nHeight) {
		this->m_nDeviceId = nDeviceId;
		this->m_pData = new char[nDataLength];
		memcpy(m_pData, pData, nDataLength);
		this->m_nDataLength = nDataLength;
		this->m_nWidth = nWidth;
		this->m_nHeight = nHeight;
	};
	void Init(const unsigned int nWidth, const unsigned int nHeight) {
		this->m_nWidth = nWidth;
		this->m_nHeight = nHeight;
		this->m_nDataLength = nWidth * nHeight;
		if (this->m_pData != NULL) {
			delete[] this->m_pData;
		}
		this->m_pData = new char[this->m_nDataLength];
	};
	~CImageData() { 
		if (this->m_pData != NULL) {
			delete[] this->m_pData;
		}
	};

public:
	unsigned int m_nDeviceId;
	char *m_pData;
	unsigned int m_nWidth;
	unsigned int m_nHeight;
	unsigned int m_nDataLength;
	DWORD m_dwTickCount;			// 相当于时间戳
};

typedef std::function<void(CQRCode *pQRCode)> ONGETNEWCODE;
typedef std::function<void(CQRCode *pQRCode)> ONCODESTATECHANGED;
typedef std::function<void(PLCSTATE state)> ONPLCSTATECHANGED;

class CAoiManager
{
public:
	CAoiManager();
	~CAoiManager();
	void Alert();
	void Welcome();
	void Heart();
	ONCODESTATECHANGED GetOnCodeStateChangedListener();

private:
	static long Socket_DispathFunction(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Socket_OnBYSRead(WPARAM wParam, LPARAM lParam);
	void Socket_OnClose(WPARAM wParam, LPARAM lParam);
	void Socket_OnConnect(WPARAM wParam, LPARAM lParam);
	void Socket_OnAccept(WPARAM wParam, LPARAM lParam);
	static UINT MesThreadProc(LPVOID lParam);
	UINT MesThreadProcInner();
	static UINT AoiThreadProc(LPVOID lParam);
	UINT AoiThreadProcInner();
	inline void Lock();
	inline void Unlock();
	void RoiPoint2WndPoint(HWND hWnd, int imgWidth, int imgHeight, double x, double y, LPPOINT pt);
	int AppedCode(CString strCode, const int nCameraId, DWORD dwTickCount);
	void InitImageDataPool(const unsigned int count, const unsigned int imgWidth, const unsigned int imgHeight);
	void FreeImageDataPool();
	CImageData * AllocImageData(const int nDeviceId, void *pBuffer, const unsigned int nDataLen, const int width, const int height);
	void RecyleImageData(CImageData *pImageData);

public:
	void SetWindows(HWND *pHwnd, int count);
	void SetSettingsPtr(CSettings *pSettings);
	void Init();
	void UnInit();
	void SetOnNewCodeListener(ONGETNEWCODE listener);
	void SetOnCodeStateChangedListener(ONCODESTATECHANGED listener);
	void SetOnPlcStateChangedListener(ONPLCSTATECHANGED listener);
	BOOL IsAoiExecute();
	void ExecuteAoi(BOOL bExecute);
	void TransferFile(CString strFilepath, CString strServer);
	void ResendCodes(CStringList &strCodeList);

private:
	static CAoiManager *m_pAoiManager;
	HANDLE m_hChannelForPlc;
	UINT_PTR m_nActiveSocket;
	CCameraEngine m_cameraEngine;
	CDeviceProcess *m_pProcess[4];
	VisionProcess m_visionProcess[4];
	std::list<CQRCode *> m_listGetCode;					// 已识别到的code的List
	std::list<CQRCode *> m_listSendingCode;				// 正在发送到SEM的code的List
	std::list<CQRCode *> m_listOkCode;					// 已成功发送到SEM的code的List
	std::list<CImageData *> m_listWaitForProcessImg;	// 待处理图像列表
	std::list<CImageData *> m_listImageDataPool;		// CImageData对象池


	CRITICAL_SECTION m_lock;
	HWND m_hWndPreview[4];						// 预览窗口
	int m_nPlcEvent;							// plc信号
	HANDLE m_hEventSemThreadExit;
	HANDLE m_hEventAoiThreadExit;
	HANDLE m_hEventGetCode;
	HANDLE m_hEventGetImage;
	BOOL m_bRunning;
	ONGETNEWCODE m_fGetNewCode;
	ONCODESTATECHANGED m_fCodeStateChanged;
	ONPLCSTATECHANGED m_fPlcStateChanged;
	CSettings *m_pSettings;
	BOOL m_bExecuteAoi;

public:
	DishAnalyse m_dishAnalyse;

private:
	HANDLE m_hChannelForTransferFile;
	CFile m_file;
	AOIFILE m_aoiFile;
	unsigned int m_nRecvLength;

	BOOL m_isOk[4];						/*  */
	double m_getStartTime;
	bool m_isExecute;


private:
	HANDLE m_hChannelForTransferFileClient;
	CString m_strSendFilepath;
	CFile m_file2;
};

