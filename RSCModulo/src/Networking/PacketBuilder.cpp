#include "PacketBuilder.h"
/* I think we're just going to pray that we never have to write bit-specific data.
#define BIT_MASK_SIZE 32

const int* PacketBuilder::BIT_MASK_OUT = PacketBuilder::initBitMask();

int* PacketBuilder::initBitMask()
{
	int* bitMask = new int[BIT_MASK_SIZE];
	for (int i = 0; i < BIT_MASK_SIZE; ++i)
	{
		bitMask[i] = (1 << i) - 1;
	}

	return bitMask;
}
*/

PacketBuilder::PacketBuilder(char opcode)
{
	this->opcode = opcode;
	writePosition = 0;
	capacity = 1;
	payload = new char[capacity];
}

PacketBuilder::~PacketBuilder()
{
	delete[] payload;
}

void PacketBuilder::checkAndResize(size_t bytesToWrite)
{
	int newSize = bytesToWrite + writePosition;
	
	if (newSize > capacity)
	{
		// Ghetto resize
		capacity *= 2;
		if (capacity < newSize)
		{
			capacity = newSize;
		}

		// Copy old payload to new array
		char* newPayload = new char[capacity];
		for (int i = 0; i < writePosition; ++i)
		{
			newPayload[i] = payload[i];
		}

		// Delete the old array
		delete[] payload;
		payload = newPayload;
	}
}

char PacketBuilder::getOpcode() const
{
	return opcode;
}

int PacketBuilder::getLength() const
{
	return writePosition;
}

Packet PacketBuilder::toPacket()
{
	// TODO: Create a new payload array that's fitted to the correct size.
	char* packetPayload = new char[writePosition];
	for (int i = 0; i < writePosition; ++i)
	{
		packetPayload[i] = payload[i];
	}

	return Packet(opcode, packetPayload, writePosition);
}

void PacketBuilder::writeByte(char byte)
{
	checkAndResize(sizeof(byte));
	payload[writePosition] = byte;
	++writePosition;
}