#include <iostream>

#include "Networking/Networking.h"
#include "Utils/ConfigFile.h"

int main(int argc, char* argv[])
{	
	ConfigFile configFile("client.config");
	int result = Networking::initializeConnection(configFile.getSetting("ip").c_str(), configFile.getSetting("port").c_str());
	if (result != 0)
	{
		std::cout << "An error has occurred" << std::endl;
	}
	return 0;
}