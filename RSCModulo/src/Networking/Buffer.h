#include <memory>
#include <string>

#ifndef BUFFER_H
#define BUFFER_H

class Buffer
{
public:
	/// <summary>
	/// Create a new wrapper for an empty char/byte array
	/// </summary>
	/// <param name="dataLen">The length of the data</param>
	Buffer(int dataLen);

	/// <summary>
	/// Create a new wrapper for char/byte array
	/// </summary>
	/// <param name="data">The data to initialize the buffer with</param>
	/// <param name="dataLen">The length of the data</param>
	Buffer(std::shared_ptr<char[]> data, int dataLen);

	/// <summary>
	/// Get the entire data buffer
	/// </summary>
	/// <returns>A shared pointer to the data buffer</returns>
	std::shared_ptr<char[]> getData() const;

	/// <summary>
	/// Get the read index
	/// </summary>
	/// <returns>The length of the data</returns>
	int getReadPosition() const;

	/// <summary>
	/// Get the write position of the buffer. This doubles as current length of the data
	/// </summary>
	/// <returns>The length of the data</returns>
	int getReadableBytes() const;

	/// <summary>
	/// Read a specific amount of bytes
	/// </summary>
	/// <param name="length">The amount of bytes to read</param>
	/// <returns>A new array of the read bytes</returns>
	std::unique_ptr<char[]> readBytes(int length);

	/// <summary>
	/// Read a single byte
	/// </summary>
	/// <returns>A byte</returns>
	char readByte();

	/// <summary>
	/// Read a single unsigned byte
	/// </summary>
	/// <returns>An unsigned byte</returns>
	unsigned char readUnsignedByte();

	/// <summary>
	/// Read a short
	/// </summary>
	/// <returns>A short</returns>
	short readShort();

	/// <summary>
	/// Read an unsigned short
	/// </summary>
	/// <returns>An unsigned short</returns>
	unsigned short readUnsignedShort();

	/// <summary>
	/// Read an int
	/// </summary>
	/// <returns>An int</returns>
	int readInt();

	/// <summary>
	/// Read a long
	/// </summary>
	/// <returns>A long</returns>
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

	/// <summary>
	/// Write a specific amount of bytes to the buffer
	/// </summary>
	/// <param name="bytes">The bytes to write</param>
	/// <param name="bytesLen">The length of the bytes to write</param>
	void writeBytes(char bytes[], int bytesLen);

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
	/// Write a single byte to the buffer
	/// </summary>
	/// <param name="byte">The byte to write</param>
	void writeByte(char byte);

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
	/// Write 3 bytes of an int to the buffer
	/// This is used only once when writing a nonce to the login block.
	/// </summary>
	/// <param name="i">The int to write</param>
	void write3ByteInt(int i);

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

	/// <summary>
	/// Write a string with a trailing null character
	/// </summary>
	/// <param name="s">The string to write</param>
	void writeCString(std::string s);

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
	/// The data
	/// </summary>
	std::shared_ptr<char[]> data;

	/// <summary>
	/// The current read index of the buffer
	/// </summary>
	int readPosition;

	/// <summary>
	/// The position to write bits
	/// </summary>
	int bitPosition;

	/// <summary>
	/// The current write index of the packet
	/// </summary>
	int writePosition;

	/// <summary>
	/// The current possible size of the data buffer
	/// </summary>
	int capacity;

	/// <summary>
	/// Makes sure the data buffer is large enough to write the specified number of bytes.
	/// If not, we reallocate a larger array
	/// </summary>
	/// <param name="bytesToWrite">How many bytes are about to be written to the buffer</param>
	void checkAndResize(size_t bytesToWrite);
};

#endif
