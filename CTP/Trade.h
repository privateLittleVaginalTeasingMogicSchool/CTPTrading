#pragma once

#include "TradeSpi.h"

void InitTrade();
void OrderSend(const char* instrument_id, char type, char direction, int volume);
void OrderClose(const char* instrument_id, char type, char direction, int volume);
int GetHolding();
void DisplayOrders();
