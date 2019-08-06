/*************************************************************************
Copyright (c) 2013 ����˫����Ƽ����޹�˾
All rights reserved.

�ļ����ƣ���׼���ȡ��dll
�ļ���ʶ����׼���ȡ��dllͷ�ļ�
ժ    Ҫ�����ú���
��ǰ�汾��V2.0.0.1
��    �ߣ�Timmy.wang
������ڣ�2019��05��14��
�޸ļ�¼��
20190514��
1:����������Mindvision���ȡ��

20180729��
1���޸�Baumer����Ĵ���ģʽ�е����������Ӳ���������
2���޸���������쳣���޷�����Brightness�Ȳ�����ʵ�������ڴ�������˳�������
3���޸�ϵͳ�е�����ع�ʱ��Ϊ200ms
4��У׼��������߼�������֧�����
5���޸�ϵͳʶ�����ʱ��ʶ������ʶ��
20181122��
1��������ǰ�ڶ�ȡ�������ʱ������ָ��û�����ٹ��ܣ����������ڴ�й¶����
2������MidVision���
20181205��
1�����������δ򿪷�������
20190107��
1�����ĳ����������ˣ�����ҪҪ�����ע���ص�������ֱ�ӶϿ��������
ֻ��������������ſ��ԣ���ֹ�����ź�һֱдlog�ļ�
20190118��
1������ֹͣ����ʱ���ӳ�ʱ�䣬��500ms���ٵ�50ms
20190326��
1�����ӱ����ϺŹ��ܣ���������������Ϻ��ļ���
20190411��
1����������л�ģʽ����������ź�֮�����
20190508��
1���������Ӳ�����������غ��½������ù���
*************************************************************************/

#pragma once

#ifndef _GCAMDEVICE_H   
#define _GCAMDEVICE_H  

#include <vector>
using namespace std;

enum CameraVendor { Dalsa, Basler, ImageSource, SHUANGYI, MVision, DahuaMV, Baumer, MindVision, Hikvision, UndefineVendor };

class CDeviceInfoDlg;
class CForceIpDlg;
typedef struct CamDeviceInfo
{
	int		  IDIndex;				//��ӦFactory������(ʵ�ʴ�ͨ��) 
	CString   StrUserIDName;		//�������
	CString   StrSN;				//���SN��
	CString	  ModelName;			//����ͺ�
	CString	  CamShowName;			//�����ʾ����
	
}DeviceInfo;
typedef struct CamSettingParam
{
	long	  m_ExposureTime;		//����ع�ʱ��
	float     m_GainValue;			//��������СĬ��ֵ��1
	BOOL      m_bAutoExposure;		//�Ƿ��Զ��ع�
	BOOL      m_bAutoGain;			//�Ƿ��Զ�����
	BOOL      m_bXMirror;			//���ʵ��X����
	BOOL      m_bYMirror;			//���ʵ��Y����
	int		  m_iRotateType;		//���ʵ��ͼ����ת(RotateType,0:90��˳ʱ����ת;1��90����ʱ����ת;2��180����ת;3:������ͼ����ת)
	int       m_iTrigEdgeType;		//Ӳ���������趨 0�������� 1 �½���
	BOOL      m_bXReverse;			//Ӳ��ʵ��Y����
	BOOL      m_bYReverse;			//Ӳ��ʵ��X����
	long	  m_ExposureDelay;		//�ع��ӳ�ʱ��
	long	  m_TrigDelay;			//�����ӳ�ʱ��
	long	  m_DebouncingTime;		//�����ź��˲�ʱ��
	long	  m_StrobeDuration;		//Ƶ���ź����ʱ��
	long	  m_StrobeDelay;		//Ƶ���ӳ����ʱ��
	int       m_iDOMode;			//0:Ӳ������Ƶ����1:�������Ƶ��,2:ͨ��DO���
	UINT32  m_iBuffCount;           //ϵͳ������������
	
	//�¼�ͼ����ISP��Ч������
	float    m_GammaValue;			//GammaֵĬ��ֵ��1
	long	 m_ShapneessValue;		//�������Ĭ��ֵ��50
	BOOL     m_bShapnessEnable;		//���������ЧĬ��OFF
	long	 m_DenoisingValue;		//Denoising����Ĭ��ֵ��50
	BOOL     m_DenoisingEnable;		//Denoising������ЧĬ��OFF
	long	 m_DigitalShiftValue;	//DigitalShift��ǿ����Ĭ��ֵ��0
	long	 m_BrightNessValue;		//BrightNess��ǿ����Ĭ��ֵ��50
	long	 m_ContrastValue;		//Contrast��ǿ����Ĭ��ֵ��50
	long	 m_ContrastThresholdValue;//Contrast��ǿ����Ĭ��ֵ��128,ģʽĬ����OFF
}CamSettingParam;

