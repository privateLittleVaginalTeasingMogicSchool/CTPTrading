#include "Trade.h"
#include "TraderSpi.h"

void InitTrade()
{
	tdapi = CThostFtdcTraderApi::CreateFtdcTraderApi("./tdflow/");
	tdspi = new TdSpi;
	tdapi->RegisterSpi(tdspi);
	tdapi->SubscribePublicTopic(THOST_TE_RESUME_TYPE::THOST_TERT_QUICK);
	tdapi->SubscribePrivateTopic(THOST_TE_RESUME_TYPE::THOST_TERT_QUICK);
	tdapi->RegisterFront(FRONTADD_TD);
	tdapi->Init();
}
