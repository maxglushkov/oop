#include "mock-canvas.h"
#include "../shapes/CRectangle.h"

TEST_CASE("Testing required CRectangle functions")
{
	CRectangle rectangle({-2.5, -0}, 5.75, 10, 0x0000ff, 0xff0000);
	REQUIRE(rectangle.GetArea() == Approx(5.75 * 10));
	REQUIRE(rectangle.GetPerimeter() == Approx(2 * (5.75 + 10)));
	REQUIRE(rectangle.ToString() == "rectangle with top left point at (-2.5; 0), width 5.75, height 10, area 57.5, perimeter 31.5, outline color #0000ff, fill color #ff0000");
	REQUIRE(rectangle.GetOutlineColor() == 0x0000ff);
	REQUIRE(rectangle.GetFillColor() == 0xff0000);
	REQUIRE(rectangle.GetLeftTop().x == -2.5);
	REQUIRE(rectangle.GetLeftTop().y == 0.0);
	REQUIRE(rectangle.GetRightBottom().x == 3.25);
	REQUIRE(rectangle.GetRightBottom().y == 10.0);
	REQUIRE(rectangle.GetWidth() == 5.75);
	REQUIRE(rectangle.GetHeight() == 10.0);
}

TEST_CASE("Drawing CRectangle")
{
	using namespace fakeit;
	Mock<ICanvas> mock;
	When(Method(mock, DrawLine)).AlwaysReturn();
	When(Method(mock, FillPolygon)).AlwaysReturn();

	CRectangle rectangle({-2.5, -0}, 5.75, 10, 0x0000ff, 0xff0000);
	rectangle.Draw(mock.get());
	Verify(Method(mock, FillPolygon) + 4 * Method(mock, DrawLine)).Exactly(1);
	Verify(Method(mock, FillPolygon).Matching(
		[&rectangle]([[maybe_unused]] std::vector<CPoint> const& points, uint32_t fillColor) -> bool
		{
			return fillColor == rectangle.GetFillColor();
		}
	)).AtLeastOnce();
	Verify(Method(mock, DrawLine).Matching(
		[&rectangle]([[maybe_unused]] CPoint const& from, [[maybe_unused]] CPoint const& to, uint32_t lineColor) -> bool
		{
			return lineColor == rectangle.GetOutlineColor();
		}
	)).Exactly(4);
}
