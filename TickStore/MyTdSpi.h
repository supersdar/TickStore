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
public:
	MyTdSpi(CThostFtdcTraderApi* pTdApi)
	{
		this->m_pTdApi = pTdApi;
	};
	~MyTdSpi();

	virtual void OnFrontConnected() ;

	virtual void OnFrontDisconnected(int nReason) ;

	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	//virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

private:
	CThostFtdcTraderApi *m_pTdApi;
};

