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
<<<<<<< HEAD
	//-3:�뽻�׷�������������

	cerr << "�뽻�׷��������ֳɹ�" << endl;
=======
	//-3:与交易服务器建立连接
	cerr << "Trader与交易服务器握手成功" << endl;
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
	//-4:�ȴ���½���
	if (pRspInfo->ErrorID==0)
	{
		cout << "���׶˳ɹ���¼" << endl;
		//-5:���㵥ȷ��	
=======
	//-4:等待登陆结果
	if (pRspInfo->ErrorID==0)
	{
		cout << "Trader 登录成功" << endl;
		//-5:结算单确认	
>>>>>>> origin/master
		ReqSettlementInfoConfirm();	
		QryAllInstrument();
	}
	else
	{
<<<<<<< HEAD
		cout << "���׶˵�¼ʧ��"<<pRspInfo->ErrorMsg << endl;
=======
		cout << "Trader 登录失败"<<pRspInfo->ErrorMsg << endl;
>>>>>>> origin/master
	}
}
void MyTdSpi::ReqSettlementInfoConfirm()
{
<<<<<<< HEAD
	//-5:���㵥ȷ��

=======
	//-5:结算单确认
>>>>>>> origin/master
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, brokerID);
	strcpy(req.InvestorID, userId);
	int ret = this->tdApi->ReqSettlementInfoConfirm(&req, ++requestId);	
<<<<<<< HEAD
	cerr << "���ͽ��㵥ȷ��..." << ((ret == 0) ? "�ɹ�" : "ʧ��") << endl;
=======
	cerr << " REQ | 发送结算单确认..." << ((ret == 0) ? "成功" : "失败") << endl;
>>>>>>> origin/master
	
}
void MyTdSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	//std::cerr << "--->>> " << __FUNCTION__ << std::endl;

<<<<<<< HEAD
	//-6:�ȴ����һ�ʽ��㵥��Ӧ
	if (pRspInfo->ErrorID==0)
	{
		cout << "����ȷ�����" << endl;
		//-7:��ѯ����
=======
	//-6:等待最后一笔结算单回应
	if (pRspInfo->ErrorID==0)
	{
		//Sleep(3000);
		cout << "结算确认完成" << endl;
		//-7:
>>>>>>> origin/master
		ReqQryOrder();
		
	}
}

void MyTdSpi::ReqQryOrder()
{
<<<<<<< HEAD
	//-7����ѯ����
=======
	//-7：查询报单
>>>>>>> origin/master
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
<<<<<<< HEAD
		//-8:��ѯ���к�Լ
=======
		//-8:查询所有合约,查询所有合约
>>>>>>> origin/master
		QryAllInstrument();		
	}
}
void MyTdSpi::QryAllInstrument() {
<<<<<<< HEAD
	//-10:��ѯ���к�Լ
=======
	//-9:查询所有合约
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
		cerr << "������ :" << pRspInfo->ErrorMsg << endl;
=======
		cerr << "错误反馈 :" << pRspInfo->ErrorMsg << endl;
>>>>>>> origin/master
	}
}

void MyTdSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

<<<<<<< HEAD
	//-11�����պ�Լ��Ϣ������append��ȫ�ֺ�Լ��Ϣ������
=======
	//-10：接收合约
>>>>>>> origin/master
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

