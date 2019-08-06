#include "stdafx.h"
#include "BarcodeDotProcess.h"

BarcodeDotProcess::BarcodeDotProcess(){
	/* code */
	m_idModel = -1;
	m_costTime = 0.0f;
	m_codeString = "";
	m_vision = ClsVision::GetClsVision();
}

BarcodeDotProcess::~BarcodeDotProcess(){
	/* code */
	m_vision->FreeBarcode2DModel(m_idModel);
}

void BarcodeDotProcess::LoadAoiParameter(AoiParams para){
	/* code */

}

void BarcodeDotProcess::Execute(HalconCpp::HObject& hObject, int modeExecute){
	/* code */

}

void BarcodeDotProcess::GetColorProcess(ImageData& imgResult, int tyMode) {
	/* code */

}

double BarcodeDotProcess::GetCostTime(void) {
	/* code */
	return m_costTime;
}

std::string BarcodeDotProcess::GetResult(void) {
	/* code */
	return m_codeString;
}

int BarcodeDotProcess::GetCodeResultStatus(void){
	/* code */
	return m_codeResult;
}

RoiRegion BarcodeDotProcess::GetRegion(void) {
	/* code */

	return m_region;
}