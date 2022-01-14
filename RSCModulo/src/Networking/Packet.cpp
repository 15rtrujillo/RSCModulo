#include <sstream>

#include "Packet.h"

// Initialize static value
long Packet::nextPacketNumber = 0;

long Packet::getNextPacketNumber()
{
	return nextPacketNumber++;
}

Packet::Packet(int opcode, char* payload, int payloadLength)
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

int Packet::getOpcode()
{
	return opcode;
}

char* Packet::getPayload()
{
	char* newPayload = new char[payloadLength];
	for (int i = 0; i < payloadLength; ++i)
	{
		newPayload[i] = payload[i];
	}

	return newPayload;
}

int Packet::getLength()
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
	for (int i = readIndex; i < payloadLength; ++i)
	{
		// We want to do this every time.
		++readIndex;

		char c = payload[i];
		if (c == 10)
			break;
		ss << c;
	}

	return ss.str();
}

std::string Packet::readZeroPaddedString()
{
	return std::string();
}
