/*************************************************************************
Copyright (c) 2013 深圳双翌光电科技有限公司
All rights reserved.

文件名称：标准相继取像dll
文件标识：标准相继取像dll头文件
摘    要：常用函数
当前版本：V2.0.0.1
作    者：Timmy.wang
完成日期：2019年05月14日
修改记录：
20190514：
1:建立独立的Mindvision相机取像

20180729：
1：修改Baumer相机的触发模式中的软件触发和硬件触发序号
2：修改相机设置异常，无法设置Brightness等参数，实际是由于创建拉流顺序引起的
3：修改系统中的最大曝光时间为200ms
4：校准各家相机高级参数的支持情况
5：修改系统识别相机时，识别后继续识别
20181122：
1：修正以前在读取相机参数时创建的指针没有销毁功能，导致数据内存泄露问题
2：增加MidVision相机
20181205：
1：增加相机多次打开防呆保护
20190107：
1：如果某个相机掉线了，则需要要把相机注销回调，并且直接断开相机连接
只有软件重新启动才可以，防止心跳信号一直写log文件
20190118：
1：较少停止拉流时的延迟时间，从500ms减少到50ms
20190326：
1：增加保存料号功能，把相机参数跟着料号文件走
20190411：
1：增加相机切换模式和软件出发信号之间加锁
20190508：
1：增加相机硬件触发上升沿和下降沿设置功能
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
	int		  IDIndex;				//对应Factory索引号(实际打开通道) 
	CString   StrUserIDName;		//相机名称
	CString   StrSN;				//相机SN号
	CString	  ModelName;			//相机型号
	CString	  CamShowName;			//相机显示名称
	
}DeviceInfo;
typedef struct CamSettingParam
{
	long	  m_ExposureTime;		//相机曝光时间
	float     m_GainValue;			//相机增益大小默认值是1
	BOOL      m_bAutoExposure;		//是否自动曝光
	BOOL      m_bAutoGain;			//是否自动增益
	BOOL      m_bXMirror;			//软件实现X镜像
	BOOL      m_bYMirror;			//软件实现Y镜像
	int		  m_iRotateType;		//软件实现图像旋转(RotateType,0:90度顺时针旋转;1：90度逆时针旋转;2：180度旋转;3:不进行图像旋转)
	int       m_iTrigEdgeType;		//硬件触发沿设定 0，上升沿 1 下降沿
	BOOL      m_bXReverse;			//硬件实现Y镜像
	BOOL      m_bYReverse;			//硬件实现X镜像
	long	  m_ExposureDelay;		//曝光延迟时间
	long	  m_TrigDelay;			//触发延迟时间
	long	  m_DebouncingTime;		//输入信号滤波时间
	long	  m_StrobeDuration;		//频闪信号输出时间
	long	  m_StrobeDelay;		//频闪延迟输出时间
	int       m_iDOMode;			//0:硬件触发频闪，1:软件触发频闪,2:通用DO输出
	UINT32  m_iBuffCount;           //系统创建缓存数量
	
	//新加图像处理ISP和效果处理
	float    m_GammaValue;			//Gamma值默认值是1
	long	 m_ShapneessValue;		//边沿锐度默认值是50
	BOOL     m_bShapnessEnable;		//边沿锐度有效默认OFF
	long	 m_DenoisingValue;		//Denoising降噪默认值是50
	BOOL     m_DenoisingEnable;		//Denoising降噪有效默认OFF
	long	 m_DigitalShiftValue;	//DigitalShift增强亮度默认值是0
	long	 m_BrightNessValue;		//BrightNess增强亮度默认值是50
	long	 m_ContrastValue;		//Contrast增强亮度默认值是50
	long	 m_ContrastThresholdValue;//Contrast增强亮度默认值是128,模式默认是OFF
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
//================以下对象属于静态成员函数（全局）====================
//====================================================================
//static函数，不管使用多少相机，也只能被调用一次
public:	
	static	vector<DeviceInfo> m_DeviceInfoVector;
	static  bool	m_bCurrentCamHasOpen[255];						// 系统中相机书否已经打开使用，防止多次打开某个相机
	static	BOOL	OpenFactory();									// Open factory and search for cameras.
	static	void	CloseFactory();									// Close open camera and close factory to clean up
	static	int		GetDeviceIndexFromUserID(CString UserID);		//根据自定义的相机的UserID，得到枚举的相机列表中的相机序号,-1是错误
	static  CameraVendor m_UseFactoryVendor;						//系统中使用那个厂家的SDK去遍历相机
//====================================================================
//================以下对象相机对象成员函数（类自己）==================
//====================================================================
public:
	BOOL  m_bNeedSaveParam;
	void LoadDeviceFromFile();
	void SaveDeviceToFile();

	//=================================================================
	//新增加API，用于将相机参数保存到不同的料号文件中去，方便切换料号
	void LoadDeviceFromProductIniFile(CString ProductPath);   //从文件中加载料号文件
	void SaveDeviceToProductIniFile(CString ProductPath);	   //保存相机参数到料号文件中

	void ShowDeviceInfoDlg(bool bSelectCam=TRUE);	
	
	/*********************************************************************
	* 相机参数修改
	*/
	void ShowCamParamInfoDlg();

	CDeviceInfoDlg	*m_pDeviceInfoDlg;	
	CString			m_strParamFileName;
	DeviceInfo		m_CurrentCamInf;
	unsigned int	m_nCurrentIndex;				//当前相机对应的list Index
	int				m_nChooseIndex;					//Choose Idex
	LONGLONG        m_iCurrentOKFramNo;				//系统取像OK数量
	LONGLONG        m_iCurrentBadFramNo;			//系统取像Bad数量
	CRITICAL_SECTION	LockSoftTrigAndMode;		//相机模式和软件触发锁
	 // Implementation
