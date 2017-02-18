#define _CRT_SECURE_NO_WARNINGS

#include "TraderSpi.h"
#include <iostream>
#include <iomanip>

// 流控判断
bool IsFlowControl(int iResult)
{
	return ((iResult == -2) || (iResult == -3));
}

void TdSpi::OnFrontConnected()
{
	std::cerr << "[td]Front Connected..." << std::endl;
	///用户登录请求
	ReqUserLogin();
}

void TdSpi::ReqUserLogin()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER);
	strcpy(req.UserID, USERID);
	strcpy(req.Password, PASSWD);
	int iResult = tdapi->ReqUserLogin(&req, ++nTdRequestID);
	std::cerr << "[td]Send Login Request... " << ((iResult == 0) ? "Successed" : "Failed") << std::endl;
}

void TdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		// 保存会话参数
		FRONTID = pRspUserLogin->FrontID;
		SESSION = pRspUserLogin->SessionID;
		int iNextOrderRef = atoi(pRspUserLogin->MaxOrderRef);
		iNextOrderRef++;
		sprintf(ORDER_REF, "%d", iNextOrderRef);
		///获取当前交易日
		std::cerr << "[td]Date: " << tdapi->GetTradingDay() << std::endl;
		///投资者结算结果确认
		SleepFor(1000);
		ReqSettlementInfoConfirm();
	}
}

void TdSpi::ReqSettlementInfoConfirm()
{
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER);
	strcpy(req.InvestorID, USERID);
	int iResult = tdapi->ReqSettlementInfoConfirm(&req, ++nTdRequestID);
	std::cerr << "[td]Request Settlement Info Confirm... " << ((iResult == 0) ? "Successed" : "Failed") << std::endl;
}

void TdSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		tdlogin = true;
		///请求查询合约
		std::cerr << "[td]Instruments:" << std::endl;
		for (int i = 0;i < iInstrumentID;i++)
		{
			ReqQryInstrument(ppInstrumentID[i]);
		}
	}
}

void TdSpi::ReqQryInstrument(const char* instrument)
{
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.InstrumentID, instrument);
	while (true)
	{
		SleepFor(1000);
		int iResult = tdapi->ReqQryInstrument(&req, ++nTdRequestID);
		if (!IsFlowControl(iResult))
		{
			std::cerr << "[td]Request Query Instrument... " << ((iResult == 0) ? "Successed" : "Failed") << std::endl;
			break;
		}
		else
		{
			std::cerr << "[td]Request Query Instrument... " << "Flow Control" << std::endl;
		}
	} // while
}

void TdSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		std::cerr << "[td]Instrument Id:\t" << pInstrument->InstrumentID << std::endl;
		///请求查询合约
		SleepFor(1000);
		ReqQryTradingAccount();
	}
}

void TdSpi::ReqQryTradingAccount()
{
	CThostFtdcQryTradingAccountField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER);
	strcpy(req.InvestorID, USERID);
	while (true)
	{
		SleepFor(1000);
		int iResult = tdapi->ReqQryTradingAccount(&req, ++nTdRequestID);
		if (!IsFlowControl(iResult))
		{
			std::cerr << "[td]Request Query Trading Account... " << ((iResult == 0) ? "Successed" : "Failed") << std::endl;
			break;
		}
		else
		{
			std::cerr << "[td]Request Query Trading Account... " << "Flow Control" << std::endl;
		}
	} // while
}

void TdSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		std::cerr << std::fixed << std::setprecision(2) << "[td]Balance: " << pTradingAccount->Balance << std::endl;
		std::cerr << std::fixed << std::setprecision(2) << "[td]Available: " << pTradingAccount->Available << std::endl;
		std::cerr << std::fixed << std::setprecision(2) << "[td]Close Profit: " << pTradingAccount->CloseProfit << std::endl;
		std::cerr << std::fixed << std::setprecision(2) << "[td]Position Profit: " << pTradingAccount->PositionProfit << std::endl;
		///请求查询投资者持仓
		SleepFor(1000);
		ReqQryInvestorPosition();
	}
}

void TdSpi::ReqQryInvestorPosition()
{
	CThostFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER);
	strcpy(req.InvestorID, USERID);
	strcpy(req.InstrumentID, ppInstrumentID[0]);
	while (true)
	{
		SleepFor(1000);
		int iResult = tdapi->ReqQryInvestorPosition(&req, ++nTdRequestID);
		if (!IsFlowControl(iResult))
		{
			std::cerr << "[td]Request Query Investor Position... " << ((iResult == 0) ? "Successed" : "Failed") << std::endl;
			break;
		}
		else
		{
			std::cerr << "[td]Request Query Investor Position... " << "Flow Control" << std::endl;
		}
	} // while
}

void TdSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		if (pInvestorPosition)
		{
			std::cerr << "[td]Open Volume:" << pInvestorPosition->OpenVolume << std::endl;
		}
		///报单录入请求
		//ReqOrderInsert(ppInstrumentID[0], THOST_FTDC_D_Buy);
	}
}

//void TdSpi::ReqOrderInsert(const char* instrument_id, char direction, double limit_price, double stop_price)
//{
//	CThostFtdcInputOrderField req;
//	memset(&req, 0, sizeof(req));
//	///经纪公司代码
//	strcpy(req.BrokerID, BROKER);
//	///投资者代码
//	strcpy(req.InvestorID, USERID);
//	///合约代码
//	strcpy(req.InstrumentID, ppInstrumentID[0]);
//	///报单引用
//	//strcpy(req.OrderRef, ORDER_REF);
//	///用户代码
//	//	TThostFtdcUserIDType	UserID;
//	///报单价格条件: 限价
//	req.OrderPriceType = THOST_FTDC_OPT_AnyPrice;
//	///买卖方向: 
//	req.Direction = direction;
//	///组合开平标志: 开仓
//	req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
//	///组合投机套保标志
//	req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
//	///价格
//	req.LimitPrice = 0;
//	///数量: 1
//	req.VolumeTotalOriginal = 1;
//	///有效期类型: 当日有效
//	req.TimeCondition = THOST_FTDC_TC_GFD;
//	///GTD日期
//	//	TThostFtdcDateType	GTDDate;
//	///成交量类型: 任何数量
//	req.VolumeCondition = THOST_FTDC_VC_AV;
//	///最小成交量: 1
//	req.MinVolume = 1;
//	///触发条件: 立即
//	req.ContingentCondition = THOST_FTDC_CC_Immediately;
//	///止损价
//	req.StopPrice = stop_price;
//	///强平原因: 非强平
//	req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
//	///自动挂起标志: 否
//	req.IsAutoSuspend = 0;
//	///业务单元
//	//	TThostFtdcBusinessUnitType	BusinessUnit;
//	///请求编号
//	//	TThostFtdcRequestIDType	RequestID;
//	///用户强评标志: 否
//	req.UserForceClose = 0;
//
//	int iResult = tdapi->ReqOrderInsert(&req, ++nTdRequestID);
//	std::cerr << "[td]Requst Order Insert... " << ((iResult == 0) ? "Successed" : "Failed") << std::endl;
//}

void TdSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::cerr << "[td]Order: #" << pInputOrder->OrderRef << std::endl;
	IsErrorRspInfo(pRspInfo);
}

void TdSpi::ReqOrderAction(CThostFtdcOrderField *pOrder)
{
	static bool ORDER_ACTION_SENT = false;		//是否发送了报单
	if (ORDER_ACTION_SENT)
		return;

	CThostFtdcInputOrderActionField req;
	memset(&req, 0, sizeof(req));
	///经纪公司代码
	strcpy(req.BrokerID, pOrder->BrokerID);
	///投资者代码
	strcpy(req.InvestorID, pOrder->InvestorID);
	///报单操作引用
	//	TThostFtdcOrderActionRefType	OrderActionRef;
	///报单引用
	strcpy(req.OrderRef, pOrder->OrderRef);
	///请求编号
	//	TThostFtdcRequestIDType	RequestID;
	///前置编号
	req.FrontID = FRONTID;
	///会话编号
	req.SessionID = SESSION;
	///交易所代码
	//	TThostFtdcExchangeIDType	ExchangeID;
	///报单编号
	//	TThostFtdcOrderSysIDType	OrderSysID;
	///操作标志
	req.ActionFlag = THOST_FTDC_AF_Delete;
	///价格
	//	TThostFtdcPriceType	LimitPrice;
	///数量变化
	//	TThostFtdcVolumeType	VolumeChange;
	///用户代码
	//	TThostFtdcUserIDType	UserID;
	///合约代码
	strcpy(req.InstrumentID, pOrder->InstrumentID);

	int iResult = tdapi->ReqOrderAction(&req, ++nTdRequestID);
	std::cerr << "--->>> 报单操作请求: " << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << std::endl;
	ORDER_ACTION_SENT = true;
}

void TdSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::cerr << "--->>> " << "OnRspOrderAction" << std::endl;
	IsErrorRspInfo(pRspInfo);
}

///报单通知
void TdSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	std::cerr << "[td]Direction: " << (pOrder->Direction == '0' ? "Buy" : "Sell")
		<< ", Price: " << pOrder->LimitPrice
		<< ", Status: " << pOrder->StatusMsg << std::endl;
}

///成交通知
void TdSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
	std::cerr << "[td]" << pTrade->InstrumentID
		<< " At Price: " << pTrade->Price << ", " 
		<< pTrade->Volume << " Traded" << std::endl;
}

void TdSpi::OnRspQryTrade(
	CThostFtdcTradeField *pTrade,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	if (bIsLast)
	{
		std::cerr << pTrade->TradeDate << " " << pTrade->TradeTime << " "
			<< "#" << pTrade->OrderRef
			<< ((pTrade->Direction == THOST_FTDC_D_Buy) ? " Buy  " : " Sell ")
			<< (pTrade->Volume)
			<< " " << pTrade->InstrumentID << " "
			<< " @ " << std::fixed << std::setprecision(2) << pTrade->Price
			<< pTrade->Volume * ((pTrade->Direction == THOST_FTDC_D_Buy) ? (MarketData->BidPrice1 - pTrade->Price) :
			(pTrade->Price - MarketData->AskPrice1)) << std::endl;
	}
}

void TdSpi::OnRspQryInvestorPositionDetail(
	CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	ReqQryTrade(pInvestorPositionDetail->TradeID);
}

void TdSpi::OnRspQryInvestorPositionCombineDetail(
	CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID, bool bIsLast)
{
	if (bIsLast)
	{
		//std::cout << pInvestorPositionCombineDetail->TradeID << std::endl;
		pInvestorPositionCombineDetail->TradeID;
	}
}

void TdSpi::ReqQryInvestorPositionDetail()
{
	CThostFtdcQryInvestorPositionDetailField QryInvestorPositionDetail;
	strcpy(QryInvestorPositionDetail.BrokerID, BROKER);
	strcpy(QryInvestorPositionDetail.InstrumentID, ppInstrumentID[0]);
	strcpy(QryInvestorPositionDetail.InvestorID, USERID);
	tdapi->ReqQryInvestorPositionDetail(&QryInvestorPositionDetail, ++nTdRequestID);
}

void TdSpi::ReqQryInvestorPositionCombineDetail()
{
	//CThostFtdcQryInvestorPositionCombineDetailField QryInvestorPositionCombineDetail;

}

void TdSpi::ReqQryTrade(const char* trade_id)
{
	CThostFtdcQryTradeField QryTrade;
	strcpy(QryTrade.BrokerID, BROKER);
	strcpy(QryTrade.ExchangeID, XCHGER);
	//strcpy(QryTrade.InstrumentID, ppInstrumentID[0]);
	strcpy(QryTrade.InvestorID, USERID);
	strcpy(QryTrade.TradeID, trade_id);
	tdapi->ReqQryTrade(&QryTrade, ++nTdRequestID);
}

void TdSpi::OnFrontDisconnected(int nReason)
{
	std::cerr << "--->>> " << "OnFrontDisconnected" << std::endl;
	std::cerr << "--->>> Reason = " << nReason << std::endl;
}

void TdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	std::cerr << "--->>> " << "OnHeartBeatWarning" << std::endl;
	std::cerr << "--->>> nTimerLapse = " << nTimeLapse << std::endl;
}

void TdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	IsErrorRspInfo(pRspInfo);
}

bool TdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// 如果ErrorID != 0, 说明收到了错误的响应
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		std::cerr << "[td]ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
	return bResult;
}

bool TdSpi::IsMyOrder(CThostFtdcOrderField *pOrder)
{
	return ((pOrder->FrontID == FRONTID) &&
		(pOrder->SessionID == SESSION) &&
		(strcmp(pOrder->OrderRef, ORDER_REF) == 0));
}

bool TdSpi::IsTradingOrder(CThostFtdcOrderField *pOrder)
{
	return ((pOrder->OrderStatus != THOST_FTDC_OST_PartTradedNotQueueing) &&
		(pOrder->OrderStatus != THOST_FTDC_OST_Canceled) &&
		(pOrder->OrderStatus != THOST_FTDC_OST_AllTraded));
}
