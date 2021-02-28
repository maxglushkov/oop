#include <fstream>
#include "matrix-3x3.h"
using std::cerr;

/// \brief Печатает сообщение об использовании.
/// \param[in] programName Название, c которым программа была запущена.
/// 	Если значение аргумента равно `nullptr`, в качестве имени программы используется `"invert"`.
void PrintUsage(const char *programName);

int main(int argc, const char *argv[])
{
	if (argc != 2)
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

	Matrix3x3 matrix;
	input >> matrix;
	std::cout << matrix.Invert();

	return 0;
}

void PrintUsage(const char *programName)
{
	if (!programName) programName = "invert";
	cerr << "Usage: " << programName << " <matrix file1>\n";
}