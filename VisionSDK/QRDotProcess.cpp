#include "stdafx.h"
#include "QRDotProcess.h"

//效果显示图
//********************************************************************
#define QR_DIRECTORY							 "./temporary/QR"                                  /* 调试目录 */ 
#define ORIGINE_QR_IMAGE_FILE_NAME               "./temporary/QR/origine_qr_image.hobj"            /* 原图 */
#define PROC_QR_IMAGE_FILE_NAME				     "./temporary/QR/proc_qr_image.hobj"               /* 预处理图  */
#define RESULT_QR_REGION_FILE_NAME               "./temporary/QR/result_qr_region.hobj"            /* 结果区域 */
//********************************************************************


QRDotProcess::QRDotProcess() {
	/* code */
	m_idModel = -1;
	m_codeString = "";
	m_vision = ClsVision::GetClsVision();

	m_codeResult = NO_STATUS;
}

QRDotProcess ::~QRDotProcess() {
	/* code */
}

void QRDotProcess::LoadAoiParameter(AoiParams para) {
	/* code */
	m_para = para;

	m_qrCodeType = m_para.int0;

	m_idMatchModel = m_para.int1;
	m_scoreThreshold = m_para.int2;
	m_rate = m_para.int3;
}

void QRDotProcess::Execute(HalconCpp::HObject& hObject, int modeExecute) {
	/* code */
	m_costTime = 0.0f;
	m_codeString = "";

	if (TEST_EXECUTE_MODE != modeExecute)  m_vision->CreateMulDir(QR_DIRECTORY);

	double start_t = clock();
	try {
		if (m_idMatchModel > -1)
		{
			//1. 首先进行搜索定位
			bool valid = ExeMatch(hObject);

			//2. 执行定位
			if (valid)  ExecuteQR(hObject, modeExecute);
		}
		else
		{
			ExecuteQR(hObject, modeExecute);
		}
	}
	catch (HalconCpp::HException&) {
		/* code */
	}
	catch (const std::exception&) {
		/* code */
	}

	double end_t = clock();
	m_costTime = end_t - start_t;
}

bool QRDotProcess::ExeMatch(HalconCpp::HObject& hObject)
{
	/* code */
	bool valid = false;
	HalconCpp::HObject hZoomObject;
	m_vision->ImageZoom(hObject, &hZoomObject, 0.01f * m_rate);

	double xPos = 0.0f;
	double yPos = 0.0f;
	double posAngle = 0.0f;
	double posScore = 0.0f;
	m_vision->FindNccModel(hZoomObject, m_idMatchModel, 0.01 * m_scoreThreshold - 0.1f, xPos, yPos, posAngle, posScore);
	if (posScore > 0.01f * m_scoreThreshold)  valid = true;

	return valid;
}

void QRDotProcess::ExecuteQR(HalconCpp::HObject& hObject, int modeExecute) {
	/* code */
	m_codeResult = NO_STATUS;
	HalconCpp::HObject hRegion;
	m_vision->ExeBarcodeData2D(hObject, hRegion, QR_BARCODE_TYPE, m_qrCodeType, m_codeString, m_region);

	if (TEST_EXECUTE_MODE != modeExecute) {
		HalconCpp::WriteImage(hObject, "hobj", 0, ORIGINE_QR_IMAGE_FILE_NAME);
		HalconCpp::WriteImage(hObject, "hobj", 0, PROC_QR_IMAGE_FILE_NAME);
		HalconCpp::WriteRegion(hRegion, RESULT_QR_REGION_FILE_NAME);
	}
}

void QRDotProcess::GetColorProcess(ImageData& imgResult, int tyMode) {
	/* code */
	switch (tyMode)
	{
	case ORIGINE_CODE2D_VIEW_TYPE:
		if (m_vision->IsPathExist(ORIGINE_QR_IMAGE_FILE_NAME)) {
			imgResult.tyMode = DEFAULT_DATE_TYPE;
			HalconCpp::ReadImage(&imgResult.hObject, ORIGINE_QR_IMAGE_FILE_NAME);
			m_vision->GetImageSize(imgResult.hObject, imgResult.width, imgResult.height);
		}
		break;

	case PROC_CODE2D_VIEW_TYPE:
		if (m_vision->IsPathExist(PROC_QR_IMAGE_FILE_NAME)) {
			imgResult.tyMode = DEFAULT_DATE_TYPE;
			HalconCpp::ReadImage(&imgResult.hObject, PROC_QR_IMAGE_FILE_NAME);
		}
		else {
			imgResult.tyMode = DEFAULT_DATE_TYPE;
			HalconCpp::ReadImage(&imgResult.hObject, ORIGINE_QR_IMAGE_FILE_NAME);
		}
		m_vision->GetImageSize(imgResult.hObject, imgResult.width, imgResult.height);
		break;

	case REGION_CODE2D_VIEW_TYPE:
		if (m_vision->IsPathExist(RESULT_QR_REGION_FILE_NAME)) {
			imgResult.tyMode = REGION_DATA_TYPE;
			HalconCpp::ReadRegion(&imgResult.hRegion, RESULT_QR_REGION_FILE_NAME);
			if (m_vision->CountObject(imgResult.hRegion) > 0)   m_vision->GenContourRegion(imgResult.hRegion, &imgResult.hRegion);
		} else {
			imgResult.tyMode = DEFAULT_DATE_TYPE;
			HalconCpp::ReadImage(&imgResult.hObject, PROC_QR_IMAGE_FILE_NAME);

		}

		if (m_vision->IsPathExist(PROC_QR_IMAGE_FILE_NAME)) {
			HalconCpp::ReadImage(&imgResult.hObject, PROC_QR_IMAGE_FILE_NAME);
		}
		else {
			HalconCpp::ReadImage(&imgResult.hObject, ORIGINE_QR_IMAGE_FILE_NAME);
		}
		m_vision->GetImageSize(imgResult.hObject, imgResult.width, imgResult.height);

		break;


	default:
		break;
	}
}