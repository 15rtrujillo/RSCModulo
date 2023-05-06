#include <iostream>
#include <memory>

#include "Networking/Buffer.h"
#include "Networking/Networking.h"
#include "Networking/PacketBuilder.h"
#include "Networking/Crypto/Cryptography.h"
#include "Utils/ConfigFile.h"
#include "Utils/Utils.h"

int main(int argc, char* argv[])
{	
	ConfigFile configFile("client.config");

	std::wstring username, password;

	std::cout << "Please enter your username: ";
	std::getline(std::wcin, username);
	std::cout << "Please enter your password: ";
	std::getline(std::wcin, password);

	// Create the login packet
	PacketBuilder packet(0);
	packet.writeByte(0); // Not reconnecting
	packet.writeInt(235); // Client version

	Buffer loginBlock(128);
	loginBlock.writeByte(10); // checksum?
	loginBlock.readByte();

	// Put ISAAC/XTEA keys
	std::unique_ptr<int[]> key = Cryptography::generateKeysOrNonces(4);
	for (int i = 0; i < 4; ++i)
	{
		loginBlock.writeInt(key[i]);
		std::cout << "Key " << i << " " << key[i] << std::endl;
		std::cout << "Key Read " << i << " " << loginBlock.readInt() << std::endl;
	}

	// Write the formatted password
    // Java Strings are always unicode, so we need to use wstrings when taking input
	// However, we have to convert the string before sending it over the network
	std::wstring formattedPassword = Utils::formatPasswordString(20, password);
	loginBlock.writeCString(Utils::convertUnicodeString(formattedPassword));

	// Generate and write 5 nonces
	std::unique_ptr<int[]> nonces = Cryptography::generateKeysOrNonces(5);
	for (int i = 0; i < 5; ++i)
	{
		loginBlock.writeInt(nonces[i]);
		std::cout << "nonce " << i << " " << nonces[i] << std::endl;
	}

	// Write a 3 byte nonce for some reason
	loginBlock.write3ByteInt(Cryptography::generateKeysOrNonces(1)[0]);

	// Encrypt the login block
	Cryptography::setRSAModulus(configFile.getSetting("rsa_modulus"));
	Cryptography::setRSAExponent(configFile.getSetting("rsa_exponent"));

	std::unique_ptr<int> encryptedLen(new int);

	std::unique_ptr<unsigned char[]> encryptedLoginBlock = Cryptography::rsaEncrypt(
		loginBlock.getData().get(), loginBlock.getReadableBytes(), encryptedLen.get());

	std::cout << std::endl << "og: " << loginBlock.getReadableBytes() << " encrypted: " << *encryptedLen << std::endl;

	// Write the length of RSA block
	packet.writeUnsignedShort(static_cast<unsigned short>(*encryptedLen));
	packet.writeBytes(encryptedLoginBlock.get(), *encryptedLen);

	// Time for the XTEA block
	Buffer xteaBlock(64);

	// Write limit30 (who knows)
	xteaBlock.writeByte(0);

	// Write 24 random bytes. I *think* I'm suppsoed to use a different RNG function for this,
	// but I don't care
	std::unique_ptr<int[]> noncesAgain = Cryptography::generateKeysOrNonces(6);
	for (int i = 0; i < 6; ++i)
	{
		xteaBlock.writeInt(noncesAgain[i]);
		std::cout << "nonce " << (i + 6) << " " << noncesAgain[i] << std::endl;
	}

	// Write the username
	xteaBlock.writeCString(Utils::convertUnicodeString(username));

	// Encrypt the XTEA block. This shouldn't need to be captured as a return value
	Cryptography::xteaEncrypt(xteaBlock, key.get());

	packet.writeUnsignedShort(xteaBlock.getReadableBytes());
	packet.writeBytes(xteaBlock);

	Networking::initializeConnection(configFile.getSetting("ip").c_str(), configFile.getSetting("port").c_str());
	int result = Networking::connectToServer();
	if (result != 0)
	{
		std::cout << "An error has occurred" << std::endl;
		return 1;
	}

	Networking::sendPacket(packet.toPacket());

	std::cin.get();

	return 0;
}