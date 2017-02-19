#pragma once

#include "Common.h"
#include <vector>

class command
{
public:
	static void thread_work();
	static void analyze_command();
	static COORD coord;
	static bool can_input;
	static bool can_dispatch;
	static char buffer[1024];
	static char* pbuf;

	static std::thread* Analyzer;
};