/***********************************************************************
		Copyright 2018-2019 �����а�������װ�����޹�˾
		All rights reserved.

		Author: zhenbin,jiang
		Date: 2019-06-05
		Version: V1.0.0.0

		Description:
			��ģ��������ʶ��Ļ���
************************************************************************/
#ifndef  BARCODE_DOT_PROCESS_H
#define  BARCODE_DOT_PROCESS_H

#include "typesdef.h"
#include "ClsVision.h"

class BarcodeDotProcess{
public:
	BarcodeDotProcess();
	~BarcodeDotProcess();

	//1. ���ز��� 
	virtual void LoadAoiParameter(AoiParams para);

	//2. ִ�в���
	virtual void Execute(HalconCpp::HObject& hObject, int modeExecute);

	//3. ��ȡִ��Ч��
	virtual void GetColorProcess(ImageData& imgResult, int tyMode);

public:
	//3. ��ȡ�ķ�ʱ��
	double GetCostTime(void);

	//4. ��ȡ���
	std::string GetResult(void);

	//5. ��ȡ����״̬
	int GetCodeResultStatus(void);

	//6. ��ȡ����Χ
	RoiRegion GetRegion(void);
public:
	AoiParams m_para;    
	std::string m_codeString;         /* ������ */
	int m_codeResult;
	HalconCpp::HTuple m_idModel;                    /* �����id�� */
	double m_costTime;
	ClsVision* m_vision;
	RoiRegion m_region;

private:

};



#endif // ! BARCODE_DOT_PROCESS_H