typedef enum{
	ContinueMode = 0,
	SoftTrigMode,
	HardTrigMode
}EWorkMode;

struct CMindVisionCameraPrivate;
struct CHikvisionCamPrivate;
struct CHuaRuiCamPrivate;

class AFX_EXT_CLASS CGeniCAMCapture : public CObject
{
public:
	CGeniCAMCapture();
	virtual ~CGeniCAMCapture();
//====================================================================
//================���¶������ھ�̬��Ա������ȫ�֣�====================
//====================================================================
//static����������ʹ�ö��������Ҳֻ�ܱ�����һ��
public:	
	static	vector<DeviceInfo> m_DeviceInfoVector;
	static  bool	m_bCurrentCamHasOpen[255];						// ϵͳ���������Ѿ���ʹ�ã���ֹ��δ�ĳ�����
	static	BOOL	OpenFactory();									// Open factory and search for cameras.
	static	void	CloseFactory();									// Close open camera and close factory to clean up
	static	int		GetDeviceIndexFromUserID(CString UserID);		//�����Զ���������UserID���õ�ö�ٵ�����б��е�������,-1�Ǵ���
	static  CameraVendor m_UseFactoryVendor;						//ϵͳ��ʹ���Ǹ����ҵ�SDKȥ�������
//====================================================================
//================���¶�����������Ա���������Լ���==================
//====================================================================
public:
	BOOL  m_bNeedSaveParam;
	void LoadDeviceFromFile();
	void SaveDeviceToFile();

	//=================================================================
	//������API�����ڽ�����������浽��ͬ���Ϻ��ļ���ȥ�������л��Ϻ�
	void LoadDeviceFromProductIniFile(CString ProductPath);   //���ļ��м����Ϻ��ļ�
	void SaveDeviceToProductIniFile(CString ProductPath);	   //��������������Ϻ��ļ���

	void ShowDeviceInfoDlg(bool bSelectCam=TRUE);	
	
	/*********************************************************************
	* ��������޸�
	*/
	void ShowCamParamInfoDlg();

	CDeviceInfoDlg	*m_pDeviceInfoDlg;	
	CString			m_strParamFileName;
	DeviceInfo		m_CurrentCamInf;
	unsigned int	m_nCurrentIndex;				//��ǰ�����Ӧ��list Index
	int				m_nChooseIndex;					//Choose Idex
	LONGLONG        m_iCurrentOKFramNo;				//ϵͳȡ��OK����
	LONGLONG        m_iCurrentBadFramNo;			//ϵͳȡ��Bad����
	CRITICAL_SECTION	LockSoftTrigAndMode;		//���ģʽ�����������
	 // Implementation
public:
	HANDLE				m_hFinishCapture;				//�������event�¼�
	bool				m_bIsCurrentColorCam;			//��ǰ����Ƿ��ǲ�ɫ�����־λ
	void				*m_pImageBuffer;				//extern Image buffer	
	int					m_iWidth;						//Image Width
	int					m_iHeight;						//Image Height
	double				m_fFrameRate;					//Frame Rate

	
	//Camera Operation
	BOOL OpenCamera(unsigned int SysCamIndex);	//�����
	void CloseCamera();							//�ر����
	BOOL StartCapture();						//Start the image acquisition thread
	BOOL StopCapture();							// Terminate the image acquisition thread
	BOOL IsCamStart();							//Get Current Camera is or nor acquisition

	//Get Image Width/Heigth
	int		GetWidth();
	int		GetHeight();

	//Get/Set ExposureVal
	BOOL GetExposureVal(double *minExposure,double *maxExposure,double *currentExposure);
	BOOL SetExposureVal(double exposureVal);
	BOOL AutoExposure(bool bValue = false);		//bValue:True�����Զ��ع֮ⷴ��ر�
	BOOL AutoGain(bool bValue = false);			//bValue:True�����Զ����棬��֮��ر�
	
	//Get/Set Gain val
	BOOL GetGainVal(double *minGain,double *maxGain,double *currentGain);
	BOOL SetGainVal(double GainVal);

	//Get/Set Gamma val
	BOOL GetGammaVal(double *minGamma,double *maxGamma,double *currentGamma);
	BOOL SetGammaVal(double GammaVal);

	//���úͻ�ȡ��ǿ���Ȳ���
	bool SetBrightness(int Val);//��������
	bool GetBrightnessVal(int *minBrightness,int *maxBrightness,int *currentBrightness);

	//���úͻ�ȡ�Աȶ�ǿ�Ȳ���
	bool SetContrast(int Val,int Threshold,int mode);//���öԱȶ� mode0 OFF Mode1 Once Mode2 Continue
	bool GetContrastVal(int *minContrast,int *maxContrast,int *currentContrast,int* Threshold,int* mode);

