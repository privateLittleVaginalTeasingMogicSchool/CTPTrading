// testTraderApi.cpp : 定义控制台应用程序的入口点。
//

#include ".\ThostTraderApi\ThostFtdcMdApi.h"
#include "MdSpi.h"

#include<iostream>
#include<Windows.h>
using namespace std;

// UserApi对象
CThostFtdcMdApi* pUserApi;

// 配置参数
char FRONT_ADDR[] = "tcp://180.168.146.187:10010";		// 前置地址
TThostFtdcBrokerIDType	BROKER_ID = "9999";				// 经纪公司代码
TThostFtdcInvestorIDType INVESTOR_ID = "082477";			// 投资者代码
TThostFtdcPasswordType  PASSWORD = "qidl2015";			// 用户密码
char *ppInstrumentID[] = {"au1706"};			// 行情订阅列表
int iInstrumentID = 1;// 行情订阅数量
extern double lastprice = 0;

// 请求编号
int iRequestID = 0;

void main(void)
{
	// 初始化UserApi
	pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();			// 创建UserApi
	CMdSpi* pUserSpi = new CMdSpi();
	pUserApi->RegisterSpi(pUserSpi);						// 注册事件类
	pUserApi->RegisterFront(FRONT_ADDR);					// connect
	pUserApi->Init();

	pUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
	while (!pUserSpi->_login);
	while (1)
	{
		cout << ppInstrumentID[0] << ": " << lastprice << endl;
		Sleep(1000);
	}

	pUserApi->Join();
//	pUserApi->Release();
}