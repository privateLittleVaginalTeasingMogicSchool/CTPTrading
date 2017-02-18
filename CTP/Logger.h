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
	

private:
	std::ostream _os;
	std::ofstream _of;
};

typedef Logger Log;
