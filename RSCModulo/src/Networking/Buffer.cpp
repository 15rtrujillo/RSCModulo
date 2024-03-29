#include <boost/endian/conversion.hpp>
#include <sstream>

#include "Buffer.h"

// Initialize static members
int Buffer::bitMaskOut[Buffer::bitMaskSize];
bool Buffer::bitMaskInitialized = false;

Buffer::Buffer(int dataLen) :
	data(std::make_unique<unsigned char[]>(dataLen)), readPosition(0), writePosition(0), bitPosition(),
	capacity(dataLen)
{
	if (!bitMaskInitialized)
	{
		initBitMask();
	}
}

Buffer::Buffer(std::shared_ptr<unsigned char[]> data, int dataLen) :
	data(data), readPosition(0), writePosition(dataLen), bitPosition(dataLen * 8), capacity(dataLen)
{
	if (!bitMaskInitialized)
	{
		initBitMask();
	}
}

std::shared_ptr<unsigned char[]> Buffer::getData() const
{
	return data;
}

int Buffer::getReadPosition() const
{
	return readPosition;
}

void Buffer::setReadPosition(int newReadPosition)
{
	readPosition = newReadPosition;
}

int Buffer::getReadableBytes() const
{
	return writePosition;
}

void Buffer::setWritePosition(int newWritePosition)
{
	writePosition = newWritePosition;
}

template <typename T>
T readBigEndianValue(unsigned char data[], int& readPosition)
{
	size_t dataLen = sizeof(T);

	T value = 0;
	std::memcpy(&value, data + readPosition, dataLen);
	boost::endian::big_to_native_inplace(value);

	readPosition += dataLen;

	return value;
}

std::unique_ptr<unsigned char[]> Buffer::readBytes(int length)
{
	std::unique_ptr<unsigned char[]> readBytes = std::make_unique<unsigned char[]>(length);
	std::memcpy(readBytes.get(), data.get() + readPosition, length);
	readPosition += length;
	return readBytes;
}

char Buffer::readByte()
{
	return static_cast<char>(data[readPosition++]);
}

unsigned char Buffer::readUnsignedByte()
{
	return data[readPosition++];
}

short Buffer::readShort()
{
	return readBigEndianValue<short>(data.get(), readPosition);
}

unsigned short Buffer::readUnsignedShort()
{
	return readBigEndianValue<unsigned short>(data.get(), readPosition);
}

int Buffer::readInt()
{
	return readBigEndianValue<int>(data.get(), readPosition);
}

unsigned int Buffer::readUnsignedInt()
{
	return readBigEndianValue<unsigned int>(data.get(), readPosition);
}

long Buffer::readLong()
{
	return readBigEndianValue<long>(data.get(), readPosition);
}

std::string Buffer::readLineFeedString()
{
	std::stringstream ss;
	for (; readPosition < capacity; ++readPosition)
	{
		char c = data[readPosition];
		if (c == 10)
			break;
		ss << c;
	}

	return ss.str();
}

std::string Buffer::readZeroPaddedString()
{
	std::stringstream ss;

	// If the readIndex doesn't have a zero, then we don't have a zero-padded string.
	if (data[readPosition] != 0) return "";

	// If the current read index is a zero, we'll go ahead and move it forward
	// because we don't want to actually include the zero in the string.
	++readPosition;

	for (; readPosition < capacity; ++readPosition)
	{
		char c = data[readPosition];
		if (c == 0)
			break;
		ss << c;
	}

	return ss.str();
}

void Buffer::writeBytes(unsigned char bytes[], int bytesLen)
{
	checkAndResize(bytesLen);
	std::memcpy(data.get() + writePosition, bytes, bytesLen);
	writePosition += bytesLen;
}

void Buffer::writeBytes(Buffer& bytes)
{
	writeBytes(bytes.getData().get(), bytes.getReadableBytes());
}

