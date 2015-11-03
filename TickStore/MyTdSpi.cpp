#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include "windows.h"
#include "MyTdSpi.h"



MyTdSpi::MyTdSpi(CThostFtdcTraderApi* tdApi, CThostFtdcMdApi *mdApi, CThostFtdcMdSpi *mdSpi)
{
	//���ڲ��Խ���ʵ���������ã����ڻص�
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

	cerr << "�뽻�׷��������ֳɹ�" << endl;
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
		cout << "���׶˳ɹ���¼" << endl;
		//-5:���㵥ȷ��	
		ReqSettlementInfoConfirm();	
		QryAllInstrument();
	}
	else
	{
		cout << "���׶˵�¼ʧ��"<<pRspInfo->ErrorMsg << endl;
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
	cerr << "���ͽ��㵥ȷ��..." << ((ret == 0) ? "�ɹ�" : "ʧ��") << endl;
	
}
void MyTdSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	//std::cerr << "--->>> " << __FUNCTION__ << std::endl;

	//-6:�ȴ����һ�ʽ��㵥��Ӧ
	if (pRspInfo->ErrorID==0)
	{
		cout << "����ȷ�����" << endl;
		//-7:��ѯ����
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
	//�����һ�ʱ�����
	if (bIsLast)
	{
		//-8:��ѯ���к�Լ
		QryAllInstrument();		
	}
}
void MyTdSpi::QryAllInstrument() {
	//-10:��ѯ���к�Լ
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
	this->tdApi->ReqQryInstrument(&req, ++requestId);//-9	
}
void MyTdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (ret) {
		cerr << "������ :" << pRspInfo->ErrorMsg << endl;
	}
}

void MyTdSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

	//-11�����պ�Լ��Ϣ������append��ȫ�ֺ�Լ��Ϣ������
	md_Instrument_all = md_Instrument_all + pInstrument->InstrumentID + ",";
	if (bIsLast)
	{
		md_Instrument_all = md_Instrument_all.substr(0, md_Instrument_all.length() - 1);
		//cout << md_Instrument_all << endl;
		//-12�����������
		this->mdApi->Init();
	}
}

void MyTdSpi::OnFrontDisconnected(int nReason)
{
	
}

void MyTdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

