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
	//-13:检测登录情况
	if (pRspInfo->ErrorID==0)
	{
		cout << "登录成功"<< endl;
		//-14:订阅行情
		SubscribeMarketData();
	}
	else
	{
		cout << pRspInfo->ErrorMsg<< endl;
	}

}

void MyMdSpi::OnFrontConnected()
{
	//-11:与行情服务器握手成功
	cout << "与行情服务器握手成功" << endl;

	//-12:请求登陆
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
		cerr << " 错误反馈 :" << pRspInfo->ErrorMsg << endl;
	}
}
//-14:订阅行情
void MyMdSpi::SubscribeMarketData()
{	

	char * tmp = (char *)md_Instrument_all.c_str();
	vector<char*> list;
	char *token = strtok(tmp, ",");
	while (token != NULL) {
		list.push_back(token);
		//cout << token << endl;
		token = strtok(NULL, ",");
	}
	size_t len = list.size();
	char** pId = new char*[len];
	for (int i = 0; i < len; i++)  
		pId[i] = list[i];

	int ret = this->mdApi->SubscribeMarketData(pId, len);
	
	cout<< " REQ订阅合约" << ((ret == 0) ? "成功" : "失败") << endl;
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

string MyMdSpi::GetSystemDate() {
	char date[50] = { 0 };
	time_t timer;
	time(&timer);
	tm* t_tm = localtime(&timer);
	sprintf(date, "%s%d%02d%02d%s", path.c_str(), t_tm->tm_year + 1900, t_tm->tm_mon, t_tm->tm_mday, ".dat");
	
	return string(date);
}

void MyMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	//-15：存储tick数据
	GetWriter(pDepthMarketData);
}

void  MyMdSpi::GetWriter(CThostFtdcDepthMarketDataField *pDepthMarketData) {
	if (fp == NULL)
	{
		fp = fopen((char *)GetSystemDate().c_str(), "ab");
		cout << "存储路径：" << GetSystemDate().c_str() << endl;

		if (fp)
		{
			cout << "存储文件创建成功：" << GetSystemDate().c_str() << endl;
		}		
	}
	if (fwrite(pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField), 1, fp) != 1)
	{
		cout << "写入错误" << endl;
	}
	cout << "成功写入一笔划tick" << endl;
	
	
}

MyMdSpi::~MyMdSpi()
{
	//-16：关闭文件
	if (fp!=NULL)
	{
		fclose(fp);
	}
}
