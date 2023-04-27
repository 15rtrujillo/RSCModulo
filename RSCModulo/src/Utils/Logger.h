#include <fstream>
#include <string>

#ifndef LOGGER_H
#define LOGGER_H

/// <summary>
/// Used to log important messages out to a log file
/// </summary>
class Logger
{
private:
	std::ofstream logfile;
	Logger();
	~Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

public:
	/// <summary>
	/// Get the singleton instance of the Logger class
	/// </summary>
	/// <returns>The logger object</returns>
	static Logger& getLogger();

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