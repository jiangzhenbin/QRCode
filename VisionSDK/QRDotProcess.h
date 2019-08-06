/***********************************************************************
		Copyright 2018-2019 深圳市八零联合装备有限公司
		All rights reserved.

		Author: zhenbin,jiang
		Date: 2019-06-05
		Version: V1.0.0.0

		Description:
				本模块是QR条码识别
************************************************************************/
#ifndef QR_DOT_PROCESS_H
#define QR_DOT_PROCESS_H

#include "BarcodeDotProcess.h"

class QRDotProcess : public BarcodeDotProcess
{
public:
	QRDotProcess();
	~QRDotProcess();

	//1. 加载参数 
	virtual void LoadAoiParameter(AoiParams para);

	//2. 执行 
	virtual void Execute(HalconCpp::HObject& hObject, int modeExecute);

	//3. 获取执行效果
	virtual void GetColorProcess(ImageData& imgResult, int tyMode);

private:
	int m_qrCodeType;
	int m_idMatchModel;
	int m_scoreThreshold;
	int m_rate;

private:

	//3. 执行检测
	void ExecuteQR(HalconCpp::HObject& hObject, int modeExecute);

	//1. 执行定位
	bool ExeMatch(HalconCpp::HObject& hObject);

};



#endif // !QR_DOT_PROCESS_H

