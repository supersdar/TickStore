#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include "windows.h"
#include "MyTdSpi.h"



MyTdSpi::MyTdSpi(CThostFtdcTraderApi* tdApi, CThostFtdcMdApi *mdApi, CThostFtdcMdSpi *mdSpi)
{
	//在内部对交易实例进行引用，便于回掉
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

	cerr << "与交易服务器握手成功" << endl;
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
		cout << "交易端成功登录" << endl;
		//-5:结算单确认	
		ReqSettlementInfoConfirm();	
		QryAllInstrument();
	}
	else
	{
		cout << "交易端登录失败"<<pRspInfo->ErrorMsg << endl;
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
	cerr << "发送结算单确认..." << ((ret == 0) ? "成功" : "失败") << endl;
	
}
void MyTdSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	//std::cerr << "--->>> " << __FUNCTION__ << std::endl;

	//-6:等待最后一笔结算单回应
	if (pRspInfo->ErrorID==0)
	{
		cout << "结算确认完成" << endl;
		//-7:查询报单
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
	//在最后一笔报单后
	if (bIsLast)
	{
		//-8:查询所有合约
		QryAllInstrument();		
	}
}
void MyTdSpi::QryAllInstrument() {
	//-10:查询所有合约
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

	//-11：接收合约信息并依此append到全局合约信息变量中
	md_Instrument_all = md_Instrument_all + pInstrument->InstrumentID + ",";
	if (bIsLast)
	{
		md_Instrument_all = md_Instrument_all.substr(0, md_Instrument_all.length() - 1);
		//cout << md_Instrument_all << endl;
		//-12：启动行情端
		this->mdApi->Init();
	}
}

void MyTdSpi::OnFrontDisconnected(int nReason)
{
	
}

void MyTdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