public:
	HANDLE				m_hFinishCapture;				//拍照完成event事件
	bool				m_bIsCurrentColorCam;			//当前相机是否是彩色相机标志位
	void				*m_pImageBuffer;				//extern Image buffer	
	int					m_iWidth;						//Image Width
	int					m_iHeight;						//Image Height
	double				m_fFrameRate;					//Frame Rate

	
	//Camera Operation
	BOOL OpenCamera(unsigned int SysCamIndex);	//打开相机
	void CloseCamera();							//关闭相机
	BOOL StartCapture();						//Start the image acquisition thread
	BOOL StopCapture();							// Terminate the image acquisition thread
	BOOL IsCamStart();							//Get Current Camera is or nor acquisition

	//Get Image Width/Heigth
	int		GetWidth();
	int		GetHeight();

	//Get/Set ExposureVal
	BOOL GetExposureVal(double *minExposure,double *maxExposure,double *currentExposure);
	BOOL SetExposureVal(double exposureVal);
	BOOL AutoExposure(bool bValue = false);		//bValue:True开启自动曝光反之则关闭
	BOOL AutoGain(bool bValue = false);			//bValue:True开启自动增益，反之则关闭
	
	//Get/Set Gain val
	BOOL GetGainVal(double *minGain,double *maxGain,double *currentGain);
	BOOL SetGainVal(double GainVal);

	//Get/Set Gamma val
	BOOL GetGammaVal(double *minGamma,double *maxGamma,double *currentGamma);
	BOOL SetGammaVal(double GammaVal);

	//设置和获取增强亮度参数
	bool SetBrightness(int Val);//设置亮度
	bool GetBrightnessVal(int *minBrightness,int *maxBrightness,int *currentBrightness);

	//设置和获取对比度强度参数
	bool SetContrast(int Val,int Threshold,int mode);//设置对比度 mode0 OFF Mode1 Once Mode2 Continue
	bool GetContrastVal(int *minContrast,int *maxContrast,int *currentContrast,int* Threshold,int* mode);

	//设置和获取边沿锐度参数
	BOOL GetSharpnessVal(int *minSharpness, int *maxSharpness, int *currentSharpness,int *EnableStatus); //EnableStatus 0 off 1ON
	BOOL SetSharpnessVal(int SharpnessVal,int EnableStatus);


	//设置和获Denoising降噪参数
	BOOL GetDenoisingVal(int *minDenoising, int *maxDenoising, int *currentDenoising,int *EnableStatus); //EnableStatus 0 off 1ON
	BOOL SetDenoisingVal(int DenoisingVal,int EnableStatus);

	//设置和获取增强亮度参数
	bool SetDigitalShiftValue(int Val);			//设置亮度
	bool GetDigitalShiftValue(int *minDigitalShiftValue,int *maxDigitalShiftValue,int *currentDigitalShiftValue);

	/************************************************************************************************************************
	* SetHorizontalMirror/SetVerticalMirror/SetMirror/SetRotate
	* 镜像和图像旋转功能为采用软件方式对图像进行操作，会损耗一些时间
	*/
	//镜像功能设定
	void SetHorizontalMirror(bool bValue);		//水平镜像	
	void SetVerticalMirror(bool bValue);		//垂直镜像

	//图像旋转,此功能只支持Dasla相机，未完成
	//RotateType,0:90度顺时针旋转;1：90度逆时针旋转;2：180度旋转;3:不进行图像旋转
	void SetRotate(int RotateType = 3);
	
	/*************************************************************************************************************************
	* SetReverseX/Y 为通过硬件设定改变镜像
	*/
	BOOL SetReverseX(bool bValue);
	BOOL SetReverseY(bool bVlue);

	
	bool		SetTriggerMode(EWorkMode nMode);				//nMode,0:连续采集;1:软件触发;2：硬件触发(目前系统只支持硬件上升沿触发)
	EWorkMode	GetCurrentCamMode();							//获取当前相机的采集模式
	BOOL		SetSoftTrig();									//软件触发
	BOOL		ExposureDelay(double val);						//设置曝光延迟时间us，,此功能未找到，未完成
	BOOL		TriggerDelay(double val);						//输入延迟 可用于硬/软触发us
	BOOL		TriggerlineDebouncing(double val);				//输入滤波时间us
	BOOL		TriggerInputPolarity();							//设置输入触发极性	
	
	/**************************************************************************************************************************
	* 频闪设定
	*/
	BOOL SetStrobePolarity(bool bRisingEdge=true);		//当频闪模式时0时，需要设置该功能,此功能未找到，未完成
	BOOL SetStrobeDuration(long val);								//频闪持续时间	us	,此功能未找到，未完成						
	BOOL SetStrobeDelay(double val);								//频闪信号延迟时间us,此功能未找到，未完成
	
	//nMode,
	//0: 输入1信号控制频闪(系统默认是上升沿触发，可以在本函数之后调用SetStrobePolarity修改);
	//1：内部曝光控制频闪(即一帧开启后输出曝光DO)
	//2: 通过自定义DO来控制频频闪
	BOOL SetStrobeOutputLineSource(int nMode);	
	//手动输出频闪，当SetStrobeOutputLineSource模式设置为2的时候有效
	BOOL SetMaunalStrobeOutPut(bool bOutputValue);	

	/*************************************************************************************************************************
	*输入输出接口函数
	*/
	BOOL ReadDI(bool *bLineStatus);
	bool WriteDO(bool bSwitch);


	/**************************************************************************************************************************
	* 相机参数设定
	*/
	CamSettingParam m_CamSettingParam;
	BOOL SetCamParam(CamSettingParam Param);
private:
	bool	m_bFlipHorizontal;
	bool	m_bFlipVertical;
	bool	m_bRotate;
public:
	/******************************************************************************************
	* 将CString转换成char*
	*/
	char* CStringToCharArray(CString cStr); 
	/******************************************************************************************
	* 将CString转换成int
	*/
	int   CStringToInt(CString str);

	/******************************************************************************************
	* 将CString转换成double
	*/
	double CStringToDouble(CString str);
	
	bool m_bCaptureFlg;
private:
	BOOL	FindFileInDir(CString FileName);
	CString	GetPathDir();		
	EWorkMode m_mode;
	bool m_bConnectFlg;													//相机打开成功
public:
	CMindVisionCameraPrivate* m_pMindVision;
	CHikvisionCamPrivate*	  m_pHikvisionVision;
	CHuaRuiCamPrivate*		  m_pHuaRuiVision;
};

#endif