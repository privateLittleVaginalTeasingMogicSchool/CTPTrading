#define _CRT_SECURE_NO_WARNINGS

#include"Query.h"
#include"QuerySpi.h"

void InitQuery()
{
	//system("md .\\mdflow");
	mdapi = CThostFtdcMdApi::CreateFtdcMdApi("./mdflow/");
	
	mdspi = new MdSpi;
	mdapi->RegisterSpi(mdspi);
	mdapi->RegisterFront(FRONTADD_MD);
	mdapi->Init();

	memset(&MarketData, 0, sizeof(MarketData));
}

void UpdatePrice()
{
	SetCursorPosition(30, 0);
}