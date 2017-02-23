#define _CRT_SECURE_NO_WARNINGS

#include "Logger.h"
#include "Common.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <time.h>


Logger::Logger(const char* fpath)
{
	_of.open(fpath, std::ios::app);
}

Logger::~Logger()
{
	_of.close();
}

Logger& Logger::operator << (const char* str)
{
	_Get_Output_Mutex
	info.append(str);
	_of << str;
	_Release_Output_Mutex
	return (*this);
}

Logger& Logger::operator << (double num)
{
	_Get_Output_Mutex
	std::stringstream ss;
	ss << num;
	info.append(ss.str());
	_of << num;
	_Release_Output_Mutex
	return (*this);
}

Logger& Logger::operator << (int num)
{
	_Get_Output_Mutex
	std::stringstream ss;
	ss << num;
	info.append(ss.str());
	_of << num;
	_Release_Output_Mutex
	return (*this);
}

Logger& Logger::operator << (char c)
{
	_Get_Output_Mutex
	info.push_back(c);
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
	NewPrompt(logger.info);
	std::endl(logger._of);
	logger.info = "";
	_Release_Output_Mutex
	return (logger);
}

Logger& Logger::_2point(Logger& logger)
{
	_Get_Output_Mutex
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
	logger.info.append(nows + 10);
	logger._of << nows + 10;
	_Release_Output_Mutex
	return logger;
}