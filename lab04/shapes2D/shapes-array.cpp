#include <cfloat>
#include <sstream>
#include "shapes-array.h"
#include "shapes/CCircle.h"
#include "shapes/CLineSegment.h"
#include "shapes/CRectangle.h"
#include "shapes/CTriangle.h"

void ReadShapes(std::istream & input, std::vector<IShapePtr> & shapes)
{
	std::string shapeName;
	while (input >> shapeName)
	{
		IShape *shape;
		if (shapeName == "segment")
		{
			shape = (new CLineSegment)->ReadFromStream(input);
		}
		else if (shapeName == "triangle")
		{
			shape = (new CTriangle)->ReadFromStream(input);
		}
		else if (shapeName == "rectangle")
		{
			shape = (new CRectangle)->ReadFromStream(input);
		}
		else if (shapeName == "circle")
		{
			shape = (new CCircle)->ReadFromStream(input);
		}
		else
		{
			throw std::invalid_argument("unknown shape");
		}
		shapes.push_back(IShapePtr(shape));
	}
}

const IShape *FindShapeWithMaxArea(std::vector<IShapePtr> const& shapes)
{
	const IShape *maxAreaShape = nullptr;
	double maxArea = 0.0;
	for (auto const& shape: shapes)
	{
		const double area = shape->GetArea();
		if (area >= maxArea)
		{
			maxArea = area;
			maxAreaShape = shape.get();
		}
	}
	return maxAreaShape;
}

const IShape *FindShapeWithMinPerimeter(std::vector<IShapePtr> const& shapes)
{
	const IShape *minPerimeterShape = nullptr;
	double minPerimeter = DBL_MAX;
	for (auto const& shape: shapes)
	{
		const double perimeter = shape->GetPerimeter();
		if (perimeter <= minPerimeter)
		{
			minPerimeter = perimeter;
			minPerimeterShape = shape.get();
		}
	}
	return minPerimeterShape;
}
