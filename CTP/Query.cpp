#define _CRT_SECURE_NO_WARNINGS

#include"Query.h"
#include"QuerySpi.h"

void InitQuery()
{
	mdapi = CThostFtdcMdApi::CreateFtdcMdApi("./mdflow/");
	
	mdspi = new MdSpi;
	mdapi->RegisterSpi(mdspi);
	mdapi->RegisterFront(FRONTADD);
	mdapi->Init();

	nRequestID = 0;
	login = false;

	MarketData = new CThostFtdcDepthMarketDataField;
	memset(MarketData, 0, sizeof(MarketData));
}