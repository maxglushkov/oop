#include <catch2/catch.hpp>
#include <sstream>
#include "../shapes-array.h"
#include "../shapes/CCircle.h"
#include "../shapes/CLineSegment.h"
#include "../shapes/CRectangle.h"
#include "../shapes/CTriangle.h"

void TestReadingShapes(std::istream & input, std::vector<IShapePtr> & shapes, size_t expectedNewSize)
{
	REQUIRE_THROWS(ReadShapes(input, shapes));
	input.clear();
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	REQUIRE(shapes.size() == expectedNewSize);
}

TEST_CASE("Checking whether shapes can be read")
{
	std::istringstream input("\
		point 0 0\n\
		circle 10 -1.5 0.3 000 fff\n\
		circle a -1.5 0.3 000 fff\n\
		circle -10 0.5 0 255 128\n\
		circle -10 0.5 -5 255 128\n\
		segment -10 0.5 0 -8.0 10000\n\
		segment -a 0.5 0 -8.0 10000\n\
		segment .0 -0.0.0.3 -ff00\n\
		segment .01i -0.0.0.3 -ff00\n\
		rectangle 0 0 100 200 808080 ffffff\n\
		rectangle 0 0 100 200 0.5 1.0\n\
		rectangle -50 -10 37.5 12.5 abcdef 012345\n\
		rectangle -50 -10 37.5 12.5 abcdef. 012345\n\
		triangle -4. 6 8.9 1.0 0. 0 abc def\n\
		triangle -4. 6 8.9 1g 0. 0 abc def\n\
		triangle 1e2 -.0 4 .01 9.99 5 40 60\n\
		triangle 1e2 -. 4 .01 9.99 5 40 60\n\
	");
	std::vector<IShapePtr> shapes;
	TestReadingShapes(input, shapes, 0);

	CCircle *circle;
	TestReadingShapes(input, shapes, 1);
	REQUIRE((circle = dynamic_cast<CCircle *>(&*shapes.back())));
	REQUIRE(circle->GetCenter().x == 10.0);
	REQUIRE(circle->GetCenter().y == -1.5);
	REQUIRE(circle->GetRadius() == 0.3);
	REQUIRE(circle->GetOutlineColor() == 0x000000);
	REQUIRE(circle->GetFillColor() == 0x000fff);

	TestReadingShapes(input, shapes, 2);
	REQUIRE((circle = dynamic_cast<CCircle *>(&*shapes.back())));
	REQUIRE(circle->GetCenter().x == -10.0);
	REQUIRE(circle->GetCenter().y == 0.5);
	REQUIRE(circle->GetRadius() == 0.0);
	REQUIRE(circle->GetOutlineColor() == 0x000255);
	REQUIRE(circle->GetFillColor() == 0x000128);

	CLineSegment *segment;
	TestReadingShapes(input, shapes, 3);
	REQUIRE((segment = dynamic_cast<CLineSegment *>(&*shapes.back())));
	REQUIRE(segment->GetStartPoint().x == -10.0);
	REQUIRE(segment->GetStartPoint().y == 0.5);
	REQUIRE(segment->GetEndPoint().x == 0.0);
	REQUIRE(segment->GetEndPoint().y == -8.0);
	REQUIRE(segment->GetOutlineColor() == 0x010000);

	TestReadingShapes(input, shapes, 4);
	REQUIRE((segment = dynamic_cast<CLineSegment *>(&*shapes.back())));
	REQUIRE(segment->GetStartPoint().x == 0.0);
	REQUIRE(segment->GetStartPoint().y == 0.0);
	REQUIRE(segment->GetEndPoint().x == 0.0);
	REQUIRE(segment->GetEndPoint().y == 0.3);
	REQUIRE(segment->GetOutlineColor() == 0xffff0100);

	CRectangle *rectangle;
	TestReadingShapes(input, shapes, 5);
	REQUIRE((rectangle = dynamic_cast<CRectangle *>(&*shapes.back())));
	REQUIRE(rectangle->GetLeftTop().x == 0.0);
	REQUIRE(rectangle->GetLeftTop().y == 0.0);
	REQUIRE(rectangle->GetWidth() == 100.0);
	REQUIRE(rectangle->GetHeight() == 200.0);
	REQUIRE(rectangle->GetOutlineColor() == 0x808080);
	REQUIRE(rectangle->GetFillColor() == 0xffffff);

	TestReadingShapes(input, shapes, 6);
	REQUIRE((rectangle = dynamic_cast<CRectangle *>(&*shapes.back())));
	REQUIRE(rectangle->GetLeftTop().x == -50.0);
	REQUIRE(rectangle->GetLeftTop().y == -10.0);
	REQUIRE(rectangle->GetWidth() == 37.5);
	REQUIRE(rectangle->GetHeight() == 12.5);
	REQUIRE(rectangle->GetOutlineColor() == 0xabcdef);
	REQUIRE(rectangle->GetFillColor() == 0x012345);

	CTriangle *triangle;
	TestReadingShapes(input, shapes, 7);
	REQUIRE((triangle = dynamic_cast<CTriangle *>(&*shapes.back())));
	REQUIRE(triangle->GetVertex1().x == -4.0);
	REQUIRE(triangle->GetVertex1().y == 6.0);
	REQUIRE(triangle->GetVertex2().x == 8.9);
	REQUIRE(triangle->GetVertex2().y == 1.0);
	REQUIRE(triangle->GetVertex3().x == 0.0);
	REQUIRE(triangle->GetVertex3().y == 0.0);
	REQUIRE(triangle->GetOutlineColor() == 0x000abc);
	REQUIRE(triangle->GetFillColor() == 0x000def);

	TestReadingShapes(input, shapes, 8);
	REQUIRE((triangle = dynamic_cast<CTriangle *>(&*shapes.back())));
	REQUIRE(triangle->GetVertex1().x == 100.0);
	REQUIRE(triangle->GetVertex1().y == 0.0);
	REQUIRE(triangle->GetVertex2().x == 4.0);
	REQUIRE(triangle->GetVertex2().y == 0.01);
	REQUIRE(triangle->GetVertex3().x == 9.99);
	REQUIRE(triangle->GetVertex3().y == 5.0);
	REQUIRE(triangle->GetOutlineColor() == 0x000040);
	REQUIRE(triangle->GetFillColor() == 0x000060);
}
