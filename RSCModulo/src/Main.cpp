#include <iostream>

#include "Networking/Networking.h"
#include "Utils/ConfigFile.h"
#include "Utils/Logger.h"

void connectToServer()
{
	const char* serverAddress = "127.0.0.1";
    unsigned short serverPort = 43596;

	Networking::socketInit();

    // Create a socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        perror("socket() failed");
        return;
    }

    // Set up the server address structure
    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverAddress, &serverAddr.sin_addr) <= 0) {
        perror("inet_pton() failed");
        Networking::socketCleanup();
        Networking::socketClose(serverSocket);
        return;
    }

    // Connect to the server
    if (connect(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("connect() failed");
        Networking::socketCleanup();
        Networking::socketClose(serverSocket);
        return;
    }

    Networking::socketCleanup();
    Networking::socketClose(serverSocket);
}

int main(int argc, char* argv[])
{	
	Logger& logger = Logger::getLogger();
	logger.info("Hello, world!");

    ConfigFile configFile;

    std::cout << configFile.settingsCount() << std::endl;
    std::cout << configFile.getSetting("ip") << std::endl;

	return 0;
}