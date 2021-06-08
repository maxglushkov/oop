#include "shapes-array.h"
#include "shapes/CCircle.h"
#include "shapes/CLineSegment.h"
#include "shapes/CRectangle.h"
#include "shapes/CTriangle.h"
using std::invalid_argument, std::istream, std::make_unique, std::unique_ptr;

unique_ptr<CLineSegment> ReadSegment(istream & input);

unique_ptr<CTriangle> ReadTriangle(istream & input);

unique_ptr<CRectangle> ReadRectangle(istream & input);

unique_ptr<CCircle> ReadCircle(istream & input);

void ReadShapes(std::istream & input, std::vector<IShapePtr> & shapes)
{
	input >> std::hex;

	std::string shapeName;
	while (input >> shapeName)
	{
		IShapePtr shape;
		if (shapeName == "segment")
		{
			shape = ReadSegment(input);
		}
		else if (shapeName == "triangle")
		{
			shape = ReadTriangle(input);
		}
		else if (shapeName == "rectangle")
		{
			shape = ReadRectangle(input);
		}
		else if (shapeName == "circle")
		{
			shape = ReadCircle(input);
		}
		else
		{
			throw invalid_argument("unknown shape");
		}
		shapes.push_back(std::move(shape));
	}
}

unique_ptr<CLineSegment> ReadSegment(istream & input)
{
	CPoint start, end;
	uint32_t color;
	input >> start >> end >> color;
	if (!input)
	{
		throw invalid_argument("segment format: <start x> <start y> <end x> <end y> <color>");
	}
	return make_unique<CLineSegment>(start, end, color);
}

unique_ptr<CTriangle> ReadTriangle(istream & input)
{
	CPoint vertex1, vertex2, vertex3;
	uint32_t outlineColor, fillColor;
	input >> vertex1 >> vertex2 >> vertex3 >> outlineColor >> fillColor;
	if (!input)
	{
		throw invalid_argument("triangle format: <1 vertex x> <1 vertex y> <2 vertex x> <2 vertex y> <3 vertex x> <3 vertex y> <outline color> <fill color>");
	}
	return make_unique<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
}

unique_ptr<CRectangle> ReadRectangle(istream & input)
{
	CPoint topLeft;
	double width, height;
	uint32_t outlineColor, fillColor;
	input >> topLeft >> width >> height >> outlineColor >> fillColor;
	if (!input)
	{
		throw invalid_argument("rectangle format: <left> <top> <width> <height> <outline color> <fill color>");
	}
	return make_unique<CRectangle>(topLeft, width, height, outlineColor, fillColor);
}

unique_ptr<CCircle> ReadCircle(istream & input)
{
	CPoint center;
	double radius;
	uint32_t outlineColor, fillColor;
	input >> center >> radius >> outlineColor >> fillColor;
	if (!input)
	{
		throw invalid_argument("circle format: <center x> <center y> <radius> <outline color> <fill color>");
	}
	return make_unique<CCircle>(center, radius, outlineColor, fillColor);
}
