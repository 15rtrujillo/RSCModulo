#include <iostream>
#include <ctime>

#include "RLogger.h"

// Helper functions
std::tm localtime_xp(std::time_t timer)
{
	std::tm bt{};
#ifdef _WIN32
	localtime_s(&bt, &timer);
#else 
	localtime_r(&timer, &bt);
#endif
	return bt;
}

std::string time_stamp(const std::string& fmt = "%F %T")
{
	std::tm bt = localtime_xp(std::time(0));
	char buf[64];
	return { buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
}

RLogger::RLogger()
{
	logfile.open("modulo.log", std::ios::out | std::ios::app);
}

RLogger::~RLogger()
{
	logfile.close();
}

void RLogger::info(std::string message)
{
	logfile << "[" << time_stamp() << "] [Info] " << message << std::endl;
}

void RLogger::warn(std::string message)
{
	logfile << "[" << time_stamp() << "] [Warn] " << message << std::endl;
}

void RLogger::error(std::string message)
{
	logfile << "[" << time_stamp() << "] [Error] " << message << std::endl;
}