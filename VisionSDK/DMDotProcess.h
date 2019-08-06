/***********************************************************************
		Copyright 2018-2019 深圳市八零联合装备有限公司
		All rights reserved.

		Author: zhenbin,jiang
		Date: 2019-06-05
		Version: V1.0.0.0

		Description:
				本模块是DM条码识别
************************************************************************/

#ifndef DM_DOT_PROCESS
#define DM_DOT_PROCESS

#include "BarcodeDotProcess.h"

class DMDotProcess : public BarcodeDotProcess
{
public:
	DMDotProcess();
	~DMDotProcess();

	//1. 加载参数 
	virtual void LoadAoiParameter(AoiParams para);

	//2. 执行 
	virtual void Execute(HalconCpp::HObject& hObject, int modeExecute);

	//3. 获取执行效果
	virtual void GetColorProcess(ImageData& imgResult, int tyMode);

private:
	int m_dmCodeType;
	int m_idMatchModel;
	int m_scoreThreshold;
	int m_rate;

private:
	//3. 执行检测
	void ExecuteDM(HalconCpp::HObject& hObject, int modeExecute);

	//4. 执行定位
	bool ExeMatch(HalconCpp::HObject& hObject);
};



#endif // !DM_DOT_PROCESS

