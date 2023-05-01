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

std::unique_ptr<char[]> Cryptography::rsaEncrypt(char toEncrypt[], int toEncryptLen, int* encryptedMessageLen)
{
    // Convert to a big int
    cpp_int dataBigInt = 0;
    for (int i = 0; i < toEncryptLen; ++i) {
        dataBigInt <<= 8;
        dataBigInt += toEncrypt[i];
    }

    // Data encrypting...
    cpp_int encrypted = powm(dataBigInt, rsaExponent, rsaModulus);

    // Convert encrypted BigInteger to a byte buffer
    std::vector<char> encryptedBuffer;
    while (encrypted > 0) {
        encryptedBuffer.insert(encryptedBuffer.begin(), (unsigned char)(encrypted % 256));
        encrypted /= 256;
    }

    *encryptedMessageLen = static_cast<int>(encryptedBuffer.size());

    std::unique_ptr<char[]> encryptedMessage(new char[*encryptedMessageLen]);
    std::copy(encryptedBuffer.begin(), encryptedBuffer.end(), encryptedMessage.get());

    return std::move(encryptedMessage);
}

void Cryptography::xteaEncrypt(char toEncrypt[], int toEncryptLen, int key[])
{
    // Make sure data is aligned to 8 bytes
    int extraBytes = toEncryptLen % 8;

    if (extraBytes != 0)
    {
        extraBytes = 8 - extraBytes;
        toEncryptLen += extraBytes;
        memset(toEncrypt + toEncryptLen - extraBytes, 0, extraBytes);
    }

    // Encrypt data in 8-byte blocks
    uint32_t* dataWords = reinterpret_cast<uint32_t*>(toEncrypt);
    uint32_t* keyWords = reinterpret_cast<uint32_t*>(const_cast<int*>(key));
    int num_blocks = toEncryptLen / 8;
    for (int i = 0; i < num_blocks; i++)
    {
        xteaEncrypt(dataWords + i * 2, keyWords);
    }
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

void Cryptography::xteaEncrypt(uint32_t data[2], const uint32_t key[4])
{
    uint32_t sum = 0;
    uint32_t delta = 0x9e3779b9;
    uint32_t v0 = data[0], v1 = data[1];
    for (int i = 0; i < 32; i++) {
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
        sum += delta;
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
    }
    data[0] = v0;
    data[1] = v1;
}
