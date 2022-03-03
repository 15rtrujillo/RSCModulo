#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include <string>

#include "Packet.h"

/// <summary>
/// Builds a packet to be sent across the network
/// </summary>
class PacketBuilder
{
private:
	// static const int* BIT_MASK_OUT;
	// static int* initBitMask();

	char opcode;
	char* payload;
	// int bitPosition;
	int writePosition;
	int capacity;

	/// <summary>
	/// Makes sure the payload buffer is large enough to write the specified number of bytes.
	/// If not, we reallocate a larger array
	/// </summary>
	/// <param name="bytesToWrite">How many bytes are about to be written to the buffer</param>
	void checkAndResize(size_t bytesToWrite);

public:
	PacketBuilder(char opcode);

	~PacketBuilder();

	char getOpcode() const;

	/// <summary>
	/// Get the length of the packet builder's current payload
	/// </summary>
	/// <returns>The length of the payload</returns>
	int getLength() const;

	/// <summary>
	/// Create a packet form the current packet builder
	/// </summary>
	/// <returns>The new packet</returns>
	Packet toPacket();

	void writeByte(char byte);

	/// <summary>
	/// Write a specific amount of bytes to the buffer
	/// </summary>
	void writeBytes(char* bytes);

	/// <summary>
	/// Fits the value into the specified number of bits and writes it to the buffer
	/// </summary>
	/// <param name="value">The value (1 <= value <= 32)</param>
	/// <param name="numBits">The number of bits to write</param>
	// PacketBuilder writeBits(int value, int numBits);

	void writeUnsignedByte(unsigned char uByte);

	void writeShort(short s);

	void writeUnsignedShort(unsigned short us);

	void writeInt(int i);

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
};

#endif