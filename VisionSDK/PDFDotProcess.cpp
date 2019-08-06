#include "stdafx.h"
#include "PDFDotProcess.h"

PDFDotProcess::PDFDotProcess(){
	/* code */
	m_idModel = -1;
	m_vision = ClsVision::GetClsVision();
}

PDFDotProcess ::~PDFDotProcess(){
	/* code */
	if (m_idModel < 0)     m_vision->FreeBarcode2DModel(m_idModel);
}
