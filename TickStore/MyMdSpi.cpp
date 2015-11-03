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
<<<<<<< HEAD
	//-13:ºÏ≤‚µ«¬º«Èøˆ
	if (pRspInfo->ErrorID==0)
	{
		cout << "µ«¬º≥…π¶"<< endl;
		//-14:∂©‘ƒ––«È
=======
	//-13:Ê£ÄÊµãÁôªÂΩïÊÉÖÂÜµ
	if (pRspInfo->ErrorID==0)
	{
		cout << "ÁôªÂΩïÊàêÂäü"<< endl;
		//-14:ËÆ¢ÈòÖË°åÊÉÖ
>>>>>>> origin/master
		SubscribeMarketData();
	}
	else
	{
		cout << pRspInfo->ErrorMsg<< endl;
	}

}

void MyMdSpi::OnFrontConnected()
{
<<<<<<< HEAD
	//-11:”Î––«È∑˛ŒÒ∆˜Œ’ ÷≥…π¶
	cout << "”Î––«È∑˛ŒÒ∆˜Œ’ ÷≥…π¶" << endl;
=======
	//-11:‰∏éË°åÊÉÖÊúçÂä°Âô®Êè°ÊâãÊàêÂäü
	cout << "‰∏éË°åÊÉÖÊúçÂä°Âô®Êè°ÊâãÊàêÂäü" << endl;
>>>>>>> origin/master

	//-12:ËØ∑Ê±ÇÁôªÈôÜ
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
<<<<<<< HEAD
		cerr << " ¥ÌŒÛ∑¥¿° :" << pRspInfo->ErrorMsg << endl;
	}
}
//-14:∂©‘ƒ––«È
void MyMdSpi::SubscribeMarketData()
{	
	// π”√","∑÷Ω‚∫œ‘º
=======
		cerr << " ÈîôËØØÂèçÈ¶à :" << pRspInfo->ErrorMsg << endl;
	}
}
//-14:ËÆ¢ÈòÖË°åÊÉÖ
void MyMdSpi::SubscribeMarketData()
{	

>>>>>>> origin/master
	char * tmp = (char *)md_Instrument_all.c_str();
	vector<char*> list;
	char *token = strtok(tmp, ",");
	while (token != NULL) {
		list.push_back(token);
		//cout << token << endl;
		token = strtok(NULL, ",");
	}
	size_t len = list.size();
	//∫œ≥…∫œ‘º∂©‘ƒ÷∏’Î
	char** pId = new char*[len];
	for (int i = 0; i < len; i++)  
		pId[i] = list[i];

	int ret = this->mdApi->SubscribeMarketData(pId, len);
	
<<<<<<< HEAD
	cout<< " ∂©‘ƒ∫œ‘º" << ((ret == 0) ? "≥…π¶" : " ß∞‹") << endl;
=======
	cout<< " REQËÆ¢ÈòÖÂêàÁ∫¶" << ((ret == 0) ? "ÊàêÂäü" : "Â§±Ë¥•") << endl;
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

<<<<<<< HEAD
string MyMdSpi::GetSavePath() {
=======
string MyMdSpi::GetSystemDate() {
>>>>>>> origin/master
	char date[50] = { 0 };
	//ªÒ»°œµÕ≥ ±º‰
	time_t timer;
	time(&timer);
	tm* t_tm = localtime(&timer);
	//∏Ò ΩªØœµÕ≥ ±º‰£¨≤¢∆¥Ω”µ√µΩ¥Ê¥¢¬∑æ∂
	sprintf(date, "%s%d%02d%02d%s", path.c_str(), t_tm->tm_year + 1900, t_tm->tm_mon, t_tm->tm_mday, ".dat");
	
	return string(date);
}

void MyMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	//-15ÔºöÂ≠òÂÇ®tickÊï∞ÊçÆ
	GetWriter(pDepthMarketData);
}
//Tickµƒ–¥»Î∑Ω∑®
void  MyMdSpi::GetWriter(CThostFtdcDepthMarketDataField *pDepthMarketData) {
	//∂‘ ◊¥Œ–¥»ÎŒƒº˛«∞≥ı ºªØŒƒº˛÷∏’Î
	if (fp == NULL)
	{
<<<<<<< HEAD
		fp = fopen((char *)GetSavePath().c_str(), "ab");
		cout << "¥Ê¥¢¬∑æ∂£∫" << GetSavePath().c_str() << endl;

		if (fp)
		{
			cout << "¥Ê¥¢Œƒº˛¥¥Ω®≥…π¶£∫" << GetSavePath().c_str() << endl;
=======
		fp = fopen((char *)GetSystemDate().c_str(), "ab");
		cout << "Â≠òÂÇ®Ë∑ØÂæÑÔºö" << GetSystemDate().c_str() << endl;

		if (fp)
		{
			cout << "Â≠òÂÇ®Êñá‰ª∂ÂàõÂª∫ÊàêÂäüÔºö" << GetSystemDate().c_str() << endl;
>>>>>>> origin/master
		}		
	}
	if (fwrite(pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField), 1, fp) != 1)
	{
		cout << "ÂÜôÂÖ•ÈîôËØØ" << endl;
	}
	cout << "ÊàêÂäüÂÜôÂÖ•‰∏ÄÁ¨îÂàítick" << endl;
	
	
}

MyMdSpi::~MyMdSpi()
{
<<<<<<< HEAD
	//-16£∫ÕÀ≥ˆ≥Ã–Ú«∞£¨πÿ±’Œƒº˛
=======
	//-16ÔºöÂÖ≥Èó≠Êñá‰ª∂
>>>>>>> origin/master
	if (fp!=NULL)
	{
		fclose(fp);
	}
}
