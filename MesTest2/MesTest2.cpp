// MesTest2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "soapH.h"
#include "WebServerSoap.nsmap"
#include <fstream>
using namespace std;

int main()
{
	// SOAP�Ŀͻ���
	struct soap m_oSoap;
	// WebService���ö���
	class _ns1__BarCodeSend barCodeSendObject;
	// WebService���ض���
	class _ns1__BarCodeSendResponse barCodeSendResponseObject;
	// SOAP��ʼ��
	soap_init(&m_oSoap);
	// ���ú����Ĳ�����ֵ
	barCodeSendObject.barcode = new std::string("062,001#,1987123456,NG,");
	/*�������ͷ�ļ�ʱû���޸�����,��ô�����·�ʽ��ֵ,���յ����͵�ȻҲ��string:
	std::string strName = "15742451354";
	getMobileCodeObject.mobileCode = strName;
	*/

	// ����WebService���󣬲���÷��ؽ��
	int nResult = soap_call___ns1__BarCodeSend(&m_oSoap, NULL, NULL, &barCodeSendObject, barCodeSendResponseObject);
	// �����ɹ�
	if (SOAP_OK == nResult)
	{
		// ������ؽ��
		std::string *string = barCodeSendResponseObject.BarCodeSendResult;
		cout << "cout:" << string->c_str() << endl;
	}
	/// �ر�SOAP
	soap_destroy(&m_oSoap);
	soap_end(&m_oSoap);
	soap_done(&m_oSoap);

	system("pause");


    return 0;
}

