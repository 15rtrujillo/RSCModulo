#include <fstream>
#include <string>

#ifndef RLOGGER_H
#define RLOGGER_H

/// Used to log important messages out to a log file
class RLogger
{
private:
	std::ofstream logfile;

protected:

public:
	RLogger();
	~RLogger();

	void info(std::string message);

	void warn(std::string message);

	void error(std::string message);
};

#endif