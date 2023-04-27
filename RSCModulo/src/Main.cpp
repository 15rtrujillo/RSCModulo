#include "Utils/Logger.h"

int main(int argc, char* argv[])
{	
	Logger& logger = Logger::getLogger();
	logger.info("Hello, world!");
	return 0;
}