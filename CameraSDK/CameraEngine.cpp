#include "CameraEngine.h"

CCameraEngine::CCameraEngine()
{

}

CCameraEngine::~CCameraEngine()
{
	for (auto item : m_mapProcess) {
		delete item.second;
	}
	m_mapProcess.clear();
}

/*
 * 初始化
 */
void CCameraEngine::Init(int nExposureTime)
{
	m_nExposureTime = nExposureTime;
	IGXFactory::GetInstance().Init();
	IGXFactory::GetInstance().UpdateDeviceList(1000, m_vectorDeviceInfo);
}

/*
 * 按钮map内容排序
 */
#include "..\QRCode\Utils.h"
void CCameraEngine::SortIndex(std::unordered_map<unsigned int, std::string> *pMap)
{
	GxIAPICPP::gxdeviceinfo_vector temp;
	for (auto item : m_vectorDeviceInfo) {
		temp.push_back(item);
	}
	m_vectorDeviceInfo.clear();

	for (int i = 0; i < 4; i++) {
		auto it = pMap->find(i+1);
		if (it != pMap->end()) {
			std::string strDeviceSN = it->second;
			CUtils::Log("第 %d 个: %s", i, strDeviceSN.c_str());
			for (auto item2 : temp) {
				CUtils::Log(">>> : %s", item2.GetSN().c_str());
				if (item2.GetSN().compare(strDeviceSN.c_str()) == 0) {
					m_vectorDeviceInfo.push_back(item2);
					break;
				}				
			}
		}
	}
}

void CCameraEngine::UnInit()
{
	try {
		// Release GxIAPICPP
		IGXFactory::GetInstance().Uninit();
	}
	catch (CGalaxyException) {
		//do noting
	}
}

int CCameraEngine::GetCameraCount()
{
	return (int)m_vectorDeviceInfo.size();
}

CDeviceProcess * CCameraEngine::OpenCamera(unsigned int index, HWND hWnd, double fFrameRate)
{
	try {
		auto it = m_mapProcess.find(index + 1);
		if (it == m_mapProcess.end()) {
			CDeviceProcess *pProcess = new CDeviceProcess();
			pProcess->OpenDevice(m_vectorDeviceInfo[index].GetSN(), hWnd, index + 1, m_nExposureTime, fFrameRate);
			m_mapProcess[index + 1] = pProcess;
			return pProcess;
		}

		return m_mapProcess[index + 1];
	}
	catch (...) {
		return NULL;
	}
}


