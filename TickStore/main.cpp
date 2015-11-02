#include <iostream>
#include <string>
#include "MyMdSpi.h"
#include "ThostFtdcTraderApi.h"
#include "MyTdSpi.h"

using namespace std;

int requestId=0;
string md_Instrument_all;
char * brokerID = "0081";
char * userId = "00476";
char * passwd = "123456";
char * MDAddress = "tcp://180.168.146.181:10100";
char * TDAddress = "tcp://180.168.146.181:10000";

int main(int argc, char* argv[])
{
	string path;
	//��ȡ����
	for (int i = 0; i < argc; i++)
	{
		cout << argv[i] << endl;
		if (strcmp(argv[i], "--path") == 0)
		{
			if (i + 1 < argc)
			{
				
				path = string(argv[i + 1]);
				//cout<<path;
				break;
			}			
		}
	}
	//��������Ч
	if (path.size()<1)
	{
		//��������,�˳�����
		cout << "��Ǹ,������������ǰʹ�� --path Path ָʾ�洢·��" << endl;
	}
	else
	{
		MyMdSpi *mdSpi = NULL;
		CThostFtdcMdApi *mdApi = CThostFtdcMdApi::CreateFtdcMdApi(".\\MdTmp\\");
		mdApi->RegisterSpi(mdSpi= new MyMdSpi(mdApi));
		mdApi->RegisterFront(MDAddress);

		MyTdSpi *tdSpi = NULL;
		CThostFtdcTraderApi *tdApi=CThostFtdcTraderApi::CreateFtdcTraderApi(".\\TdTmp\\");
		tdApi->RegisterSpi(tdSpi=new MyTdSpi(tdApi));
		tdApi->SubscribePublicTopic(THOST_TERT_RESTART);
		tdApi->SubscribePrivateTopic(THOST_TERT_QUICK);
		tdApi->RegisterFront(TDAddress);



		mdApi->Init();
		tdApi->Join();
	}

	getchar();
	return 0;
}