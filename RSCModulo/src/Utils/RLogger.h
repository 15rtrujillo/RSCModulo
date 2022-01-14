#include <fstream>
#include <string>

#ifndef RLOGGER_H
#define RLOGGER_H

/// <summary>
/// Used to log important messages out to a log file
/// </summary>
class RLogger
{
	friend class LogManager;

private:
	std::ofstream logfile;
	RLogger();
	~RLogger();

public:

	/// <summary>
	/// Log message to file with an info tag
	/// </summary>
	/// <param name="message">The message to log</param>
	void info(std::string message);

	/// <summary>
	/// Log message to file with a warning tag
	/// </summary>
	/// <param name="message">The message to log</param>
	void warn(std::string message);

	/// <summary>
	/// Log message to file with an error tag
	/// </summary>
	/// <param name="message">The message to log</param>
	void error(std::string message);
};

#endif