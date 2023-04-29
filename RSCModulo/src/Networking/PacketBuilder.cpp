#include "PacketBuilder.h"

// Initialize static members
int PacketBuilder::bitMaskOut[PacketBuilder::bitMaskSize];
bool PacketBuilder::bitMaskInitialized = false;

PacketBuilder::PacketBuilder(char opcode)
{
	this->opcode = opcode;
	writePosition = 0;
	capacity = 1;
	payload = std::make_unique<char[]>(capacity);

	if (!bitMaskInitialized)
	{
		initBitMask();
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
	std::unique_ptr<char[]> packetPayload = std::make_unique<char[]>(writePosition);
	std::memcpy(packetPayload.get(), payload.get(), writePosition);

	return Packet(opcode, std::move(packetPayload), writePosition);
}

void PacketBuilder::writeByte(char byte)
{
	checkAndResize(sizeof(byte));
	payload[writePosition++] = byte;
}

void PacketBuilder::writeBytes(char bytes[], int bytesLen)
{
	checkAndResize(bytesLen);
	std::memcpy(payload.get() + writePosition, bytes, bytesLen);
	writePosition += bytesLen;
}

void PacketBuilder::startBitAccess()
{
	bitPosition = writePosition * 8;
}

void PacketBuilder::finishBitAccess()
{
	writePosition = (bitPosition + 7) / 8;
}

void PacketBuilder::writeBits(int value, int numBits)
{
}

void PacketBuilder::writeUnsignedByte(unsigned char uByte)
{
	checkAndResize(sizeof(uByte));
	payload[writePosition++] = uByte;
}

void PacketBuilder::writeShort(short s)
{
	size_t dataLen = sizeof(s);
	checkAndResize(dataLen);

	short* writeLocation = reinterpret_cast<short*>(payload.get() + writePosition);
	*writeLocation = s;

	writePosition += dataLen;
}

void PacketBuilder::writeUnsignedShort(unsigned short us)
{
	size_t dataLen = sizeof(us);
	checkAndResize(dataLen);

	unsigned short* writeLocation = reinterpret_cast<unsigned short*>(payload.get() + writePosition);
	*writeLocation = us;

	writePosition += dataLen;
}

void PacketBuilder::writeInt(int i)
{
	size_t dataLen = sizeof(i);
	checkAndResize(dataLen);

	int* writeLocation = reinterpret_cast<int*>(payload.get() + writePosition);
	*writeLocation = i;

	writePosition += dataLen;
}

void PacketBuilder::writeLong(long l)
{
	size_t dataLen = sizeof(l);
	checkAndResize(dataLen);

	long* writeLocation = reinterpret_cast<long*>(payload.get() + writePosition);
	*writeLocation = l;

	writePosition += dataLen;
}

void PacketBuilder::writeLineFeedString(std::string s)
{
	// Account for the \n character
	checkAndResize(s.size() + 1);

	// Copy everything but the null terminator
	memcpy(payload.get() + writePosition, s.c_str(), s.size());
	writePosition += s.size();

	// Append the \n character
	payload[writePosition++] = 10;
}

void PacketBuilder::writeZeroPaddedString(std::string s)
{
	// Account for the two null characters
	checkAndResize(s.size() + 2);

	// Append the first null character
	payload[writePosition++] = 0;

	// Copy everything but the null terminator
	memcpy(payload.get() + writePosition, s.c_str(), s.size());
	writePosition += s.size();

	// Append the final null character
	payload[writePosition++] = 0;
}

void PacketBuilder::initBitMask()
{
	for (int i = 0; i < bitMaskSize; ++i)
	{
		bitMaskOut[i] = (1 << i) - 1;
	}

	bitMaskInitialized = true;
}

void PacketBuilder::checkAndResize(size_t bytesToWrite)
{
	int newSize = bytesToWrite + writePosition;

	if (newSize > capacity)
	{
		// Calculate new capacity
		size_t newCapacity = std::max(2 * capacity, newSize);

		// Allocate new payload array and copy old payload
		std::unique_ptr<char[]> newPayload = std::make_unique<char[]>(newCapacity);
		std::memcpy(newPayload.get(), payload.get(), writePosition);

		// Reset unique_ptr and update capacity
		payload = std::move(newPayload);
		capacity = newCapacity;
	}
}
