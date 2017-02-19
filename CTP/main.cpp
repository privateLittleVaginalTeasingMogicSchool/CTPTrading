#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "thostmduserapi.lib")
#pragma comment(lib, "thosttraderapi.lib")

#include "Common.h"
#include "Query.h"
#include "Trade.h"

#include<iomanip>
#include<vector>


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
const char* XCHGER = "SHFE";
CThostFtdcMdApi* mdapi;
CThostFtdcTraderApi* tdapi;
MdSpi* mdspi;
TdSpi* tdspi;
bool mdlogin = false;
bool tdlogin = false;
char* ppInstrumentID[1] = { "au1706" };
int iInstrumentID = 1;
std::vector<TThostFtdcTradeIDType> trade_orders;
Logger lgr("log.txt");



int main()
{
	InitScreen();
	InitQuery();
	while (!mdlogin);
	InitTrade();
	while (!tdlogin);
	mdapi->SubscribeMarketData(ppInstrumentID, iInstrumentID);

	SleepFor(1000);
	//DisplayOrders();
	
	while (true)
	{
		OrderSend(ppInstrumentID[0], THOST_FTDC_OF_CloseToday, THOST_FTDC_D_Sell, 1);
		SleepFor(500);
		StoreCursorPosition();
		SetCursorPosition(95, 1);
		SetTextColor(NULL, FOREGROUND_RED);
		std::cout << std::fixed;
		std::cout << std::setprecision(2) << MarketData->AskPrice1 << "   " << MarketData->AskVolume1 << "   " << std::endl;
		SetCursorPosition(95, 3);
		std::cout << std::setprecision(2) << MarketData->BidPrice1 << "   " << MarketData->BidVolume1 << "   " << std::endl;
		RestoreTextColor();
		RestoreCursorPosition();
	}
	return 0;
}
