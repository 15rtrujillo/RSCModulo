#include <chrono>
#include <cstdlib>
#include <vector>
#include <boost/endian/conversion.hpp>
#include <boost/multiprecision/cpp_int.hpp>


#include "Cryptography.h"

namespace mp = boost::multiprecision;

mp::cpp_int Cryptography::rsaModulus = 0;
mp::cpp_int Cryptography::rsaExponent = 0;

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
	rsaModulus = mp::cpp_int(modulus);
}

void Cryptography::setRSAExponent(std::string exponent)
{
	rsaExponent = mp::cpp_int(exponent);
}

std::unique_ptr<unsigned char[]> Cryptography::rsaEncrypt(unsigned char toEncrypt[], int toEncryptLen, int* encryptedDataLen)
{
    // Convert the buffer to a big-endian cpp_int
    mp::cpp_int data;
    mp::import_bits(data, toEncrypt, toEncrypt + toEncryptLen);

    // Perform moduluar exponentiation
    mp::cpp_int encrypted = mp::powm(data, rsaExponent, rsaModulus);

    // Export into 8-bit unsigned values, most significant bit first:
    std::vector<unsigned char> bytes;

    mp::export_bits(encrypted, std::back_inserter(bytes), 8);

    // Put them in the buffer
    std::unique_ptr<unsigned char[]> encryptedData = std::make_unique<unsigned char[]>(bytes.size());
    std::memcpy(encryptedData.get(), bytes.data(), bytes.size());

    // Return stuff
    *encryptedDataLen = bytes.size();
    return std::move(encryptedData);
}

void Cryptography::xteaEncrypt(Buffer& toEncrypt, int key[])
{
    int currentWritePos = toEncrypt.getReadableBytes();
    int currentReadPos = toEncrypt.getReadPosition();

    toEncrypt.setReadPosition(0);
    toEncrypt.setWritePosition(0);

    int blocks = currentWritePos / 8;

    for (int i = 0; i < blocks; ++i)
    {
        int v0 = toEncrypt.readUnsignedInt();
        int v1 = toEncrypt.readUnsignedInt();
        int sum = 0;
        int delta = -1640531527;

        for (int j = 32; j-- > 0; v1 += (((unsigned int)v0 >> 5) ^ (v0 << 4)) + v0 ^ sum + key[((unsigned int)sum >> 11) & 1356857347]) {
            v0 += v1 + ((v1 << 4) ^ ((unsigned int)v1 >> 5)) ^ sum + key[3 & sum];
            sum += delta;
        }

        toEncrypt.writeInt(v0);
        toEncrypt.writeInt(v1);
    }

    toEncrypt.setReadPosition(currentReadPos);
    toEncrypt.setWritePosition(currentWritePos);
}

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
