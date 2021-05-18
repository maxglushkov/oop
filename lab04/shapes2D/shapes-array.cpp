#include "shapes-array.h"
#include "shapes/CCircle.h"
#include "shapes/CLineSegment.h"
#include "shapes/CRectangle.h"
#include "shapes/CTriangle.h"
using std::invalid_argument;

void ReadShapes(std::istream & input, std::vector<IShapePtr> & shapes)
{
	input >> std::hex;

	std::string shapeName;
	while (input >> shapeName)
	{
		IShape *shape;
		if (shapeName == "segment")
		{
			CPoint start, end;
			uint32_t color;
			input >> start >> end >> color;
			if (!input)
			{
				throw invalid_argument("segment format: <start x> <start y> <end x> <end y> <color>");
			}
			shape = new CLineSegment(start, end, color);
		}
		else if (shapeName == "triangle")
		{
			CPoint vertex1, vertex2, vertex3;
			uint32_t outlineColor, fillColor;
			input >> vertex1 >> vertex2 >> vertex3 >> outlineColor >> fillColor;
			if (!input)
			{
				throw invalid_argument("triangle format: <1 vertex x> <1 vertex y> <2 vertex x> <2 vertex y> <3 vertex x> <3 vertex y> <outline color> <fill color>");
			}
			shape = new CTriangle(vertex1, vertex2, vertex3, outlineColor, fillColor);
		}
		else if (shapeName == "rectangle")
		{
			CPoint topLeft;
			double width, height;
			uint32_t outlineColor, fillColor;
			input >> topLeft >> width >> height >> outlineColor >> fillColor;
			if (!input)
			{
				throw invalid_argument("rectangle format: <left> <top> <width> <height> <outline color> <fill color>");
			}
			shape = new CRectangle(topLeft, width, height, outlineColor, fillColor);
		}
		else if (shapeName == "circle")
		{
			CPoint center;
			double radius;
			uint32_t outlineColor, fillColor;
			input >> center >> radius >> outlineColor >> fillColor;
			if (!input)
			{
				throw invalid_argument("circle format: <center x> <center y> <radius> <outline color> <fill color>");
			}
			shape = new CCircle(center, radius, outlineColor, fillColor);
		}
		else
		{
			throw invalid_argument("unknown shape");
		}
		shapes.push_back(IShapePtr(shape));
	}
}
