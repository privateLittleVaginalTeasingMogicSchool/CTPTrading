#define _CRT_SECURE_NO_WARNINGS

#include "Trade.h"
#include "TradeSpi.h"

#include <iostream>

void InitTrade()
{
	//system("md .\\tdflow");
	tdapi = CThostFtdcTraderApi::CreateFtdcTraderApi("./tdflow/");
	tdspi = new TdSpi;
	tdapi->RegisterSpi(tdspi);
	tdapi->SubscribePublicTopic(THOST_TE_RESUME_TYPE::THOST_TERT_QUICK);
	tdapi->SubscribePrivateTopic(THOST_TE_RESUME_TYPE::THOST_TERT_QUICK);
	tdapi->RegisterFront(FRONTADD_TD);
	tdapi->Init();
}

void OrderSend(const char* instrument_id, char type, char direction, int volume)
{
	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));
	///经纪公司代码
	strcpy(req.BrokerID, BROKER);
	///投资者代码
	strcpy(req.InvestorID, USERID);
	///合约代码
	strcpy(req.InstrumentID, instrument_id);
	///报单引用
	//strcpy(req.OrderRef, ORDER_REF);
	///用户代码
	//	TThostFtdcUserIDType	UserID;
	///报单价格条件: 限价
	req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	///买卖方向: 
	req.Direction = direction;
	///组合开平标志: 开仓
	req.CombOffsetFlag[0] = type;
	///组合投机套保标志
	req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
	///价格
	req.LimitPrice = (direction == THOST_FTDC_D_Buy) ? MarketData->AskPrice1 : MarketData->BidPrice1;
	///数量: 1
	req.VolumeTotalOriginal = volume;
	///有效期类型: 当日有效
	req.TimeCondition = THOST_FTDC_TC_GFD;
	///GTD日期
	//	TThostFtdcDateType	GTDDate;
	///成交量类型: 任何数量
	req.VolumeCondition = THOST_FTDC_VC_AV;
	///最小成交量: 1
	req.MinVolume = 1;
	///触发条件: 立即
	req.ContingentCondition = THOST_FTDC_CC_Immediately;
	///止损价
	//req.StopPrice = stop_price;
	///强平原因: 非强平
	req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	///自动挂起标志: 否
	req.IsAutoSuspend = 0;
	///业务单元
	//	TThostFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	//	TThostFtdcRequestIDType	RequestID;
	///用户强评标志: 否
	req.UserForceClose = 0;

	int iResult = tdapi->ReqOrderInsert(&req, ++nTdRequestID);
	lgr << Log::t << "[td]Requst Order Insert... " << ((iResult == 0) ? "Successed" : "Failed") << Log::endl;
}

int GetHolding()
{
	return 0;
}

void OrderClose(const char* instrument_id, char direction, int volume)
{
	//OrderSend(instrument_id, THOST_FTDC_OF_Close)
}

void DisplayOrders()
{
	tdspi->ReqQryInvestorPositionDetail();
}