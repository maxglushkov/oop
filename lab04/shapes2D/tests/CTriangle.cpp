#include <catch2/catch.hpp>
#include <sstream>
#include "../shapes/CTriangle.h"
#include "main.h"

TEST_CASE("Testing required CTriangle functions")
{
	std::istringstream input("-5.0 0 5 0.0 0 5 0000 ffff");
	CTriangle triangle;
	triangle.ReadFromStream(input);
	REQUIRE(triangle.GetArea() == Approx(25.0));
	REQUIRE(triangle.GetPerimeter() == Approx(10.0 + 2.0 * sqrt(50.0)));
	REQUIRE(triangle.ToString() == "triangle with vertices at (-5; 0), (5; 0), (0; 5)");
	REQUIRE(triangle.GetOutlineColor() == 0x000000);
	REQUIRE(triangle.GetFillColor() == 0x00ffff);
	REQUIRE(triangle.GetVertex1().x == -5.0);
	REQUIRE(triangle.GetVertex1().y == 0.0);
	REQUIRE(triangle.GetVertex2().x == 5.0);
	REQUIRE(triangle.GetVertex2().y == 0.0);
	REQUIRE(triangle.GetVertex3().x == 0.0);
	REQUIRE(triangle.GetVertex3().y == 5.0);
}

TEST_CASE("Checking how malformed triangle descriptions are processed")
{
	CTriangle triangle;
	std::istringstream input("\
		-4. 6 8.9 1g 0. 0 abc def\n\
		-4. 6 8.9 1.0 0. 0 abc def\n\
		1e2 -. 4 .01 9.99 5 40 60\n\
		1e2 -.0 4 .01 9.99 5 40 60\n\
	");

	REQUIRE_THROWS(triangle.ReadFromStream(input));
	IgnoreInvalidShape(input);

	REQUIRE_NOTHROW(triangle.ReadFromStream(input));
	REQUIRE(triangle.GetVertex1().x == -4.0);
	REQUIRE(triangle.GetVertex1().y == 6.0);
	REQUIRE(triangle.GetVertex2().x == 8.9);
	REQUIRE(triangle.GetVertex2().y == 1.0);
	REQUIRE(triangle.GetVertex3().x == 0.0);
	REQUIRE(triangle.GetVertex3().y == 0.0);
	REQUIRE(triangle.GetOutlineColor() == 0x000abc);
	REQUIRE(triangle.GetFillColor() == 0x000def);

	REQUIRE_THROWS(triangle.ReadFromStream(input));
	IgnoreInvalidShape(input);

	REQUIRE_NOTHROW(triangle.ReadFromStream(input));
	REQUIRE(triangle.GetVertex1().x == 100.0);
	REQUIRE(triangle.GetVertex1().y == 0.0);
	REQUIRE(triangle.GetVertex2().x == 4.0);
	REQUIRE(triangle.GetVertex2().y == 0.01);
	REQUIRE(triangle.GetVertex3().x == 9.99);
	REQUIRE(triangle.GetVertex3().y == 5.0);
	REQUIRE(triangle.GetOutlineColor() == 0x000040);
	REQUIRE(triangle.GetFillColor() == 0x000060);
}
