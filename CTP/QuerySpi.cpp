#define _CRT_SECURE_NO_WARNINGS

#include"QuerySpi.h"

#include<memory.h>
#include<iostream>
#include<Windows.h>

void MdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo,
	int nRequestID, bool bIsLast)
{
	std::cerr << "--->>> " << "OnRspError" << std::endl;
	IsErrorRspInfo(pRspInfo);
}

void MdSpi::OnFrontDisconnected(int nReason)
{
	std::cerr << "--->>> " << "OnFrontDisconnected" << std::endl;
	std::cerr << "--->>> Reason = " << nReason << std::endl;
}

void MdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	std::cerr << "--->>> " << "OnHeartBeatWarning" << std::endl;
	std::cerr << "--->>> nTimerLapse = " << nTimeLapse << std::endl;
}

void MdSpi::OnFrontConnected()
{
	login = false;
	std::cerr << "--->>> " << "OnFrontConnected" << std::endl;
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
	int iResult = mdapi->ReqUserLogin(&req, ++nRequestID);
	std::cerr << "--->>> 发送用户登录请求: " << ((iResult == 0) ? "成功" : "失败") << std::endl;

}

void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::cerr << "--->>> " << "OnRspUserLogin" << std::endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		login = true;
		///获取当前交易日
		std::cerr << "--->>> 获取当前交易日 = " << mdapi->GetTradingDay() << std::endl;
	}
}

void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::cerr << "OnRspSubMarketData" << std::endl;
}

void MdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::cerr << "OnRspUnSubMarketData" << std::endl;
}

void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	memcpy(MarketData, pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
}

bool MdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// 如果ErrorID != 0, 说明收到了错误的响应
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		std::cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
	return bResult;
}