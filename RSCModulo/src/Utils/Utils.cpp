#include <sstream>

#include "Utils.h"

std::wstring Utils::formatPasswordString(int totalLen, std::wstring& s)
{
    std::wstringstream formattedString;
    for (int i = 0; i < totalLen; ++i)
    {
        if (i >= s.length())
        {
            // If we've past the length of the original string,
            // we start adding spaces until we reach the specified length
            formattedString << L" ";
        }

        else
        {
            // Check for allowed characters
            // If a character is allowed, we'll add it to the new string
            wchar_t c = s.at(i);
            if (c >= 97 && c <= 122)
            {
                formattedString << c;
            }

            else if (c >= 65 && c <= 90)
            {
                formattedString << c;
            }

            else if (c >= 48 && c <= 57)
            {
                formattedString << c;
            }

            // If the character isn't allowed, we replace it with an underscore
            else
            {
                formattedString << L'_';
            }
        }
    }

    return formattedString.str();
}

std::string Utils::convertUnicodeString(std::wstring& s)
{
    std::stringstream convertedString;
    for (int i = 0; i < s.length(); ++i)
    {
        wchar_t c = s.at(i);
        if (c > 0 && c < L'\200' || c >= L'\240' && c <= L'\377')
        {
            convertedString << static_cast<char>(c);
        }

        else if (c == '\u20AC')
        {
            convertedString << static_cast<char>(-128);
        }

        else if (c == '\u201A')
        {
            convertedString << static_cast<char>(-126);
        }

        else if (c == '\u0192')
        {
            convertedString << static_cast<char>(-125);
        }

        else if (c == '\u201E')
        {
            convertedString << static_cast<char>(-124);
        }

        else if (c == '\u2026')
        {
            convertedString << static_cast<char>(-123);
        }

        else if (c == '\u2020')
        {
            convertedString << static_cast<char>(-122);
        }

        else if (c == '\u2021')
        {
            convertedString << static_cast<char>(-121);
        }

        else if (c == '\u02C6')
        {
            convertedString << static_cast<char>(-120);
        }

        else if (c == '\u2030')
        {
            convertedString << static_cast<char>(-119);
        }

        else if (c == '\u0160')
        {
            convertedString << static_cast<char>(-118);
        }

        else if (c == '\u2039')
        {
            convertedString << static_cast<char>(-117);
        }

        else if (c == '\u0152')
        {
            convertedString << static_cast<char>(-116);
        }

        else if (c == '\u017D')
        {
            convertedString << static_cast<char>(-114);
        }

        else if (c == '\u2018')
        {
            convertedString << static_cast<char>(-111);
        }

        else if (c == '\u2019')
        {
            convertedString << static_cast<char>(-110);
        }

        else if (c == '\u201C')
        {
            convertedString << static_cast<char>(-109);
        }

        else if (c == '\u201D')
        {
            convertedString << static_cast<char>(-108);
        }

        else if (c == '\u2022')
        {
            convertedString << static_cast<char>(-107);
        }

        else if (c == '\u2013')
        {
            convertedString << static_cast<char>(-106);
        }

        else if (c == '\u2014')
        {
            convertedString << static_cast<char>(-105);
        }

        else if (c == '\u02DC')
        {
            convertedString << static_cast<char>(-104);
        }

        else if (c == '\u2122')
        {
            convertedString << static_cast<char>(-103);
        }

        else if (c == '\u0161')
        {
            convertedString << static_cast<char>(-102);
        }

        else if (c == '\u203A')
        {
            convertedString << static_cast<char>(-101);
        }

        else if (c == '\u0153')
        {
            convertedString << static_cast<char>(-100);
        }

        else if (c == '\u017E')
        {
            convertedString << static_cast<char>(-98);
        }

        else if (c == '\u0178')
        {
            convertedString << static_cast<char>(-97);
        }

        else
        {
            convertedString << static_cast<char>('?');
        }

    }

    return convertedString.str();
}
