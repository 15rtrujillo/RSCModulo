#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include <memory>
#include <string>

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
	int getLength() const;

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
	void writeBytes(char bytes[], int bytesLen);

	/// <summary>
	/// Set up the Packet Builder so that bits can be written to the payload.
	/// Must be called before writing bits.
	/// </summary>
	void startBitAccess();

	/// <summary>
	/// Restore the original functionality of the Packet Builder.
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
	static const int bitMaskSize = 32;

	/// <summary>
	/// Bit mask array
	/// </summary>
	static int bitMaskOut[];

	/// <summary>
	/// Used to only initialize the bit mask once
	/// </summary>
	static bool bitMaskInitialized;

	/// <summary>
	/// Initialize the bit mask with values
	/// </summary>
	static void initBitMask();

	/// <summary>
	/// The packet's opcode
	/// </summary>
	char opcode;

	/// <summary>
	/// The data payload of the packet
	/// </summary>
	std::unique_ptr<char[]> payload;

	/// <summary>
	/// The position to write bits
	/// </summary>
	int bitPosition;

	/// <summary>
	/// The current write index of the packet
	/// </summary>
	int writePosition;

	/// <summary>
	/// The current possible size of the payload
	/// </summary>
	int capacity;

	/// <summary>
	/// Makes sure the payload buffer is large enough to write the specified number of bytes.
	/// If not, we reallocate a larger array
	/// </summary>
	/// <param name="bytesToWrite">How many bytes are about to be written to the buffer</param>
	void checkAndResize(size_t bytesToWrite);
};

#endif
