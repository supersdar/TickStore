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
	//-3:与交易服务器建立连接
	cerr << "Trader与交易服务器握手成功" << endl;
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, brokerID);
	strcpy(req.UserID, userId);
	strcpy(req.Password, passwd);
	this->tdApi->ReqUserLogin(&req, ++requestId);
}

void MyTdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
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
	}
}
void MyTdSpi::ReqSettlementInfoConfirm()
{
	//-5:结算单确认
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, brokerID);
	strcpy(req.InvestorID, userId);
	int ret = this->tdApi->ReqSettlementInfoConfirm(&req, ++requestId);	
	cerr << " REQ | 发送结算单确认..." << ((ret == 0) ? "成功" : "失败") << endl;
	
}
void MyTdSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	//std::cerr << "--->>> " << __FUNCTION__ << std::endl;

	//-6:等待最后一笔结算单回应
	if (pRspInfo->ErrorID==0)
	{
		//Sleep(3000);
		cout << "结算确认完成" << endl;
		//-7:
		ReqQryOrder();
		
	}
}

void MyTdSpi::ReqQryOrder()
{
	//-7：查询报单
	CThostFtdcQryOrderField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.InvestorID, userId);
	int ret = this->tdApi->ReqQryOrder(&req, ++requestId);
}

void MyTdSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	
	if (bIsLast)
	{
		//-8:查询所有合约,查询所有合约
		QryAllInstrument();		
	}
}
void MyTdSpi::QryAllInstrument() {
	//-9:查询所有合约
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
	this->tdApi->ReqQryInstrument(&req, ++requestId);//-9	
}
void MyTdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (ret) {
		cerr << "错误反馈 :" << pRspInfo->ErrorMsg << endl;
	}
}

void MyTdSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

	//-10：接收合约
	md_Instrument_all = md_Instrument_all + pInstrument->InstrumentID + ",";
	if (bIsLast)
	{
		md_Instrument_all = md_Instrument_all.substr(0, md_Instrument_all.length() - 1);
		//cout << md_Instrument_all << endl;
		this->mdApi->Init();
	}
}

void MyTdSpi::OnFrontDisconnected(int nReason)
{
	
}

void MyTdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

