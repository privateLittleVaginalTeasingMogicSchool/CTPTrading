#define _CRT_SECURE_NO_WARNINGS

#include"QuerySpi.h"

#include<memory.h>
#include<iostream>
#include<chrono>
#include<thread>

void MdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo,
	int nRequestID, bool bIsLast)
{
	lgr << Log::t << "[md]Error: ";
	IsErrorRspInfo(pRspInfo);
	lgr << Log::t << Log::endl;
}

void MdSpi::OnFrontDisconnected(int nReason)
{
	lgr << Log::t << "[md]Front Disconnected... ";
	lgr << Log::t << "Reason: " << nReason << Log::endl;
}

void MdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	lgr << Log::t << "[md]HeartBeatWarning: ";
	lgr << Log::t << "nTimerLapse = " << nTimeLapse << Log::endl;
}

void MdSpi::OnFrontConnected()
{
	lgr << Log::t << "[md]Front Connected..." << Log::endl;
	///用户登录请求
	ReqUserLogin();
}

void MdSpi::ReqUserLogin()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER);
	strcpy(req.UserID, USERID);
	strcpy(req.Password, PASSWD);
	int iResult = mdapi->ReqUserLogin(&req, ++nMdRequestID);
	lgr << Log::t << "[md]Send Login Request... " << ((iResult == 0) ? "Successed" : "Failed") << Log::endl;
}

void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		mdlogin = true;
		///获取当前交易日
		lgr << Log::t << "[md]Date: " << mdapi->GetTradingDay() << Log::endl;
	}
}

void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	
}

void MdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	
}

void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	memcpy(&MarketData, pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
}


bool MdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		lgr << Log::t << "[md]ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg;
	return bResult;
}