#include <boost/multiprecision/cpp_int.hpp>
#include <memory>

#include "ISAAC.h"

#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

class Cryptography
{
public:
	/// <summary>
	/// Get a reference to the incoming ISAAC instance
	/// </summary>
	/// <returns>A reference to the incoming ISAAC instance</returns>
	static ISAAC& getIsaacIn();

	/// <summary>
	/// Get a reference to the outgoing ISAAC instance
	/// </summary>
	/// <returns>A reference to the outgoing ISAAC instance</returns>
	static ISAAC& getIsaacOut();

	/// <summary>
	/// Uses ISAAC encryption to encode an opcode
	/// </summary>
	/// <param name="opcode">The opcode to encode</param>
	/// <returns>The encoded opcode</returns>
	static int encodeOpcode(int opcode);

	/// <summary>
	/// Set the modulus portion of the RSA encryption key
	/// </summary>
	/// <param name="modulus">The RSA modulus</param>
	static void setRSAModulus(std::string modulus);

	/// <summary>
	/// Set the exponent portion of the RSA encryption key
	/// </summary>
	/// <param name="exponent">The RSA exponent</param>
	static void setRSAExponent(std::string exponent);

	/// <summary>
	/// Encrypt a byte array using RSA
	/// </summary>
	/// <param name="toEncrypt">The byte array to encrypt</param>
	/// <param name="toEncryptLen">The length of the byte array</param>
	/// <param name="encryptedMessageLen">The resulting encrypted byte array's length</param>
	/// <returns>The encrypted data</returns>
	static std::unique_ptr<unsigned char[]> rsaEncrypt(unsigned char toEncrypt[], int toEncryptLen, int* encryptedMessageLen);

	static std::unique_ptr<unsigned char[]> rsaDecrypt(unsigned char toDecrypt[], int toDecryptLen, int* decryptedMessageLen);

	/// <summary>
	/// Encrypts a block of data using XTEA
	/// </summary>
	/// <param name="toEncrypt">The data to be encrypted</param>
	/// <param name="toEncryptLen">The length of the encrypted data</param>
	/// <param name="key">The key for the XTEA encryption. This should be the same as the ISAAC key</param>
	/// <returns>The encrypted data. It should be the same length as the original</returns>
	static void xteaEncrypt(unsigned char toEncrypt[], int toEncryptLen, int key[]);

	/// <summary>
	/// Generates large, random numbers to use as nonces or keys
	/// </summary>
	/// <param name="size">The size of the nonce/key to generate. For ISAAC/XTEA keys, use 4</param>
	/// <returns>The generated key/nonces</returns>
	static std::unique_ptr<int[]> generateKeysOrNonces(int size);

	static boost::multiprecision::cpp_int rsaModulus;
	static boost::multiprecision::cpp_int rsaExponent;

private:


	/// <summary>
	/// Helper function used for XTEA encryption
	/// </summary>
	/// <param name="data">Two, eight-byte block of data</param>
	/// <param name="key">The 128-bit encryption key</param>
	static void xteaEncrypt(uint32_t data[2], const uint32_t key[4]);
};

#endif
