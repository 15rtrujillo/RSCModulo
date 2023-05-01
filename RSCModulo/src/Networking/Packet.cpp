#include "Packet.h"

// Initialize static value
long Packet::nextPacketNumber = 0;

long Packet::getNextPacketNumber()
{
	return nextPacketNumber++;
}

Packet::Packet(char opcode, std::shared_ptr<char[]> payload, int payloadLength) : 
	opcode(opcode), payload(payload, payloadLength), packetNumber(getPacketNumber())
{

}

char Packet::getOpcode() const
{
	return opcode;
}

long Packet::getPacketNumber() const
{
	return packetNumber;
}

Buffer& Packet::getPayload()
{
	return payload;
}

int Packet::getReadableBytes() const
{
	return payload.getReadableBytes();
}

int Packet::getReadPosition() const
{
	return payload.getReadPosition();
}

char Packet::readByte()
{
	return payload.readByte();
}

std::unique_ptr<char[]> Packet::readBytes(int length)
{
	return payload.readBytes(length);
}

unsigned char Packet::readUnsignedByte()
{
	return payload.readUnsignedByte();
}

short Packet::readShort()
{
	return payload.readShort();
}

unsigned short Packet::readUnsignedShort()
{
	return payload.readUnsignedShort();
}

int Packet::readInt()
{
	return payload.readInt();
}

long Packet::readLong()
{
	return payload.readLong();
}

std::string Packet::readLineFeedString()
{
	return payload.readLineFeedString();
}

std::string Packet::readZeroPaddedString()
{
	return payload.readZeroPaddedString();
}
