#pragma once
#include "../VisionSDK/ClsVision.h"
#include "../VisionSDK/BarcodeDotProcess.h"
#include "../VisionSDK/DMDotProcess.h"
#include "../VisionSDK/QRDotProcess.h"

class VisionProcess
{
public:
	VisionProcess();
	~VisionProcess();

public:
	void Init();
	void Process(HalconCpp::HObject& hObject, int codeType, std::string& strOutCode, double &fCostTime, RoiRegion *pRoiRegion);
	int Process8BitImage(const void *pImgData, const int width, const int height, int codeType, std::string& strOutCode, double &fCostTime, RoiRegion *pRoiRegion);

private:
	ClsVision* m_pVision;
	DMDotProcess m_dmDotProcess;
	QRDotProcess m_qrDotProcess;   /* QR Barcode*/
};

