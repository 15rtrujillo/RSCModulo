#include <fstream>
#include <string>

#ifndef LOGGER_H
#define LOGGER_H

/// <summary>
/// Used to log important messages out to a log file
/// </summary>
class Logger
{
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
	void info(const std::string &message) const;

	/// <summary>
	/// Log message to file with a warning tag
	/// </summary>
	/// <param name="message">The message to log</param>
	void warning(const std::string &message) const;

	/// <summary>
	/// Log message to file with an error tag
	/// </summary>
	/// <param name="message">The message to log</param>
	void error(const std::string &message) const;

	/// <summary>
	/// Log message to file with an fatal tag
	/// </summary>
	/// <param name="message">The message to log</param>
	void fatal(const std::string& message) const;

private:
	Logger();

	Logger(const Logger&) = delete;

	Logger& operator=(const Logger&) = delete;
};

#endif
