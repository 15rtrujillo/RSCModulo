#ifndef ISAAC_H
#define ISAAC_H

/// <summary>
/// An implementation of an ISAAC cipher.
/// </summary>
class ISAAC
{
public:
	/// <summary>
	/// The golden ratio
	/// </summary>
	static const int ratio = 0x9e3779b9;

	/// <summary>
	/// The log of the size of the results and memory arrays.
	/// </summary>
	static const int sizeLog = 8;

	/// <summary>
	/// The size of the results and memory arrays.
	/// </summary>
	static const int size = 1 << sizeLog;

	/// <summary>
	/// For pseudorandom lookup.
	/// </summary>
	static const int mask = (size - 1) << 2;

	/// <summary>
	/// Construct an ISAAC cypher
	/// </summary>
	ISAAC();

	/// <summary>
	/// Changes the cypher key
	/// </summary>
	/// <param name="seed">The seed</param>
	/// <param name="seedLen">The size of the seed array</param>
	void setKeys(int seed[], int seedLen);

	/// <summary>
	/// Resets the ISAAC cypher
	/// </summary>
	void reset();

	/// <summary>
	/// Gets the next value
	/// </summary>
	/// <returns>The next value</returns>
	int getNextValue();

	/// <summary>
	/// Generates 256 results
	/// </summary>
	void isaac();

	/// <summary>
	/// Initializes the ISAAC cypher
	/// </summary>
	/// <param name="flag">Flag indicating if we should perform a second pass.</param>
	void initialize(bool flag);

	/// <summary>
	/// Check if the keys have been set for this ISAAC instance
	/// </summary>
	/// <returns>True if the keys have been set</returns>
	bool areKeysSet();

private:
	/// <summary>
	/// The count through the results
	/// </summary>
	int count;

	/// <summary>
	/// The results
	/// </summary>
	int results[size];

	/// <summary>
	/// The internal memory state
	/// </summary>
	int memory[size];

	/// <summary>
	/// The accumulator
	/// </summary>
	int a;

	/// <summary>
	/// The last result
	/// </summary>
	int b;

	/// <summary>
	/// The counter
	/// </summary>
	int c;

	/// <summary>
	/// Have the keys been set?
	/// </summary>
	bool keysSet;
};

#endif
