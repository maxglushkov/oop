#include <fstream>
#include <iostream>
#include "template.h"
using std::cerr;

void PrintUsage(const char *programName);

int main(int argc, const char *argv[])
{
	argc -= 3;
	if (argc < 0 || argc & 1)
	{
		PrintUsage(argv[0]);
		return 1;
	}

	const char *const inputFile = argv[1];
	std::ifstream input(inputFile);
	if (!input)
	{
		cerr << "Cannot open file \"" << inputFile << "\" for input.\n";
		return 1;
	}

	const char *const outputFile = argv[2];
	std::ofstream output(outputFile);
	if (!output)
	{
		cerr << "Cannot open file \"" << outputFile << "\" for output.\n";
		return 1;
	}

	std::map<std::string, std::string> params;
	for (argv += 3, argc /= 2; argc; --argc)
	{
		const char *const param = *argv++;
		const char *const value = *argv++;
		params.emplace(param, value);
	}

	if (!ExpandTemplateStream(input, output, params))
	{
		cerr << "IO error occurred or input file contains too long lines.\n";
		return 1;
	}
	return 0;
}

void PrintUsage(const char *programName)
{
	if (!programName)
	{
		programName = "expand-template";
	}
	cerr << "Usage: " << programName << " <input-file> <output-file> [<param> <value> [<param> <value> …]]\n";
}
