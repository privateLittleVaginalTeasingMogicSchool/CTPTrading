#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "thostmduserapi.lib")
#pragma comment(lib, "thosttraderapi.lib")

#include "Query.h"
//#include "Trader.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "Query.h"
#ifdef _WIN32
#include<Windows.h>
#endif

int nRequestID;
CThostFtdcDepthMarketDataField* MarketData;
char* FRONTADD = "tcp://180.168.146.187:10010";
const char* USERID = "082477";
const char* PASSWD = "123456";
const char* BROKER = "9999";
CThostFtdcMdApi* mdapi;
CThostFtdcMdSpi* mdspi;
bool login;
char* ppInstrumentID[1] = { "au1706" };
int iInstrumentID = 1;

int main()
{
	InitQuery();
	while (!login);

	mdapi->SubscribeMarketData(ppInstrumentID, iInstrumentID);

	while (true)
	{
		std::cout << MarketData->AskPrice1 << std::endl;
#ifdef _WIN32
		Sleep(1000);
#endif
	}
	return 0;
}
