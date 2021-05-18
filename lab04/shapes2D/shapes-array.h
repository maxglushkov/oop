#pragma once
#include <algorithm>
#include <memory>
#include "shapes/IShape.h"

typedef std::unique_ptr<IShape> IShapePtr;

void ReadShapes(std::istream & input, std::vector<IShapePtr> & shapes);

inline std::vector<IShapePtr>::const_iterator FindShapeWithMaxArea(std::vector<IShapePtr> const& shapes)
{
	return std::max_element(
		shapes.begin(), shapes.end(),
		[](IShapePtr const& lhs, IShapePtr const& rhs)
		{
			return lhs->GetArea() < rhs->GetArea();
		}
	);
}

inline std::vector<IShapePtr>::const_iterator FindShapeWithMinPerimeter(std::vector<IShapePtr> const& shapes)
{
	return std::min_element(
		shapes.begin(), shapes.end(),
		[](IShapePtr const& lhs, IShapePtr const& rhs)
		{
			return lhs->GetPerimeter() < rhs->GetPerimeter();
		}
	);
}
