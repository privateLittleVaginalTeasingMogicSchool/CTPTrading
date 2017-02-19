#pragma once

#include "Common.h"

class command
{
public:
	static void thread_work();
	static void analyze_command();
	static COORD coord;
	static bool can_input;
	static char buffer[1024];
	static char* pbuf;
};