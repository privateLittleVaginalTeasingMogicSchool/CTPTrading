#define _CRT_SECURE_NO_WARNINGS

#include "Logger.h"
#include "Common.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <time.h>


Logger::Logger(const char* fpath)
	:_os(std::cerr.rdbuf())
{
	_of.open(fpath, std::ios::app);
	_line_cnt = 0;
}

Logger::~Logger()
{
	_of.close();
}

Logger& Logger::operator << (const char* str)
{
	_Get_Output_Mutex
	_os << str;
	_of << str;
	_Release_Output_Mutex
	return (*this);
}

Logger& Logger::operator << (double num)
{
	_Get_Output_Mutex
	_os << num;
	_of << num;
	_Release_Output_Mutex
	return (*this);
}

Logger& Logger::operator << (int num)
{
	_Get_Output_Mutex
	_os << num;
	_of << num;
	_Release_Output_Mutex
	return (*this);
}

Logger& Logger::operator << (char c)
{
	_Get_Output_Mutex
	_os << c;
	_of << c;
	_Release_Output_Mutex
	return (*this);
}

Logger& Logger::operator<<(Logger& (__cdecl *pfunc)(Logger&))
{
	return ((*pfunc)(*this));
}

Logger& Logger::endl(Logger& logger)
{
	_Get_Output_Mutex
	logger._line_cnt++;
	std::endl(logger._os);
	std::endl(logger._of);
	if (logger._line_cnt >= 45)
	{
		logger._line_cnt = 0;
		system("cls");
		InitScreen();
	}
	_Release_Output_Mutex
	return (logger);
}

Logger& Logger::_2point(Logger& logger)
{
	_Get_Output_Mutex
	std::fixed(logger._os);
	(*std::setprecision(2)._Pfun)(logger._os, 2);
	std::fixed(logger._of);
	(*std::setprecision(2)._Pfun)(logger._of, 2);
	_Release_Output_Mutex
	return (logger);
}

Logger& Logger::t(Logger& logger)
{
	_Get_Output_Mutex
	time_t now = time(NULL);
	char* nows = ctime(&now);
	nows[10] = '[';
	nows[19] = ']';
	nows[20] = ' ';
	nows[21] = 0;
	logger._os << nows + 10;
	logger._of << nows + 10;
	_Release_Output_Mutex
	return logger;
}