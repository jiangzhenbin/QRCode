#pragma once
#include <unordered_map>
#include <string>

class CSettings
{
public:
	CSettings();
	~CSettings();

public:
	CString m_strProductModel;
	int m_nTestTotal;
	int m_nNgCount;
	int m_codeType;                         /* jiang, Barcode Type */
	int m_nCodeLengthFilterType;			/* 0:不启用 1:小于 2:等于 3:大于 */
	int m_nCodeLengthFileterValue;			/* 长度 */
	int m_nCameraExposureTime;				/* 相机曝光 */
	int m_nEnableCameraCount;				/* 启用的相机数 */
	std::unordered_map<unsigned int, std::string> m_mapCameraSN;
	CString m_strCameraKey;
	int m_nAoiMaxTickCount;					// 同一托盘的检测时间差(毫秒)
	int m_nQRCodeBufferSize;	
	BOOL m_bDishCheck;
	char m_szMesEndPoint[256];
	char szUVId[32];
	double m_fFrameRate;
};

