#include "Networking.h"

int Networking::socketInit()
{
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(2, 0), &wsa_data);
#else
    return 0;
#endif
}

int Networking::socketCleanup()
{
#ifdef _WIN32
    return WSACleanup();
#else
    return 0;
#endif
}

int Networking::socketClose(SOCKET sock)
{

    int status = 0;

#ifdef _WIN32
    status = shutdown(sock, SD_BOTH);
    if (status == 0) { status = closesocket(sock); }
#else
    status = shutdown(sock, SHUT_RDWR);
    if (status == 0) { status = close(sock); }
#endif

    return status;

}