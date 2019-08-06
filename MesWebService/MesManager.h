#pragma once
#include <string>

class MesManager
{
public:
	MesManager();
	~MesManager();

public:
	static int SendCode(const char *pEndPoint, const std::string functionId, const std::string deviceId, std::string code, bool isOk, std::string &out);
};

