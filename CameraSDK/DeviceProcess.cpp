//------------------------------------------------------------
/**
\file    DeviceProcess.cpp 
\brief   Device Process 
*/
//------------------------------------------------------------

#include "DeviceProcess.h"

CDeviceProcess::CDeviceProcess(void)
{
	m_pBitmap                   = NULL;
	m_pSampleCaptureEventHandle = NULL;
	m_bIsOpen                   = false;
	m_bIsSnap                   = false;
	m_bShowDeviceFPS            = true;
	m_nDeviceIndex              = 0;
	m_strDeviceSN               = "";
	m_pSampleCaptureEventHandle = new CSampleCaptureEventHandler();
	m_pRecordDeviceSNFPS        = new char[1024];
	m_fOnRecvImage = nullptr;
}

CDeviceProcess::~CDeviceProcess(void)
{
	if (m_pSampleCaptureEventHandle != NULL)
	{
		delete m_pSampleCaptureEventHandle;
		m_pSampleCaptureEventHandle = NULL;
	}

	if (m_pRecordDeviceSNFPS != NULL)
	{
		delete[] m_pRecordDeviceSNFPS;
		m_pRecordDeviceSNFPS = NULL;
	}
}

//------------------------------------------------------------
/**
\brief   Open Device 
\param   strDeviceSN   [in]         Device serial number
\param   m_pWnd        [in]         the handle for window
\param   nDeviceIndex  [in]         Device index
\return  void
*/
//------------------------------------------------------------
void CDeviceProcess::OpenDevice(gxstring strDeviceSN, HWND hWnd, int nDeviceIndex, int nExposureTime, double fFrameRate)
{
	bool bIsDeviceOpen   = false;      ///< The flag indicate whether the device has been opened
	bool bIsStreamOpen   = false;      ///< The flag indicate whether the stream has been opened
	try
	{
		if (m_bIsOpen || hWnd == NULL || strDeviceSN == "")
		{
			throw std::exception("Invalid parameter!");
		}

		m_strDeviceSN = strDeviceSN;
		m_nDeviceIndex  = nDeviceIndex;

		// Open device
		m_objDevicePtr = IGXFactory::GetInstance().OpenDeviceBySN(strDeviceSN,GX_ACCESS_EXCLUSIVE);
		bIsDeviceOpen = true;

		// Get the feature control
		m_objFeatureControlPtr = m_objDevicePtr->GetRemoteFeatureControl();

		// Set the continuous frame acquisition mode
		m_objFeatureControlPtr->GetEnumFeature("AcquisitionMode")->SetValue("Continuous");

		// Set the TriggerMode off
		m_objFeatureControlPtr->GetEnumFeature("TriggerMode")->SetValue("Off");

		// Get the number of the device stream 
		int nCount = m_objDevicePtr->GetStreamCount();

		if (nCount > 0)
		{
			m_objStreamPtr = m_objDevicePtr->OpenStream(0);
			bIsStreamOpen = true;
		}
		else
		{
			throw std::exception("No stream found!");
		}

		m_bIsOpen = true;

		if (m_pBitmap != NULL)
		{
			delete m_pBitmap;
			m_pBitmap = NULL;
		}
		m_pBitmap = new CGXBitmap(m_objDevicePtr, hWnd);

		m_objFeatureControlPtr->GetFloatFeature("ExposureTime")->SetValue((float)nExposureTime);

		m_objFeatureControlPtr->GetFloatFeature("AcquisitionFrameRate")->SetValue(fFrameRate);

		m_objFeatureControlPtr->GetEnumFeature("AcquisitionFrameRateMode")->SetValue("On");

	}
	catch (CGalaxyException& e)
	{

		// Check whether the device stream has been opened
		if (bIsStreamOpen)
		{
			m_objStreamPtr->Close();
		} 

		// Check whether the device has been opened
		if (bIsDeviceOpen)
		{
			m_objDevicePtr->Close();
		}

		if (m_pBitmap != NULL)
		{
			delete m_pBitmap;
			m_pBitmap = NULL;
		}

		m_bIsOpen = false;

		throw e;

	}
	catch (std::exception& e)
	{
		// Check whether the device stream has been opened
		if (bIsStreamOpen)
		{
			m_objStreamPtr->Close();
		} 

		// Check whether the device has been opened
		if (bIsDeviceOpen)
		{
			m_objDevicePtr->Close();
		}

		if (m_pBitmap != NULL)
		{
			delete m_pBitmap;
			m_pBitmap = NULL;
		}

		m_bIsOpen = false;

		throw e;
	}

}
//------------------------------------------------------------
/**
\brief   Close Device 

\return  void
*/
//------------------------------------------------------------
void CDeviceProcess::CloseDevice()
{
	if (!m_bIsOpen)
	{
		return;
	}

	try
	{
		// Check whether the device has been stopped acquisition
		if (m_bIsSnap)
		{

			// Send AcquisitionStop command
			m_objFeatureControlPtr->GetCommandFeature("AcquisitionStop")->Execute();

			// Stop Stream acquisition
			m_objStreamPtr->StopGrab();

			// Unregister the CaptureCallback function
			m_objStreamPtr->UnregisterCaptureCallback();
		}
	}
	catch (CGalaxyException)
	{
		//do noting
	}

	try
	{
		// Close stream
		m_objStreamPtr->Close();
	}
	catch (CGalaxyException)
	{
		//do noting
	}

	try
	{
		// Close device
		m_objDevicePtr->Close();
	}
	catch (CGalaxyException)
	{
		//do noting
	}

	m_bIsSnap = false;
	m_bIsOpen = false;

	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}

}
//------------------------------------------------------------
/**
\brief   Start Snap 

\return  void
*/
//------------------------------------------------------------
void CDeviceProcess::StartSnap()
{
	// Check whether the device has been opened
	if (!m_bIsOpen)
	{
		return;
	}

	try
	{
		// Register the CaptureCallback function
		m_objStreamPtr->RegisterCaptureCallback(m_pSampleCaptureEventHandle,this);
	}
	catch (CGalaxyException& e)
	{
		throw e;
	}

	try
	{

		// Start stream channel acquisition
		m_objStreamPtr->StartGrab();
	}
	catch (CGalaxyException& e)
	{
		// Unregister the CaptureCallback function
		m_objStreamPtr->UnregisterCaptureCallback();
		throw e;
	}

	try
	{
		// Send AcquisitionStart command
		m_objFeatureControlPtr->GetCommandFeature("AcquisitionStart")->Execute();

		m_bIsSnap = true;
	}
	catch (CGalaxyException& e)
	{
		// Stop stream channel acquisition
		m_objStreamPtr->StopGrab();

		// Unregister the CaptureCallback function
		m_objStreamPtr->UnregisterCaptureCallback();
		throw e;
	}
	catch (std::exception& e)
	{
		// Stop stream channel acquisition
		m_objStreamPtr->StopGrab();

		// Unregister the CaptureCallback function
		m_objStreamPtr->UnregisterCaptureCallback();
		throw e;
	}

}

