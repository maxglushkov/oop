#include <catch2/catch.hpp>
#include "../shapes/CRectangle.h"

TEST_CASE("Testing required CRectangle functions")
{
	CRectangle rectangle({-2.5, -0}, 5.75, 10, 0x0000ff, 0xff0000);
	REQUIRE(rectangle.GetArea() == Approx(5.75 * 10));
	REQUIRE(rectangle.GetPerimeter() == Approx(2 * (5.75 + 10)));
	REQUIRE(rectangle.ToString() == "rectangle with top left point at (-2.5; 0), width 5.75, height 10, outline color #0000ff, fill color #ff0000");
	REQUIRE(rectangle.GetOutlineColor() == 0x0000ff);
	REQUIRE(rectangle.GetFillColor() == 0xff0000);
	REQUIRE(rectangle.GetLeftTop().x == -2.5);
	REQUIRE(rectangle.GetLeftTop().y == 0.0);
	REQUIRE(rectangle.GetRightBottom().x == 3.25);
	REQUIRE(rectangle.GetRightBottom().y == 10.0);
	REQUIRE(rectangle.GetWidth() == 5.75);
	REQUIRE(rectangle.GetHeight() == 10.0);
}
