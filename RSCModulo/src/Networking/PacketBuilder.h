#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

/// <summary>
/// Builds a packet to be sent across the network
/// </summary>
class PacketBuilder
{
private:
	static const int* BIT_MASK_OUT;
	static int* initBitMask();

	int opcode;
	char* payload;
	int bitPosition;

public:
	PacketBuilder(int opcode);

	~PacketBuilder();


};

#endif