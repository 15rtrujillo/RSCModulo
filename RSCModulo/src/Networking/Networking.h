#ifdef _WIN32
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600  /* Windows Vista */
#endif
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
typedef int SOCKET
#endif

#ifndef NETWORKING_H
#define NETWORKING_H

/// <summary>
/// Provides functions for cross-platform networking
/// </summary>
class Networking
{
public:
	/// <summary>
	/// Initialize Winsock (only needed for Windows)
	/// </summary>
	/// <returns>Non-zero if failure</returns>
	static int socketInit();

	/// <summary>
	/// Clean up Winsock (only needed for Windows)
	/// </summary>
	/// <returns>Non-zero if failure</returns>
	static int socketCleanup();

	/// <summary>
	/// Cross platform socket close
	/// </summary>
	/// <param name="sock">The socket to close (on POSIX this is just an int)</param>
	/// <returns>Non-zero if failure</returns>
	static int socketClose(SOCKET sock);

private:
	/// <summary>
	/// The socket for the connection to the server
	/// </summary>
	SOCKET socket;
};

#endif
