#include "LogManager.h"

// Initialize the static member
RLogger* LogManager::logger = nullptr;

LogManager::~LogManager()
{
	delete logger;
}

RLogger* LogManager::getLogger()
{
	if (logger == nullptr)
	{
		logger = new RLogger;
	}
	return logger;
}