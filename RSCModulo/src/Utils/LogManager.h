#include "RLogger.h"

#ifndef LOGMANAGER_H
#define LOGMANAGER_H

class LogManager
{
private:
	static RLogger* logger;
	LogManager();
	~LogManager();

public:
	static RLogger* getLogger();
};

#endif