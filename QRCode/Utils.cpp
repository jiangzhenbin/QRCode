#include "stdafx.h"
#include "Utils.h"

char CUtils::m_szTag[32] = "[Utils]\0";
CUtils::CUtils()
{
}

CUtils::~CUtils()
{
}

void CUtils::SetTag(char *szTag)
{
	strcpy_s(m_szTag, szTag);
}

void CUtils::Log(char* szMessage, ...)
{
	char szFullMessage[MAX_PATH];
	char szFormatMessage[MAX_PATH];

	// format message
	va_list ap;
	va_start(ap, szMessage);
	_vsnprintf_s(szFormatMessage, MAX_PATH, szMessage, ap);
	va_end(ap);
	strncat_s(szFormatMessage, "\n", MAX_PATH);
	strcpy_s(szFullMessage, CUtils::m_szTag);
	strcat_s(szFullMessage, szFormatMessage);
	OutputDebugStringA(szFullMessage);
}

