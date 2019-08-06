#include "stdafx.h"
#include "ClsVision.h"

ClsVision::ClsVision(){
	/* code */
}

ClsVision::~ClsVision(){
	/* code */

}

ClsVision* ClsVision::m_vision = NULL;
ClsVision* ClsVision::GetClsVision(void) {
	/* code */
	if (NULL != m_vision)  return m_vision;

	m_vision = new ClsVision();
	return m_vision;
}


void ClsVision::FreeBarcode2DModel(HalconCpp::HTuple& hvModelID) {
	/* code */
	FreeBarcode2DModelApi(hvModelID);
}

void ClsVision::CreateCodeDMModel(int codeMode, HalconCpp::HTuple& hvModelID){
	/* code */
	CreateCodeDMModelApi(codeMode, hvModelID);
}

void ClsVision::ExecuteDataCode2D(HalconCpp::HObject& hObject, HalconCpp::HObject& hTarget, HalconCpp::HTuple& idModel, std::string& codeString, RoiRegion& region)
{
	/* code */
	ExecuteDataCode2DApi(hObject, hTarget, idModel, codeString, region);
}

bool ClsVision::CreateMulDir(std::string path) {
	/* code */
	if (IsPathExist(path.c_str())) {
		DeleteDirectoryAndFiles(path);
		return true;
	}

	int m = 0;
	int n = 0;
	std::string str1 = path;
	std::string str2 = str1.substr(0, 1);

	str1 = str1.substr(2, str1.size());

	while (m >= 0) {
		m = (int)(str1.find('/'));

		str2 += '/' + str1.substr(0, m);
		n = _access(str2.c_str(), 0); //判断该目录是否存在
		if (-1 == n) {
			if (_mkdir(str2.c_str()) != 0)     return false;          /* 创建目录 */
		}

		str1 = str1.substr(m + 1, str1.size());
	}

	return true;
}

BOOL ClsVision::IsPathExist(const CString & csPath) {
	/* code */
	DWORD dwAttrib = GetFileAttributes(csPath);
	return INVALID_FILE_ATTRIBUTES != dwAttrib;
}

void ClsVision::DeleteDirectoryAndFiles(std::string filePath) {
	/* code  */
	char buffer[MAX_PATH] = { 0, };
	WIN32_FIND_DATA pNextInfo;                  /*搜索得到的文件信息将储存在pNextInfo中*/
	sprintf_s(buffer, "%s/*.hobj", filePath.c_str());
	HANDLE hFile = FindFirstFile(buffer, &pNextInfo);    /*请注意是 &pNextInfo , 不是 pNextInfo */

	if (INVALID_HANDLE_VALUE == hFile)    return;

	do {
		if (pNextInfo.cFileName[0] == '.')  continue;   /*过滤.和..*/

		if (!(pNextInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			sprintf_s(buffer, "%s/%s", filePath.c_str(), pNextInfo.cFileName);
			DeleteFileA(buffer);
		}
	} while (FindNextFile(hFile, &pNextInfo));

	if (hFile)  FindClose(hFile);               /* 释放句柄FindClose */
}

void ClsVision::ImageCopy(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget) {
	/* code */
	ImageCopyApi(hObject, hTarget);
}

void ClsVision::ImageMedian(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, double szRadius) {
	/* code */
	ImageMedianApi(hObject, hTarget, szRadius);
}

void ClsVision::ImageFilterProcess(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, FilterPara para) {
	/* code */
	ImageFilterProcessApi(hObject, hTarget, para);
}

void ClsVision::ImageZoom(HalconCpp::HObject& hObject, HalconCpp::HObject* hTarget, double rate) {
	/* code */
	ImageZoomApi(hObject, hTarget, rate);
}

int ClsVision::CountObject(HalconCpp::HObject& hObject) {
	/* code */
	int count = 0;
	CountObjectApi(hObject, &count);

	return count;
}

std::string ClsVision::GetSubString(std::string strOrigine, int idStart, int sz) {
	/* code */
	int szOrigine = (int)(strOrigine.size());
	if (idStart + sz > szOrigine) {
		std::string str = "";
		return str;
	}

	std::string str(strOrigine.substr(idStart, idStart + sz));

	return str;
}

void ClsVision::RegionZooom(HalconCpp::HObject& hRegion, HalconCpp::HObject* hTarget, double rate) {
	/* code */
	RegionZooomApi(hRegion, hTarget, rate);
}

void ClsVision::GetImageSize(HalconCpp::HObject& hObject, int& width, int& height) {
	/* code */
	GetImageSizeApi(hObject, &width, &height);
}

void ClsVision::GenContourRegion(HalconCpp::HObject& hRegion, HalconCpp::HObject* hTarget) {
	/* code */
	GenContourRegionApi(hRegion, hTarget);
}

void ClsVision::CreateCodeQRModel(int codeMode, HalconCpp::HTuple& hvModelID) {
	/* code */
	CreateCodeQRModelApi(codeMode, hvModelID);
}

AoiParams ClsVision::AoiParametersInit(int iType) {
	/* code */
	AoiParams para;
	para.iType = iType;

	para.int0 = 0;
	para.int1 = -1;
	para.int2 = -1;
	para.int3 = -1;
	para.int4 = -1;
	para.int5 = -1;
	para.int6 = -1;
	para.int7 = -1;
	para.int8 = -1;
	para.int9 = -1;
	para.int10 = -1;

	return para;
}

void ClsVision::ExeBarcodeData2D(HalconCpp::HObject& hObject, HalconCpp::HObject& hTarget, int codeType, int codeMode, std::string& codeString, RoiRegion& region)
{
	/* code */
	ExeBarcodeData2DApi(hObject, hTarget, codeType, codeMode, codeString, region);
}

void ClsVision::CreateNccModel(HalconCpp::HObject& hObject, double angleLimit, int& idResult)
{
	/* code */
	CreateNccModelApi(hObject, angleLimit, idResult);
}

void ClsVision::FindNccModel(HalconCpp::HObject& hObject, int idModel, double minScore, double& xResult, double& yResult, double& angleResult, double& scoreResult)
{
	/* code */
	FindNccModelApi(hObject, idModel, minScore, xResult, yResult, angleResult, scoreResult);
}

void ClsVision::ClearNccModel(int idModel)
{
	/* code */
	ClearNccModelApi(idModel);
}