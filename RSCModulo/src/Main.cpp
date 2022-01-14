#include "Utils/RLogger.h"
#include "Utils/LogManager.h"

int main(int argc, char* argv[])
{	
	RLogger* logger = LogManager::getLogger();
	logger->info("Hello, world!");
	return 0;
}