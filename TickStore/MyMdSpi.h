#pragma once
#include <iostream>
#include <string>
#include <map>
#include "ThostFtdcMdApi.h"

using namespace std;

extern int requestId;
extern string md_Instrument_all;
extern char * brokerID;
extern char * userId;
extern char * passwd;
extern char * MDAddress;
extern char * TDAddress;

class MyMdSpi : public CThostFtdcMdSpi
{
private:
	//行情api指针
	CThostFtdcMdApi *mdApi;
	FILE *fp;
	////合约与文件流的对
	//map<string, fstream *> repositoryMap;
public:
	MyMdSpi(CThostFtdcMdApi* api)
	{
		this->mdApi = api;
	}
	void ReqUserLogin(TThostFtdcBrokerIDType appId, TThostFtdcUserIDType userId, TThostFtdcPasswordType passwd);
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason);

	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///取消订阅询价应答
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	string GetSystemDate();

	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
	
	void SubscribeMarketData();

	void GetWriter(TThostFtdcInstrumentIDType	InstrumentID, TThostFtdcPriceType	LastPrice, TThostFtdcTimeType	UpdateTime);

	~MyMdSpi();
	//void ClearRepositoryMap();


};

