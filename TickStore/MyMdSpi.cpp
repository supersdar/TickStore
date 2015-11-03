#define _CRT_SECURE_NO_WARNINGS
#include "MyMdSpi.h"
#include<string>
#include <vector>
#include<time.h>
#include<windows.h>

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
	//����¼���
	if (pRspInfo->ErrorID==0)
	{
		cout << "��¼�ɹ�"<< endl;
	}
	else
	{
		cout << pRspInfo->ErrorMsg<< endl;
	}

}

void MyMdSpi::OnFrontConnected()
{
	
	cout << "����������ֳɹ�" << endl;
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

void MyMdSpi::SubscribeMarketData()
{
	//���
	//ClearRepositoryMap();	

	char * tmp = (char *)md_Instrument_all.c_str();
	vector<char*> list;
	char *token = strtok(tmp, ",");
	while (token != NULL) {
		list.push_back(token);
		token = strtok(NULL, ",");
	}
	size_t len = list.size();
	char** pId = new char*[len];
	for (int i = 0; i < len; i++)  
		pId[i] = list[i];

	int ret = this->mdApi->SubscribeMarketData(pId, len);
	
	cout<< " �����ĺ�Լ" << ((ret == 0) ? "�ɹ�" : "ʧ��") << endl;

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
	char date[9] = { 0 };
	time_t timer;
	time(&timer);
	tm* t_tm = localtime(&timer);
	sprintf(date, "%d%02d%02d%s", t_tm->tm_year + 1900, t_tm->tm_mon, t_tm->tm_mday,".dat");
	return string(date);
}
void  MyMdSpi::GetWriter(TThostFtdcInstrumentIDType	InstrumentID, double LastPrice, TThostFtdcTimeType	UpdateTime) {
	if (fp==NULL)
	{
		fp = fopen((char *)GetSystemDate().c_str(), "ab");
	}
	 
	fwrite(InstrumentID, sizeof(InstrumentID), sizeof(InstrumentID), fp);
	//fwrite(LastPrice, sizeof(double), sizeof(double), fp);
	fwrite(UpdateTime, sizeof(UpdateTime), sizeof(UpdateTime), fp);
	fwrite("\r\n", 1, 2, fp);
}
void MyMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	//if(strcmp(pDepthMarketData->InstrumentID, m_instId) == 0)

	
	string date = pDepthMarketData->InstrumentID;
	//	LastPrice


}

MyMdSpi::~MyMdSpi()
{
}

//void MyMdSpi::ClearRepositoryMap()
//{
//	/*fstream *fp;
//	for (map<string, fstream *>::iterator i = repositoryMap.begin(); i != repositoryMap.end();i++)
//	{
//		fp = (fstream *)i->second;
//		fp->close();
//	}
//	repositoryMap.clear();*/
//}
