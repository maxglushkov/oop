#include <algorithm>
#include <climits>
#include <iostream>
#include "format-int.h"
using std::string;

constexpr int MIN_RADIX = 2;
constexpr int MAX_RADIX = 36;
constexpr char DIGITS[MAX_RADIX + 1] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

bool IsValidRadix(int radix)
{
	return radix >= MIN_RADIX && radix <= MAX_RADIX;
}

int StringToInt(const std::string & str, int radix, bool & wasError)
{
	wasError = true;
	if (!IsValidRadix(radix)) return 0;

	auto iter = str.begin();
	if (iter == str.end()) return 0;

	bool isNegative = false;
	if (*iter == '-')
	{
		++iter;
		isNegative = true;
	}

	static_assert(sizeof(long long) > sizeof(int), "long long must be wider than int");
	long long number = 0;
	for (; iter != str.end(); ++iter)
	{
		const char c = *iter;
		unsigned char digit = 0;
		for (;; ++digit)
		{
			if (digit == radix) return 0;
			if (c == DIGITS[digit]) break;
		}

		number = number * radix + digit;
		if (isNegative ? -number < INT_MIN : number > INT_MAX) return 0;
	}

	wasError = false;
	return isNegative ? -number : number;
}

string IntToString(int n, int radix, bool & wasError)
{
	wasError = true;
	if (!IsValidRadix(radix)) return string();

	string str;
	if (n == 0)
	{
		str.push_back(DIGITS[0]);
	}
	else
	{
		long long number = n;
		if (number < 0) number = -number;
		while (number)
		{
			str.push_back(DIGITS[number % radix]);
			number /= radix;
		}

		if (n < 0) str.push_back('-');
		reverse(str.begin(), str.end());
	}
	wasError = false;
	return str;
}

string ChangeRadix(const std::string & strValue, int sourceNotation, int destinationNotation)
{
	bool wasError;

	const int intValue = StringToInt(strValue, sourceNotation, wasError);
	if (wasError) return string();

	const string && strResult = IntToString(intValue, destinationNotation, wasError);
	if (wasError) return string();

	return strResult;
}

void PrintRadixConstraints()
{
	std::cerr << "Radix must be a decimal integer between " << MIN_RADIX << " and " << MAX_RADIX << ".\n";
}
