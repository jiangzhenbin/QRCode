#ifndef  CLS_VISION_H
#define CLS_VISION_H

#include <Windows.h>
#include <WinBase.h>
#include <stdlib.h>
#include <HalconCpp.h>
#include <vector>

#include <string>
#include <iostream>
#include <io.h>
#include <direct.h>

#include "typesdef.h"
#include "LibraryVisionUnit.h"

class ClsVision{
public:
	ClsVision();
	~ClsVision();

	//1. ��ȡClsVision�ľ��
	static ClsVision* GetClsVision(void);

	//2. �ͷ�ģ��
	void FreeBarcode2DModel(HalconCpp::HTuple& hvModelID);

	//3. ����ģ��
	void CreateCodeDMModel(int codeMode, HalconCpp::HTuple& hvModelID);

	//4. ���ҽ�� 
	void ExecuteDataCode2D(HalconCpp::HObject& hObject, HalconCpp::HObject& hTarget, HalconCpp::HTuple& idModel, std::string& codeString, RoiRegion& region);

	//5. ����Ŀ¼
	bool CreateMulDir(std::string path);

	//6. ͼ�񿽱�
	void ImageCopy(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget);

	//7. ��ֵ�˲�
	void ImageMedian(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, double szRadius);

	//8. �˲�����
	void ImageFilterProcess(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, FilterPara para);

	//9. ͼ������
	void ImageZoom(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, double rate);

	//10. ����
	int CountObject(HalconCpp::HObject& hObject);

	//12. Copy�����ַ���
	std::string GetSubString(std::string strOrigine, int idStart, int sz);

	//13. ��������
	void RegionZooom(HalconCpp::HObject& hRegion, HalconCpp::HObject* hTarget, double rate);

	//14. �ļ�Ŀ¼�Ƿ����
	BOOL IsPathExist(const CString & csPath);

	//15. ͼ���С
	void GetImageSize(HalconCpp::HObject& hObject, int& width, int& height);

	//16. ��������
	void GenContourRegion(HalconCpp::HObject& hRegion, HalconCpp::HObject* hTarget);

	//17. ����ģ��
	void CreateCodeQRModel(int codeMode, HalconCpp::HTuple& hvModelID);

	//18. ��ʼ���������
	AoiParams AoiParametersInit(int iType);

	//19. ʶ������
	void ExeBarcodeData2D(HalconCpp::HObject& hObject, HalconCpp::HObject& hTarget, int codeType, int codeMode, std::string& codeString, RoiRegion& region);

	//20. ����ģ��
	void CreateNccModel(HalconCpp::HObject& hObject, double angleLimit, int& idResult);

	//21. ����ģ��
	void FindNccModel(HalconCpp::HObject& hObject, int idModel, double minScore, double& xResult, double& yResult, double& angleResult, double& scoreResult);

	//22. �ͷ�ģ��
	void ClearNccModel(int idModel);


private:
	static ClsVision* m_vision;

private:
	

	//1. ɾ���ļ�
	void DeleteDirectoryAndFiles(std::string filePath);


};


#endif // ! CLS_VISION_H

