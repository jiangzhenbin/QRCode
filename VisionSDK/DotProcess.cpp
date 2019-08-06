#include "stdafx.h"
#include "DotProcess.h"

DotProcess::DotProcess(){
	/* code */
}

DotProcess::~DotProcess() {
	/* code */
	if (NULL != m_dotProcess) {
		delete m_dotProcess;
		m_dotProcess = NULL;
	}
}

void DotProcess::LoadAoiParameter(AoiParams para) {
	/* code */
	if (NULL != m_dotProcess) {
		delete m_dotProcess;
		m_dotProcess = NULL;
	}

	m_para = para;

	switch (para.iType) {
	case DM_BARCODE_TYPE:
		m_dotProcess = new DMDotProcess();
		m_dotProcess->LoadAoiParameter(para);
		break;

	case QR_BARCODE_TYPE:
		m_dotProcess = new QRDotProcess();
		m_dotProcess->LoadAoiParameter(para);
		break;

	case PDF_BARCODE_TYPE:
		m_dotProcess = new PDFDotProcess();
		m_dotProcess->LoadAoiParameter(para);
		break;

	default:
		break;
	}
}

void DotProcess::Execute(HalconCpp::HObject& hObject, int modeExecute) {
	/* code */
	if (NULL == m_dotProcess)  LoadAoiParameter(m_para);

	m_dotProcess->Execute(hObject, modeExecute);
}

void DotProcess::GetColorProcess(ImageData& imgResult, int tyMode) {
	/* code */
	m_dotProcess->GetColorProcess(imgResult, tyMode);
}