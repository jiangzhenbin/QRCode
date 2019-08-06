////////////////////////////////////
// BYSsocketDll.h

// һЩ����

//
///////////////
// �����Ϣ
#define BYSWM_BYSMSG					WM_USER+1000		// SCDLL��״̬��Ϣ
#define BYSWM_SOCKETMSGTCP				WM_USER+1009		// Sockets����ϢTCP
#define BYSWM_SOCKETMSGUDP				WM_USER+1100		// Sockets����ϢUDP
#define BYSWM_CONNECT					WM_USER+1101		// ���ӽ��
#define BYSWM_ACCEPT					WM_USER+1102		// �пͻ�����ʱ
#define BYSWM_READ						WM_USER+1103		// �����ݵ���ʱ
#define BYSWM_WRITE						WM_USER+1104		// ������Ҫ����ʱ
#define BYSWM_CLOSE						WM_USER+1105		// ���ӹر�ʱ����ϢID
#define BYSWM_SENDDATARESULT			WM_USER+1106		// �������ݵĽ��
#define BYSWM_WORKTHREAD_ENTER			WM_USER+1107		// �����߳̽���ʱ
#define BYSWM_WORKTHREAD_LEAVE			WM_USER+1108		// �����߳��뿪ʱ



#define			BYSEND_STATE_OK		01	// ����״̬-�ɹ�
#define			BYSEND_STATE_TIMEOUT	02	// ����״̬-��ʱ
#define			BYSEND_STATE_NOSERVER	03	// �Ҳ���������



#define BYS_MSG_INITING					1				// ���ڳ�ʼ��
#define BYS_MSG_INITOK					2				// ��ʼ���ɹ�
#define BYS_MSG_INITERROR				3				// ��ʼ���ɹ�
#define BYS_MSG_TERM					4				// ��ʼ���ɹ�
#define BYS_MSG_STARTUP					5				// ����������
#define BYS_MSG_STOP					6				// ��ֹͣ����
#define BYS_MSG_CREATECHANNELSOK		7				// ������ͨ���ɹ�
#define BYS_MSG_CREATECHANNELSERROR		8				// ������ͨ��ʧ��
#define BYS_ER_NOSERVER					1001			// �Ҳ���������



// ����Ŀͻ���
typedef struct _ACCEPTClient
{
	UINT_PTR			socket;
	DWORD				address;
	DWORD				port;
	DWORD				index;
	DWORD				threadId;
} ACCEPTClient;


// ���ݽṹ
// Socket�յĵ�����
typedef struct _BYSRECVDATA
{
	UINT_PTR			sock;				// SOCKET;
	HANDLE				hChannels;			// BYSCHANNELSָ��
	char*				pData;				// ����ָ��
	DWORD				dwLen;				// ���ݳ���
	unsigned int		uiIp;				// ��Դip(UDP��ʽʱʹ��)
	unsigned int		usPort;				// ��Դ�˿�(UDP��ʽʱʹ��)
	LONG_PTR			dwUserData;			// �û�����
} BYSRECVDATA;

typedef void (*AddLogTextFunction)(char*);			// ��ʾ��־�ĺ���, �ɵ���������

// ��Ϣ������, �ɵ���������(����ⲿ����û�д���, ֻ��������Ϣ������)
typedef long (*MSGDispatchFunction)(UINT, WPARAM, LPARAM);

// UDP�����ص�����
typedef long (*OnUDPClientHeart)(BYSRECVDATA *, char*, unsigned int, unsigned int *);
typedef long (*OnUDPHeartRespone)(BYSRECVDATA *);


// UDP�յ����ݻص�����
typedef long (*OnUDPRecvData)(BYSRECVDATA *);

///////////////////////////////////////////////////////////////////////////////////
//// Define C linkage if using a C++ compiler
///////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	
	///////////////////////////////////////////////////////////////////////////////////
	//// Determine callling convention baesd on compiler
	///////////////////////////////////////////////////////////////////////////////////
#ifdef __BORLANDC__
	
#ifdef __WIN32__
#define EXPORTED __declspec(dllexport) __stdcall
#else
#define EXPORTED FAR PASCAL __export
#endif // WIN32
	
#else // __BORLANDC__
	
	
#ifdef WIN32
#define EXPORTED __declspec(dllexport)
#else
#define EXPORTED FAR PASCAL __export
#endif // WIN32
	
