
// QRCode.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQRCodeApp: 
// �йش����ʵ�֣������ QRCode.cpp
//

class CQRCodeApp : public CWinApp
{
public:
	CQRCodeApp();


public:
	CString m_strAppDir;
	CString m_strAppFile;


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CQRCodeApp theApp;