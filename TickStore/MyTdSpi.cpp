#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include "windows.h"
#include "MyTdSpi.h"



MyTdSpi::MyTdSpi(CThostFtdcTraderApi* tdApi, CThostFtdcMdApi *mdApi, CThostFtdcMdSpi *mdSpi)
{
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
	//-3:与交易服务器建立连接
	cerr << "Trader与交易服务器握手成功" << endl;
=======
	//-3:涓庝氦鏄撴湇鍔″櫒寤虹珛杩炴帴
	cerr << "Trader涓庝氦鏄撴湇鍔″櫒鎻℃墜鎴愬姛" << endl;
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
	//-4:等待登陆结果
	if (pRspInfo->ErrorID==0)
	{
		cout << "Trader 登录成功" << endl;
		//-5:结算单确认	
		ReqSettlementInfoConfirm();	
		QryAllInstrument();
	}
	else
	{
		cout << "Trader 登录失败"<<pRspInfo->ErrorMsg << endl;
=======
	//-4:绛夊緟鐧婚檰缁撴灉
	if (pRspInfo->ErrorID==0)
	{
		cout << "Trader 鐧诲綍鎴愬姛" << endl;
		//-5:缁撶畻鍗曠‘璁�	
		ReqSettlementInfoConfirm();		
	}
	else
	{
		cout << "Trader 鐧诲綍澶辫触"<<pRspInfo->ErrorMsg << endl;
>>>>>>> origin/master
	}
}
void MyTdSpi::ReqSettlementInfoConfirm()
{
<<<<<<< HEAD
	//-5:结算单确认
=======
	//-5:缁撶畻鍗曠‘璁�
>>>>>>> origin/master
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, brokerID);
	strcpy(req.InvestorID, userId);
	int ret = this->tdApi->ReqSettlementInfoConfirm(&req, ++requestId);	
<<<<<<< HEAD
	cerr << " REQ | 发送结算单确认..." << ((ret == 0) ? "成功" : "失败") << endl;
=======
	cerr << " REQ | 鍙戦�佺粨绠楀崟纭..." << ((ret == 0) ? "鎴愬姛" : "澶辫触") << endl;
>>>>>>> origin/master
	
}
void MyTdSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
<<<<<<< HEAD
	//std::cerr << "--->>> " << __FUNCTION__ << std::endl;

	//-6:等待最后一笔结算单回应
	if (pRspInfo->ErrorID==0)
	{
		//Sleep(3000);
		cout << "结算确认完成" << endl;
=======
	std::cerr << "--->>> " << __FUNCTION__ << std::endl;

	//-6:绛夊緟鏈�鍚庝竴绗旂粨绠楀崟鍥炲簲
	if (pRspInfo->ErrorID==0)
	{
		Sleep(3000);
		cout << "缁撶畻纭瀹屾垚" << endl;
>>>>>>> origin/master
		//-7:
		ReqQryOrder();
		
	}
}

void MyTdSpi::ReqQryOrder()
{
<<<<<<< HEAD
	//-7：查询报单
=======
	//-7锛氭煡璇㈡姤鍗�
>>>>>>> origin/master
	CThostFtdcQryOrderField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.InvestorID, userId);
	int ret = this->tdApi->ReqQryOrder(&req, ++requestId);
}

void MyTdSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	
	if (bIsLast)
	{
<<<<<<< HEAD
		//-8:查询所有合约,查询所有合约
		QryAllInstrument();		
	}
}
void MyTdSpi::QryAllInstrument() {
	//-9:查询所有合约
=======
		//-8:鏌ヨ鎵�鏈夊悎绾�,鏌ヨ鎵�鏈夊悎绾�
		QryAllInstrument();
		
	}
}
void MyTdSpi::QryAllInstrument() {
	//鏌ヨ鎵�鏈夊悎绾�
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
		cerr << "错误反馈 :" << pRspInfo->ErrorMsg << endl;
=======
		cerr << " 閿欒鍙嶉 锛�" << pRspInfo->ErrorMsg << endl;
>>>>>>> origin/master
	}
}

void MyTdSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
<<<<<<< HEAD

	//-10：接收合约
	md_Instrument_all = md_Instrument_all + pInstrument->InstrumentID + ",";
	if (bIsLast)
	{
		md_Instrument_all = md_Instrument_all.substr(0, md_Instrument_all.length() - 1);
		//cout << md_Instrument_all << endl;
		this->mdApi->Init();
=======
	//-9锛氭帴鏀跺悎绾�
	if (pRspInfo->ErrorID == 0)
	{
		md_Instrument_all = md_Instrument_all + pInstrument->InstrumentID + ",";
		if (bIsLast)
		{
			md_Instrument_all = md_Instrument_all.substr(0, md_Instrument_all.length() - 1);
			cerr << md_Instrument_all << endl;
			this->mdApi->Init();
		}
>>>>>>> origin/master
	}
}

void MyTdSpi::OnFrontDisconnected(int nReason)
{
	
}

void MyTdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

