#include <catch2/catch.hpp>
#include "../shapes/CPoint.h"

TEST_CASE("Testing additional CPoint functions")
{
	CPoint first{2, -0.1};
	CPoint second{-2, 2.9};
	REQUIRE(first.Distance(second) == Approx(5));
	REQUIRE(second.Distance(first) == Approx(5));
	CPoint third{2, 0};
	REQUIRE(first.Distance(third) == Approx(0.1));
	REQUIRE(third.Distance(first) == Approx(0.1));
}
