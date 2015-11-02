#pragma once
#include <iostream>
#include <string>
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcMdApi.h"

using namespace std;

extern int requestId;
extern string md_Instrument_all;
extern char * brokerID;
extern char * userId;
extern char * passwd;
extern char * MDAddress;
extern char * TDAddress;

class MyTdSpi :	public CThostFtdcTraderSpi
{
private:
	CThostFtdcTraderApi *tdApi;
	CThostFtdcMdApi *mdApi;
	CThostFtdcMdSpi *mdSpi;
	
public:
	MyTdSpi(CThostFtdcTraderApi* tdApi,CThostFtdcMdApi *mdApi,CThostFtdcMdSpi *mdSpi);
	~MyTdSpi();

	virtual void OnFrontConnected() ;

	virtual void OnFrontDisconnected(int nReason) ;

	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	void ReqSettlementInfoConfirm();

	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
	
	void ReqQryOrder();

	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	void QryAllInstrument();

	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	//virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;


};