#endif //__BORLANDC__
	
	
	
	/////////////////////////////////////////////////////////////////////////////////////
	//// ��������
	////////////////////////////////////////////////////////////////////////////////////
	int			EXPORTED	BYS_Initialize(HWND);
	int			EXPORTED	BYS_Term();
	int			EXPORTED	BYS_ChangeMsg(UINT, UINT);	
	HANDLE		EXPORTED	BYS_CreateChannelsTCPS(char*, UINT);
	HANDLE		EXPORTED	BYS_CreateChannelsTCPC(char* pName,
								char* pServer = NULL, UINT nSPort = 0);
	HANDLE		EXPORTED	BYS_CreateChannelsUDP(char*, UINT, DWORD);
	HANDLE		EXPORTED	BYS_CreateChannelsPFW(char*);
	int			EXPORTED	BYS_CloseChannels(HANDLE);
	int			EXPORTED	BYS_CloseSocket(DWORD dwSocket);
	int			EXPORTED	BYS_Connect(HANDLE, char*, UINT);
	int			EXPORTED	BYS_Send(HANDLE, char*,	DWORD, UINT sock = NULL);
	int			EXPORTED	BYS_Sendto(HANDLE, char*, DWORD, UINT, UINT, BOOL bRetry = TRUE);
	int			EXPORTED	BYS_SendHeartDatato(HANDLE hChannels, char* pData, DWORD dwLen, UINT uIP, UINT uPort);
	int			EXPORTED	BYS_Sendto2(HANDLE hChannels, char* pData,
							DWORD dwLen, UINT uIP, UINT uPort, BOOL bRetry, 
							DWORD dwUserData, HANDLE hEvent, DWORD *pdwFinishCode, UINT *pnUseTime);
	int			EXPORTED	BYS_Sendto3(HANDLE hChannels, char* pData,
												DWORD dwLen, UINT uIP, UINT uPort);
	int			EXPORTED	BYS_GetChannelsCount();
	HANDLE		EXPORTED	BYS_GetChannelsAt(int);
	int			EXPORTED	BYS_GetChannelsName(HANDLE, char*, int);
	BOOL		EXPORTED	BYS_ChannelIsConnected(HANDLE hChannel);
	DWORD		EXPORTED	BYS_GetChannelsSocket(HANDLE);
	UINT		EXPORTED	BYS_GetChannelsPort(HANDLE);
	LONG_PTR	EXPORTED	BYS_GetChannelsUserdata(HANDLE hChannels);
	int			EXPORTED	BYS_GetChannelsType(HANDLE);
	int			EXPORTED	BYS_GetChannelsTypeEx(HANDLE);
	int			EXPORTED	BYS_GetUDPPacketSize();
	int			EXPORTED	BYS_SetUDPPacketSize(int);
	int			EXPORTED	BYS_UIP2SIP(UINT, char*, int);
	LPVOID 		EXPORTED	BYS_GetIPString(UINT uiIP);
	UINT		EXPORTED	BYS_SIP2UIP(char*);
	UINT		EXPORTED	BYS_GetHostSIP(char* pHost, char* pBuf, int nBufSize);
	UINT		EXPORTED	BYS_GetHostUIP(char* pHost);
	DWORD		EXPORTED	BYS_GetSendPress(HANDLE, DWORD);
	int			EXPORTED	BYS_SetALTFunction(AddLogTextFunction pFunction);
	int			EXPORTED	BYS_SetMSGDFunction(MSGDispatchFunction pMSGDispatchFunction);	
	int			EXPORTED	BYS_SetMSGDFunction2(MSGDispatchFunction pMSGDispatchFunction);	
	int			EXPORTED	BYS_SetChannelsUDPClientHeartCallback(HANDLE hChannels, OnUDPClientHeart pOnUDPClientHeart);	
	int			EXPORTED	BYS_SetChannelsUDPHeartResponeCallback(HANDLE hChannels, OnUDPHeartRespone pOnUDPHeartRespone);	
	int			EXPORTED	BYS_SetChannelsUDPRecvDataCallback(HANDLE hChannels, OnUDPRecvData pOnUDPRecvData);
	int			EXPORTED	BYS_ClientBeginSend(HANDLE hChannels, HANDLE hEvent);
	int			EXPORTED	BYS_ClientSending(HANDLE hChannels, char* pData, DWORD dwLen);
	int			EXPORTED	BYS_ClientEndSend(HANDLE hChannels);
	int			EXPORTED	BYS_SeverSetSocketTickPointer(HANDLE hChannels, SOCKET sock, DWORD *pdwTick);
	int			EXPORTED	BYS_ServerSendAdditional(HANDLE hChannels, char* pData, DWORD dwLen, SOCKET sock, char *pShorData, DWORD dwShortDataLen);
	int			EXPORTED	BYS_SetChannelTag(HANDLE hChannel, unsigned int index, DWORD tag);
	DWORD		EXPORTED	BYS_GetChannelTag(HANDLE hChannel, unsigned int index);

#ifdef __cplusplus
};

#endif //__cplusplus