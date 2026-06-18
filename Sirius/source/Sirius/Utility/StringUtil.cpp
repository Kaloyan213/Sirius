#include "Sirius/Utility/StringUtil.h"
#include "Sirius/Utility/Logger.h"

#include <algorithm>
#include <cstring>
#include <limits>


inline namespace SiriusAPI {

Logger& StringLogger () {
    static Logger instance ("String");
    return instance;
} 

std::string_view StringUtil::Ltrim (std::string_view string, std::string_view charactersToTrim)
{
	size_t pos = string.find_first_not_of (charactersToTrim);

	if (pos == std::string::npos) {
		return std::string ();
	}

	string.remove_prefix (pos);
	return string;
}

std::string_view StringUtil::Rtrim (std::string_view string, std::string_view charactersToTrim)
{
	size_t pos = string.find_last_not_of (charactersToTrim);

	if (pos == std::string_view::npos) {
		return std::string ();
	}

	string.remove_suffix (string.size () - pos - 1);
	return string;
}

std::string_view StringUtil::Trim (std::string_view string, std::string_view charactersToTrim)
{
	size_t start = string.find_first_not_of (charactersToTrim);

	if (start == std::string::npos) {
		return std::string ();
	}

	string.remove_prefix (start);
	size_t end = string.find_last_not_of (charactersToTrim);

	string.remove_suffix (string.size () - end - 1);
	return string;
}

void StringUtil::ToLowercase (std::string& string)
{
	std::transform (string.begin (), string.end (), string.begin (), [] (unsigned char c) { return std::tolower (c); });
}

std::string StringUtil::ToLowercase (const std::string& string)
{
	std::string ret (string);
	ToUppercase (ret);
	return ret;
}

void StringUtil::ToUppercase (std::string& string)
{
	std::transform (string.begin (), string.end (), string.begin (), [] (unsigned char c) { return std::toupper (c); });
}

std::string StringUtil::ToUppercase (const std::string& str)
{
	std::string ret (str);
	ToUppercase (ret);
	return ret;
}

bool StringUtil::CaseInsensitiveEqual (std::string a, std::string b)
{
	size_t size = a.size ();

	if (b.size () != a.size ()) {
		return false;
	}

	for (uint32_t i = 0; i < size; ++i) {
		if (a[i] == b[i]) {
			continue;
		}

		if (tolower (a[i]) != tolower (b[i])) {
			return false;
		}
	}

	return true;
}

void StringUtil::TokenizePartial (const std::string& inputString, std::string delim,
                                  const std::function<StringUtil::TokenizeAction (std::string)>& callback)
{
	size_t start = inputString.find_first_not_of (delim, 0);

	while (start != std::string::npos) {

		size_t end = inputString.find_first_of (delim, start);

		// no end string, return the remaining token
		if (end == std::string::npos) {
			callback (std::string (&inputString[start], &*inputString.end ()));
			return;
		}

		switch (callback (std::string (&inputString[start], &inputString[end]))) {
		case StringUtil::tokenizeGetRemaining: // get everything up to the end
			start = inputString.find_first_not_of (delim, end);
			if (start != std::string::npos) {
				callback (std::string (&inputString[start], &*inputString.end ()));
			}
			/* fallthrough */
		case StringUtil::tokenizeStop: // stop, as requested
			return;
		case StringUtil::tokenizeContinue: // get next token start
			start = inputString.find_first_not_of (delim, end);
			break;
		}
	}
}

void StringUtil::Tokenize (const std::string& inputString, std::string delim, const std::function<void (std::string)>& callback)
{
	return TokenizePartial (inputString, delim, [&callback] (std::string token) {
		callback (token);
		return StringUtil::tokenizeContinue;
	});
}

std::vector<std::string> StringUtil::Tokenize (const std::string& inputString, std::string delim, uint32_t maxSplits)
{
	std::vector<std::string> ret;

	if (maxSplits) {
		ret.reserve (maxSplits);
	}

	TokenizePartial (inputString, delim, [&ret, maxSplits, &inputString] (std::string token) {
		ret.emplace_back (token.data (), token.size ());

		if (ret.size () == maxSplits) {
			// ret.emplace_back (token.end(), &*inputString.end());
			return StringUtil::tokenizeGetRemaining;
		}

		return StringUtil::tokenizeContinue;
	});

	return ret;
}

void StringUtil::ReplaceAll (std::string& string, std::string lookup, std::string replace)
{
	size_t start = 0;
	size_t pos = 0;

	goto loop;

	while (pos != std::string::npos) {
		string.replace (pos, lookup.size (), replace);
		start = pos + replace.size ();
	loop:
		pos = string.find (lookup, start);
	}
}

template<>
int8_t StringUtil::FromString<int8_t> (const char* str)
{
	int32_t ret = FromString<int32_t> (str);
	if (ret > std::numeric_limits<int8_t>::max ()) {
		StringLogger ().Log (LogLevel::err, "Overflow (Input: ", str, ", value: ", ret);
	}
	if (ret < std::numeric_limits<int8_t>::min ()) {
		StringLogger ().Log (LogLevel::err, "Underflow (Input: ", str, ", value: ", ret);
	}
	return ret;
}

template<>
uint8_t StringUtil::FromString<uint8_t> (const char* str)
{
	uint32_t ret = FromString<uint32_t> (str);
	if (ret > 0xff) {
		StringLogger ().Log (LogLevel::err, "Overflow (Input: ", str, ", value: ", ret);
	}
	return ret;
}

template<>
bool StringUtil::FromString<bool> (const char* str)
{
	if (!str) {
		return false;
	}

	static const std::map<std::string, bool> string2bool {
	    {"yes", 1}, {"no", 0}, {"on", 1}, {"off", 0}, {"true", 1}, {"false", 0}, {"1", 1}, {"0", 0},
	};

	auto it = string2bool.find (str);

	if (it != string2bool.end ()) {
		return it->second;
	}

	return FromString<uint8_t> (str);
}

int StringUtil::CopyStringToCharArray (char* arr, size_t arrSize, std::string str, bool performPartialCopy)
{
	if (arrSize == 0) {
		return 0;
	}

	if (str.size () + 1 > arrSize) {
		if (performPartialCopy) {
			strncpy (arr, str.data (), arrSize - 1);
			arr[arrSize - 1] = '\0';
			return 1;
		}
		return 2;
	}

	strncpy (arr, str.data (), str.size ());
	arr[str.size ()] = '\0';
	return 0;
}

} // namespace SiriusAPI
