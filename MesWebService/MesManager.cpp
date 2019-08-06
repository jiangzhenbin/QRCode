#include "MesManager.h"
#include "soapH.h"
#include "WebServerSoap.nsmap"

MesManager::MesManager()
{
}


MesManager::~MesManager()
{
}

int MesManager::SendCode(const char *pEndPoint, const std::string functionId, const std::string deviceId, std::string code, bool isOk, std::string &out)
{
	int nRet = -1;
	struct soap m_oSoap;
	class _ns1__BarCodeSend barCodeSendObject;
	class _ns1__BarCodeSendResponse barCodeSendResponseObject;


	// SOAP初始化
	soap_init(&m_oSoap);


	// 调用函数的参数赋值
	char szBuffer[256];
	sprintf_s(szBuffer, 256, "%s,%s,%s,%s,", functionId.c_str(), deviceId.c_str(), code.c_str(), isOk ? "OK" : "NG");
	std::string strData = szBuffer;
	barCodeSendObject.barcode = &strData;


	// 发送WebService请求，并获得返回结果
	int nResult = soap_call___ns1__BarCodeSend(&m_oSoap, pEndPoint, NULL, &barCodeSendObject, barCodeSendResponseObject);
	if (SOAP_OK == nResult) {
		// 输出返回结果
		out = barCodeSendResponseObject.BarCodeSendResult->c_str();
		nRet = 0;
	}
	/// 关闭SOAP
	soap_destroy(&m_oSoap);
	soap_end(&m_oSoap);
	soap_done(&m_oSoap);

	return nRet;
}
