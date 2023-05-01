#include <boost/asio.hpp>
#include <memory>

#include "Packet.h"

#ifndef NETWORKING_H
#define NETWORKING_H

/// <summary>
/// Provides functions for cross-platform networking
/// </summary>
class Networking
{
public:
	static void initializeConnection(const char* serverAddress, const char* port);

	static int connectToServer();

	static void sendPacket(Packet packet);

	static void closeConnection();

private:
	Networking();

	/// <summary>
	/// Socket to the server
	/// </summary>
	static std::unique_ptr<boost::asio::ip::tcp::socket> sock;
	static boost::asio::ip::tcp::resolver::iterator endpoint_iterator;

	/// <summary>
	/// Used to keep track of whether we have actually connected or not
	/// </summary>
	static bool initialized;
};

#endif