//------------------------------------------------------------
/**
\brief   Stop Snap 

\return  void
*/
//------------------------------------------------------------
void CDeviceProcess::StopSnap()
{
	// Check whether the device has been opened
	if (!m_bIsOpen || !m_bIsSnap)
	{
		return;
	}

	try
	{
		// Send AcquisitionStop command
		m_objFeatureControlPtr->GetCommandFeature("AcquisitionStop")->Execute();

		// Stop stream channel acquisition
		m_objStreamPtr->StopGrab();

		// Unregister the CaptureCallback function
		m_objStreamPtr->UnregisterCaptureCallback();

		// frame rate is set 0 
		m_objfps.Reset();

		m_bIsSnap = false;
	}
	catch (CGalaxyException& e)
	{
		throw e;

	}
	catch (std::exception& e)
	{
		throw e;

	}
}

//------------------------------------------------------------
/**
\brief   Get Device Open Flag 

\return  void
*/
//------------------------------------------------------------
bool CDeviceProcess::IsOpen() const
{
	return m_bIsOpen;
}

//------------------------------------------------------------
/**
\brief   Get Device Snap Flag 

\return  void
*/
//------------------------------------------------------------
bool CDeviceProcess::IsSnap() const
{
	return m_bIsSnap;
}

//------------------------------------------------------------
/**
\brief   Set Show frame Frequency Flag

\return  void
*/
//------------------------------------------------------------
void CDeviceProcess::SetShowFPS(bool bIsShowFps)
{
	m_bShowDeviceFPS = bIsShowFps;
}

//------------------------------------------------------------
/**
\brief   Get Show frame Frequency Flag

\return  void
*/
//------------------------------------------------------------
bool CDeviceProcess::GetShowFPS()
{
	return m_bShowDeviceFPS;
}

//------------------------------------------------------------
/**
\brief   Refresh Device SN and FPS

\return  void
*/
//------------------------------------------------------------
void CDeviceProcess::RefreshDeviceSNFPS()
{
	double dFps = 0;        ///< frame rate

	//Update frame rate
	m_objfps.UpdateFps();

	// Get the latest frame rate
	dFps = m_objfps.GetFps();

	sprintf_s(m_pRecordDeviceSNFPS, 1024,
		"Serial number:%d SN:%s FPS:%.2f",
		m_nDeviceIndex,
		m_strDeviceSN.c_str(),
		dFps);
}

//------------------------------------------------------------
/**
\brief   Show Image
\param   objImageDataPointer [in]       Image process

\return  void
*/
//------------------------------------------------------------
void CDeviceProcess::__ShowPicture(CImageDataPointer& objImageDataPointer)
{
	if (m_bShowDeviceFPS)
	{
		// Increase the number of frames
		m_objfps.IncreaseFrameNum();

		// Show Image and frame rate
		m_pBitmap->Show(objImageDataPointer,m_pRecordDeviceSNFPS);

	}
	else
	{
		// Show Image
		m_pBitmap->Show(objImageDataPointer, m_pt1, m_pt2);
	}
}

void CDeviceProcess::OnRecvImageData(CImageDataPointer& objImageDataPointer)
{
	if (m_fOnRecvImage != nullptr) {
		m_fOnRecvImage(m_nDeviceIndex, (unsigned int)objImageDataPointer->GetWidth(), (unsigned int)objImageDataPointer->GetHeight(),
			objImageDataPointer->GetBuffer(), (unsigned int)objImageDataPointer->GetPayloadSize());
	}
}

void CDeviceProcess::SetOnRecvImageListener(ONRECVIMAGE listener)
{
	m_fOnRecvImage = listener;
}

void CDeviceProcess::SetRoiRegion(LPPOINT lpPoint1, LPPOINT lpPoint2)
{
	m_pt1.x = lpPoint1->x;
	m_pt1.y = lpPoint1->y;
	m_pt2.x = lpPoint2->x;
	m_pt2.y = lpPoint2->y;
}

gxstring CDeviceProcess::GetDeviceSN()
{
	return m_strDeviceSN;
}


