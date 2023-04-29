#include <iostream>
#include <ctime>

#include "Logger.h"

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

Logger::Logger()
{
	logfile.open("modulo.log", std::ios::out | std::ios::app);
}

Logger::~Logger()
{
	logfile.close();
}

Logger& Logger::getLogger()
{
	static Logger logger;
	return logger;
}

void Logger::info(std::string message)
{
	logfile << "[" << time_stamp() << "] [Info] " << message << std::endl;
}

void Logger::warn(std::string message)
{
	logfile << "[" << time_stamp() << "] [Warn] " << message << std::endl;
}

void Logger::error(std::string message)
{
	logfile << "[" << time_stamp() << "] [Error] " << message << std::endl;
}
