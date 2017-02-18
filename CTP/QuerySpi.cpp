#define _CRT_SECURE_NO_WARNINGS

#include"QuerySpi.h"

#include<memory.h>
#include<iostream>
#include<chrono>
#include<thread>

void MdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo,
	int nRequestID, bool bIsLast)
{
	std::cerr << "[md]Error: ";
	IsErrorRspInfo(pRspInfo);
	std::cerr << std::endl;
}

void MdSpi::OnFrontDisconnected(int nReason)
{
	std::cerr << "[md]Front Disconnected... ";
	std::cerr << "Reason: " << nReason << std::endl;
}

void MdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	std::cerr << "[md]HeartBeatWarning: ";
	std::cerr << "nTimerLapse = " << nTimeLapse << std::endl;
}

void MdSpi::OnFrontConnected()
{
	mdlogin = false;
	std::cerr << "[md]Front Connected..." << std::endl;
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
	std::cerr << "[md]Send Login Request... " << ((iResult == 0) ? "Successed" : "Failed") << std::endl;
}

void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		mdlogin = true;
		///获取当前交易日
		std::cerr << "[md]Date: " << mdapi->GetTradingDay() << std::endl;
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
	memcpy(MarketData, pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
}


bool MdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		std::cerr << "[md]ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg;
	return bResult;
}