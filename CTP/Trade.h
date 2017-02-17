#pragma once

#include "TraderSpi.h"

void InitTrade();
void OrderSend(const char* instrument_id, char type, char direction, int volume);
