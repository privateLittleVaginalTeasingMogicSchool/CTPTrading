#include "Common.h"
#include "price.h"

#include<iomanip>

COORD price::coord;

void price::thread_work()
{
	while (true)
	{
		SleepFor(500);
		_Get_Output_Mutex
		StoreCursorPosition(&coord);
		SetCursorPosition(95, 1);
		SetTextColor(NULL, FOREGROUND_RED);
		std::cout << std::fixed;
		std::cout << std::setprecision(2) << MarketData->AskPrice1 << "   " << MarketData->AskVolume1 << "   " << std::endl;
		SetCursorPosition(95, 3);
		std::cout << std::setprecision(2) << MarketData->BidPrice1 << "   " << MarketData->BidVolume1 << "   " << std::endl;
		RestoreTextColor();
		RestoreCursorPosition(&coord);
		_Release_Output_Mutex
	}
}
