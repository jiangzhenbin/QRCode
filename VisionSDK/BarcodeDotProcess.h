/***********************************************************************
		Copyright 2018-2019 深圳市八零联合装备有限公司
		All rights reserved.

		Author: zhenbin,jiang
		Date: 2019-06-05
		Version: V1.0.0.0

		Description:
			本模块是条码识别的基类
************************************************************************/
#ifndef  BARCODE_DOT_PROCESS_H
#define  BARCODE_DOT_PROCESS_H

#include "typesdef.h"
#include "ClsVision.h"

class BarcodeDotProcess{
public:
	BarcodeDotProcess();
	~BarcodeDotProcess();

	//1. 加载参数 
	virtual void LoadAoiParameter(AoiParams para);

	//2. 执行操作
	virtual void Execute(HalconCpp::HObject& hObject, int modeExecute);

	//3. 获取执行效果
	virtual void GetColorProcess(ImageData& imgResult, int tyMode);

public:
	//3. 获取耗费时间
	double GetCostTime(void);

	//4. 获取结果
	std::string GetResult(void);

	//5. 获取条码状态
	int GetCodeResultStatus(void);

	//6. 获取区域范围
	RoiRegion GetRegion(void);
public:
	AoiParams m_para;    
	std::string m_codeString;         /* 条码结果 */
	int m_codeResult;
	HalconCpp::HTuple m_idModel;                    /* 条码的id号 */
	double m_costTime;
	ClsVision* m_vision;
	RoiRegion m_region;

private:

};



#endif // ! BARCODE_DOT_PROCESS_H

