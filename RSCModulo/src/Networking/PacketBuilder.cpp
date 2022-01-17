#include "PacketBuilder.h"

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