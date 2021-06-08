#include <catch2/catch.hpp>
#include "../shapes/CCircle.h"

TEST_CASE("Testing required CCircle functions")
{
	CCircle circle({-7.2, 4}, 5.75, 0x000000, 0xffffff);
	REQUIRE(circle.GetArea() == Approx(M_PI * 5.75 * 5.75));
	REQUIRE(circle.GetPerimeter() == Approx(2 * M_PI * 5.75));
	REQUIRE(circle.ToString() == "circle with the center at (-7.2; 4), radius 5.75, area 103.869, perimeter 36.1283, outline color #000000, fill color #ffffff");
	REQUIRE(circle.GetOutlineColor() == 0x000000);
	REQUIRE(circle.GetFillColor() == 0xffffff);
	REQUIRE(circle.GetCenter().x == -7.2);
	REQUIRE(circle.GetCenter().y == 4.0);
	REQUIRE(circle.GetRadius() == 5.75);
}
