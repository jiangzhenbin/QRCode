#include "stdafx.h"
#include "DMDotProcess.h"

//效果显示图
//********************************************************************
#define DM_DIRECTORY							 "./temporary/DM"                                  /* 调试目录 */ 
#define ORIGINE_DM_IMAGE_FILE_NAME               "./temporary/DM/origine_dm_image.hobj"            /* 原图 */
#define PROC_DM_IMAGE_FILE_NAME				     "./temporary/DM/proc_dm_image.hobj"               /* 预处理图  */
#define RESULT_DM_REGION_FILE_NAME               "./temporary/DM/result_dm_region.hobj"             /* 结果区域 */
//********************************************************************


DMDotProcess::DMDotProcess() {
	/* code */
	m_idModel = -1;
	m_idMatchModel = -1;
	m_codeString = "";
	m_vision = ClsVision::GetClsVision();

	m_codeResult = NO_STATUS;
}

DMDotProcess ::~DMDotProcess() {
	/* code */
}

void DMDotProcess::LoadAoiParameter(AoiParams para) {
	/* code */
	m_para = para;

	m_dmCodeType = m_para.int0;
	m_idMatchModel = m_para.int1;
	m_scoreThreshold = m_para.int2;
	m_rate = m_para.int3;
}

void DMDotProcess::Execute(HalconCpp::HObject& hObject, int modeExecute){
	/* code */
	m_costTime = 0.0f;
	m_codeString = "";
	if (TEST_EXECUTE_MODE != modeExecute)  m_vision->CreateMulDir(DM_DIRECTORY);

	double start_t = clock();
	try {
		if (m_idMatchModel > -1)
		{
			//1. 首先进行搜索定位
			bool valid = ExeMatch(hObject);
			
			//2. 执行定位
			if (valid)  ExecuteDM(hObject, modeExecute);
		}
		else
		{
			ExecuteDM(hObject, modeExecute);
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

bool DMDotProcess::ExeMatch(HalconCpp::HObject& hObject)
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

void DMDotProcess::ExecuteDM(HalconCpp::HObject& hObject, int modeExecute){
	/* code */
	m_codeResult = NO_STATUS;

	HalconCpp::HObject hRegion;
	m_vision->ExeBarcodeData2D(hObject, hRegion, DM_BARCODE_TYPE, m_dmCodeType, m_codeString, m_region);
    
	
	if (TEST_EXECUTE_MODE != modeExecute) {
		HalconCpp::WriteImage(hObject, "hobj", 0, ORIGINE_DM_IMAGE_FILE_NAME);
		HalconCpp::WriteImage(hObject, "hobj", 0, PROC_DM_IMAGE_FILE_NAME);
		HalconCpp::WriteRegion(hRegion, RESULT_DM_REGION_FILE_NAME);
	}
}

void DMDotProcess::GetColorProcess(ImageData& imgResult, int tyMode) {
	/* code */
	switch (tyMode)
	{
	case ORIGINE_CODE2D_VIEW_TYPE:
		if (m_vision->IsPathExist(ORIGINE_DM_IMAGE_FILE_NAME)) {
			imgResult.tyMode = DEFAULT_DATE_TYPE;
			HalconCpp::ReadImage(&imgResult.hObject, ORIGINE_DM_IMAGE_FILE_NAME);
			m_vision->GetImageSize(imgResult.hObject, imgResult.width, imgResult.height);
		}
		break;

	case PROC_CODE2D_VIEW_TYPE:
		if (m_vision->IsPathExist(PROC_DM_IMAGE_FILE_NAME)) {
			imgResult.tyMode = DEFAULT_DATE_TYPE;
			HalconCpp::ReadImage(&imgResult.hObject, PROC_DM_IMAGE_FILE_NAME);
		} else {
			imgResult.tyMode = DEFAULT_DATE_TYPE;
			HalconCpp::ReadImage(&imgResult.hObject, ORIGINE_DM_IMAGE_FILE_NAME);
		}
		m_vision->GetImageSize(imgResult.hObject, imgResult.width, imgResult.height);
		break;

	case REGION_CODE2D_VIEW_TYPE:
		if (m_vision->IsPathExist(RESULT_DM_REGION_FILE_NAME)) {
			imgResult.tyMode = REGION_DATA_TYPE;
			HalconCpp::ReadRegion(&imgResult.hRegion, RESULT_DM_REGION_FILE_NAME);
			if (m_vision->CountObject(imgResult.hRegion) > 0)   m_vision->GenContourRegion(imgResult.hRegion, &imgResult.hRegion);
		} else {
			imgResult.tyMode = DEFAULT_DATE_TYPE;
			HalconCpp::ReadImage(&imgResult.hObject, PROC_DM_IMAGE_FILE_NAME);
			
		}

		if (m_vision->IsPathExist(PROC_DM_IMAGE_FILE_NAME)) {
			HalconCpp::ReadImage(&imgResult.hObject, PROC_DM_IMAGE_FILE_NAME);
		} else {
			HalconCpp::ReadImage(&imgResult.hObject, ORIGINE_DM_IMAGE_FILE_NAME);
		}
		m_vision->GetImageSize(imgResult.hObject, imgResult.width, imgResult.height);

		break;


	default:
		break;
	}
}