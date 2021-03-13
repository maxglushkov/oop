#include <catch2/catch.hpp>
#include "../html-entity.h"
using namespace std::literals;

TEST_CASE("Checking entity-character mapping")
{
	REQUIRE(DecodeHtmlEntity("amp"sv) == '&');
	REQUIRE(DecodeHtmlEntity("apos"sv) == '\'');
	REQUIRE(DecodeHtmlEntity("gt"sv) == '>');
	REQUIRE(DecodeHtmlEntity("lt"sv) == '<');
	REQUIRE(DecodeHtmlEntity("quot"sv) == '"');
}

TEST_CASE("Checking entities that should not be mapped")
{
	REQUIRE(!DecodeHtmlEntity("AMP"sv));
	REQUIRE(!DecodeHtmlEntity("&apos;"sv));
	REQUIRE(!DecodeHtmlEntity("quote"sv));
	REQUIRE(!DecodeHtmlEntity("{}"sv));
}
