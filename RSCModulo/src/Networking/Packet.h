#include <memory>
#include <string>

#include "Buffer.h"

#ifndef PACKET_H
#define PACKET_H

/// <summary>
/// Wrapper for char/byte array that gets read from/sent across network
/// </summary>
class Packet
{
public:
	/// <summary>
	/// Create a new wrapper for char/byte array that gets read from/sent across network
	/// </summary>
	/// <param name="opcode">The packet's opcode</param>
	/// <param name="payload">The packet's payload</param>
	/// <param name="payloadLength">The length of the payload</param>
	Packet(char opcode, std::shared_ptr<char[]> payload, int payloadLength);

	/// <summary>
	/// Get the packet number
	/// </summary>
	/// <returns>The packet number</returns>
	long getPacketNumber() const;

	/// <summary>
	/// Get the packet opcode
	/// </summary>
	/// <returns>The packet opcode</returns>
	char getOpcode() const;

	/// <summary>
	/// Get the entire payload buffer
	/// </summary>
	/// <returns>A reference to the payload buffer</returns>
	Buffer& getPayload();

	/// <summary>
	/// Get the length of the packet's payload
	/// </summary>
	/// <returns>The length of the payload</returns>
	int getReadableBytes() const;

	/// <summary>
	/// Get the current read index
	/// </summary>
	/// <returns>The index of the data being read</returns>
	int getReadPosition() const;

	/// <summary>
	/// Read a single byte from the packet
	/// </summary>
	/// <returns>A byte from the packet</returns>
	char readByte();

	/// <summary>
	/// Read a specific amount of bytes from the buffer
	/// </summary>
	/// <param name="length">The amount of bytes to read</param>
	/// <returns>A new array of the read bytes</returns>
	std::unique_ptr<char[]> readBytes(int length);

	/// <summary>
	/// Read a single unsigned byte from the packet
	/// </summary>
	/// <returns>An unsigned byte from the packet</returns>
	unsigned char readUnsignedByte();

	/// <summary>
	/// Read a short from the packet
	/// </summary>
	/// <returns>A short from the packet</returns>
	short readShort();

	/// <summary>
	/// Read an unsigned short from the packet
	/// </summary>
	/// <returns>An unsigned short from the packet</returns>
	unsigned short readUnsignedShort();

	/// <summary>
	/// Read an int from the packet
	/// </summary>
	/// <returns>An int from the packet</returns>
	int readInt();

	/// <summary>
	/// Read a long from the packet
	/// </summary>
	/// <returns>A long from the packet</returns>
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

private:
	/// <summary>
	/// An identifier for the packet
	/// </summary>
	long packetNumber;

	/// <summary>
	/// The packet's opcode
	/// </summary>
	char opcode;

	/// <summary>
	/// The data payload of the packet
	/// </summary>
	Buffer payload;

	/// <summary>
	/// Used for keeping track of the packet number
	/// </summary>
	static long nextPacketNumber;

	/// <summary>
	/// Get the next packet number
	/// </summary>
	/// <returns>The next packet number</returns>
	static long getNextPacketNumber();
};
#endif
