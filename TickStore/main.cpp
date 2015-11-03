#include <iostream>
#include <string>
#include "MyMdSpi.h"
#include "ThostFtdcTraderApi.h"
#include "MyTdSpi.h"

#include <windows.h>

using namespace std;

int requestId=0;
string md_Instrument_all;
char * brokerID = "9999";
char * userId = "039198";
char * passwd = "123456";
char * MDAddress = "tcp://180.168.146.187:10010";
char * TDAddress = "tcp://180.168.146.187:10000";

int main(int argc, char* argv[])
{
	string path;
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
	path=".\\Contracts\\";
	if (path.size()<1)
	{
		//参数有误,退出程序
		cout << "抱歉,请在启动程序前使用 --path Path 指示存储路径" << endl;
	}
	else
	{
		//-1:实例化行情订阅
		MyMdSpi *mdSpi = NULL;
		CThostFtdcMdApi *mdApi = CThostFtdcMdApi::CreateFtdcMdApi(".\\MdTmp\\");
		mdApi->RegisterSpi(mdSpi= new MyMdSpi(mdApi));
		mdApi->RegisterFront(MDAddress);

		//-2:实例化交易对象
		MyTdSpi *tdSpi = NULL;
		CThostFtdcTraderApi *tdApi=CThostFtdcTraderApi::CreateFtdcTraderApi(".\\TdTmp\\");
		tdApi->RegisterSpi(tdSpi=new MyTdSpi(tdApi,mdApi,mdSpi));
		tdApi->SubscribePublicTopic(THOST_TERT_RESTART);
		tdApi->SubscribePrivateTopic(THOST_TERT_QUICK);
		tdApi->RegisterFront(TDAddress);

		tdApi->Init();
		tdApi->Join();
	}

	getchar();
	return 0;
}