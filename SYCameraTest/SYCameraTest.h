
// SYCameraTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSYCameraTestApp: 
// �йش����ʵ�֣������ SYCameraTest.cpp
//

class CSYCameraTestApp : public CWinApp
{
public:
	CSYCameraTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSYCameraTestApp theApp;