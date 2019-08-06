#include "stdafx.h"
#include "VisionProcess.h"


VisionProcess::VisionProcess()
{
	m_pVision = NULL;
}


VisionProcess::~VisionProcess()
{
}

void VisionProcess::Init()
{
	m_pVision = ClsVision::GetClsVision();
}

void VisionProcess::Process(HalconCpp::HObject& hObject, int codeType, std::string& strOutCode, double &fCostTime, RoiRegion *pRoiRegion)
{
#if 1        /* jiang */
	if (1 == codeType)
	{
		BarcodeDotProcess* dotProcess = &m_dmDotProcess;
		AoiParams para = m_pVision->AoiParametersInit(DM_BARCODE_TYPE);
		para.int0 = LOW_DM_TYPE;
		dotProcess->LoadAoiParameter(para);

		HalconCpp::HObject hProcObject;
		m_pVision->ImageZoom(hObject, &hProcObject, 0.6f);

		dotProcess->Execute(hProcObject, TEST_EXECUTE_MODE);
		strOutCode = dotProcess->GetResult();
		fCostTime = dotProcess->GetCostTime();

		if (pRoiRegion != NULL) {
			RoiRegion roiRegion = dotProcess->GetRegion();
			roiRegion.pt0.x = roiRegion.pt0.x / 0.6f;
			roiRegion.pt0.y = roiRegion.pt0.y / 0.6f;
			roiRegion.pt1.x = roiRegion.pt1.x / 0.6f;
			roiRegion.pt1.y = roiRegion.pt1.y / 0.6f;
			memcpy(pRoiRegion, &roiRegion, sizeof(RoiRegion));
}

		}
	else if (2 == codeType) {
		BarcodeDotProcess* dotProcess = &m_dmDotProcess;
		AoiParams para = m_pVision->AoiParametersInit(DM_BARCODE_TYPE);
		para.int0 = HIGH_DM_TYPE;
		dotProcess->LoadAoiParameter(para);

		HalconCpp::HObject hProcObject;
		m_pVision->ImageZoom(hObject, &hProcObject, 0.6f);

		dotProcess->Execute(hProcObject, TEST_EXECUTE_MODE);
		strOutCode = dotProcess->GetResult();
		fCostTime = dotProcess->GetCostTime();

		if (pRoiRegion != NULL) {
			RoiRegion roiRegion = dotProcess->GetRegion();
			roiRegion.pt0.x = roiRegion.pt0.x / 0.6f;
			roiRegion.pt0.y = roiRegion.pt0.y / 0.6f;
			roiRegion.pt1.x = roiRegion.pt1.x / 0.6f;
			roiRegion.pt1.y = roiRegion.pt1.y / 0.6f;
			memcpy(pRoiRegion, &roiRegion, sizeof(RoiRegion));
		}
	}
	else if (3 == codeType) {
		BarcodeDotProcess* dotProcess = &m_qrDotProcess;
		AoiParams para = m_pVision->AoiParametersInit(QR_BARCODE_TYPE);
		para.int0 = DEFAULT_QR_TYPE;
		dotProcess->LoadAoiParameter(para);

		dotProcess->Execute(hObject, TEST_EXECUTE_MODE);
		strOutCode = dotProcess->GetResult();
		fCostTime = dotProcess->GetCostTime();

		if (pRoiRegion != NULL) {
			RoiRegion roiRegion = dotProcess->GetRegion();
			memcpy(pRoiRegion, &roiRegion, sizeof(RoiRegion));
		}
	}
	else if (4 == codeType) {
		BarcodeDotProcess* dotProcess = &m_qrDotProcess;
		AoiParams para = m_pVision->AoiParametersInit(QR_BARCODE_TYPE);
		para.int0 = OPT_QR_TYPE;
		dotProcess->LoadAoiParameter(para);

		HalconCpp::HObject hProcObject;
		m_pVision->ImageZoom(hObject, &hProcObject, 0.6f);

		dotProcess->Execute(hProcObject, TEST_EXECUTE_MODE);
		strOutCode = dotProcess->GetResult();
		fCostTime = dotProcess->GetCostTime();

		if (pRoiRegion != NULL) {
			RoiRegion roiRegion = dotProcess->GetRegion();
			roiRegion.pt0.x = roiRegion.pt0.x / 0.6f;
			roiRegion.pt0.y = roiRegion.pt0.y / 0.6f;
			roiRegion.pt1.x = roiRegion.pt1.x / 0.6f;
			roiRegion.pt1.y = roiRegion.pt1.y / 0.6f;
			memcpy(pRoiRegion, &roiRegion, sizeof(RoiRegion));
		}
	}
	else {
		BarcodeDotProcess* dotProcess = &m_dmDotProcess;
		AoiParams para = m_pVision->AoiParametersInit(DM_BARCODE_TYPE);
		para.int0 = DEFAULT_DM_TYPE;
		dotProcess->LoadAoiParameter(para);

		dotProcess->Execute(hObject, TEST_EXECUTE_MODE);
		strOutCode = dotProcess->GetResult();
		fCostTime = dotProcess->GetCostTime();

		if (pRoiRegion != NULL) {
			RoiRegion roiRegion = dotProcess->GetRegion();
			memcpy(pRoiRegion, &roiRegion, sizeof(RoiRegion));
		}
	}
#else
	BarcodeDotProcess* dotProcess = &m_dmDotProcess;
	AoiParams para = m_pVision->AoiParametersInit(DM_BARCODE_TYPE);
	para.int0 = DEFAULT_DM_TYPE;
	dotProcess->LoadAoiParameter(para);

	dotProcess->Execute(hObject, TEST_EXECUTE_MODE);
	strOutCode = dotProcess->GetResult();
	fCostTime = dotProcess->GetCostTime();

	if (pRoiRegion != NULL) {
		RoiRegion roiRegion = dotProcess->GetRegion();
		memcpy(pRoiRegion, &roiRegion, sizeof(RoiRegion));
	}
#endif
}

int VisionProcess::Process8BitImage(const void *pImgData, const int width, const int height, int codeType, std::string& strOutCode, double &fCostTime, RoiRegion *pRoiRegion)
{
	// 将图像转换为HObject，再调用Process
	try {
		HalconCpp::HObject m_hImage;
		HalconCpp::GenImage1(&m_hImage, "byte", width, height, (Hlong)pImgData);
		HalconCpp::HTuple htWidth, htHeight;
		HalconCpp::GetImageSize(m_hImage, &htWidth, &htHeight);
		if (width != htWidth[0].I() || height != htHeight[0].I()) {
			return -1;
		}
		else {
			Process(m_hImage, codeType, strOutCode, fCostTime, pRoiRegion);

			return 0;
		}
	}
	catch (HalconCpp::HException &except) {
		TRACE("LoadFromData 11 HalconCpp::HException >> %s", (char *)except.ErrorMessage().Text());
		return -2;
	}
}
