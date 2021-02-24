#include <fstream>
#include "replace.h"
using std::cerr;

/// \brief Печатает сообщение об использовании.
/// \param[in] programName Название, c которым программа была запущена.
/// 	Если значение аргумента равно `nullptr`, в качестве имени программы используется `"replace"`.
void PrintUsage(const char *programName);

int main(int argc, const char *argv[])
{
	if (argc != 5)
	{
		PrintUsage(argv[0]);
		return 1;
	}

	std::ifstream input(argv[1]);
	if (!input)
	{
		cerr << "Cannot open file \"" << argv[1] << "\" for input.\n";
		return 1;
	}

	std::ofstream output(argv[2]);
	if (!output)
	{
		cerr << "Cannot open file \"" << argv[2] << "\" for output.\n";
		return 1;
	}

	if (!TextStreamReplace(input, output, argv[3], argv[4]))
	{
		cerr << "Input file contains too long lines or IO error occurred.\n";
		return 1;
	}

	output.flush();
	return 0;
}

void PrintUsage(const char *programName)
{
	if (!programName) programName = "replace";
	std::cerr << "Usage: " << programName << " <input file> <output file> <search string> <replace string>\n";
}
