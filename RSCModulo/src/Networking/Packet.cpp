#include <sstream>

#include "Packet.h"

// Initialize static value
long Packet::nextPacketNumber = 0;

long Packet::getNextPacketNumber()
{
	return nextPacketNumber++;
}

Packet::Packet(char opcode, char* payload, int payloadLength)
{
	this->opcode = opcode;
	this->payload = payload;
	this->payloadLength = payloadLength;
	this->packetNumber = getNextPacketNumber();
}

Packet::~Packet()
{
	delete[] payload;
}

char Packet::getOpcode() const
{
	return opcode;
}

long Packet::getPacketNumber() const
{
	return packetNumber;
}

char* Packet::getPayload() const
{
	char* newPayload = new char[payloadLength];
	for (int i = 0; i < payloadLength; ++i)
	{
		newPayload[i] = payload[i];
	}

	return newPayload;
}

int Packet::getLength() const
{
	return payloadLength;
}

char Packet::readByte()
{
	return payload[readIndex++];
}

char* Packet::readBytes(int length)
{
	char* readBytes = new char[length];
	for (int i = 0; i < length; ++i)
	{
		readBytes[i] = payload[readIndex + i];
	}

	readIndex += length;

	return readBytes;
}

unsigned char Packet::readUnsignedByte()
{
	return payload[readIndex++] & 0xFF;
}

short Packet::readShort()
{
	// Black magics
	short readShort = *reinterpret_cast<short*>(&payload[readIndex]);
	readIndex += sizeof(short);
	return readShort;
}

unsigned short Packet::readUnsignedShort()
{
	// Black magics
	unsigned short readShort = (*reinterpret_cast<short*>(&payload[readIndex])) & 0xFF;
	readIndex += sizeof(unsigned short);
	return readShort;
}

int Packet::readInt()
{
	// Black magics
	int readInt = *reinterpret_cast<int*>(&payload[readIndex]);
	readIndex += sizeof(int);
	return readInt;
}

long Packet::readLong()
{
	// Black magics
	long readLong = *reinterpret_cast<long*>(&payload[readIndex]);
	readIndex += sizeof(long);
	return readLong;
}

std::string Packet::readLineFeedString()
{
	std::stringstream ss;
	for (; readIndex < payloadLength; ++readIndex)
	{
		char c = payload[readIndex];
		if (c == 10)
			break;
		ss << c;
	}

	return ss.str();
}

std::string Packet::readZeroPaddedString()
{
	std::stringstream ss;

	// If the readIndex doesn't have a zero, then we don't have a zero-padded string.
	if (payload[readIndex] != 0) return "";

	// If the current read index is a zero, we'll go ahead and move it forward
	// because we don't want to actually include the zero in the string.
	++readIndex;

	for (; readIndex < payloadLength; ++readIndex)
	{
		char c = payload[readIndex];
		if (c == 0)
			break;
		ss << c;
	}

	return ss.str();
}
