#include <catch2/catch.hpp>
#include <sstream>
#include "../shapes/CRectangle.h"
#include "main.h"

TEST_CASE("Testing required CRectangle functions")
{
	std::istringstream input("-2.5 -0 5.75 10 0000ff ff0000");
	CRectangle rectangle;
	rectangle.ReadFromStream(input);
	REQUIRE(rectangle.GetArea() == Approx(5.75 * 10));
	REQUIRE(rectangle.GetPerimeter() == Approx(2 * (5.75 + 10)));
	REQUIRE(rectangle.ToString() == "rectangle with top left point at (-2.5; -0), width 5.75, height 10");
	REQUIRE(rectangle.GetOutlineColor() == 0x0000ff);
	REQUIRE(rectangle.GetFillColor() == 0xff0000);
	REQUIRE(rectangle.GetLeftTop().x == -2.5);
	REQUIRE(rectangle.GetLeftTop().y == 0.0);
	REQUIRE(rectangle.GetRightBottom().x == 3.25);
	REQUIRE(rectangle.GetRightBottom().y == 10.0);
	REQUIRE(rectangle.GetWidth() == 5.75);
	REQUIRE(rectangle.GetHeight() == 10.0);
}

TEST_CASE("Checking how malformed rectangle descriptions are processed")
{
	CRectangle rectangle;
	std::istringstream input("\
		0 0 100 200 0.5 1.0\n\
		0 0 100 200 808080 ffffff\n\
		-50 -10 37.5 12.5 abcdef. 012345\n\
		-50 -10 37.5 12.5 abcdef 012345\n\
	");

	REQUIRE_THROWS(rectangle.ReadFromStream(input));
	IgnoreInvalidShape(input);

	REQUIRE_NOTHROW(rectangle.ReadFromStream(input));
	REQUIRE(rectangle.GetLeftTop().x == 0.0);
	REQUIRE(rectangle.GetLeftTop().y == 0.0);
	REQUIRE(rectangle.GetWidth() == 100.0);
	REQUIRE(rectangle.GetHeight() == 200.0);
	REQUIRE(rectangle.GetOutlineColor() == 0x808080);
	REQUIRE(rectangle.GetFillColor() == 0xffffff);

	REQUIRE_THROWS(rectangle.ReadFromStream(input));
	IgnoreInvalidShape(input);

	REQUIRE_NOTHROW(rectangle.ReadFromStream(input));
	REQUIRE(rectangle.GetLeftTop().x == -50.0);
	REQUIRE(rectangle.GetLeftTop().y == -10.0);
	REQUIRE(rectangle.GetWidth() == 37.5);
	REQUIRE(rectangle.GetHeight() == 12.5);
	REQUIRE(rectangle.GetOutlineColor() == 0xabcdef);
	REQUIRE(rectangle.GetFillColor() == 0x012345);
}
