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

void InitScreen()
{
	StoreCursorPosition();
	SetCursorPosition(95, 0);
	std::cout << "Ask: ";
	SetCursorPosition(95, 1);
	std::cout << "-----------";
	SetCursorPosition(95, 2);
	std::cout << "Bid: ";
	RestoreCursorPosition();
}

int main()
{
	InitScreen();
	InitQuery();
	while (!mdlogin);
	InitTrade();
	while (!tdlogin);
	mdapi->SubscribeMarketData(ppInstrumentID, iInstrumentID);

	SleepFor(1000);
	OrderSend(ppInstrumentID[0], THOST_FTDC_OF_Open, THOST_FTDC_D_Buy, 1);
	
	while (true)
	{
		SleepFor(500);
		StoreCursorPosition();
		SetCursorPosition(100, 0);
		SetTextColor(NULL, FOREGROUND_RED);
		std::cout << MarketData->AskPrice1 << std::endl;
		SetCursorPosition(100, 2);
		std::cout << MarketData->BidPrice1 << std::endl;
		RestoreTextColor();
		RestoreCursorPosition();
	}
	return 0;
}
