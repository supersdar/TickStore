#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include "windows.h"
#include "MyTdSpi.h"



MyTdSpi::MyTdSpi(CThostFtdcTraderApi* tdApi, CThostFtdcMdApi *mdApi, CThostFtdcMdSpi *mdSpi)
{
	//ÔÚÄÚ²¿¶Ô½»Ò×ÊµÀý½øÐÐÒýÓÃ£¬±ãÓÚ»Øµô
	this->tdApi = tdApi;
	this->mdApi = mdApi;
	this->mdSpi = mdSpi;
}

MyTdSpi::~MyTdSpi()
{

}

void MyTdSpi::OnFrontConnected()
{
<<<<<<< HEAD
	//-3:Óë½»Ò×·þÎñÆ÷½¨Á¢Á¬½Ó

	cerr << "Óë½»Ò×·þÎñÆ÷ÎÕÊÖ³É¹¦" << endl;
=======
	//-3:ä¸Žäº¤æ˜“æœåŠ¡å™¨å»ºç«‹è¿žæŽ¥
	cerr << "Traderä¸Žäº¤æ˜“æœåŠ¡å™¨æ¡æ‰‹æˆåŠŸ" << endl;
>>>>>>> origin/master
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, brokerID);
	strcpy(req.UserID, userId);
	strcpy(req.Password, passwd);
	this->tdApi->ReqUserLogin(&req, ++requestId);
}

void MyTdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
<<<<<<< HEAD
	//-4:µÈ´ýµÇÂ½½á¹û
	if (pRspInfo->ErrorID==0)
	{
		cout << "½»Ò×¶Ë³É¹¦µÇÂ¼" << endl;
		//-5:½áËãµ¥È·ÈÏ	
=======
	//-4:ç­‰å¾…ç™»é™†ç»“æžœ
	if (pRspInfo->ErrorID==0)
	{
		cout << "Trader ç™»å½•æˆåŠŸ" << endl;
		//-5:ç»“ç®—å•ç¡®è®¤	
>>>>>>> origin/master
		ReqSettlementInfoConfirm();	
		QryAllInstrument();
	}
	else
	{
<<<<<<< HEAD
		cout << "½»Ò×¶ËµÇÂ¼Ê§°Ü"<<pRspInfo->ErrorMsg << endl;
=======
		cout << "Trader ç™»å½•å¤±è´¥"<<pRspInfo->ErrorMsg << endl;
>>>>>>> origin/master
	}
}
void MyTdSpi::ReqSettlementInfoConfirm()
{
<<<<<<< HEAD
	//-5:½áËãµ¥È·ÈÏ

=======
	//-5:ç»“ç®—å•ç¡®è®¤
>>>>>>> origin/master
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, brokerID);
	strcpy(req.InvestorID, userId);
	int ret = this->tdApi->ReqSettlementInfoConfirm(&req, ++requestId);	
<<<<<<< HEAD
	cerr << "·¢ËÍ½áËãµ¥È·ÈÏ..." << ((ret == 0) ? "³É¹¦" : "Ê§°Ü") << endl;
=======
	cerr << " REQ | å‘é€ç»“ç®—å•ç¡®è®¤..." << ((ret == 0) ? "æˆåŠŸ" : "å¤±è´¥") << endl;
>>>>>>> origin/master
	
}
void MyTdSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	//std::cerr << "--->>> " << __FUNCTION__ << std::endl;

<<<<<<< HEAD
	//-6:µÈ´ý×îºóÒ»±Ê½áËãµ¥»ØÓ¦
	if (pRspInfo->ErrorID==0)
	{
		cout << "½áËãÈ·ÈÏÍê³É" << endl;
		//-7:²éÑ¯±¨µ¥
=======
	//-6:ç­‰å¾…æœ€åŽä¸€ç¬”ç»“ç®—å•å›žåº”
	if (pRspInfo->ErrorID==0)
	{
		//Sleep(3000);
		cout << "ç»“ç®—ç¡®è®¤å®Œæˆ" << endl;
		//-7:
>>>>>>> origin/master
		ReqQryOrder();
		
	}
}

void MyTdSpi::ReqQryOrder()
{
<<<<<<< HEAD
	//-7£º²éÑ¯±¨µ¥
=======
	//-7ï¼šæŸ¥è¯¢æŠ¥å•
>>>>>>> origin/master
	CThostFtdcQryOrderField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.InvestorID, userId);
	int ret = this->tdApi->ReqQryOrder(&req, ++requestId);
}

void MyTdSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//ÔÚ×îºóÒ»±Ê±¨µ¥ºó
	if (bIsLast)
	{
<<<<<<< HEAD
		//-8:²éÑ¯ËùÓÐºÏÔ¼
=======
		//-8:æŸ¥è¯¢æ‰€æœ‰åˆçº¦,æŸ¥è¯¢æ‰€æœ‰åˆçº¦
>>>>>>> origin/master
		QryAllInstrument();		
	}
}
void MyTdSpi::QryAllInstrument() {
<<<<<<< HEAD
	//-10:²éÑ¯ËùÓÐºÏÔ¼
=======
	//-9:æŸ¥è¯¢æ‰€æœ‰åˆçº¦
>>>>>>> origin/master
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
	this->tdApi->ReqQryInstrument(&req, ++requestId);//-9	
}
void MyTdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (ret) {
<<<<<<< HEAD
		cerr << "´íÎó·´À¡ :" << pRspInfo->ErrorMsg << endl;
=======
		cerr << "é”™è¯¯åé¦ˆ :" << pRspInfo->ErrorMsg << endl;
>>>>>>> origin/master
	}
}

void MyTdSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

<<<<<<< HEAD
	//-11£º½ÓÊÕºÏÔ¼ÐÅÏ¢²¢ÒÀ´Ëappendµ½È«¾ÖºÏÔ¼ÐÅÏ¢±äÁ¿ÖÐ
=======
	//-10ï¼šæŽ¥æ”¶åˆçº¦
>>>>>>> origin/master
	md_Instrument_all = md_Instrument_all + pInstrument->InstrumentID + ",";
	if (bIsLast)
	{
		md_Instrument_all = md_Instrument_all.substr(0, md_Instrument_all.length() - 1);
		//cout << md_Instrument_all << endl;
		//-12£ºÆô¶¯ÐÐÇé¶Ë
		this->mdApi->Init();
	}
}

void MyTdSpi::OnFrontDisconnected(int nReason)
{
	
}

void MyTdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

