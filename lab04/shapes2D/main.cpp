#include <iostream>
#include "shapes-array.h"
#include "shapes/ISolidShape.h"
using std::cerr, std::cout;

void PrintUsage(const char *programName);

void PrintShape(const IShape *shape);

int main(int argc, const char *argv[])
{
	if (argc > 1)
	{
		PrintUsage(argv[0]);
		return 1;
	}

	std::vector<IShapePtr> shapes;
	try
	{
		ReadShapes(std::cin, shapes);
	}
	catch (std::invalid_argument e)
	{
		cerr << "Error: " << e.what() << '\n';
		return 1;
	}

	cout << std::hex;
	if (auto maxAreaShape = FindShapeWithMaxArea(shapes))
	{
		cout << "Shape with max area is ";
		PrintShape(maxAreaShape);
	}
	if (auto minPerimeterShape = FindShapeWithMinPerimeter(shapes))
	{
		cout << "Shape with min perimeter is ";
		PrintShape(minPerimeterShape);
	}
	return 0;
}

void PrintUsage(const char *programName)
{
	if (!programName)
	{
		programName = "shapes2D";
	}
	cerr << "Usage: " << programName << '\n';
	cerr << "Reads shape descriptions from standard input.\n";
	cerr << "Prints information about the shapes with max area and min perimeter.\n";
}

void PrintShape(const IShape *shape)
{
	cout << shape->ToString();
	cout << "\n\tArea: " << shape->GetArea();
	cout << "\n\tPerimeter: " << shape->GetPerimeter();
	cout << "\n\tOutline color: " << shape->GetOutlineColor();
	if (auto solidShape = dynamic_cast<const ISolidShape *>(shape))
	{
		cout << "\n\tFill color: " << solidShape->GetFillColor();
	}
	cout << '\n';
}
