#include <catch2/catch.hpp>
#include "../html.h"
using namespace std::literals;

TEST_CASE("Checking whether HTML entities are decoded")
{
	REQUIRE(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s"s) == "Cat <says> \"Meow\". M&M's");
}

TEST_CASE("Checking whether invalid HTML entities are left intact")
{
	REQUIRE(HtmlDecode("1 & 2 == 0; 1 &lt; 2 != 0; 2 & 2 == ..."s) == "1 & 2 == 0; 1 < 2 != 0; 2 & 2 == ...");
}

TEST_CASE("Checking whether nested entities are processed correctly")
{
	REQUIRE(HtmlDecode("&&amp;apos; &&lt;name&gt;;"s) == "&&apos; &<name>;");
}
