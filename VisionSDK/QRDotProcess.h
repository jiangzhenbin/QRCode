/***********************************************************************
		Copyright 2018-2019 �����а�������װ�����޹�˾
		All rights reserved.

		Author: zhenbin,jiang
		Date: 2019-06-05
		Version: V1.0.0.0

		Description:
				��ģ����QR����ʶ��
************************************************************************/
#ifndef QR_DOT_PROCESS_H
#define QR_DOT_PROCESS_H

#include "BarcodeDotProcess.h"

class QRDotProcess : public BarcodeDotProcess
{
public:
	QRDotProcess();
	~QRDotProcess();

	//1. ���ز��� 
	virtual void LoadAoiParameter(AoiParams para);

	//2. ִ�� 
	virtual void Execute(HalconCpp::HObject& hObject, int modeExecute);

	//3. ��ȡִ��Ч��
	virtual void GetColorProcess(ImageData& imgResult, int tyMode);

private:
	int m_qrCodeType;
	int m_idMatchModel;
	int m_scoreThreshold;
	int m_rate;

private:

	//3. ִ�м��
	void ExecuteQR(HalconCpp::HObject& hObject, int modeExecute);

	//1. ִ�ж�λ
	bool ExeMatch(HalconCpp::HObject& hObject);

};



#endif // !QR_DOT_PROCESS_H

