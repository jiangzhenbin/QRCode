#pragma once
class CUtils
{
public:
	CUtils();
	~CUtils();

public:
	static void SetTag(char *szTag);
	static void Log(char* szMessage, ...);


public:
	static char m_szTag[32];
};

