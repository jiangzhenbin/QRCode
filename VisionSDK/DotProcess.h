#ifndef DOT_PROCESS
#define DOT_PROCESS

#include "BarcodeDotProcess.h"
#include "DMDotProcess.h"
#include "QRDotProcess.h"
#include "PDFDotProcess.h"

class DotProcess{
public:
	DotProcess();
	~DotProcess();

	//1. ���ز��� 
	void LoadAoiParameter(AoiParams para);

	//2. ִ�м��
	void Execute(HalconCpp::HObject& hObject, int modeExecute);

	//3. ���
	void GetColorProcess(ImageData& imgResult, int tyMode);

private:
	BarcodeDotProcess* m_dotProcess;
	AoiParams m_para;

};

#endif // !DOT_PROCESS

