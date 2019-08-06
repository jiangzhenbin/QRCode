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
	int m_nCodeLengthFilterType;			/* 0:������ 1:С�� 2:���� 3:���� */
	int m_nCodeLengthFileterValue;			/* ���� */
	int m_nCameraExposureTime;				/* ����ع� */
	int m_nEnableCameraCount;				/* ���õ������ */
	std::unordered_map<unsigned int, std::string> m_mapCameraSN;
	CString m_strCameraKey;
	int m_nAoiMaxTickCount;					// ͬһ���̵ļ��ʱ���(����)
	int m_nQRCodeBufferSize;	
	BOOL m_bDishCheck;
	char m_szMesEndPoint[256];
	char szUVId[32];
	double m_fFrameRate;
};

