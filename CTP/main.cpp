#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "thostmduserapi.lib")
#pragma comment(lib, "thosttraderapi.lib")

#include "Common.h"
#include "Query.h"
#include "Trade.h"
#include<string>


int nMdRequestID = 0;
int nTdRequestID = 0;
CThostFtdcDepthMarketDataField* MarketData;
char* FRONTADD_MD = "tcp://180.168.146.187:10010";
char* FRONTADD_TD = "tcp://180.168.146.187:10000";
int SESSION;
int FRONTID;
TThostFtdcOrderRefType ORDER_REF;
const char* USERID = "079056";
const char* PASSWD = "123456";
const char* BROKER = "9999";
CThostFtdcMdApi* mdapi;
CThostFtdcTraderApi* tdapi;
MdSpi* mdspi;
TdSpi* tdspi;
bool mdlogin = false;
bool tdlogin = false;
char* ppInstrumentID[1] = { "au1706" };
int iInstrumentID = 1;

int main()
{
	InitQuery();
	while (!mdlogin);
	InitTrade();
	while (!tdlogin);
	mdapi->SubscribeMarketData(ppInstrumentID, iInstrumentID);

	SleepFor(1000);
	tdspi->ReqOrderInsert(ppInstrumentID[0], THOST_FTDC_D_Buy, MarketData->AskPrice1);

	while (true)
	{
		SleepFor(1000);
		//std::cout << MarketData->AskPrice1 << std::endl;
	}
	return 0;
}
