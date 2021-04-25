#pragma once
#include <memory>
#include <vector>
#include "shapes/IShape.h"

typedef std::unique_ptr<IShape> IShapePtr;

void ReadShapes(std::istream & input, std::vector<IShapePtr> & shapes);

const IShape *FindShapeWithMaxArea(std::vector<IShapePtr> const& shapes);

const IShape *FindShapeWithMinPerimeter(std::vector<IShapePtr> const& shapes);
