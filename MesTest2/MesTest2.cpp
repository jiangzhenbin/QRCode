// MesTest2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "soapH.h"
#include "WebServerSoap.nsmap"
#include <fstream>
using namespace std;

int main()
{
	// SOAP的客户端
	struct soap m_oSoap;
	// WebService调用对象
	class _ns1__BarCodeSend barCodeSendObject;
	// WebService返回对象
	class _ns1__BarCodeSendResponse barCodeSendResponseObject;
	// SOAP初始化
	soap_init(&m_oSoap);
	// 调用函数的参数赋值
	barCodeSendObject.barcode = new std::string("062,001#,1987123456,NG,");
	/*如果生成头文件时没有修改类型,那么用如下方式赋值,接收的类型当然也是string:
	std::string strName = "15742451354";
	getMobileCodeObject.mobileCode = strName;
	*/

	// 发送WebService请求，并获得返回结果
	int nResult = soap_call___ns1__BarCodeSend(&m_oSoap, NULL, NULL, &barCodeSendObject, barCodeSendResponseObject);
	// 操作成功
	if (SOAP_OK == nResult)
	{
		// 输出返回结果
		std::string *string = barCodeSendResponseObject.BarCodeSendResult;
		cout << "cout:" << string->c_str() << endl;
	}
	/// 关闭SOAP
	soap_destroy(&m_oSoap);
	soap_end(&m_oSoap);
	soap_done(&m_oSoap);

	system("pause");


    return 0;
}

