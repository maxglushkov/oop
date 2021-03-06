#include "mock-canvas.h"
#include "../shapes/CLineSegment.h"

TEST_CASE("Testing required CLineSegment functions")
{
	CLineSegment segment({8.9, -0.001}, {-200, 10}, 0xffff00);
	REQUIRE(segment.GetArea() == 0.0);
	REQUIRE(segment.GetPerimeter() == Approx(sqrt(208.9 * 208.9 + 10.001 * 10.001)));
	REQUIRE(segment.ToString() == "line segment with the beginning at (8.9; -0.001), the end at (-200; 10), area 0, perimeter 209.139, outline color #ffff00");
	REQUIRE(segment.GetOutlineColor() == 0xffff00);
	REQUIRE(segment.GetStartPoint().x == 8.9);
	REQUIRE(segment.GetStartPoint().y == -0.001);
	REQUIRE(segment.GetEndPoint().x == -200.0);
	REQUIRE(segment.GetEndPoint().y == 10.0);
}

TEST_CASE("Drawing CLineSegment")
{
	using namespace fakeit;
	Mock<ICanvas> mock;
	When(Method(mock, DrawLine)).AlwaysReturn();

	CLineSegment segment({8.9, -0.001}, {-200, 10}, 0xffff00);
	segment.Draw(mock.get());
	Verify(Method(mock, DrawLine).Using(
		segment.GetStartPoint(),
		segment.GetEndPoint(),
		segment.GetOutlineColor()
	)).Exactly(1);
}
