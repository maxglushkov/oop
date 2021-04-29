#include <catch2/catch.hpp>
#include <sstream>
#include "../shapes/CLineSegment.h"
#include "main.h"

TEST_CASE("Testing required CLineSegment functions")
{
	std::istringstream input("8.9 -0.001 -200 10 ffff00");
	CLineSegment segment;
	segment.ReadFromStream(input);
	REQUIRE(!segment.GetArea());
	REQUIRE(segment.GetPerimeter() == Approx(sqrt(208.9 * 208.9 + 10.001 * 10.001)));
	REQUIRE(segment.ToString() == "line segment with the beginning at (8.9; -0.001) and the end at (-200; 10)");
	REQUIRE(segment.GetOutlineColor() == 0xffff00);
	REQUIRE(segment.GetStartPoint().x == 8.9);
	REQUIRE(segment.GetStartPoint().y == -0.001);
	REQUIRE(segment.GetEndPoint().x == -200.0);
	REQUIRE(segment.GetEndPoint().y == 10.0);
}

TEST_CASE("Checking how malformed line segment descriptions are processed")
{
	CLineSegment segment;
	std::istringstream input("\
		-a 0.5 0 -8.0 10000\n\
		-10 0.5 0 -8.0 10000\n\
		.01i -0.0.0.3 -ff00\n\
		.0 -0.0.0.3 -ff00\n\
	");

	REQUIRE_THROWS(segment.ReadFromStream(input));
	IgnoreInvalidShape(input);

	REQUIRE_NOTHROW(segment.ReadFromStream(input));
	REQUIRE(segment.GetStartPoint().x == -10.0);
	REQUIRE(segment.GetStartPoint().y == 0.5);
	REQUIRE(segment.GetEndPoint().x == 0.0);
	REQUIRE(segment.GetEndPoint().y == -8.0);
	REQUIRE(segment.GetOutlineColor() == 0x010000);

	REQUIRE_THROWS(segment.ReadFromStream(input));
	IgnoreInvalidShape(input);

	REQUIRE_NOTHROW(segment.ReadFromStream(input));
	REQUIRE(segment.GetStartPoint().x == 0.0);
	REQUIRE(segment.GetStartPoint().y == 0.0);
	REQUIRE(segment.GetEndPoint().x == 0.0);
	REQUIRE(segment.GetEndPoint().y == 0.3);
	REQUIRE(segment.GetOutlineColor() == 0xffff0100);
}
