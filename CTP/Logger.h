#pragma once

#include <iostream>
#include <fstream>
#include <string>


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
	std::ofstream _of;
	std::string info;
};

typedef Logger Log;
