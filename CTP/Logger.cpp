#include "Logger.h"
#include <fstream>
#include <iostream>


Logger::Logger(const char* fpath)
	:_os(std::cerr.rdbuf())
{
	_of.open(fpath, std::ios::app);
}

Logger::~Logger()
{
	_of.close();
	std::cout << std::endl;
}

Logger& Logger::operator << (const char* str)
{
	_os << str;
	_of << str;
	return (*this);
}

Logger& Logger::operator << (double num)
{
	_os << num;
	_of << num;
	return (*this);
}

Logger& Logger::operator << (int num)
{
	_os << num;
	_of << num;
	return (*this);
}

Logger& Logger::operator << (char c)
{
	_os << c;
	_of << c;
	return (*this);
}

Logger& Logger::operator<<(Logger& (__cdecl *pfunc)(Logger&))
{
	return ((*pfunc)(*this));
}

Logger& Logger::endl(Logger& logger)
{
	std::endl(logger._os);
	std::endl(logger._of);
	return (logger);
}