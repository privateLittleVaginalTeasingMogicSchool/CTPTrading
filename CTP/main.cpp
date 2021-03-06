#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "thostmduserapi.lib")
#pragma comment(lib, "thosttraderapi.lib")

#include "Common.h"
#include "Query.h"
#include "Trade.h"
#include "price.h"
#include "command.h"
#include "EA.h"

#include<iomanip>
#include<vector>
#include<array>


int nMdRequestID = 0;
int nTdRequestID = 0;
CThostFtdcDepthMarketDataField MarketData;
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
bool mdlogin;
bool tdlogin;
char* ppInstrumentID[1] = { "au1706" };
int iInstrumentID = 1;
std::vector<TThostFtdcTradeIDType> trade_orders;
Logger lgr("log.txt");
extern bool EAEnabled = false;

/*
	线程0：报价更新
	线程1：接受命令
	线程2：获取持仓量
	线程3：EA线程
	线程4：
*/
std::vector<std::thread> threads(5);

bool output_mutex = false;

//int main()
//{
//	system("mode con:cols=120  lines=52");
//	InitDisplayBuffer();
//	FirstPrintDisplayBuffer();
//	threads[0] = std::thread(command::thread_work);
//	//threads[1] = std::thread(price::thread_work);
//	threads[2] = std::thread(PrintDisplayBuffer);
//	threads[0].join();
//	//threads[1].join();
//	threads[2].join();
//}

int main()
{
	InitScreen();
	InitQuery();
	while (!mdlogin);
	InitTrade();
	while (!tdlogin);
	mdapi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
	threads[0] = std::thread(price::thread_work);
	threads[1] = std::thread(command::thread_work);
	threads[2] = std::thread(PrintDisplayBuffer);
	threads[3] = std::thread(EA);
	Sleep(1000);
	threads[0].join();
	threads[1].join();
	threads[2].join();
	threads[3].join();
	return 0;
}
