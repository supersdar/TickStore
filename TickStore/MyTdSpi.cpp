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
	//-3:�뽻�׷�������������
	cerr << "Trader�뽻�׷��������ֳɹ�" << endl;
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, brokerID);
	strcpy(req.UserID, userId);
	strcpy(req.Password, passwd);
	this->tdApi->ReqUserLogin(&req, ++requestId);
}

void MyTdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//-4:�ȴ���½���
	if (pRspInfo->ErrorID==0)
	{
		cout << "Trader ��¼�ɹ�" << endl;
		//-5:���㵥ȷ��	
		ReqSettlementInfoConfirm();	
		QryAllInstrument();
	}
	else
	{
		cout << "Trader ��¼ʧ��"<<pRspInfo->ErrorMsg << endl;
	}
}
void MyTdSpi::ReqSettlementInfoConfirm()
{
	//-5:���㵥ȷ��
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, brokerID);
	strcpy(req.InvestorID, userId);
	int ret = this->tdApi->ReqSettlementInfoConfirm(&req, ++requestId);	
	cerr << " REQ | ���ͽ��㵥ȷ��..." << ((ret == 0) ? "�ɹ�" : "ʧ��") << endl;
	
}
void MyTdSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	std::cerr << "--->>> " << __FUNCTION__ << std::endl;

	//-6:�ȴ����һ�ʽ��㵥��Ӧ
	if (pRspInfo->ErrorID==0)
	{
		Sleep(3000);
		cout << "����ȷ�����" << endl;
		//-7:
		ReqQryOrder();
		
	}
}

void MyTdSpi::ReqQryOrder()
{
	//-7����ѯ����
	CThostFtdcQryOrderField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.InvestorID, userId);
	int ret = this->tdApi->ReqQryOrder(&req, ++requestId);
}

void MyTdSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	
	if (bIsLast)
	{
		//-8:��ѯ���к�Լ,��ѯ���к�Լ
		QryAllInstrument();
		
	}
}
void MyTdSpi::QryAllInstrument() {
	//��ѯ���к�Լ
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
	this->tdApi->ReqQryInstrument(&req, ++requestId);//-9	
}
void MyTdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (ret) {
		cerr << " ������ ��" << pRspInfo->ErrorMsg << endl;
	}
}

void MyTdSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//-9�����պ�Լ
	if (pRspInfo->ErrorID == 0)
	{
		md_Instrument_all = md_Instrument_all + pInstrument->InstrumentID + ",";
		if (bIsLast)
		{
			md_Instrument_all = md_Instrument_all.substr(0, md_Instrument_all.length() - 1);
			cerr << md_Instrument_all << endl;
			this->mdApi->Init();
		}
	}
}

void MyTdSpi::OnFrontDisconnected(int nReason)
{
	
}

void MyTdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

