#pragma once

#include"QuerySpi.h"

#include<vector>

class Query
{
public:
	Query();
	void Init();
	~Query();

	void SubscribeMarketData(char *ppInstrumentID[], int nCount);
	void UnSubscribeMarketData(char *ppInstrumentID[], int nCount);

	CThostFtdcDepthMarketDataField MarketData;

private:
	CThostFtdcMdApi* _mdapi;
	CThostFtdcMdSpi* _mdspi;
	static char* FRONTADD;

	std::vector<char*> _instruments;
};