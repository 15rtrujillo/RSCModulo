#include <string>

#ifndef PACKET_H
#define PACKET_H

/// <summary>
/// Wrapper for char/byte array that gets read from/sent across network
/// </summary>
class Packet
{
private:
	int opcode;
	long packetNumber;
	char* payload;
	int payloadLength;
	int readIndex = 0;

	static long getNextPacketNumber();

public:
	static long nextPacketNumber;
	
	Packet(int opcode, char* payload, int payloadLength);

	~Packet();

	int getOpcode();

	/// <summary>
	/// Get the entire payload buffer
	/// </summary>
	/// <returns>A COPY of the payload buffer</returns>
	char* getPayload();

	/// <summary>
	/// Get the length of the packet's payload
	/// </summary>
	/// <returns>The length of the payload</returns>
	int getLength();

	char readByte();

	/// <summary>
	/// Read a specific amount of bytes from the buffer
	/// </summary>
	/// <param name="length">The amount of bytes to read</param>
	/// <returns>A NEW array of the read bytes</returns>
	char* readBytes(int length);

	unsigned char readUnsignedByte();

	short readShort();

	unsigned short readUnsignedShort();

	int readInt();

	long readLong();

	/// <summary>
	/// Read data until encountering a line feed character (ASCII 10) and
	/// interpret as a string
	/// </summary>
	/// <returns>The read string (does not include LF character)</returns>
	std::string readLineFeedString();

	/// <summary>
	/// Reads a string padded by zero at both ends
	/// </summary>
	/// <returns>The string without either padding zeros</returns>
	std::string readZeroPaddedString();
};

#endif