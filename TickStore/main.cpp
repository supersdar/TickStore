#include <iostream>
#include <string>
#include "MyMdSpi.h"
#include "ThostFtdcTraderApi.h"
#include "MyTdSpi.h"

#include <windows.h>

using namespace std;

//请求编号
int requestId=0;
//存储所有合约
string md_Instrument_all;//每个合约之间用逗号隔开
//tick数据的存储路径
string path;
//期货公司编号
char * brokerID = "9999";
//客户账号
char * userId = "039198";
//密码
char * passwd = "123456";
//行情服务器地址
char * MDAddress = "tcp://180.168.146.187:10010";
//交易服务器地址
char * TDAddress = "tcp://180.168.146.187:10000";

int main(int argc, char* argv[])
{
	//读取启动参数
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
	//未设置存储路径，设置一个默认路径
	if (path.size()<1)
	{
		cout << "未使用 --path Path 指示存储路径，tick数据将默认存储到Contracts" << endl;
		path = ".\\Contracts\\";
	}

	//-1:实例化行情订阅
	MyMdSpi *mdSpi = NULL;
	CThostFtdcMdApi *mdApi = CThostFtdcMdApi::CreateFtdcMdApi(".\\MdTmp\\");//请确保运行目录中有MdTmp
	mdApi->RegisterSpi(mdSpi= new MyMdSpi(mdApi));
	mdApi->RegisterFront(MDAddress);

	//-2:实例化交易对象
	MyTdSpi *tdSpi = NULL;
	CThostFtdcTraderApi *tdApi=CThostFtdcTraderApi::CreateFtdcTraderApi(".\\TdTmp\\");//请确保运行目录中有TdTmp
	tdApi->RegisterSpi(tdSpi=new MyTdSpi(tdApi,mdApi,mdSpi));
	tdApi->SubscribePublicTopic(THOST_TERT_RESTART);
	tdApi->SubscribePrivateTopic(THOST_TERT_QUICK);
	tdApi->RegisterFront(TDAddress);

	//启动交易对象
	tdApi->Init();
	tdApi->Join();

	getchar();
	return 0;
}