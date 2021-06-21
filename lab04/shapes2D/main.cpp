#include <iostream>
#include "canvas/CCanvas.h"
#include "canvas/ICanvasDrawable.h"
#include "shapes-array.h"
using std::cerr, std::cout;

void PrintUsage(const char *programName);

int main(int argc, const char *argv[])
{
	if (argc > 1)
	{
		PrintUsage(argv[0]);
		return 1;
	}

	try
	{
		std::vector<IShapePtr> shapes;
		ReadShapes(std::cin, shapes);
		auto iter = FindShapeWithMaxArea(shapes);
		if (iter != shapes.end())
		{
			cout << "Shape with max area is " << (*iter)->ToString() << '\n';
		}
		iter = FindShapeWithMinPerimeter(shapes);
		if (iter != shapes.end())
		{
			cout << "Shape with min perimeter is " << (*iter)->ToString() << '\n';
		}

		CCanvas canvas;
		for (IShapePtr const& shape: shapes)
		{
			dynamic_cast<ICanvasDrawable const&>(*shape).Draw(canvas);
		}
		canvas.DisplayAndPause();
		return 0;
	}
	catch (std::exception const& e)
	{
		cerr << "Error: " << e.what() << '\n';
		return 1;
	}
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
