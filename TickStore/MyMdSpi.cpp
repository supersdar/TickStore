#define _CRT_SECURE_NO_WARNINGS
#include "MyMdSpi.h"
#include<string>
#include <vector>
#include<time.h>
#include<windows.h>

extern string path;

using namespace std;

void MyMdSpi::ReqUserLogin(TThostFtdcBrokerIDType appId, TThostFtdcUserIDType userId, TThostFtdcPasswordType passwd)
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, appId);
	strcpy(req.UserID, userId);
	strcpy(req.Password, passwd);
	int ret=this->mdApi->ReqUserLogin(&req,requestId);
}
void MyMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//-13:����¼���
	if (pRspInfo->ErrorID==0)
	{
		cout << "��¼�ɹ�"<< endl;
		//-14:��������
		SubscribeMarketData();
	}
	else
	{
		cout << pRspInfo->ErrorMsg<< endl;
	}

}

void MyMdSpi::OnFrontConnected()
{
	//-11:��������������ֳɹ�
	cout << "��������������ֳɹ�" << endl;

	//-12:�����½
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, brokerID);
	strcpy(req.UserID, userId);
	strcpy(req.Password, passwd);
	int ret =this->mdApi->ReqUserLogin(&req, ++requestId);
}

void MyMdSpi::OnFrontDisconnected(int nReason)
{
	
}

void MyMdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void MyMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (ret) {
		cerr << " ������ :" << pRspInfo->ErrorMsg << endl;
	}
}
//-14:��������
void MyMdSpi::SubscribeMarketData()
{	
	//ʹ��","�ֽ��Լ
	char * tmp = (char *)md_Instrument_all.c_str();
	vector<char*> list;
	char *token = strtok(tmp, ",");
	while (token != NULL) {
		list.push_back(token);
		//cout << token << endl;
		token = strtok(NULL, ",");
	}
	size_t len = list.size();
	//�ϳɺ�Լ����ָ��
	char** pId = new char*[len];
	for (int i = 0; i < len; i++)  
		pId[i] = list[i];

	int ret = this->mdApi->SubscribeMarketData(pId, len);
	
	cout<< " ���ĺ�Լ" << ((ret == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void MyMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void MyMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void MyMdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

string MyMdSpi::GetSavePath() {
	char date[50] = { 0 };
	//��ȡϵͳʱ��
	time_t timer;
	time(&timer);
	tm* t_tm = localtime(&timer);
	//��ʽ��ϵͳʱ�䣬��ƴ�ӵõ��洢·��
	sprintf(date, "%s%d%02d%02d%s", path.c_str(), t_tm->tm_year + 1900, t_tm->tm_mon, t_tm->tm_mday, ".dat");
	
	return string(date);
}

void MyMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	//-15���洢tick����
	GetWriter(pDepthMarketData);
}
//Tick��д�뷽��
void  MyMdSpi::GetWriter(CThostFtdcDepthMarketDataField *pDepthMarketData) {
	//���״�д���ļ�ǰ��ʼ���ļ�ָ��
	if (fp == NULL)
	{
		fp = fopen((char *)GetSavePath().c_str(), "ab");
		cout << "�洢·����" << GetSavePath().c_str() << endl;

		if (fp)
		{
			cout << "�洢�ļ������ɹ���" << GetSavePath().c_str() << endl;
		}		
	}
	if (fwrite(pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField), 1, fp) != 1)
	{
		cout << "д�����" << endl;
	}
	cout << "�ɹ�д��һ�ʻ�tick" << endl;
	
	
}

MyMdSpi::~MyMdSpi()
{
	//-16���˳�����ǰ���ر��ļ�
	if (fp!=NULL)
	{
		fclose(fp);
	}
}
