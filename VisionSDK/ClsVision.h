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

	//1. 获取ClsVision的句柄
	static ClsVision* GetClsVision(void);

	//2. 释放模板
	void FreeBarcode2DModel(HalconCpp::HTuple& hvModelID);

	//3. 创建模板
	void CreateCodeDMModel(int codeMode, HalconCpp::HTuple& hvModelID);

	//4. 查找结果 
	void ExecuteDataCode2D(HalconCpp::HObject& hObject, HalconCpp::HObject& hTarget, HalconCpp::HTuple& idModel, std::string& codeString, RoiRegion& region);

	//5. 创建目录
	bool CreateMulDir(std::string path);

	//6. 图像拷贝
	void ImageCopy(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget);

	//7. 中值滤波
	void ImageMedian(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, double szRadius);

	//8. 滤波处理
	void ImageFilterProcess(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, FilterPara para);

	//9. 图像缩放
	void ImageZoom(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, double rate);

	//10. 数量
	int CountObject(HalconCpp::HObject& hObject);

	//12. Copy部分字符串
	std::string GetSubString(std::string strOrigine, int idStart, int sz);

	//13. 区域缩放
	void RegionZooom(HalconCpp::HObject& hRegion, HalconCpp::HObject* hTarget, double rate);

	//14. 文件目录是否存在
	BOOL IsPathExist(const CString & csPath);

	//15. 图像大小
	void GetImageSize(HalconCpp::HObject& hObject, int& width, int& height);

	//16. 区域轮廓
	void GenContourRegion(HalconCpp::HObject& hRegion, HalconCpp::HObject* hTarget);

	//17. 创建模板
	void CreateCodeQRModel(int codeMode, HalconCpp::HTuple& hvModelID);

	//18. 初始化条码参数
	AoiParams AoiParametersInit(int iType);

	//19. 识别条码
	void ExeBarcodeData2D(HalconCpp::HObject& hObject, HalconCpp::HObject& hTarget, int codeType, int codeMode, std::string& codeString, RoiRegion& region);

	//20. 创建模板
	void CreateNccModel(HalconCpp::HObject& hObject, double angleLimit, int& idResult);

	//21. 查找模板
	void FindNccModel(HalconCpp::HObject& hObject, int idModel, double minScore, double& xResult, double& yResult, double& angleResult, double& scoreResult);

	//22. 释放模板
	void ClearNccModel(int idModel);


private:
	static ClsVision* m_vision;

private:
	

	//1. 删除文件
	void DeleteDirectoryAndFiles(std::string filePath);


};


#endif // ! CLS_VISION_H