void Buffer::startBitAccess()
{
	bitPosition = writePosition * 8;
}

void Buffer::finishBitAccess()
{
	writePosition = (bitPosition + 7) / 8;
}

void Buffer::writeBits(int value, int numBits)
{
	// I don't ever want to have to implement this please
}

template <typename T>
void writeBigEndianValue(T value, unsigned char data[], int& writePosition)
{
	size_t dataLen = sizeof(T);

	boost::endian::native_to_big_inplace(value);
	std::memcpy(data + writePosition, &value, dataLen);

	writePosition += dataLen;
}

void Buffer::writeByte(char byte)
{
	checkAndResize(sizeof(char));
	writeBigEndianValue(byte, data.get(), writePosition);
}

void Buffer::writeUnsignedByte(unsigned char uByte)
{
	checkAndResize(sizeof(unsigned char));
	writeBigEndianValue(uByte, data.get(), writePosition);
}

void Buffer::writeShort(short s)
{
	checkAndResize(sizeof(short));
	writeBigEndianValue(s, data.get(), writePosition);
}

void Buffer::writeUnsignedShort(unsigned short us)
{
	checkAndResize(sizeof(unsigned short));
	writeBigEndianValue(us, data.get(), writePosition);
}

void Buffer::write3ByteInt(int i3)
{
	checkAndResize(sizeof(int) - 1);
	size_t dataLen = sizeof(int) - 1;

	boost::endian::native_to_big_inplace(i3);

	// We need to add one here so that we can get rid of the MSB
	std::memcpy(data.get() + writePosition, &i3 + 1, dataLen);

	writePosition += dataLen;
}

void Buffer::writeInt(int i)
{
	checkAndResize(sizeof(int));
	writeBigEndianValue(i, data.get(), writePosition);
}

void Buffer::writeUnsignedInt(unsigned int ui)
{
	checkAndResize(sizeof(int));
	writeBigEndianValue(ui, data.get(), writePosition);
}

void Buffer::writeLong(long l)
{
	checkAndResize(sizeof(long));
	writeBigEndianValue(l, data.get(), writePosition);
}

void Buffer::writeLineFeedString(std::string s)
{
	// Account for the \n character
	checkAndResize(s.size() + 1);

	// Copy everything but the null terminator
	memcpy(data.get() + writePosition, s.c_str(), s.size());
	writePosition += s.size();

	// Append the \n character
	data[writePosition++] = 10;
}

void Buffer::writeZeroPaddedString(std::string s)
{
	// Account for the two null characters
	checkAndResize(s.size() + 2);

	// Append the first null character
	data[writePosition++] = 0;

	// Copy everything but the null terminator
	memcpy(data.get() + writePosition, s.c_str(), s.size());
	writePosition += s.size();

	// Append the final null character
	data[writePosition++] = 0;
}

void Buffer::writeCString(std::string s)
{
	// Account for the null character
	size_t dataLen = s.size() + 1;
	checkAndResize(dataLen);

	// Copy everything including the null terminator
	memcpy(data.get() + writePosition, s.c_str(), dataLen);
	writePosition += dataLen;
}

void Buffer::initBitMask()
{
	for (int i = 0; i < bitMaskSize; ++i)
	{
		bitMaskOut[i] = (1 << i) - 1;
	}

	bitMaskInitialized = true;
}

void Buffer::checkAndResize(size_t bytesToWrite)
{
	int newSize = bytesToWrite + writePosition;

	if (newSize > capacity)
	{
		// Calculate new capacity
		size_t newCapacity = std::max(2 * capacity, newSize);

		// Allocate new data array and copy old data
		std::unique_ptr<unsigned char[]> newData = std::make_unique<unsigned char[]>(newCapacity);
		std::memcpy(newData.get(), data.get(), writePosition);

		// Reset unique_ptr and update capacity
		data = std::move(newData);
		capacity = newCapacity;
	}
}