#pragma once

#include "Core/Core.h"

#include <stddef.h>
#include <stdint.h>
#include <functional>
#include <map>
#include <sstream>
#include <vector>
#include <string>


inline namespace SiriusAPI {

class SIRIUS_API StringUtil {
public:
    enum TokenizeAction {
        tokenizeContinue,
		tokenizeStop,   
		tokenizeGetRemaining
    };

	static std::string_view Ltrim (std::string_view string, std::string_view charactersToTrim = " \t");
	static std::string_view Rtrim (std::string_view string, std::string_view charactersToTrim = " \t");
	static std::string_view Trim (std::string_view string, std::string_view charactersToTrim = " \t");

	static void ToLowercase (std::string& string);
	static std::string ToLowercase (const std::string& string);
	static void ToUppercase (std::string& string);

	static std::string ToUppercase (const std::string& string);
	static bool CaseInsensitiveEqual (std::string a, std::string b);
    
	static std::vector<std::string> Tokenize (const std::string& inputString, std::string delim, uint32_t maxSplits = 0);
	static void Tokenize (const std::string& inputString, std::string delim, const std::function<void (std::string)>& callback);
	static void TokenizePartial (const std::string& inputString, std::string delim, const std::function<TokenizeAction (std::string)>& callback);

	static void ReplaceAll (std::string& string, std::string lookup, std::string replace);

	template<typename... Args>
	static std::string FromStream (std::stringstream stream, Args&&... args)
	{
		(stream << ... << args);
		return stream.str ();
	}

	template<typename... Args>
	static std::string FromStream (Args&&... args)
	{
		return FromStream (std::stringstream (), std::forward<Args> (args)...);
	}

	template<typename T>
	static std::string ToString (const T& value)
	{
		return std::to_string (value);
	}

	static std::string ToString (const std::string& str)
	{
		return str;
	}

	static std::string ToString (const char* str)
	{
		return str;
	}

	static std::string ToString (char* str)
	{
		return str;
	}

	template<typename T>
	static T FromString (const char* str);

	template<typename T>
	static T FromString (const char* str, T defaultValue);

	template<typename T>
	static T FromString (const std::string& str)
	{
		return FromString<T> (str.c_str ());
	}

	template<typename T>
	static T FromString (const std::string& str, T defaultValue)
	{
		return FromString<T> (str.c_str (), defaultValue);
	}

	template<size_t N>
	static constexpr int CopyStringToCharArray (char (&arr)[N], std::string str, bool performPartialCopy)
	{
		static_assert (N > 1, "Expecting array size to be greater than 1");
		return CopyStringToCharArray (arr, N, str, performPartialCopy);
	}

	static int CopyStringToCharArray (char* arr, size_t arrSize, std::string str, bool performPartialCopy);

private:
	StringUtil () = delete;
	~StringUtil () = delete;
};

template<>
int8_t StringUtil::FromString<int8_t> (const char* str);

template<>
uint8_t StringUtil::FromString<uint8_t> (const char* str);

template<>
inline const char* StringUtil::FromString<const char*> (const char* str)
{
	return str;
}

template<>
bool StringUtil::FromString<bool> (const char* str);

template<typename T>
inline T StringUtil::FromString (const char* str)
{
	static_assert (sizeof (T) > 1, "fromString called for char type, for which no overload exists");

	std::stringstream ss (str);

	T ret {};
	ss >> ret;
	return ret;
}

template<typename T>
inline T StringUtil::FromString (const char* str, T defaultValue)
{
	if (!str) {
		return defaultValue;
	}

	return FromString<T> (str);
}

template<>
inline std::string StringUtil::FromString<std::string> (const char* str)
{
	return str;
}

template<>
inline std::string StringUtil::FromString<std::string> (const std::string& str)
{
	return str;
}

} //namespace SiriusAPI
