#include "Networking.h"

using namespace boost::asio;
using namespace boost::asio::ip;

int Networking::initializeConnection(const char* serverAddress, const char* port)
{
    io_context io_context;

    // Create a TCP resolver and query the server endpoint
    tcp::resolver resolver(io_context);
    tcp::resolver::query query(serverAddress, port);

    // Resolve the endpoint iterator and create a socket
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    tcp::socket socket(io_context);

    return connectToServer(socket, endpoint_iterator);
}

int Networking::connectToServer(tcp::socket& socket, tcp::resolver::iterator endpoint_iterator)
{
    // Connect the socket to the server
    boost::system::error_code error;
    connect(socket, endpoint_iterator, error);
    if (error)
    {
        return 1;
    }
    return 0;
}