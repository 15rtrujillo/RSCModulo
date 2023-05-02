#include "PacketBuilder.h"

PacketBuilder::PacketBuilder(char opcode) :
	opcode(opcode), payload(128)
{

}

char PacketBuilder::getOpcode() const
{
	return opcode;
}

int PacketBuilder::getWritePosition() const
{
	return payload.getReadableBytes();
}

void PacketBuilder::setWritePosition(int newWritePosition)
{
	payload.setWritePosition(newWritePosition);
}

Packet PacketBuilder::toPacket()
{
	int packetLen = payload.getReadableBytes();

	std::unique_ptr<unsigned char[]> packetPayload = std::make_unique<unsigned char[]>(packetLen);
	std::memcpy(packetPayload.get(), payload.getData().get(), packetLen);

	return Packet(opcode, std::move(packetPayload), packetLen);
}

void PacketBuilder::writeByte(char byte)
{
	payload.writeByte(byte);
}

void PacketBuilder::writeBytes(unsigned char bytes[], int bytesLen)
{
	payload.writeBytes(bytes, bytesLen);
}

void PacketBuilder::writeBytes(Buffer bytes)
{
	writeBytes(bytes.getData().get(), bytes.getReadableBytes());
}

void PacketBuilder::startBitAccess()
{
	payload.startBitAccess();
}

void PacketBuilder::finishBitAccess()
{
	payload.finishBitAccess();
}

void PacketBuilder::writeBits(int value, int numBits)
{
	payload.writeBits(value, numBits);
}

void PacketBuilder::writeUnsignedByte(unsigned char uByte)
{
	payload.writeUnsignedByte(uByte);
}

void PacketBuilder::writeShort(short s)
{
	payload.writeShort(s);
}

void PacketBuilder::writeUnsignedShort(unsigned short us)
{
	payload.writeUnsignedShort(us);
}

void PacketBuilder::writeInt(int i)
{
	payload.writeInt(i);
}

void PacketBuilder::writeUnsignedInt(unsigned int ui)
{
	payload.writeUnsignedInt(ui);
}

void PacketBuilder::writeLong(long l)
{
	payload.writeLong(l);
}

void PacketBuilder::writeLineFeedString(std::string s)
{
	payload.writeLineFeedString(s);
}

void PacketBuilder::writeZeroPaddedString(std::string s)
{
	payload.writeZeroPaddedString(s);
}
