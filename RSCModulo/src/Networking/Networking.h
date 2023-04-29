#include <boost/asio.hpp>

#ifndef NETWORKING_H
#define NETWORKING_H

/// <summary>
/// Provides functions for cross-platform networking
/// </summary>
class Networking
{
public:
	static int initializeConnection(const char* serverAddress, const char* port);

	static int connectToServer(boost::asio::ip::tcp::socket& socket, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

private:
	/// <summary>
	/// Socket to the server
	/// </summary>
	static boost::asio::ip::tcp::socket socket;

	/// <summary>
	/// Used to keep track of whether we have actually connected or not
	/// </summary>
	static bool connected;
};

#endif
