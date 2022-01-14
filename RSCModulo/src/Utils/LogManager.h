#include "RLogger.h"

#ifndef LOGMANAGER_H
#define LOGMANAGER_H

/// <summary>
/// Manages the RLogger
/// </summary>
class LogManager
{
private:
	static RLogger* logger;
	LogManager();
	~LogManager();

public:
	/// <summary>
	/// Gets the RLogger instance
	/// </summary>
	/// <returns>Either a new or the existing RLogger instance</returns>
	static RLogger* getLogger();
};

#endif