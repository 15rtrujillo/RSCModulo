#include <fstream>
#include <string>

#ifndef RLOGGER_H
#define RLOGGER_H

/// Used to log important messages out to a log file
class RLogger
{
	friend class LogManager;

private:
	std::ofstream logfile;
	RLogger();
	~RLogger();

public:

	void info(std::string message);

	void warn(std::string message);

	void error(std::string message);
};

#endif