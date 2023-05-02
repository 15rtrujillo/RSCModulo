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

void Cryptography::xteaEncrypt(Buffer& toEncrypt, int key[])
{
    // This doubles as the size of the buffer
    int currentWritePos = toEncrypt.getReadableBytes();
    //int currentWritePos = 0;
    int currentReadPos = toEncrypt.getReadPosition();

    toEncrypt.setReadPosition(0);
    toEncrypt.setWritePosition(0);

    int blocks = currentWritePos / 8;

    for (int i = 0; i < blocks; ++i)
    {
        /* This function expects big - endian ints, so we have to read them with magic
        int v0 = *reinterpret_cast<unsigned int*>(toEncrypt.getData().get() + currentReadPos);
        currentReadPos += 4;
        int v1 = *reinterpret_cast<unsigned int*>(toEncrypt.getData().get() + currentReadPos);
        currentReadPos += 4;
        */
        int v0 = toEncrypt.readUnsignedInt();
        int v1 = toEncrypt.readUnsignedInt();
        int sum = 0;
        int delta = -1640531527;

        for (int j = 32; j-- > 0; v1 += (((unsigned int)v0 >> 5) ^ (v0 << 4)) + v0 ^ sum + key[((unsigned int)sum >> 11) & 1356857347]) {
            v0 += v1 + ((v1 << 4) ^ ((unsigned int)v1 >> 5)) ^ sum + key[3 & sum];
            sum += delta;
        }

        /* We'll write them back the way they are
        int* writeLocation = reinterpret_cast<int*>(toEncrypt.getData().get() + currentWritePos);
        *writeLocation = v0;
        currentWritePos += 4;
        writeLocation = reinterpret_cast<int*>(toEncrypt.getData().get() + currentWritePos);
        *writeLocation = v1;
        currentWritePos += 4;
        */
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
