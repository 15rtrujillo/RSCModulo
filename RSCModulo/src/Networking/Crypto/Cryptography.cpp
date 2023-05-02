#include <chrono>
#include <cstdlib>
#include <vector>

#include "Cryptography.h"

using namespace boost::multiprecision;

cpp_int Cryptography::rsaModulus = 0;
cpp_int Cryptography::rsaExponent = 0;

ISAAC& Cryptography::getIsaacIn()
{
	static ISAAC isaac;
	return isaac;
}

ISAAC& Cryptography::getIsaacOut()
{
	static ISAAC isaac;
	return isaac;
}

int Cryptography::encodeOpcode(int opcode)
{
    return (opcode + getIsaacOut().getNextValue()) & 0xFF;
}

void Cryptography::setRSAModulus(std::string modulus)
{
	rsaModulus = cpp_int(modulus);
}

void Cryptography::setRSAExponent(std::string exponent)
{
	rsaExponent = cpp_int(exponent);
}

std::unique_ptr<unsigned char[]> Cryptography::rsaEncrypt(unsigned char toEncrypt[], int toEncryptLen, int* encryptedMessageLen)
{
    // Convert to a big int
    cpp_int dataBigInt = 0;
    for (int i = 0; i < toEncryptLen; ++i)
    {
        dataBigInt <<= 8;
        dataBigInt += toEncrypt[i];
    }

    // Data encrypting...
    cpp_int encrypted = powm(dataBigInt, rsaExponent, rsaModulus);

    // Convert encrypted BigInteger to a byte buffer
    std::vector<unsigned char> encryptedBuffer;
    while (encrypted > 0)
    {
        encryptedBuffer.insert(encryptedBuffer.begin(), (unsigned char)(encrypted % 256));
        encrypted /= 256;
    }

    *encryptedMessageLen = static_cast<int>(encryptedBuffer.size());

    std::unique_ptr<unsigned char[]> encryptedMessage(new unsigned char[*encryptedMessageLen]);
    std::copy(encryptedBuffer.begin(), encryptedBuffer.end(), encryptedMessage.get());

    return std::move(encryptedMessage);
}

void Cryptography::xteaEncrypt(unsigned char data[], int length, const int keys[])
{
    int blocks = length / 8;
    uint32_t* input = reinterpret_cast<uint32_t*>(&data[0]);
    uint32_t v0, v1, sum;

    for (int i = 0; i < blocks; i++)
    {
        v0 = input[2 * i];
        v1 = input[2 * i + 1];
        sum = 0;
        for (int j = 0; j < XTEA_NUM_ROUNDS; j++) {
            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + keys[sum & 3]);
            sum += XTEA_DELTA;
            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + keys[(sum >> 11) & 3]);
        }
        input[2 * i] = v0;
        input[2 * i + 1] = v1;
    }

    // Convert from little-endian to big-endian
    for (int i = 0; i < length; i += 4)
    {
        uint32_t& word = input[i / 4];
        word = ((word << 24) & 0xff000000) |
            ((word << 8) & 0x00ff0000) |
            ((word >> 8) & 0x0000ff00) |
            ((word >> 24) & 0x000000ff);
    }
}

//void Cryptography::xteaEncrypt(Buffer& toEncrypt, int key[])
//{
//    // This doubles as the size of the buffer
//    int currentWritePos = toEncrypt.getReadableBytes();
//
//    int blocks = currentWritePos / 8;
//
//    for (int i = 0; i < blocks; ++i) {
//        int v0 = toEncrypt.readUnsignedInt();
//        int v1 = toEncrypt.readUnsignedInt();
//        int sum = 0;
//        int delta = -1640531527;
//
//        for (int j = 32; j-- > 0; v1 += ((v0 >> 5) ^ (v0 << 4)) + v0 ^ sum + key[(sum >> 11) & 1356857347]) {
//            v0 += v1 + ((v1 << 4) ^ (v1 >> 5)) ^ sum + key[3 & sum];
//            sum += delta;
//        }
//
//        toEncrypt.writeInt(v0);
//        toEncrypt.writeInt(v1);
//    }
//
//    toEncrypt.setWritePosition(currentWritePos);
//}

std::unique_ptr<int[]> Cryptography::generateKeysOrNonces(int size)
{
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));

    std::unique_ptr<int[]> ptr = std::make_unique<int[]>(size);
    for (int i = 0; i < size; ++i)
    {
        ptr[i] = static_cast<int>(9.9999999E7 * (static_cast<double>(rand()) / RAND_MAX));
    }

    return std::move(ptr);
}
