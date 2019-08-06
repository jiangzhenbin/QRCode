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

	//1. 加载参数 
	void LoadAoiParameter(AoiParams para);

	//2. 执行检测
	void Execute(HalconCpp::HObject& hObject, int modeExecute);

	//3. 检测
	void GetColorProcess(ImageData& imgResult, int tyMode);

private:
	BarcodeDotProcess* m_dotProcess;
	AoiParams m_para;

};

#endif // !DOT_PROCESS

