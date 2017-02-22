#define _CRT_SECURE_NO_WARNINGS

#include "Common.h"
#include "price.h"

#include <iomanip>
#include <sstream>

COORD price::coord;

void chg_price()
{
	std::stringstream ask;
	ask << "Ask: " << std::fixed << std::setprecision(2) << MarketData->AskPrice1;
	int asklen = ask.str().size();
	ask	<< std::setw(20 - asklen) << std::right << MarketData->AskVolume1;
	info[1] = ask.str();
	std::stringstream bid;
	bid << "Bid: " << std::fixed << std::setprecision(2) << MarketData->BidPrice1;
	int bidlen = bid.str().size();
	bid	<< std::setw(20 - bidlen) << std::right << MarketData->BidVolume1;
	info[2] = bid.str();
}

void price::thread_work()
{
	while (true)
	{
		SleepFor(500);
		_Get_Output_Mutex
		chg_price();
		_Release_Output_Mutex
	}
}
