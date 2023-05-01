#include "Crypto/Cryptography.h"
#include "Networking.h"

using namespace boost::asio;
using namespace boost::asio::ip;

// Initialize static variables
std::unique_ptr<tcp::socket> Networking::sock = nullptr;
tcp::resolver::iterator Networking::endpoint_iterator;
bool Networking::initialized = false;

void Networking::initializeConnection(const char* serverAddress, const char* port)
{
    if (!initialized)
    {
        static io_context io_context;

        // Create a TCP resolver and query the server endpoint
        tcp::resolver resolver(io_context);
        tcp::resolver::query query(serverAddress, port);

        // Resolve the endpoint iterator and create a socket
        endpoint_iterator = resolver.resolve(query);
        sock = std::make_unique<tcp::socket>(io_context);

        initialized = true;
    }
}

int Networking::connectToServer()
{
    if (!initialized)
    {
        return 1;
    }

    // Connect the socket to the server
    boost::system::error_code error;
    connect(*sock, endpoint_iterator, error);
    if (error)
    {
        return 2;
    }

    return 0;
}

void Networking::sendPacket(Packet packet)
{
    // +1 is for the opcode
    int packetLength = packet.getReadableBytes() + 1;

    // Encrypt the opcode if ISAAC has been initialized
    int encodedOpcode;
    if (Cryptography::getIsaacOut().areKeysSet())
    {
        encodedOpcode = Cryptography::encodeOpcode(packet.getOpcode());
    }

    else
    {
        encodedOpcode = packet.getOpcode();
    }

    // This buffer is the intermediate buffer.
    Buffer almostReady(packetLength);

    // If the packet is bigger than 160 bytes, we need to write the length in two bytes instead
    if (packetLength >= 160)
    {
        // Write the size
        almostReady.writeByte(static_cast<char>(packetLength / 256 + 160));
        almostReady.writeByte(static_cast<char>(packetLength & 0xFF));

        // Write the opcode
        almostReady.writeByte(static_cast<char>(encodedOpcode));

        // Write the rest
        almostReady.writeBytes(packet.getPayload());
    }

    else
    {
        // Write the size
        almostReady.writeByte(static_cast<char>(packetLength));
        int bufferLen = packet.getReadableBytes();

        if (packetLength != 1)
        {
            // So the way I understand this is that, the last byte of the payload goes
            // IN BETWEEN the size that we just wrote and the opcode. WTF Jagex!?
            // So let's make a new buffer to do this. +1 for the opcode
            Buffer stupidity(bufferLen + 1);

            // Add the last byte
            stupidity.writeByte(packet.getPayload().getData()[bufferLen - 1]);

            // Add the opcode
            stupidity.writeByte(static_cast<char>(encodedOpcode));

            // Now add everything else except the last byte.
            for (int i = 0; i < bufferLen - 1; ++i)
            {
                stupidity.writeByte(packet.getPayload().getData()[i]);
            }

            // Write it all to the OG buffer
            almostReady.writeBytes(stupidity);
        }

        else
        {
            // This packet is just an opcode.
            almostReady.writeByte(static_cast<char>(encodedOpcode));
        }

    }

    write(*sock, buffer(almostReady.getData().get(), almostReady.getReadableBytes()));
}

void Networking::closeConnection()
{
    (*sock).close();
}