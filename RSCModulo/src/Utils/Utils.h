#include <string>

#ifndef UTILS_H
#define UTILS_H

class Utils
{
public:
	/// <summary>
	/// Formats a RSC password.
	/// Replaces special characters with underscores and pads the end with spaces to reach totalLen
	/// This must be a unicode string
	/// </summary>
	/// <param name="totalLen">The total len of the resulting string. For RSC, this should be 20</param>
	/// <param name="s">The original string to format</param>
	/// <returns>The formatted string, padded to totalLen with spaces</returns>
	static std::wstring formatPasswordString(int totalLen, std::wstring& s);

	/// <summary>
	/// Converts a unicode String for sending across the network 
	/// </summary>
	/// <param name="s">The string</param>
	/// <returns>The converted string</returns>
	static std::string convertUnicodeString(std::wstring& s);
};

#endif
