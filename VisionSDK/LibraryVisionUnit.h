#ifndef LIBRARY_VISION_UNIT_H
#define LIBRARY_VISION_UNIT_H

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <HalconCpp.h>
#include "typesdef.h"

//1. 释放模板
void FreeBarcode2DModelApi(HalconCpp::HTuple& hvModelID);

//2. 创建DM码的模板
void CreateCodeDMModelApi(int codeMode, HalconCpp::HTuple& hvModelID);

//3. 识别条码
void ExecuteDataCode2DApi(HalconCpp::HObject& hObject, HalconCpp::HObject& hTarget, HalconCpp::HTuple& idModel, std::string& codeString, RoiRegion& region);

//6. 图像拷贝
void ImageCopyApi(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget);

//7. 中值滤波
void ImageMedianApi(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, double szRadius);

//8. 滤波处理
void ImageFilterProcessApi(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, FilterPara para);

//9. 图像缩放
void ImageZoomApi(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, double rate);

//10. 数量
void CountObjectApi(HalconCpp::HObject& hObject, int* countResult);

//13. 区域缩放
void RegionZooomApi(HalconCpp::HObject& hRegion, HalconCpp::HObject* hTarget, double rate);

//15. 图像大小
void GetImageSizeApi(HalconCpp::HObject& hObject, int* width, int* height);

//16. 区域轮廓
void GenContourRegionApi(HalconCpp::HObject& hRegion, HalconCpp::HObject* hTarget);

//18. 创建模板
void CreateCodeQRModelApi(int codeMode, HalconCpp::HTuple& hvModelID);

//19. 查找二维条码
void ExeBarcodeData2DApi(HalconCpp::HObject& hObject, HalconCpp::HObject& hTarget, int codeType, int codeMode, std::string& codeString, RoiRegion& region);

//20. 创建模板
void CreateNccModelApi(HalconCpp::HObject& hObject, double angleLimit, int& idResult);

//21. 查找模板
void FindNccModelApi(HalconCpp::HObject& hObject, int idModel, double minScore, double& xResult, double& yResult, double& angleResult, double& scoreResult);

//22. 释放模板
void ClearNccModelApi(int idModel);

#endif // !LIBRARY_VISION_UNIT_H

