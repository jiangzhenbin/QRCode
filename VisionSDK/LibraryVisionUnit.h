#ifndef LIBRARY_VISION_UNIT_H
#define LIBRARY_VISION_UNIT_H

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <HalconCpp.h>
#include "typesdef.h"

//1. �ͷ�ģ��
void FreeBarcode2DModelApi(HalconCpp::HTuple& hvModelID);

//2. ����DM���ģ��
void CreateCodeDMModelApi(int codeMode, HalconCpp::HTuple& hvModelID);

//3. ʶ������
void ExecuteDataCode2DApi(HalconCpp::HObject& hObject, HalconCpp::HObject& hTarget, HalconCpp::HTuple& idModel, std::string& codeString, RoiRegion& region);

//6. ͼ�񿽱�
void ImageCopyApi(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget);

//7. ��ֵ�˲�
void ImageMedianApi(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, double szRadius);

//8. �˲�����
void ImageFilterProcessApi(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, FilterPara para);

//9. ͼ������
void ImageZoomApi(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, double rate);

//10. ����
void CountObjectApi(HalconCpp::HObject& hObject, int* countResult);

//13. ��������
void RegionZooomApi(HalconCpp::HObject& hRegion, HalconCpp::HObject* hTarget, double rate);

//15. ͼ���С
void GetImageSizeApi(HalconCpp::HObject& hObject, int* width, int* height);

//16. ��������
void GenContourRegionApi(HalconCpp::HObject& hRegion, HalconCpp::HObject* hTarget);

//18. ����ģ��
void CreateCodeQRModelApi(int codeMode, HalconCpp::HTuple& hvModelID);

//19. ���Ҷ�ά����
void ExeBarcodeData2DApi(HalconCpp::HObject& hObject, HalconCpp::HObject& hTarget, int codeType, int codeMode, std::string& codeString, RoiRegion& region);

//20. ����ģ��
void CreateNccModelApi(HalconCpp::HObject& hObject, double angleLimit, int& idResult);

//21. ����ģ��
void FindNccModelApi(HalconCpp::HObject& hObject, int idModel, double minScore, double& xResult, double& yResult, double& angleResult, double& scoreResult);

//22. �ͷ�ģ��
void ClearNccModelApi(int idModel);

#endif // !LIBRARY_VISION_UNIT_H

