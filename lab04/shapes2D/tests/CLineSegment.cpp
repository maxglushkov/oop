#include <catch2/catch.hpp>
#include "../shapes/CLineSegment.h"

TEST_CASE("Testing required CLineSegment functions")
{
	CLineSegment segment({8.9, -0.001}, {-200, 10}, 0xffff00);
	REQUIRE(!segment.GetArea());
	REQUIRE(segment.GetPerimeter() == Approx(sqrt(208.9 * 208.9 + 10.001 * 10.001)));
	REQUIRE(segment.ToString() == "line segment with the beginning at (8.9; -0.001), the end at (-200; 10), color #ffff00");
	REQUIRE(segment.GetOutlineColor() == 0xffff00);
	REQUIRE(segment.GetStartPoint().x == 8.9);
	REQUIRE(segment.GetStartPoint().y == -0.001);
	REQUIRE(segment.GetEndPoint().x == -200.0);
	REQUIRE(segment.GetEndPoint().y == 10.0);
}
