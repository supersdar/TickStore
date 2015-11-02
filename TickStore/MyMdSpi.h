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
	//����apiָ��
	CThostFtdcMdApi *mdApi;
	FILE *fp;
	////��Լ���ļ����Ķ�
	//map<string, fstream *> repositoryMap;
public:
	MyMdSpi(CThostFtdcMdApi* api)
	{
		this->mdApi = api;
	}
	void ReqUserLogin(TThostFtdcBrokerIDType appId, TThostFtdcUserIDType userId, TThostFtdcPasswordType passwd);
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason);

	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������Ӧ��
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ȡ����������Ӧ��
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ȡ������ѯ��Ӧ��
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	string GetSystemDate();

	///�������֪ͨ
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
	
	void SubscribeMarketData();

	void GetWriter(TThostFtdcInstrumentIDType	InstrumentID, TThostFtdcPriceType	LastPrice, TThostFtdcTimeType	UpdateTime);

	~MyMdSpi();
	//void ClearRepositoryMap();


};

