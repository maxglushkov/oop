#include <catch2/catch.hpp>
#include "../shapes/CTriangle.h"

TEST_CASE("Testing required CTriangle functions")
{
	CTriangle triangle({-5.0, 0}, {5, 0.0}, {0, 5}, 0x0000, 0xffff);
	REQUIRE(triangle.GetArea() == Approx(25.0));
	REQUIRE(triangle.GetPerimeter() == Approx(10.0 + 2.0 * sqrt(50.0)));
	REQUIRE(triangle.ToString() == "triangle with vertices at (-5; 0), (5; 0), (0; 5), area 25, perimeter 24.1421, outline color #000000, fill color #00ffff");
	REQUIRE(triangle.GetOutlineColor() == 0x000000);
	REQUIRE(triangle.GetFillColor() == 0x00ffff);
	REQUIRE(triangle.GetVertex1().x == -5.0);
	REQUIRE(triangle.GetVertex1().y == 0.0);
	REQUIRE(triangle.GetVertex2().x == 5.0);
	REQUIRE(triangle.GetVertex2().y == 0.0);
	REQUIRE(triangle.GetVertex3().x == 0.0);
	REQUIRE(triangle.GetVertex3().y == 5.0);
}
