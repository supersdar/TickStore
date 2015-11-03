#define _CRT_SECURE_NO_WARNINGS
#include "MyMdSpi.h"
#include<string>
#include <vector>
#include<time.h>
#include<windows.h>

<<<<<<< HEAD
extern string path;

=======
>>>>>>> origin/master
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
<<<<<<< HEAD
	//-13:¼ì²âµÇÂ¼Çé¿ö
	if (pRspInfo->ErrorID==0)
	{
		cout << "µÇÂ¼³É¹¦"<< endl;
		//-14:¶©ÔÄÐÐÇé
		SubscribeMarketData();
=======
	//æ£€æµ‹ç™»å½•æƒ…å†µ
	if (pRspInfo->ErrorID==0)
	{
		cout << "ç™»å½•æˆåŠŸ"<< endl;
>>>>>>> origin/master
	}
	else
	{
		cout << pRspInfo->ErrorMsg<< endl;
	}

}

void MyMdSpi::OnFrontConnected()
{
<<<<<<< HEAD
	//-11:ÓëÐÐÇé·þÎñÆ÷ÎÕÊÖ³É¹¦
	cout << "ÓëÐÐÇé·þÎñÆ÷ÎÕÊÖ³É¹¦" << endl;

	//-12:ÇëÇóµÇÂ½
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, brokerID);
	strcpy(req.UserID, userId);
	strcpy(req.Password, passwd);
	int ret =this->mdApi->ReqUserLogin(&req, ++requestId);
=======
	
	cout << "ä¸ŽæœåŠ¡å™¨æ¡æ‰‹æˆåŠŸ" << endl;
>>>>>>> origin/master
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
<<<<<<< HEAD
		cerr << " ´íÎó·´À¡ :" << pRspInfo->ErrorMsg << endl;
	}
}
//-14:¶©ÔÄÐÐÇé
void MyMdSpi::SubscribeMarketData()
{
	
=======
		cerr << " é”™è¯¯åé¦ˆ :" << pRspInfo->ErrorMsg << endl;
	}
}

void MyMdSpi::SubscribeMarketData()
{
	//æ¸…ç©º
	//ClearRepositoryMap();	
>>>>>>> origin/master

	char * tmp = (char *)md_Instrument_all.c_str();
	vector<char*> list;
	char *token = strtok(tmp, ",");
	while (token != NULL) {
		list.push_back(token);
<<<<<<< HEAD
		//cout << token << endl;
=======
>>>>>>> origin/master
		token = strtok(NULL, ",");
	}
	size_t len = list.size();
	char** pId = new char*[len];
	for (int i = 0; i < len; i++)  
		pId[i] = list[i];

	int ret = this->mdApi->SubscribeMarketData(pId, len);
	
<<<<<<< HEAD
	cout<< " REQ¶©ÔÄºÏÔ¼" << ((ret == 0) ? "³É¹¦" : "Ê§°Ü") << endl;
=======
	cout<< " è¯·æ±‚è®¢é˜…åˆçº¦" << ((ret == 0) ? "æˆåŠŸ" : "å¤±è´¥") << endl;

>>>>>>> origin/master
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
<<<<<<< HEAD
	char date[50] = { 0 };
	time_t timer;
	time(&timer);
	tm* t_tm = localtime(&timer);
	sprintf(date, "%s%d%02d%02d%s", path.c_str(), t_tm->tm_year + 1900, t_tm->tm_mon, t_tm->tm_mday, ".dat");
	
	return string(date);
}

void MyMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	//-15£º´æ´¢tickÊý¾Ý
	GetWriter(pDepthMarketData);
}

void  MyMdSpi::GetWriter(CThostFtdcDepthMarketDataField *pDepthMarketData) {
	if (fp == NULL)
	{
		fp = fopen((char *)GetSystemDate().c_str(), "ab");
		cout << "´æ´¢Â·¾¶£º" << GetSystemDate().c_str() << endl;

		if (fp)
		{
			cout << "´æ´¢ÎÄ¼þ´´½¨³É¹¦£º" << GetSystemDate().c_str() << endl;
		}		
	}
	if (fwrite(pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField), 1, fp) != 1)
	{
		cout << "Ð´Èë´íÎó" << endl;
	}
	cout << "³É¹¦Ð´ÈëÒ»±Ê»®tick" << endl;
	
	
=======
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


>>>>>>> origin/master
}

MyMdSpi::~MyMdSpi()
{
<<<<<<< HEAD
	//-16£º¹Ø±ÕÎÄ¼þ
	if (fp!=NULL)
	{
		fclose(fp);
	}
=======
>>>>>>> origin/master
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
