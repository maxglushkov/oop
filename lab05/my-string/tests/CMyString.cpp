#include <catch2/catch.hpp>
#include <sstream>
#include "../CMyString.h"
using std::string;

static void TestMyStringOrdering(CMyString const& lhs, CMyString const& rhs, int expectedOrd)
{
	REQUIRE((lhs == rhs) == (expectedOrd == 0));
	REQUIRE((lhs != rhs) == (expectedOrd != 0));
	REQUIRE((lhs < rhs) == (expectedOrd < 0));
	REQUIRE((lhs > rhs) == (expectedOrd > 0));
	REQUIRE((lhs <= rhs) == (expectedOrd <= 0));
	REQUIRE((lhs >= rhs) == (expectedOrd >= 0));
}

TEST_CASE("Checking constructors and getters")
{
	CMyString empty;
	REQUIRE(strcmp(empty.GetStringData(), "") == 0);
	REQUIRE_THROWS(empty[size_t(-1)]);
	REQUIRE_THROWS(empty[0]);
	REQUIRE(empty.GetLength() == 0);

	CMyString cStr("Null-terminated string");
	REQUIRE(strcmp(cStr.GetStringData(), "Null-terminated string") == 0);
	REQUIRE_THROWS(cStr[size_t(-1)]);
	REQUIRE(cStr[0] == 'N');
	REQUIRE(cStr[21] == 'g');
	REQUIRE_THROWS(cStr[22]);
	REQUIRE(cStr.GetLength() == 22);

	CMyString stdStr(string("std::string"));
	REQUIRE(strcmp(stdStr.GetStringData(), "std::string") == 0);
	REQUIRE(stdStr.GetLength() == 11);

	constexpr static char MEM_BLK[] = "Memory\0block";
	CMyString memStr(MEM_BLK, sizeof MEM_BLK - 1);
	REQUIRE(strcmp(memStr.GetStringData(), "Memory") == 0);
	REQUIRE(strcmp(memStr.GetStringData() + 7, "block") == 0);
	REQUIRE_THROWS(memStr[12]);
	REQUIRE(memStr.GetLength() == 12);

	CMyString copied(cStr);
	REQUIRE(copied.GetStringData() != cStr.GetStringData());
	REQUIRE(copied == cStr);

	CMyString moved(std::move(stdStr));
	REQUIRE(moved.GetStringData() != stdStr.GetStringData());
	REQUIRE(stdStr.GetStringData() == empty.GetStringData());
	REQUIRE(moved == "std::string");

	REQUIRE(CMyString("").GetStringData() == empty.GetStringData());
	REQUIRE(CMyString(string()).GetStringData() == empty.GetStringData());
	REQUIRE(CMyString(nullptr, 0).GetStringData() == empty.GetStringData());
	REQUIRE(CMyString(empty).GetStringData() == empty.GetStringData());
	REQUIRE(CMyString(std::move(empty)).GetStringData() == empty.GetStringData());
	REQUIRE(empty.GetLength() == 0);
}

TEST_CASE("Checking assignment operators")
{
	CMyString copied;
	REQUIRE(copied.GetLength() == 0);

	CMyString original("Copied");
	copied = original;
	REQUIRE(copied.GetStringData() != original.GetStringData());
	REQUIRE(copied == "Copied");
	REQUIRE(original == "Copied");

	CMyString moved("Erased");
	REQUIRE(moved == "Erased");

	moved = std::move(original);
	REQUIRE(moved == "Copied");
	REQUIRE(original.GetLength() == 0);
	REQUIRE(copied == "Copied");
}

TEST_CASE("Checking whether strings can be concatenated")
{
	CMyString left("lhs part -");
	CMyString right("- rhs part");
	REQUIRE(left + right == "lhs part -- rhs part");

	const char *const leftData = left.GetStringData();
	left += "";
	left += string();
	REQUIRE(left.GetStringData() == leftData);
	REQUIRE((left + "").GetStringData() != leftData);
	REQUIRE(("" + left).GetStringData() != leftData);

	REQUIRE_THROWS(left[10]);
	REQUIRE(left.GetLength() == 10);
	left += CMyString("", 1);
	REQUIRE(left[10] == '\0');
	REQUIRE_THROWS(left[11]);
	REQUIRE(left.GetLength() == 11);

	left += right;
	REQUIRE(strcmp(left.GetStringData(), "lhs part -") == 0);
	REQUIRE(strcmp(left.GetStringData() + 11, "- rhs part") == 0);
	REQUIRE(left.GetLength() == 21);
}

TEST_CASE("Checking string ordering")
{
	CMyString first;
	CMyString second1("Very long string but definitely not the greatest");
	CMyString second2(second1);
	CMyString third("short std");
	CMyString forth("short str");
	CMyString last("short string");

	TestMyStringOrdering(first, second1, -1);
	TestMyStringOrdering(second2, first, 1);
	TestMyStringOrdering(second1, second2, 0);
	TestMyStringOrdering(second2, second1, 0);
	TestMyStringOrdering(third, second2, 1);
	TestMyStringOrdering(second1, third, -1);
	TestMyStringOrdering(third, forth, -1);
	TestMyStringOrdering(forth, third, 1);
	TestMyStringOrdering(third, last, -1);
	TestMyStringOrdering(last, forth, 1);
}

TEST_CASE("Checking whether strings can be modified")
{
	CMyString str("0aB\08", 5);

	for (size_t index = 0; index < str.GetLength(); ++index)
	{
		++str[index];
	}
	REQUIRE(strcmp(str.GetStringData(), "1bC\19") == 0);

	str.Clear();
	REQUIRE(str.GetLength() == 0);
	REQUIRE(str.GetStringData() == CMyString().GetStringData());
}

TEST_CASE("Extracting substrings")
{
	constexpr char TEST_STR[] = "First\0Second\0Last";
	CMyString str(TEST_STR, sizeof TEST_STR - 1);

	REQUIRE_THROWS(str.SubString(size_t(-1)));

	REQUIRE(str.SubString(0) == str);

	CMyString substr = str.SubString(6, 6);
	REQUIRE(substr.GetLength() == 6);
	REQUIRE(substr == "Second");

	substr = str.SubString(6, 12);
	REQUIRE(substr.GetLength() == 11);
	REQUIRE(strcmp(substr.GetStringData(), "Second") == 0);
	REQUIRE(strcmp(substr.GetStringData() + 7, "Last") == 0);

	substr = str.SubString(17);
	REQUIRE(substr.GetLength() == 0);
	REQUIRE(substr.GetStringData() == CMyString().GetStringData());

	REQUIRE_THROWS(str.SubString(18));
}

TEST_CASE("Checking string outputting")
{
	constexpr char TEST_STR[] = "Some\0text";

	std::ostringstream output;
	output << CMyString(TEST_STR, sizeof TEST_STR);
	REQUIRE(output.str().length() == sizeof TEST_STR);
	REQUIRE(memcmp(output.str().data(), TEST_STR, sizeof TEST_STR) == 0);
}
