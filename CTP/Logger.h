#pragma once

#include <iostream>
#include <fstream>


class Logger
{
public:
	Logger(const char* fpath);
	~Logger();
	Logger& operator << (const char* str);
	Logger& operator << (double num);
	Logger& operator << (int num);
	Logger& operator << (char c);
	Logger& operator<<(Logger& (__cdecl *_Pfn)(Logger&));
	static Logger& endl(Logger& logger);
	static Logger& _2point(Logger& logger);
	static Logger& t(Logger& logger);
private:
	std::ostream _os;
	std::ofstream _of;
	int _line_cnt;
};

typedef Logger Log;
