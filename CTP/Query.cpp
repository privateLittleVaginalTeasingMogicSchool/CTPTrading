#include"Query.h"

char* Query::FRONTADD = "tcp://180.168.146.187:10010";

Query::Query()
{
	// Empty
}

void Query::Init()
{
	_mdapi = CThostFtdcMdApi::CreateFtdcMdApi();
	_mdspi = new QuerySpi(&(this->MarketData));
	_mdapi->RegisterSpi(_mdspi);
	_mdapi->RegisterFront(FRONTADD);
	_mdapi->Init();
}



Query::~Query()
{
	if (_mdspi)
	{
		delete _mdspi;
		_mdspi = nullptr;
	}
}

void Query::SubscribeMarketData(char * ppInstrumentID[], int nCount)
{
	_mdapi->SubscribeMarketData(ppInstrumentID, nCount);
}

void Query::UnSubscribeMarketData(char * ppInstrumentID[], int nCount)
{
	_mdapi->UnSubscribeMarketData(ppInstrumentID, nCount);
}
