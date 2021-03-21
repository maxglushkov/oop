#include <fstream>
#include "matrix-3x3.h"
using std::cerr, std::cout;

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

	const char *const matrixFile = argv[1];
	std::ifstream input(matrixFile);
	if (!input)
	{
		cerr << "Cannot open file \"" << matrixFile << "\" for input.\n";
		return 1;
	}

	Matrix3x3 originalMatrix;
	if (!ReadMatrix(input, originalMatrix))
	{
		cerr << "Cannot load matrix from \"" << matrixFile << "\": input-output or format error.\n";
		return 1;
	}

	Matrix3x3 invertedMatrix;
	if (!InvertMatrix(originalMatrix, invertedMatrix))
	{
		cerr << "Failed to invert matrix: singular matrix\n";
		return 1;
	}

	cout.setf(std::ios::fixed);
	cout.precision(3);
	WriteMatrix(cout, invertedMatrix);
	return 0;
}

void PrintUsage(const char *programName)
{
	if (!programName)
	{
		programName = "invert";
	}
	cerr << "Usage: " << programName << " <matrix file1>\n";
}
