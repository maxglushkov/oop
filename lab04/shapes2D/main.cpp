#include <iostream>
#include "shapes-array.h"
#include "shapes/ISolidShape.h"
using std::cerr, std::cout;

void PrintUsage(const char *programName);

void PrintShape(IShape const& shape);

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
	catch (std::exception const& e)
	{
		cerr << "Error: " << e.what() << '\n';
		return 1;
	}

	cout << std::hex;
	auto iter = FindShapeWithMaxArea(shapes);
	if (iter != shapes.end())
	{
		cout << "Shape with max area is ";
		PrintShape(**iter);
	}
	iter = FindShapeWithMinPerimeter(shapes);
	if (iter != shapes.end())
	{
		cout << "Shape with min perimeter is ";
		PrintShape(**iter);
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

void PrintShape(IShape const& shape)
{
	cout << shape.ToString();
	cout << "\n\tArea: " << shape.GetArea();
	cout << "\n\tPerimeter: " << shape.GetPerimeter();
	cout << "\n\tOutline color: " << shape.GetOutlineColor();
	if (auto solidShape = dynamic_cast<const ISolidShape *>(&shape))
	{
		cout << "\n\tFill color: " << solidShape->GetFillColor();
	}
	cout << '\n';
}
