#include <catch2/catch.hpp>
#include <sstream>
#include "../shapes/CCircle.h"
#include "main.h"

TEST_CASE("Testing required CCircle functions")
{
	std::istringstream input("-7.2 4 5.75 0 ffffff");
	CCircle circle;
	circle.ReadFromStream(input);
	REQUIRE(circle.GetArea() == Approx(M_PI * 5.75 * 5.75));
	REQUIRE(circle.GetPerimeter() == Approx(2 * M_PI * 5.75));
	REQUIRE(circle.ToString() == "circle with the center at (-7.2; 4) and radius 5.75");
	REQUIRE(circle.GetOutlineColor() == 0x000000);
	REQUIRE(circle.GetFillColor() == 0xffffff);
	REQUIRE(circle.GetCenter().x == -7.2);
	REQUIRE(circle.GetCenter().y == 4.0);
	REQUIRE(circle.GetRadius() == 5.75);
}

TEST_CASE("Checking how malformed circle descriptions are processed")
{
	CCircle circle;
	std::istringstream input("\
		a -1.5 0.3 000 fff\n\
		10 -1.5 0.3 000 fff\n\
		-10 0.5 -5 255 128\n\
		-10 0.5 0 255 128\n\
	");

	REQUIRE_THROWS(circle.ReadFromStream(input));
	IgnoreInvalidShape(input);

	REQUIRE_NOTHROW(circle.ReadFromStream(input));
	REQUIRE(circle.GetCenter().x == 10.0);
	REQUIRE(circle.GetCenter().y == -1.5);
	REQUIRE(circle.GetRadius() == 0.3);
	REQUIRE(circle.GetOutlineColor() == 0x000000);
	REQUIRE(circle.GetFillColor() == 0x000fff);

	REQUIRE_THROWS(circle.ReadFromStream(input));
	IgnoreInvalidShape(input);

	REQUIRE_NOTHROW(circle.ReadFromStream(input));
	REQUIRE(circle.GetCenter().x == -10.0);
	REQUIRE(circle.GetCenter().y == 0.5);
	REQUIRE(circle.GetRadius() == 0.0);
	REQUIRE(circle.GetOutlineColor() == 0x000255);
	REQUIRE(circle.GetFillColor() == 0x000128);
}
