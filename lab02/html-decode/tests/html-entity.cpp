#include <catch2/catch.hpp>
#include "../html-entity.h"
using namespace std::literals;

bool TestHtmlEntityDecoding(std::string_view const& testEntity, size_t expectedSize, char expected)
{
	char got;
	if (DecodeHtmlEntity(testEntity, got) != expectedSize)
	{
		return false;
	}
	return got == expected;
}

TEST_CASE("Checking entity-character mapping")
{
	REQUIRE(TestHtmlEntityDecoding("&amp"sv, 4, '&'));
	REQUIRE(TestHtmlEntityDecoding("&apos"sv, 5, '\''));
	REQUIRE(TestHtmlEntityDecoding("&gt"sv, 3, '>'));
	REQUIRE(TestHtmlEntityDecoding("&lt"sv, 3, '<'));
	REQUIRE(TestHtmlEntityDecoding("&quot"sv, 5, '"'));
}

TEST_CASE("Checking entities that should be mapped")
{
	REQUIRE(TestHtmlEntityDecoding("&amp;TEXT"sv, 5, '&'));
	REQUIRE(TestHtmlEntityDecoding("&lt&gt"sv, 3, '<'));
	REQUIRE(TestHtmlEntityDecoding("&quote;"sv, 5, '"'));
}

TEST_CASE("Checking entities that should not be mapped")
{
	constexpr char CANARY = -128;
	char decoded = CANARY;
	REQUIRE(!DecodeHtmlEntity(""sv, decoded));
	REQUIRE(!DecodeHtmlEntity("a"sv, decoded));
	REQUIRE(!DecodeHtmlEntity("AMP"sv, decoded));
	REQUIRE(!DecodeHtmlEntity("apos;"sv, decoded));
	REQUIRE(!DecodeHtmlEntity("{quote}"sv, decoded));
	REQUIRE(decoded == CANARY);
}
