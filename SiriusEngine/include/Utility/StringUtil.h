/* 
 * Copyright (c) Kaloyan Badankov
 */

#pragma once

#include "Core/Core.h"

#include <stddef.h>
#include <stdint.h>
#include <functional>
#include <sstream>
#include <vector>
#include <string>

/**
 * @brief Static String utility class that provides various string manipulation functions.
 * 
 */

inline namespace SiriusAPI {

class SIRIUS_API StringUtil {
public:
    enum TokenizeAction {
        tokenizeContinue,
		tokenizeStop,   
		tokenizeGetRemaining
    };

	/**
	 * @brief Left trim the string by removing all characters to the left of the first non 'charactersToTrim' value.
	 * 
	 * @param string String to be trimmed
	 * @param charactersToTrim What characters to trim from the string. Default is whitespace and tab.
	 * @return std::string_view The string view after trimming
	 */
	static std::string_view Ltrim (std::string_view string, std::string_view charactersToTrim = " \t");
	/**
	 * @brief Right trim the string by removing all characters to the right of the last non 'charactersToTrim' value.
	 * 
	 * @param string String to be trimmed
	 * @param charactersToTrim What characters to trim from the string. Default is whitespace and tab.
	 * @return std::string_view 
	 */
	static std::string_view Rtrim (std::string_view string, std::string_view charactersToTrim = " \t");
	/**
	 * @brief Ltrim and rtrim the string by removing all characters to the left and right of the first and last non 'charactersToTrim' value.
	 * 
	 * @param string String to be trimmed
	 * @param charactersToTrim What characters to trim from the string. Default is whitespace and tab.
	 * @return std::string_view 
	 */
	static std::string_view Trim (std::string_view string, std::string_view charactersToTrim = " \t");

	/**
	 * @brief ToLowercase the string in place.
	 * 
	 * @param string String to be converted to lowercase
	 */
	static void ToLowercase (std::string& string);

	/**
	 * @brief ToLowercase the string and return a new string.
	 * 
	 * @param string String to be converted to lowercase
	 * @return std::string New string in lowercase
	 */
	static std::string ToLowercase (const std::string& string);

	/**
	 * @brief ToUppercase the string in place.
	 * 
	 * @param string String to be converted to uppercase
	 */
	static void ToUppercase (std::string& string);

	/**
	 * @brief ToUppercase the string and return a new string.
	 * 
	 * @param string String to be converted to uppercase
	 * @return std::string New string in uppercase
	 */
	static std::string ToUppercase (const std::string& string);

	/**
	 * @brief Compares two strings in a case-insensitive manner.
	 * 
	 * @param a String a to compare
	 * @param b String b to compare
	 * @return bool True if the strings are equal, false otherwise 
	 */
	static bool CaseInsensitiveEqual (std::string a, std::string b);
    
	static std::vector<std::string> Tokenize (const std::string& inputString, std::string delim, uint32_t maxSplits = 0);
	static void Tokenize (const std::string& inputString, std::string delim, const std::function<void (std::string)>& callback);
	static void TokenizePartial (const std::string& inputString, std::string delim, const std::function<TokenizeAction (std::string)>& callback);

	/**
	 * @brief Replaces all occurrences of 'lookup' in 'string' with 'replace'.
	 * 
	 * @param string String to perform the replacement on. This string will be modified in place.
	 * @param lookup String to be replaced.
	 * @param replace String to replace 'lookup' with.
	 */
	static void ReplaceAll (std::string& string, std::string lookup, std::string replace);

	/**
	 * @brief Template function to convert a stream and arguments into a string.
	 * 
	 * @param stream Stream to be used for conversion. 
	 * @param args Additional arguments to be added to the stream.
	 * @return std::string String representation of the stream and arguments.
	 */
	template<typename... Args>
	static std::string FromStream (std::stringstream stream, Args&&... args)
	{
		(stream << ... << args);
		return stream.str ();
	}

	/**
	 * @brief Template function to convert arguments into a string using a stringstream.
	 * 
	 * @param args Arguments to be added to the stream. 
	 * @return std::string Returns the string representation of the arguments.
	 */
	template<typename... Args>
	static std::string FromStream (Args&&... args)
	{
		return FromStream (std::stringstream (), std::forward<Args> (args)...);
	}

	/**
	 * @brief Template function to convert a value of type T into a string.
	 * 
	 * @param value Value to be converted into a string.
	 * @return std::string Returns the string representation of the value.
	 */
	template<typename T>
	static std::string ToString (const T& value)
	{
		return std::to_string (value);
	}

	/**
	 * @brief Function returns a copy of the string. This is a specialization for std::string and char* types to avoid unnecessary conversions.
	 * 
	 * @param str Value to copy into a new string.
	 * @return std::string Returns a copy of the string.
	 */
	static std::string ToString (const std::string& str)
	{
		return str;
	}

	/**
	 * @brief Used to convert a C-style string (char*) to a std::string. This is a specialization for char* types to avoid unnecessary conversions.
	 * 
	 * @param str C-style string to convert to std::string.
	 * @return std::string Results in a std::string copy of the C-style string.
	 */
	static std::string ToString (const char* str)
	{
		return str;
	}

	/**
	 * @brief Used to convert a C-style string (char*) to a std::string. This is a specialization for char* types to avoid unnecessary conversions.
	 * 
	 * @param str C-style string to convert to std::string.
	 * @return std::string Results in a std::string copy of the C-style string.
	 */
	static std::string ToString (char* str)
	{
		return str;
	}

	/**
	 * @brief  Template function to convert a string to a value of type T. This function is specialized for certain types (int8_t, uint8_t, bool, std::string) to handle their specific conversion needs.
	 * 
	 * @param str String to be converted to type T.
	 * @return T Returns the value of type T converted from the string.
	 */
	template<typename T>
	static T FromString (const char* str);

	/**
	 * @brief Template function to convert a string to a value of type T with a default value. If the string is null, the default value is returned. This function is specialized for certain types (int8_t, uint8_t, bool, std::string) to handle their specific conversion needs.
	 * 
	 * @param str String to be converted to type T.
	 * @param defaultValue Default value to return if the string is null.
	 * @return T Returns the value of type T converted from the string, or the default value if the string is null.
	 */
	template<typename T>
	static T FromString (const char* str, T defaultValue);

	/**
	 * @brief Template function to convert a std::string to a value of type T. This function is specialized for certain types (int8_t, uint8_t, bool, std::string) to handle their specific conversion needs.
	 * 
	 * @param str String to be converted to type T. 
	 * @return T Returns the value of type T converted from the string.
	 */
	template<typename T>
	static T FromString (const std::string& str)
	{
		return FromString<T> (str.c_str ());
	}

	/**
	 * @brief Template function to convert a std::string to a value of type T with a default value. If the string is empty, the default value is returned. This function is specialized for certain types (int8_t, uint8_t, bool, std::string) to handle their specific conversion needs.
	 * 
	 * @param str String to be converted to type T.
	 * @param defaultValue Default value to return if the string is empty.
	 * @return T Returns the value of type T converted from the string, or the default value if the string is empty.
	 */
	template<typename T>
	static T FromString (const std::string& str, T defaultValue)
	{
		return FromString<T> (str.c_str (), defaultValue);
	}

	/**
	 * @brief Copies a string into a character array. If the string is larger than the array, it will either copy as much as possible or return an error based on the 'performPartialCopy' flag.
	 * 
	 * @tparam N Size of the character array.
	 * @param str String to be copied into the character array.
	 * @param performPartialCopy Specifies whether to perform a partial copy if the string is larger than the array. If true, it will copy as much as possible and null-terminate the array. If false, it will return an error code.
	 * @return constexpr int Returns 0 on success, 1 if a partial copy was performed, and 2 if the string is too large and no copy was performed.
	 */
	template<size_t N>
	static constexpr int CopyStringToCharArray (char (&arr)[N], std::string str, bool performPartialCopy)
	{
		static_assert (N > 1, "Expecting array size to be greater than 1");
		return CopyStringToCharArray (arr, N, str, performPartialCopy);
	}

	/**
	 * @brief Copies a string into a character array. If the string is larger than the array, it will either copy as much as possible or return an error based on the 'performPartialCopy' flag.
	 * 
	 * @param arr Array pointer to copy the string into.
	 * @param arrSize Size of the character array to copy the string into. 
	 * @param str String to be copied into the character array.
	 * @param performPartialCopy Specifies whether to perform a partial copy if the string is larger than the array. If true, it will copy as much as possible and null-terminate the array. If false, it will return an error code.
	 * @return int Returns 0 on success, 1 if a partial copy was performed, and 2 if the string is too large and no copy was performed.
	 */
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
