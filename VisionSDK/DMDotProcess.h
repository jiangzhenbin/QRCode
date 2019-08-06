/***********************************************************************
		Copyright 2018-2019 �����а�������װ�����޹�˾
		All rights reserved.

		Author: zhenbin,jiang
		Date: 2019-06-05
		Version: V1.0.0.0

		Description:
				��ģ����DM����ʶ��
************************************************************************/

#ifndef DM_DOT_PROCESS
#define DM_DOT_PROCESS

#include "BarcodeDotProcess.h"

class DMDotProcess : public BarcodeDotProcess
{
public:
	DMDotProcess();
	~DMDotProcess();

	//1. ���ز��� 
	virtual void LoadAoiParameter(AoiParams para);

	//2. ִ�� 
	virtual void Execute(HalconCpp::HObject& hObject, int modeExecute);

	//3. ��ȡִ��Ч��
	virtual void GetColorProcess(ImageData& imgResult, int tyMode);

private:
	int m_dmCodeType;
	int m_idMatchModel;
	int m_scoreThreshold;
	int m_rate;

private:
	//3. ִ�м��
	void ExecuteDM(HalconCpp::HObject& hObject, int modeExecute);

	//4. ִ�ж�λ
	bool ExeMatch(HalconCpp::HObject& hObject);
};



#endif // !DM_DOT_PROCESS

