#ifdef _WIN32
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501  /* Windows XP. */
#endif
#include <winsock2.h>
#include <Ws2tcpip.h>
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

/// Provides functions for cross-platform networking
class Networking
{
public:
	/// Initialize Winsock (only needed for Windows)
	/// Returns non-zero if failure
	static int socketInit();

	/// Clean up Winsock (only needed for Windows)
	static int socketCleanup();

	/// Cross-platform socket close
	static int socketClose(SOCKET sock);
};

#endif