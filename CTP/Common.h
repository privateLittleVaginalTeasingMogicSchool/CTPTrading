#pragma once

#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include<chrono>
#include<thread>

class MdSpi;
class TdSpi;

extern int nMdRequestID;
extern int nTdRequestID;
extern CThostFtdcDepthMarketDataField* MarketData;
extern char* FRONTADD_MD;
extern char* FRONTADD_TD;
extern TThostFtdcFrontIDType FRONTID;
extern TThostFtdcSessionIDType SESSION;
extern TThostFtdcOrderRefType ORDER_REF;
extern const char* USERID;
extern const char* PASSWD;
extern const char* BROKER;
extern CThostFtdcMdApi* mdapi;
extern MdSpi* mdspi;
extern CThostFtdcTraderApi* tdapi;
extern TdSpi* tdspi;
extern bool mdlogin;
extern bool tdlogin;
extern char* ppInstrumentID[1];
extern int iInstrumentID;

void SleepFor(int milliseconds);