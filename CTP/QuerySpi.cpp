#include"QuerySpi.h"

#include<memory.h>

const char* USERID = "079056";
const char* PASSWD = "123456";
const char* BROKER = "9999";

QuerySpi::QuerySpi(CThostFtdcDepthMarketDataField* dstAdd)
{
	_dstAdd = dstAdd;
}

void QuerySpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	memcpy(_dstAdd, pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
}

void QuerySpi::OnFrontConnected()
{

}

void QuerySpi::OnFrontDisconnected(int nReason)
{

}

void QuerySpi::OnHeartBeatWarning(int nTimeLapse)
{
}

void QuerySpi::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void QuerySpi::OnRspUserLogout(CThostFtdcUserLogoutField * pUserLogout, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void QuerySpi::OnRspError(CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void QuerySpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void QuerySpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}
