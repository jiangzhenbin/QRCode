#pragma once

#include "DeviceProcess.h"
#include <unordered_map>

class CCameraEngine
{
public:
	CCameraEngine();
	virtual ~CCameraEngine();

public:
	void Init(int nExposureTime);
	void UnInit();
	void SortIndex(std::unordered_map<unsigned int, std::string> *pMap);
	int GetCameraCount();
	CDeviceProcess * OpenCamera(unsigned int index, HWND hWnd, double fFrameRate);


private:
	int m_nExposureTime;

private:
	GxIAPICPP::gxdeviceinfo_vector m_vectorDeviceInfo;          ///< Device information
	std::unordered_map<unsigned int, CDeviceProcess *> m_mapProcess;
};

