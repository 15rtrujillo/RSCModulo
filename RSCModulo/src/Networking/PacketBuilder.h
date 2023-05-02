#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include <memory>
#include <string>

#include "Buffer.h"
#include "Packet.h"

/// <summary>
/// Builds a packet to be sent across the network
/// </summary>
class PacketBuilder
{
public:
	PacketBuilder(char opcode);

	/// <summary>
	/// Get the opcode associated with the packet builder
	/// </summary>
	/// <returns>The opcode associated with the packet builder</returns>
	char getOpcode() const;

	/// <summary>
	/// Get the length of the packet builder's current payload
	/// </summary>
	/// <returns>The length of the payload</returns>
	int getWritePosition() const;

	/// <summary>
	/// Set the write position of the buffer
	/// </summary>
	/// <param name="newWritePosition">The new write position</param>
	void setWritePosition(int newWritePosition);

	/// <summary>
	/// Create a packet form the current packet builder
	/// </summary>
	/// <returns>The new packet</returns>
	Packet toPacket();

	/// <summary>
	/// Write a single byte to the buffer
	/// </summary>
	/// <param name="byte">The byte to write</param>
	void writeByte(char byte);

	/// <summary>
	/// Write a specific amount of bytes to the buffer
	/// </summary>
	/// <param name="bytes">The bytes to write</param>
	/// <param name="bytesLen">The length of the bytes to write</param>
	void writeBytes(unsigned char bytes[], int bytesLen);

	/// <summary>
	/// Write a Buffer of bytes to the buffer
	/// </summary>
	/// <param name="bytes">The Buffer of bytes to write</param>
	void writeBytes(Buffer bytes);

	/// <summary>
	/// Set up the buffer so that bits can be written.
	/// Must be called before writing bits.
	/// </summary>
	void startBitAccess();

	/// <summary>
	/// Restore the original functionality of the buffer.
	/// Should be called after writing bits.
	/// </summary>
	void finishBitAccess();

	/// <summary>
	/// Fits the value into the specified number of bits and writes it to the buffer
	/// </summary>
	/// <param name="value">The value (1 <= value <= 32)</param>
	/// <param name="numBits">The number of bits to write</param>
	void writeBits(int value, int numBits);

	/// <summary>
	/// Write a single, unsigned byte to the buffer
	/// </summary>
	/// <param name="uByte">The unsigned byte to write</param>
	void writeUnsignedByte(unsigned char uByte);

	/// <summary>
	/// Write a single short to the buffer
	/// </summary>
	/// <param name="s">The short to write</param>
	void writeShort(short s);

	/// <summary>
	/// Write a single, unsigned short to the buffer
	/// </summary>
	/// <param name="us">The unsigned short to write</param>
	void writeUnsignedShort(unsigned short us);

	/// <summary>
	/// Write a single int to the buffer
	/// </summary>
	/// <param name="i">The int to write</param>
	void writeInt(int i);

	/// <summary>
	/// Write a single unsigned int to the buffer
	/// </summary>
	/// <param name="ui">The unsigned int to write</param>
	void writeUnsignedInt(unsigned int ui);

	/// <summary>
	/// Write a single long to the buffer
	/// </summary>
	/// <param name="byte">The long to write</param>
	void writeLong(long l);

	/// <summary>
	/// Write a string to the buffer and adds a terminating line feed character
	/// </summary>
	/// <param name="s">The string to write</param>
	void writeLineFeedString(std::string s);

	/// <summary>
	/// Writes a string and adds zeros to both ends
	/// </summary>
	/// <param name="s">The string to write</param>
	void writeZeroPaddedString(std::string s);

private:
	/// <summary>
	/// The packet's opcode
	/// </summary>
	char opcode;

	/// <summary>
	/// The data payload of the packet
	/// </summary>
	Buffer payload;
};

#endif