	//���úͻ�ȡ������Ȳ���
	BOOL GetSharpnessVal(int *minSharpness, int *maxSharpness, int *currentSharpness,int *EnableStatus); //EnableStatus 0 off 1ON
	BOOL SetSharpnessVal(int SharpnessVal,int EnableStatus);


	//���úͻ�Denoising�������
	BOOL GetDenoisingVal(int *minDenoising, int *maxDenoising, int *currentDenoising,int *EnableStatus); //EnableStatus 0 off 1ON
	BOOL SetDenoisingVal(int DenoisingVal,int EnableStatus);

	//���úͻ�ȡ��ǿ���Ȳ���
	bool SetDigitalShiftValue(int Val);			//��������
	bool GetDigitalShiftValue(int *minDigitalShiftValue,int *maxDigitalShiftValue,int *currentDigitalShiftValue);

	/************************************************************************************************************************
	* SetHorizontalMirror/SetVerticalMirror/SetMirror/SetRotate
	* �����ͼ����ת����Ϊ���������ʽ��ͼ����в����������һЩʱ��
	*/
	//�������趨
	void SetHorizontalMirror(bool bValue);		//ˮƽ����	
	void SetVerticalMirror(bool bValue);		//��ֱ����

	//ͼ����ת,�˹���ֻ֧��Dasla�����δ���
	//RotateType,0:90��˳ʱ����ת;1��90����ʱ����ת;2��180����ת;3:������ͼ����ת
	void SetRotate(int RotateType = 3);
	
	/*************************************************************************************************************************
	* SetReverseX/Y Ϊͨ��Ӳ���趨�ı侵��
	*/
	BOOL SetReverseX(bool bValue);
	BOOL SetReverseY(bool bVlue);

	
	bool		SetTriggerMode(EWorkMode nMode);				//nMode,0:�����ɼ�;1:�������;2��Ӳ������(Ŀǰϵͳֻ֧��Ӳ�������ش���)
	EWorkMode	GetCurrentCamMode();							//��ȡ��ǰ����Ĳɼ�ģʽ
	BOOL		SetSoftTrig();									//�������
	BOOL		ExposureDelay(double val);						//�����ع��ӳ�ʱ��us��,�˹���δ�ҵ���δ���
	BOOL		TriggerDelay(double val);						//�����ӳ� ������Ӳ/����us
	BOOL		TriggerlineDebouncing(double val);				//�����˲�ʱ��us
	BOOL		TriggerInputPolarity();							//�������봥������	
	
	/**************************************************************************************************************************
	* Ƶ���趨
	*/
	BOOL SetStrobePolarity(bool bRisingEdge=true);		//��Ƶ��ģʽʱ0ʱ����Ҫ���øù���,�˹���δ�ҵ���δ���
	BOOL SetStrobeDuration(long val);								//Ƶ������ʱ��	us	,�˹���δ�ҵ���δ���						
	BOOL SetStrobeDelay(double val);								//Ƶ���ź��ӳ�ʱ��us,�˹���δ�ҵ���δ���
	
	//nMode,
	//0: ����1�źſ���Ƶ��(ϵͳĬ���������ش����������ڱ�����֮�����SetStrobePolarity�޸�);
	//1���ڲ��ع����Ƶ��(��һ֡����������ع�DO)
	//2: ͨ���Զ���DO������ƵƵ��
	BOOL SetStrobeOutputLineSource(int nMode);	
	//�ֶ����Ƶ������SetStrobeOutputLineSourceģʽ����Ϊ2��ʱ����Ч
	BOOL SetMaunalStrobeOutPut(bool bOutputValue);	

	/*************************************************************************************************************************
	*��������ӿں���
	*/
	BOOL ReadDI(bool *bLineStatus);
	bool WriteDO(bool bSwitch);


	/**************************************************************************************************************************
	* ��������趨
	*/
	CamSettingParam m_CamSettingParam;
	BOOL SetCamParam(CamSettingParam Param);
private:
	bool	m_bFlipHorizontal;
	bool	m_bFlipVertical;
	bool	m_bRotate;
public:
	/******************************************************************************************
	* ��CStringת����char*
	*/
	char* CStringToCharArray(CString cStr); 
	/******************************************************************************************
	* ��CStringת����int
	*/
	int   CStringToInt(CString str);

	/******************************************************************************************
	* ��CStringת����double
	*/
	double CStringToDouble(CString str);
	
	bool m_bCaptureFlg;
private:
	BOOL	FindFileInDir(CString FileName);
	CString	GetPathDir();		
	EWorkMode m_mode;
	bool m_bConnectFlg;													//����򿪳ɹ�
public:
	CMindVisionCameraPrivate* m_pMindVision;
	CHikvisionCamPrivate*	  m_pHikvisionVision;
	CHuaRuiCamPrivate*		  m_pHuaRuiVision;
};

#endif